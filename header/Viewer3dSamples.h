
#ifndef VIEWER3DSAMPLES_H
#define VIEWER3DSAMPLES_H

#include "BaseSample.h"

#include <AIS_InteractiveContext.hxx>
#include <V3d_View.hxx>

//! Implements viewer 3D samples.
class Viewer3dSamples : public BaseSample
{
    DEFINE_STANDARD_RTTI_INLINE(Viewer3dSamples, BaseSample)
public:

    Viewer3dSamples(const TCollection_AsciiString& theSampleSourcePath,
        const Handle(V3d_View)& theView,
        const Handle(AIS_InteractiveContext)& theContext)
        : BaseSample(theSampleSourcePath, theContext),
        myView(theView)
    {}

    void AppendBottle();
    void ClearExtra();

protected:
    virtual void ExecuteSample(const TCollection_AsciiString& theSampleName) Standard_OVERRIDE;

private:

    // One function for every sample
    void SpotLight3dSample();
    void PositionalLight3dSample();
    void DirectionalLight3dSample();
    void AmbientLight3dSample();
    void ClearLight3dSample();
    void VerticesSelect3dSample();
    void EdgesSelect3dSample();
    void FacesSelect3dSample();
    void NeutralPointSelect3dSample();
    void WireFramePresentation3dSample();
    void ShadingPresentation3dSample();
    void RedColorPresentation3dSample();
    void GrayColorPresentation3dSample();
    void PlasticPresentation3dSample();
    void BronzePresentation3dSample();
    void OpaquePresentation3dSample();
    void HalfTransparencyPresentation3dSample();
    void VboOn3dSample();
    void VboOff3dSample();

private:

    Handle(V3d_View) myView;

};

#endif  //VIEWER3DSAMPLES_H
