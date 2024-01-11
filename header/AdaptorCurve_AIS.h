
#ifndef ADAPTOR_CURVE_AIS_H
#define ADAPTOR_CURVE_AIS_H

#include <AIS_InteractiveObject.hxx>
#include <Geom_Curve.hxx>

//! AIS interactive Object for Geom_Curve
class AdaptorCurve_AIS : public AIS_InteractiveObject
{
    DEFINE_STANDARD_RTTI_INLINE(AdaptorCurve_AIS, AIS_InteractiveObject)
public:
    AdaptorCurve_AIS(const Handle(Geom_Curve)& theCurve) : myCurve(theCurve) {}
private:

    //! Return TRUE for supported display modes (modes 0 and 1 are supported).
    virtual Standard_Boolean AcceptDisplayMode(const Standard_Integer theMode) const Standard_OVERRIDE { return theMode == 0 || theMode == 1; }

    //! Compute presentation.
    Standard_EXPORT virtual void Compute(const Handle(PrsMgr_PresentationManager)& thePrsMgr,
        const Handle(Prs3d_Presentation)& thePrs,
        const Standard_Integer theMode) Standard_OVERRIDE;

    //! Compute selection (not implemented).
    virtual void ComputeSelection(const Handle(SelectMgr_Selection)&,
        const Standard_Integer) Standard_OVERRIDE {}

private:
    Handle(Geom_Curve) myCurve;
};

#endif