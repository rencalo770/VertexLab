
#ifndef OCAFSAMPLES_H
#define OCAFSAMPLES_H

#include "BaseSample.h"
#include "TOcaf_Application.h"

#include <AIS_InteractiveContext.hxx>
#include <V3d_Viewer.hxx>
#include <TDocStd_Document.hxx>
#include <fstream>
#include <iostream>
#include <ctime>
using namespace std;


//! Implements OCAF samples
class OcafSamples : public BaseSample
{
    DEFINE_STANDARD_RTTI_INLINE(OcafSamples, BaseSample)
public:

    OcafSamples(const TCollection_AsciiString& theSampleSourcePath,
        const Handle(V3d_Viewer)& theViewer,
        const Handle(AIS_InteractiveContext)& theContext)
        : BaseSample(theSampleSourcePath, theContext),
        myViewer(theViewer)
    {
        //
    }

    virtual void Process(const TCollection_AsciiString& theSampleName) Standard_OVERRIDE;

    void ClearExtra();
    void SetFileName(const TCollection_AsciiString& theFileName) { myFileName = theFileName; };

    static Standard_Boolean IsExportSample(const TCollection_AsciiString& theSampleName);
    static Standard_Boolean IsImportSample(const TCollection_AsciiString& theSampleName);
    static Standard_Boolean IsBinarySample(const TCollection_AsciiString& theSampleName);
    static Standard_Boolean IsXmlSample(const TCollection_AsciiString& theSampleName);

    static void AppendFile(string content);


protected:
    virtual void ExecuteSample(const TCollection_AsciiString& theSampleName) Standard_OVERRIDE;

private:
    // One function for every sample
    void CreateOcafDocument();
    void CreateBoxOcafSample();
    void CreateCylinderOcafSample();
    void ModifyBoxOcafSample();
    void ModifyCylinderOcafSample();
    void UndoOcafSample();
    void RedoOcafSample();
    void DialogOpenOcafSample();
    void DialogSaveBinOcafSample();
    void DialogSaveXmlOcafSample();
    void DisplayPresentation();
    void DialogOcafStepImportSample();
    void DialogOcafStepExportSample();
    void DialogOcafVrmlImportSample();
    void DialogOcafVrmlExportSample();

private:

    TCollection_AsciiString  myFileName;
    Handle(V3d_Viewer)       myViewer;
    Handle(TDocStd_Document) myOcafDoc;
};

#endif  //OCAFSAMPLES_H
