
#include "../header/Sample2D_Markers.h"

#include <Aspect_TypeOfMarker.hxx>

// generic marker 通用标记
Sample2D_Markers::Sample2D_Markers(const Standard_Real theXPosition,
    const Standard_Real theYPosition,
    const Aspect_TypeOfMarker theMarkerType,
    const Quantity_Color theColor,
    const Standard_Real theScaleOrId)
    : myArrayOfPoints(new Graphic3d_ArrayOfPoints(1))
{
    myXPosition = theXPosition;
    myYPosition = theYPosition;
    myMarkerType = theMarkerType;
    myColor = theColor;
    myIndex = theScaleOrId;
}

Sample2D_Markers::Sample2D_Markers(const Standard_Real theXPosition,
    const Standard_Real theYPosition,
    const Handle(Graphic3d_ArrayOfPoints)& theArrayOfPoints,
    const Aspect_TypeOfMarker theMarkerType,
    const Quantity_Color theColor,
    const Standard_Real theScaleOrId)
    : myArrayOfPoints(new Graphic3d_ArrayOfPoints(6))
{
    myXPosition = theXPosition;
    myYPosition = theYPosition;
    myMarkerType = theMarkerType;
    myColor = theColor;
    myIndex = theScaleOrId;
    myArrayOfPoints = theArrayOfPoints;
}

void Sample2D_Markers::Compute(const Handle(PrsMgr_PresentationManager)&,
    const Handle(Prs3d_Presentation)& thePrs,
    const Standard_Integer theMode)
{
    if (theMode != 0)
    {
        return;
    }

    if (myMarkerType == Aspect_TOM_USERDEFINED)
    {
        Handle(Graphic3d_AspectMarker3d) aMarker = new Graphic3d_AspectMarker3d(Aspect_TOM_POINT, myColor, myIndex);
        thePrs->CurrentGroup()->SetGroupPrimitivesAspect(aMarker);
        thePrs->CurrentGroup()->AddPrimitiveArray(myArrayOfPoints);
    }
    else
    {
        Handle(Graphic3d_AspectMarker3d) aMarker = new Graphic3d_AspectMarker3d(myMarkerType, myColor, myIndex);
        thePrs->CurrentGroup()->SetPrimitivesAspect(aMarker);
        Handle(Graphic3d_ArrayOfPoints) anArrayOfPoints = new Graphic3d_ArrayOfPoints(1);
        anArrayOfPoints->AddVertex(myXPosition, myYPosition, 0);
        thePrs->CurrentGroup()->AddPrimitiveArray(anArrayOfPoints);
    }
}
