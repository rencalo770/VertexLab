
#ifndef _Sample2D_Image_HeaderFile
#define _Sample2D_Image_HeaderFile
#include <Standard_Macro.hxx>
#include <Standard_DefineHandle.hxx>

#include <OSD_File.hxx>
#include <Standard_Boolean.hxx>
#include <Standard_CString.hxx>
#include <Standard_Integer.hxx>
#include <SelectMgr_Selection.hxx>
#include <Standard_OStream.hxx>
#include <Standard_IStream.hxx>
#include <AIS_Shape.hxx>
#include <TopoDS_Face.hxx>

//! AIS shape for sample 2D image
class Sample2D_Image : public AIS_Shape
{
    DEFINE_STANDARD_RTTI_INLINE(Sample2D_Image, AIS_Shape)
public:

    //! Constructor.
    Standard_EXPORT Sample2D_Image(const TCollection_AsciiString& theFileName,
        const Standard_Real theX = 0.0,
        const Standard_Real theY = 0.0,
        const Standard_Real theScale = 1.0);

    //! Return image coordinates.
    void GetCoord(Standard_Real& theX, Standard_Real& theY) const
    {
        theX = myX;
        theY = myY;
    }

    //! Return image coordinates.
    void SetCoord(const Standard_Real theX, const Standard_Real theY)
    {
        myX = theX;
        myY = theY;
    }

    //! Return image scale factor.
    Standard_Real GetScale() const { return myScale; }

    //! Set image scale factor.
    void SetScale(const Standard_Real theNewScale) { myScale = theNewScale; }

    //! Assign new interactive context to the object.
    Standard_EXPORT virtual void SetContext(const Handle(AIS_InteractiveContext)& theContext) Standard_OVERRIDE;

private:

    void MakeShape();

protected:

    TopoDS_Face myFace;
    TCollection_AsciiString myFilename;
    Standard_Real myX;
    Standard_Real myY;
    Standard_Real myScale;

};

#endif
