
#ifndef ADAPTOR_PNT2D_AIS_H
#define ADAPTOR_PNT2D_AIS_H

#include <Geom2d_Point.hxx>
#include <AIS_InteractiveObject.hxx>

//! AIS interactive Object for Geom2d_Point
class AdaptorPnt2d_AIS : public AIS_InteractiveObject
{
    DEFINE_STANDARD_RTTI_INLINE(AdaptorPnt2d_AIS, AIS_InteractiveObject)
public:
    AdaptorPnt2d_AIS(const Handle(Geom2d_Point)& thePoint,
        Standard_Real theElevation = 0)
        : myPoint(thePoint->X(), thePoint->Y(), theElevation) {}

private:

    //! Return TRUE for supported display modes (only mode 0 is supported).
    virtual Standard_Boolean AcceptDisplayMode(const Standard_Integer theMode) const Standard_OVERRIDE { return theMode == 0; }

    //! Compute presentation.
    virtual void Compute(const Handle(PrsMgr_PresentationManager)& thePrsMgr,
        const Handle(Prs3d_Presentation)& thePrs,
        const Standard_Integer theMode) Standard_OVERRIDE;

    //! Compute selection (not implemented).
    virtual void ComputeSelection(const Handle(SelectMgr_Selection)&,
        const Standard_Integer) Standard_OVERRIDE {}

private:

    gp_Pnt myPoint;

};

#endif // ADAPTOR_PNT2D_AIS_H
