
#include "../header/AdaptorCurve_AIS.h"

#include <GeomAdaptor_Curve.hxx>
#include <Prs3d_LineAspect.hxx>
#include <StdPrs_PoleCurve.hxx>
#include <StdPrs_Curve.hxx>

void AdaptorCurve_AIS::Compute(const Handle(PrsMgr_PresentationManager)&,
    const Handle(Prs3d_Presentation)& thePrs,
    const Standard_Integer theMode)
{
    GeomAdaptor_Curve anAdaptorCurve(myCurve);
    switch (theMode)
    {
    case 1:
    {
        Handle(Prs3d_Drawer) aPoleDrawer = new Prs3d_Drawer();
        aPoleDrawer->SetLineAspect(new Prs3d_LineAspect(Quantity_NOC_RED, Aspect_TOL_SOLID, 1.0));
        StdPrs_PoleCurve::Add(thePrs, anAdaptorCurve, aPoleDrawer);
    }
    Standard_FALLTHROUGH
    case 0:
    {
        StdPrs_Curve::Add(thePrs, anAdaptorCurve, myDrawer);
        break;
    }
    }
}
