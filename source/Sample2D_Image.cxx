
#include "../header/Sample2D_Image.h"

#include <AIS_InteractiveContext.hxx>
#include <BRepBuilderAPI_MakeEdge.hxx>
#include <BRepBuilderAPI_MakeWire.hxx>
#include <BRepBuilderAPI_MakeFace.hxx>
#include <gp_Pnt.hxx>
#include <Graphic3d_Texture2D.hxx>
#include <Image_AlienPixMap.hxx>
#include <Prs3d_ShadingAspect.hxx>
#include <TopoDS_Edge.hxx>
#include <TopoDS_Wire.hxx>
#include <QDebug>

Sample2D_Image::Sample2D_Image(const TCollection_AsciiString& theFileName,
    const Standard_Real theX,
    const Standard_Real theY,
    const Standard_Real theScale)
    : AIS_Shape(TopoDS_Shape()),
    myFilename(theFileName),
    myX(theX),
    myY(theY),
    myScale(theScale)
{
    //
    MakeShape();
}

void Sample2D_Image::MakeShape()
{
    Standard_Real coeff = 1.0;
    Handle(Image_AlienPixMap) anImage = new Image_AlienPixMap();
    if (anImage->Load(myFilename))
    {
        coeff = Standard_Real(anImage->Height()) / Standard_Real(anImage->Width()) * myScale;
    }
    qDebug() << "IsNull222";
    TopoDS_Edge E1 = BRepBuilderAPI_MakeEdge(gp_Pnt(myX, myY, 0.),
        gp_Pnt(100 * myScale + myX, myY, 0.));
    TopoDS_Edge E2 = BRepBuilderAPI_MakeEdge(gp_Pnt(100 * myScale + myX, myY, 0.),
        gp_Pnt(100 * myScale + myX, 100 * coeff + myY, 0.));
    TopoDS_Edge E3 = BRepBuilderAPI_MakeEdge(gp_Pnt(100 * myScale + myX, 100 * coeff + myY, 0.),
        gp_Pnt(myX, 100 * coeff + myY, 0.));
    TopoDS_Edge E4 = BRepBuilderAPI_MakeEdge(gp_Pnt(myX, 100 * coeff + myY, 0.),
        gp_Pnt(myX, myY, 0.));
    TopoDS_Wire anImageBounds = BRepBuilderAPI_MakeWire(E1, E2, E3, E4);
    myFace = BRepBuilderAPI_MakeFace(gp_Pln(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1)), anImageBounds);
}

void Sample2D_Image::SetContext(const Handle(AIS_InteractiveContext)& theContext)
{
    if (theContext.IsNull() || theContext->CurrentViewer().IsNull())
    {
        qDebug() << "IsNull";
        AIS_InteractiveObject::SetContext(theContext);
        return;
    }

    AIS_InteractiveObject::SetContext(theContext);
    MakeShape();
    this->Set(TopoDS_Shape(myFace));

    myDrawer->SetShadingAspect(new Prs3d_ShadingAspect());
    Handle(Graphic3d_Texture2D) aTexture = new Graphic3d_Texture2D(myFilename);
    aTexture->DisableModulate();
    myDrawer->ShadingAspect()->Aspect()->SetTextureMap(aTexture);
    myDrawer->ShadingAspect()->Aspect()->SetTextureMapOn();
}
