
#ifndef ADAPTOR_CURVE2D_AIS_H
#define ADAPTOR_CURVE2D_AIS_H

#include <AIS_InteractiveObject.hxx>
#include <Geom2d_Curve.hxx>
#include <Aspect_TypeOfLine.hxx>
#include <Aspect_WidthOfLine.hxx>

//! AIS interactive Object for Geom2d_Curve
class AdaptorCurve2d_AIS : public AIS_InteractiveObject
{
    DEFINE_STANDARD_RTTI_INLINE(AdaptorCurve2d_AIS, AIS_InteractiveObject)
public:
    AdaptorCurve2d_AIS(const Handle(Geom2d_Curve)& theGeom2dCurve,
        const Aspect_TypeOfLine theTypeOfline = Aspect_TOL_SOLID,
        const Aspect_WidthOfLine theWidthOfLine = Aspect_WOL_MEDIUM);

    Standard_Integer   NbPossibleSelection() const { return 1; }
    Aspect_TypeOfLine  GetTypeOfLine()       const { return myTypeOfLine; }
    void               SetTypeOfLine(const Aspect_TypeOfLine aNewTypeOfLine) { myTypeOfLine = aNewTypeOfLine; }
    Aspect_WidthOfLine GetWidthOfLine()      const { return myWidthOfLine; }
    void               SetWidthOfLine(const Aspect_WidthOfLine aNewWidthOfLine) { myWidthOfLine = aNewWidthOfLine; }
    Standard_Boolean   GetDisplayPole()      const { return myDisplayPole; }
    void               SetDisplayPole(const Standard_Boolean aNewDisplayPole) { myDisplayPole = aNewDisplayPole; }
    Standard_Boolean   GetDisplayCurbure()   const { return myDisplayCurbure; }
    void               SetDisplayCurbure(const Standard_Boolean aNewDisplayCurbure) { myDisplayCurbure = aNewDisplayCurbure; }
    Standard_Real      GetDiscretisation()   const { return myDiscretisation; }
    void               SetDiscretisation(const Standard_Real aNewDiscretisation) { myDiscretisation = aNewDiscretisation; }

private:
    //! Return TRUE for supported display modes (only 0 mode is supported).
    virtual Standard_Boolean AcceptDisplayMode(const Standard_Integer theMode) const Standard_OVERRIDE { return theMode == 0; }

    //! Compute presentation.
    virtual void Compute(const Handle(PrsMgr_PresentationManager)& thePrsMgr,
        const Handle(Prs3d_Presentation)& thePrs,
        const Standard_Integer theMode) Standard_OVERRIDE;

    //! Compute selection (not implemented).
    virtual void ComputeSelection(const Handle(SelectMgr_Selection)&,
        const Standard_Integer) Standard_OVERRIDE {}

private:

    Handle(Geom2d_Curve) myGeom2dCurve;
    Aspect_TypeOfLine   myTypeOfLine;
    Aspect_WidthOfLine  myWidthOfLine;
    Standard_Boolean    myDisplayPole;
    Standard_Boolean    myDisplayCurbure;
    Standard_Real       myDiscretisation;
    Standard_Real       myradiusmax;
    Standard_Real       myradiusratio;

};

#endif
