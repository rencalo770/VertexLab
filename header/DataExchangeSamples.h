
#ifndef DATAEXCHANGESAMPLES_H
#define DATAEXCHANGESAMPLES_H

#include "BaseSample.h"

#include <STEPControl_StepModelType.hxx>
#include <V3d_View.hxx>
#include <QDebug>
#include <RWObj_ConfigurationNode.hxx>
#include <Vrml_ConfigurationNode.hxx>
#include <DE_Provider.hxx>

//! Implements Data Exchange samples
class DataExchangeSamples : public BaseSample
{
    DEFINE_STANDARD_RTTI_INLINE(DataExchangeSamples, BaseSample)
public:

    DataExchangeSamples(const TCollection_AsciiString& theSampleSourcePath,
        const Handle(V3d_View)& theView,
        const Handle(AIS_InteractiveContext)& theContext)
        : BaseSample(theSampleSourcePath, theContext),
        myStepType(STEPControl_AsIs),
        myView(theView)
    {
        //
    }

    virtual void Process(const TCollection_AsciiString& theSampleName) Standard_OVERRIDE;

    void AppendBottle();
    void SetFileName(TCollection_AsciiString theFileName) { myFileName = theFileName; };
    void SetStepType(STEPControl_StepModelType theStepType) { 
        qDebug() << "-----theStepType------------";
        qDebug() << theStepType;
        qDebug() << "-----theStepType------------";
        myStepType = theStepType; 
    };

    static Standard_Boolean IsExportSample(const TCollection_AsciiString& theSampleName) {
        return theSampleName == "BrepExportSample"
            || theSampleName == "StepExportSample"
            || theSampleName == "IgesExportSample"
            || theSampleName == "StlExportSample"
            || theSampleName == "VrmlExportSample"
            || theSampleName == "ImageExportSample";
    }
    static Standard_Boolean IsImportSample(const TCollection_AsciiString& theSampleName) {
        return theSampleName == "BrepImportSample"
            || theSampleName == "StepImportSample"
            || theSampleName == "IgesImportSample";
    }
    static Standard_Boolean IsBrepSample(const TCollection_AsciiString& theSampleName) { return theSampleName == "BrepExportSample" || theSampleName == "BrepImportSample"; }
    static Standard_Boolean IsStepSample(const TCollection_AsciiString& theSampleName) { return theSampleName == "StepExportSample" || theSampleName == "StepImportSample"; }
    static Standard_Boolean IsIgesSample(const TCollection_AsciiString& theSampleName) { return theSampleName == "IgesExportSample" || theSampleName == "IgesImportSample"; }
    static Standard_Boolean IsStlSample(const TCollection_AsciiString& theSampleName) { return theSampleName == "StlExportSample"; }
    static Standard_Boolean IsVrmlSample(const TCollection_AsciiString& theSampleName) { return theSampleName == "VrmlExportSample"; }
    static Standard_Boolean IsImageSample(const TCollection_AsciiString& theSampleName) { return theSampleName == "ImageExportSample"; }

protected:
    virtual void ExecuteSample(const TCollection_AsciiString& theSampleName) Standard_OVERRIDE;

private:
    TCollection_AsciiString   myFileName;
    STEPControl_StepModelType myStepType;
    
    RWObj_ConfigurationNode objConfig;
    Handle(DE_Provider) objDeProvider = objConfig.BuildProvider();


    Vrml_ConfigurationNode vrmlConfig;
    Handle(DE_Provider) vrmlDeProvider = vrmlConfig.BuildProvider();

    Handle(V3d_View)          myView;


private:
    Standard_Boolean CheckFacetedBrep();
    // One function for every sample
    void BrepExportSample();
    void StepExportSample();
    void IgesExportSample();
    void StlExportSample();
    void ObjExportSample();// 新增
    void VrmlExportSample();
    void ImageExportSample();

    void BrepImportSample();
    void StepImportSample();
    void IgesImportSample();
    void StlImportSample();// 新增
    void ObjImportSample();// 新增
    void VrmlImportSample();// 新增
};

#endif  //DATAEXCHANGESAMPLES_H
