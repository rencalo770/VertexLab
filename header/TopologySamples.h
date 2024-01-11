
#ifndef TOPOLOGYSAMPLES_H
#define TOPOLOGYSAMPLES_H

#include "BaseSample.h"

#include <AIS_InteractiveContext.hxx>

//! Implements Topology samples
class TopologySamples : public BaseSample
{
    DEFINE_STANDARD_RTTI_INLINE(TopologySamples, BaseSample)
public:

    TopologySamples(const TCollection_AsciiString& theSampleSourcePath,
        const Handle(AIS_InteractiveContext)& theContext)
        : BaseSample(theSampleSourcePath, theContext)
    {}

protected:
    virtual void ExecuteSample(const TCollection_AsciiString& theSampleName) Standard_OVERRIDE;

private:
    // One function for every sample
    void Vertex3dSample();
    void Edge3dSample();
    void Face3dSample();
    void Wire3dSample();
    void Shell3dSample();
    void Solid3dSample();
    void Edge2dSample();
    void Box3dSample();
    void Cylinder3dSample();
    void Revolution3dSample();
    void TopologyIterator3dSample();
    void TopologyExplorer3dSample();
    void AssessToCurve3dSample();
    void AssessToCompositeCurve3dSample();
    void AssessToSurface3dSample();
    void Common3dSample();
    void Cut3dSample();
    void Fuse3dSample();
    void Section3dSample();
    void Splitter3dSample();
    void Defeaturing3dSample();
    void Fillet3dSample();
    void Chamfer3dSample();
    void Offset3dSample();
    void Evolved3dSample();
    void Copy3dSample();
    void Transform3dSample();
    void ConvertToNurbs3dSample();
    void SewContiguousFaces3dSample();
    void CheckValidity3dSample();
    void ComputeLinearProperties3dSample();
    void ComputeSurfaceProperties3dSample();
    void ComputeVolumeProperties3dSample();
};

#endif  //TOPOLOGYSAMPLES_H
