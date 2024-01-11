
#ifndef VIEWER2DSAMPLES_H
#define VIEWER2DSAMPLES_H

#include "BaseSample.h"

#include <AIS_InteractiveContext.hxx>
#include <V3d_View.hxx>

//! Implements viewer 2D samples.
class Viewer2dSamples : public BaseSample
{
    DEFINE_STANDARD_RTTI_INLINE(Viewer2dSamples, BaseSample)
public:

    Viewer2dSamples(const TCollection_AsciiString& theSampleSourcePath,
        const Handle(V3d_View)& theView,
        const Handle(V3d_Viewer)& theViewer,
        const Handle(AIS_InteractiveContext)& theContext)
        : BaseSample(theSampleSourcePath, theContext),
        myView(theView),
        myViewer(theViewer)
    {}

    void SetFileName(const TCollection_AsciiString& theFileName) { myFileName = theFileName; }
    void ClearExtra();

    static Standard_Boolean IsFileSample(const TCollection_AsciiString& theSampleName) { return theSampleName == "BackgroungImage2dSample"; }
    static Standard_Boolean IsShadedSample(const TCollection_AsciiString& theSampleName) { return theSampleName == "BackgroungImage2dSample"; }

protected:
    virtual void ExecuteSample(const TCollection_AsciiString& theSampleName) Standard_OVERRIDE;

private:

    // One function for every sample
    void TextView2dSample();
    void MarkerView2dSample();
    void FillAreaView2dSample();
    void LoopOnFaceView2dSample();
    void RectagularLineGrid2dSample();
    void RectagularPointGrid2dSample();
    void CircularLineGrid2dSample();
    void CircularPointGrid2dSample();
    void ClearGrid2dSample();
    void BackgroundImage2dSample();

private:

    TCollection_AsciiString myFileName;
    Handle(V3d_View)        myView;
    Handle(V3d_Viewer)      myViewer;

};

#endif // VIEWER2DSAMPLES_H
