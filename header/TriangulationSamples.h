
#ifndef TRIANGULATIONSAMPLES_H
#define TRIANGULATIONSAMPLES_H

#include "BaseSample.h"

//! Implements Triangulation sample
class TriangulationSamples : public BaseSample
{
    DEFINE_STANDARD_RTTI_INLINE(TriangulationSamples, BaseSample)
public:

    TriangulationSamples(const TCollection_AsciiString& theSampleSourcePath,
        const Handle(AIS_InteractiveContext)& theContext)
        : BaseSample(theSampleSourcePath, theContext)
    {
        //
    }

protected:
    virtual void ExecuteSample(const TCollection_AsciiString& theSampleName) Standard_OVERRIDE;

private:
    // One function for every sample
    void Triangulation3dSample();

};

#endif  //TRIANGULATIONSAMPLES_H
