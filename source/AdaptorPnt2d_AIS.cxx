
#include "../header/AdaptorPnt2d_AIS.h"

#include <Geom_CartesianPoint.hxx>
#include <StdPrs_Point.hxx>

void AdaptorPnt2d_AIS::Compute(const Handle(PrsMgr_PresentationManager)&,
    const Handle(Prs3d_Presentation)& thePrs,
    const Standard_Integer theMode)
{
    if (theMode != 0)
    {
        return;
    }

    Handle(Geom_CartesianPoint) aGeomPoint = new Geom_CartesianPoint(myPoint);
    StdPrs_Point::Add(thePrs, aGeomPoint, myDrawer);
}
