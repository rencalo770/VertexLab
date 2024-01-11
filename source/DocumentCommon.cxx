
#include "../header/DocumentCommon.h"

#include "../header/ApplicationCommonWindow.h"
#include "../header/DialogTransparency.h"

#include <Standard_WarningsDisable.hxx>
#include <QApplication>
#include <QColor>
#include <QColorDialog>
#include <QStatusBar>
#include <Standard_WarningsRestore.hxx>

#include <AIS_InteractiveObject.hxx>
#include <Aspect_DisplayConnection.hxx>
#include <Graphic3d_NameOfMaterial.hxx>
#include <OpenGl_GraphicDriver.hxx>
#include <OSD_Environment.hxx>

#include <TCollection_AsciiString.hxx>

// =======================================================================
// scope    : private
// function : Viewer
// purpose  :
// =======================================================================
Handle(V3d_Viewer) DocumentCommon::Viewer(const Standard_ExtString,
    const Standard_CString,
    const Standard_Real theViewSize,
    const V3d_TypeOfOrientation theViewProj,
    const Standard_Boolean theComputedMode,
    const Standard_Boolean theDefaultComputedMode)
{
    static Handle(OpenGl_GraphicDriver) aGraphicDriver; //openglÍ¼ÐÎÇý¶¯
    if (aGraphicDriver.IsNull())
    {
        Handle(Aspect_DisplayConnection) aDisplayConnection;
#if !defined(_WIN32) && !defined(__WIN32__) && (!defined(__APPLE__) || defined(MACOSX_USE_GLX))
        aDisplayConnection = new Aspect_DisplayConnection(OSD_Environment("DISPLAY").Value());
#endif
        aGraphicDriver = new OpenGl_GraphicDriver(aDisplayConnection);
    }

    Handle(V3d_Viewer) aViewer = new V3d_Viewer(aGraphicDriver);
    aViewer->SetDefaultViewSize(theViewSize);
    aViewer->SetDefaultViewProj(theViewProj);
    aViewer->SetComputedMode(theComputedMode);
    aViewer->SetDefaultComputedMode(theDefaultComputedMode);
    return aViewer;
}

DocumentCommon::DocumentCommon(ApplicationCommonWindow* theApp)
    : QObject(theApp),
    myContextIsEmpty(true)
{
    TCollection_ExtendedString a3DName("Visu3D");

    myViewer = this->Viewer(a3DName.ToExtString(), "", 1000.0, V3d_XposYnegZpos, Standard_True, Standard_True);

    myViewer->SetDefaultLights();
    myViewer->SetLightOn();

    myContext = new AIS_InteractiveContext(myViewer);
}

void DocumentCommon::SetObjects(const NCollection_Vector<Handle(AIS_InteractiveObject)>& theObjects,
    Standard_Boolean theDisplayShaded)
{
    myContext->RemoveAll(Standard_False);
    myContextIsEmpty = theObjects.IsEmpty();

    for (NCollection_Vector<Handle(AIS_InteractiveObject)>::Iterator anIter(theObjects);
        anIter.More(); anIter.Next())
    {
        const Handle(AIS_InteractiveObject)& anObject = anIter.Value();
        if (!theDisplayShaded)
        {
            myContext->Display(anObject, Standard_False);
        }
        else
        {
            myContext->Display(anObject, AIS_Shaded, 0, Standard_False);
        }
    }
    myViewer->Redraw();
}

void DocumentCommon::Clear()
{
    myContext->RemoveAll(Standard_True);
    myContextIsEmpty = true;
}
