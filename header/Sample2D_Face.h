
#ifndef _Sample2D_Face_HeaderFile
#define _Sample2D_Face_HeaderFile

#include <AIS_InteractiveObject.hxx>
#include <Geom2d_TrimmedCurve.hxx>
#include <Graphic3d_ArrayOfPolylines.hxx>
#include <Graphic3d_AspectLine3d.hxx>
#include <TopoDS_Face.hxx>
#include <TColGeom_SequenceOfCurve.hxx>

//! AIS interactive Object for sample 2D face
class Sample2D_Face : public AIS_InteractiveObject
{
    DEFINE_STANDARD_RTTI_INLINE(Sample2D_Face, AIS_InteractiveObject)
public:

    Standard_EXPORT Sample2D_Face(const TopoDS_Shape& theFace);

public:

    TopoDS_Shape& Shape() { return myshape; }
    void SetFace(const TopoDS_Shape& theFace) { myshape = theFace; }

public:

    Quantity_Color myFORWARDColor;
    Quantity_Color myREVERSEDColor;
    Quantity_Color myINTERNALColor;
    Quantity_Color myEXTERNALColor;
    Standard_Integer myWidthIndex;
    Standard_Integer myTypeIndex;

private:

    //! Return TRUE for supported display modes (only mode 0 is supported).
    virtual Standard_Boolean AcceptDisplayMode(const Standard_Integer theMode) const Standard_OVERRIDE { return theMode == 0; }

    //! Compute presentation.
    virtual void Compute(const Handle(PrsMgr_PresentationManager)& thePrsMgr,
        const Handle(Prs3d_Presentation)& thePrs,
        const Standard_Integer theMode) Standard_OVERRIDE;

    //! Compute selection.
    virtual void ComputeSelection(const Handle(SelectMgr_Selection)& theSelection,
        const Standard_Integer theMode) Standard_OVERRIDE;

    virtual void ClearSelected() Standard_OVERRIDE;

    //! Method for advanced customizable selection of picked object
    virtual void HilightSelected(const Handle(PrsMgr_PresentationManager)& thePrsMgr,
        const SelectMgr_SequenceOfOwner& theOwners) Standard_OVERRIDE;

    //! Method for advanced customizable highlighting of picked object.
    virtual void HilightOwnerWithColor(const Handle(PrsMgr_PresentationManager)& thePM,
        const Handle(Prs3d_Drawer)& theStyle,
        const Handle(SelectMgr_EntityOwner)& theOwner) Standard_OVERRIDE;

    void DrawMarker(const Handle(Geom2d_TrimmedCurve)& theCurve,
        const Handle(Prs3d_Presentation)& thePresentation);

    void FillData(Standard_Boolean isSizesRecomputed = Standard_False);

private:

    TopoDS_Shape myshape;
    TColGeom_SequenceOfCurve mySeq_FORWARD;
    TColGeom_SequenceOfCurve mySeq_REVERSED;
    TColGeom_SequenceOfCurve mySeq_INTERNAL;
    TColGeom_SequenceOfCurve mySeq_EXTERNAL;

    Handle(Graphic3d_ArrayOfPolylines) myForwardArray;
    Handle(Graphic3d_ArrayOfPolylines) myReversedArray;
    Handle(Graphic3d_ArrayOfPolylines) myInternalArray;
    Handle(Graphic3d_ArrayOfPolylines) myExternalArray;

    Standard_Integer myForwardNum;
    Standard_Integer myReversedNum;
    Standard_Integer myInternalNum;
    Standard_Integer myExternalNum;
    Standard_Integer myForwardBounds;
    Standard_Integer myReversedBounds;
    Standard_Integer myInternalBounds;
    Standard_Integer myExternalBounds;

};

#endif
