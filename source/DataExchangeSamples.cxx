
#include "../header/DataExchangeSamples.h"

//#include "MakeBottle.h"
#include "../3d/MyBottleTool.h"
#include "../3d/MySurfaceTool.h"

#include <AIS_ViewCube.hxx>
#include <AIS_Shape.hxx>
#include <BRepTools.hxx>
#include <BRep_Tool.hxx>
#include <BRep_Builder.hxx>
#include <Geom_Surface.hxx>
#include <Geom_Plane.hxx>
#include <Geom_Line.hxx>
#include <Graphic3d_TextureEnv.hxx>
#include <IFSelect_ReturnStatus.hxx>
#include <IGESControl_Controller.hxx>
#include <IGESControl_Reader.hxx>
#include <IGESControl_Writer.hxx>
#include <Interface_Static.hxx>
#include <STEPControl_Reader.hxx>
#include <STEPControl_Writer.hxx>
#include <StlAPI_Writer.hxx>
#include <StlAPI_Reader.hxx>
#include <TopExp_Explorer.hxx>
#include <TopoDS.hxx>
#include <TopoDS_Shape.hxx>
#include <TopoDS_Compound.hxx>
#include <TopTools_HSequenceOfShape.hxx>
#include <VrmlAPI_Writer.hxx>
#include <RWObj_Provider.hxx>

void DataExchangeSamples::Process(const TCollection_AsciiString& theSampleName)
{
    if (IsImportSample(theSampleName))
    {
        myObject3d.Clear();
    }
    myObject2d.Clear();
    myCode.Clear();
    myIsProcessed = Standard_False;
    try
    {
        ExecuteSample(theSampleName);
    }
    catch (...)
    {
        TraceError(TCollection_AsciiString("Error in sample: ") + theSampleName);
    }
}

void DataExchangeSamples::AppendBottle()
{
    MyBottleTool* bt = new MyBottleTool();
    TopoDS_Shape aBottle = bt->make(50, 70, 30);

    //MySurfaceTool mySurfaceTool;
    //TopoDS_Shape aBottle =  mySurfaceTool.MakeSurfaceWithConstrains();


    Handle(AIS_InteractiveObject) aShape = new AIS_Shape(aBottle);
    //AIS_InteractiveObject *aisObj = aShape.get();
    //Quantity_Color color = Quantity_Color();
    //color.SetValues(Quantity_NOC_RED);
    //aisObj->SetColor(color);

    myObject3d.Append(aShape);
    Handle(AIS_ViewCube) aViewCube = new AIS_ViewCube();
    myObject3d.Append(aViewCube);
    myResult << "A bottle shape was created." << std::endl;
}

void DataExchangeSamples::ExecuteSample(const TCollection_AsciiString& theSampleName)
{
    Standard_Boolean anIsSamplePresent = Standard_True;
    FindSourceCode(theSampleName);
    if (theSampleName == "BrepExportSample")
    {
        BrepExportSample();
    }
    else if (theSampleName == "StepExportSample")
    {
        StepExportSample();
    }
    else if (theSampleName == "IgesExportSample")
    {
        IgesExportSample();
    }
    else if (theSampleName == "StlExportSample")
    {
        StlExportSample();
    }
    else if (theSampleName == "VrmlExportSample")
    {
        VrmlExportSample();
    }
    else if (theSampleName == "ImageExportSample")
    {
        ImageExportSample();
    }
    else if (theSampleName == "BrepImportSample")
    {
        BrepImportSample();
    }
    else if (theSampleName == "StepImportSample")
    {
        StepImportSample();
    }
    else if (theSampleName == "IgesImportSample")
    {
        IgesImportSample();
    }
    else if (theSampleName == "StlImportSample") {
        StlImportSample();
    }
    else if (theSampleName == "ObjExportSample") {
        ObjExportSample();
    }
    else if (theSampleName == "ObjImportSample") {
        ObjImportSample();
    }
    else if (theSampleName == "VrmlImportSample") {
        VrmlImportSample();
    }
    else
    {
        myResult << "No function found: " << theSampleName;
        myCode += TCollection_AsciiString("No function found: ") + theSampleName;
        anIsSamplePresent = Standard_False;
    }
    myIsProcessed = anIsSamplePresent;
}

void DataExchangeSamples::BrepExportSample()
{
    Standard_Boolean anIsShapeExist = Standard_False;
    for (NCollection_Vector<Handle(AIS_InteractiveObject)>::Iterator anIter(myObject3d);
        anIter.More(); anIter.Next())
    {
        const Handle(AIS_InteractiveObject)& anObject = anIter.Value();
        if (Handle(AIS_Shape) aShape = Handle(AIS_Shape)::DownCast(anObject))
        {
            anIsShapeExist = Standard_True;
            if (BRepTools::Write(aShape->Shape(), myFileName.ToCString()))
            {
                myResult << "A shape was successfully written" << std::endl;
            }
            else
            {
                myResult << "A shape was not written" << std::endl;
            }
            break; // write only one shape
        }
    }
    if (!anIsShapeExist)
    {
        myResult << "A shape does not exist" << std::endl;
    }
}


void DataExchangeSamples::ObjExportSample() {
   
    for (NCollection_Vector<Handle(AIS_InteractiveObject)>::Iterator anIter(myObject3d); anIter.More(); anIter.Next())
    {
        const Handle(AIS_InteractiveObject)& anObject = anIter.Value();
        if (Handle(AIS_Shape) aShape = Handle(AIS_Shape)::DownCast(anObject))
        {
            Message_ProgressRange& theProgress = Message_ProgressRange();
            bool status = this->objDeProvider->Write(myFileName.ToCString(), aShape->Shape(), theProgress);
            if (status != IFSelect_RetDone)
            {
                myResult << "A shape was not transferred successfully" << std::endl;
                return;
            }
        }
    }
    myResult << " write obj file successfully" << std::endl;
};



void DataExchangeSamples::StepExportSample()
{
    if (myStepType < 0)
    {
        myResult << "Unknown step type" << std::endl;
        return;
    }

    IFSelect_ReturnStatus aStatus;

    if (myStepType == STEPControl_FacetedBrep && !CheckFacetedBrep())
    {
        myResult << "At least one shape doesn't contain facets" << std::endl;
        return;
    }

    STEPControl_Writer aStepWriter;
    for (NCollection_Vector<Handle(AIS_InteractiveObject)>::Iterator anIter(myObject3d);
        anIter.More(); anIter.Next())
    {
        const Handle(AIS_InteractiveObject)& anObject = anIter.Value();
        if (Handle(AIS_Shape) aShape = Handle(AIS_Shape)::DownCast(anObject))
        {
            aStatus = aStepWriter.Transfer(aShape->Shape(), myStepType);
            if (aStatus != IFSelect_RetDone)
            {
                myResult << "A shape was not transferred successfully" << std::endl;
                return;
            }
        }
    }
    aStatus = aStepWriter.Write(myFileName.ToCString());

    switch (aStatus)
    {
    case IFSelect_RetError:
        myResult << "Incorrect Data." << std::endl;
        break;
    case IFSelect_RetFail:
        myResult << "Writing error" << std::endl;
        break;
    case IFSelect_RetVoid:
        myResult << "Nothing to transfer." << std::endl;
        break;
    case IFSelect_RetStop:
    case IFSelect_RetDone:
        myResult << "A STEP file was successfully written" << std::endl;
        break;
    }

}

void DataExchangeSamples::IgesExportSample()
{
    IGESControl_Controller::Init();
    IGESControl_Writer anIgesWriter(Interface_Static::CVal("XSTEP.iges.unit"),
        Interface_Static::IVal("XSTEP.iges.writebrep.mode"));

    Standard_Boolean anIsShapeExist = Standard_False;
    for (NCollection_Vector<Handle(AIS_InteractiveObject)>::Iterator anIter(myObject3d);
        anIter.More(); anIter.Next())
    {
        const Handle(AIS_InteractiveObject)& anObject = anIter.Value();
        if (Handle(AIS_Shape) aShape = Handle(AIS_Shape)::DownCast(anObject))
        {
            anIsShapeExist = Standard_True;
            anIgesWriter.AddShape(aShape->Shape());
        }
    }
    if (anIsShapeExist)
    {
        anIgesWriter.ComputeModel();
        if (anIgesWriter.Write(myFileName.ToCString()))
        {
            myResult << "A STEP file was successfully written" << std::endl;
        }
        else
        {
            myResult << "A STEP file was not written" << std::endl;
        }
    }
    else
    {
        myResult << "Shapes do not exist" << std::endl;
    }
}

void DataExchangeSamples::StlExportSample()
{
    TopoDS_Compound aTopoCompound;
    BRep_Builder aBuilder;
    aBuilder.MakeCompound(aTopoCompound);

    Standard_Boolean anIsShapeExist = Standard_False;
    for (NCollection_Vector<Handle(AIS_InteractiveObject)>::Iterator anIter(myObject3d);
        anIter.More(); anIter.Next())
    {
        const Handle(AIS_InteractiveObject)& anObject = anIter.Value();
        if (Handle(AIS_Shape) aShape = Handle(AIS_Shape)::DownCast(anObject))
        {
            anIsShapeExist = Standard_True;
            aBuilder.Add(aTopoCompound, aShape->Shape());
        }
    }
    if (anIsShapeExist)
    {
        StlAPI_Writer aStlWriter;
        if (aStlWriter.Write(aTopoCompound, myFileName.ToCString()))
        {
            myResult << "A STL file was successfully written" << std::endl;
        }
        else
        {
            myResult << "A STL file was not written" << std::endl;
        }
    }
    else
    {
        myResult << "Shapes do not exist" << std::endl;
    }
}

void DataExchangeSamples::VrmlExportSample()
{
    TopoDS_Compound aTopoCompound;
    BRep_Builder aBrepBuilder;
    aBrepBuilder.MakeCompound(aTopoCompound);

    Standard_Boolean anIsShapeExist = Standard_False;
    for (NCollection_Vector<Handle(AIS_InteractiveObject)>::Iterator anIter(myObject3d);
        anIter.More(); anIter.Next())
    {
        const Handle(AIS_InteractiveObject)& anObject = anIter.Value();
        if (Handle(AIS_Shape) aShape = Handle(AIS_Shape)::DownCast(anObject))
        {
            anIsShapeExist = Standard_True;
            aBrepBuilder.Add(aTopoCompound, aShape->Shape());
        }
    }
    if (anIsShapeExist)
    {
        VrmlAPI_Writer aVrmlWriter;
        if (aVrmlWriter.Write(aTopoCompound, myFileName.ToCString()))
        {
            myResult << "A VRML file was successfully written" << std::endl;
        }
        else
        {
            myResult << "A VRML file was not written" << std::endl;
        }
    }
    else
    {
        myResult << "Shapes do not exist" << std::endl;
    }
}

void DataExchangeSamples::ImageExportSample()
{
    if (myView)
    {
        Standard_Boolean aResult = myView->Dump(myFileName.ToCString());
        if (aResult)
        {
            myResult << "An image file was successfully written" << std::endl;
        }
        else
        {
            myResult << "An image file was not written" << std::endl;
        }
    }
}

void DataExchangeSamples::BrepImportSample()
{
    TopoDS_Shape aTopoShape;
    BRep_Builder aBuilder;
    Standard_Boolean aResult = BRepTools::Read(aTopoShape, myFileName.ToCString(), aBuilder);
    if (aResult)
    {
        Handle(AIS_Shape) anAisShape = new AIS_Shape(aTopoShape);
        myObject3d.Append(anAisShape);
        myResult << "A BREP file was read successfully" << std::endl;
    }
    else
    {
        myResult << "A BREP file was not read successfully" << std::endl;
    }

}

void DataExchangeSamples::StepImportSample()
{
    Handle(TopTools_HSequenceOfShape) aSequence = new TopTools_HSequenceOfShape();
    STEPControl_Reader aReader;
    const IFSelect_ReturnStatus aStatus = aReader.ReadFile(myFileName.ToCString());
    if (aStatus != IFSelect_RetDone)
    {
        myResult << "A BREP file was not read successfully" << std::endl;
        return;
    }

    bool anIsFailsOnly = false;
    aReader.PrintCheckLoad(anIsFailsOnly, IFSelect_ItemsByEntity);

    int aRootsNumber = aReader.NbRootsForTransfer();
    aReader.PrintCheckTransfer(anIsFailsOnly, IFSelect_ItemsByEntity);
    for (Standard_Integer i = 1; i <= aRootsNumber; i++)
    {
        aReader.TransferRoot(i);
    }

    int aShapesNumber = aReader.NbShapes();
    for (int i = 1; i <= aShapesNumber; i++)
    {
        TopoDS_Shape aTopoShape = aReader.Shape(i);
        Handle(AIS_Shape) anAisShape = new AIS_Shape(aTopoShape);
        myObject3d.Append(anAisShape);
    }
    myResult << "A STEP file was read successfully" << std::endl;
}

void DataExchangeSamples::IgesImportSample()
{
    IGESControl_Reader aReader;
    int status = aReader.ReadFile(myFileName.ToCString());
    if (status != IFSelect_RetDone)
    {
        myResult << "A IGES file was not read successfully" << std::endl;
        return;
    }
    aReader.TransferRoots();
    TopoDS_Shape aTopoShape = aReader.OneShape();
    Handle(AIS_Shape) anAisShape = new AIS_Shape(aTopoShape);
    myObject3d.Append(anAisShape);
    myResult << "A IGES file was read successfully" << std::endl;
}


void DataExchangeSamples::StlImportSample() {
    StlAPI_Reader aReader;
    TopoDS_Shape aTopoShape;
    int status = aReader.Read(aTopoShape, myFileName.ToCString());
    if (status != IFSelect_RetDone)
    {
        myResult << "A Stl file was not read successfully" << std::endl;
        return;
    }

    Handle(AIS_Shape) anAisShape = new AIS_Shape(aTopoShape);
    myObject3d.Append(anAisShape);
    myResult << "A Stl file was read successfully" << std::endl;
}


void DataExchangeSamples::ObjImportSample() {
    //先清理，确保内存总是维持在可控范围
    myObject3d.Clear();
    TopoDS_Shape& aTopoShape = TopoDS_Shape();
    Message_ProgressRange& theProgress = Message_ProgressRange();
    Standard_Boolean status = this->objDeProvider->Read(myFileName.ToCString(), aTopoShape, theProgress);
    if (status != IFSelect_RetDone)
    {
        myResult << "A Obj file was not read successfully:" << status << std::endl;
        return;
    }

    Handle(AIS_Shape) anAisShape = new AIS_Shape(aTopoShape);
    myObject3d.Append(anAisShape);
    myResult << "A Obj file was read successfully" << std::endl;
};


void DataExchangeSamples::VrmlImportSample() {

    //先清理，确保内存总是维持在可控范围
    myObject3d.Clear();
    TopoDS_Shape& aTopoShape = TopoDS_Shape();
    Message_ProgressRange& theProgress = Message_ProgressRange();
    Standard_Boolean status = this->vrmlDeProvider->Read(myFileName.ToCString(), aTopoShape, theProgress);
    if (status != IFSelect_RetDone)
    {
        myResult << "A vrml file was not read successfully:" << status << std::endl;
        return;
    }

    Handle(AIS_Shape) anAisShape = new AIS_Shape(aTopoShape);
    myObject3d.Append(anAisShape);
    myResult << "A vrml file was read successfully" << std::endl;


}


Standard_Boolean DataExchangeSamples::CheckFacetedBrep()
{
    Standard_Boolean anError = Standard_False;
    for (NCollection_Vector<Handle(AIS_InteractiveObject)>::Iterator anIter(myObject3d);
        anIter.More(); anIter.Next())
    {
        const Handle(AIS_InteractiveObject)& anObject = anIter.Value();
        if (Handle(AIS_Shape) aShape = Handle(AIS_Shape)::DownCast(anObject))
        {
            const TopoDS_Shape aTopoShape = aShape->Shape();
            for (TopExp_Explorer aFaceExplorer(aTopoShape, TopAbs_FACE); aFaceExplorer.More() && !anError; aFaceExplorer.Next())
            {
                Handle(Geom_Surface) aSurface = BRep_Tool::Surface(TopoDS::Face(aFaceExplorer.Current()));
                if (!aSurface->IsKind(STANDARD_TYPE(Geom_Plane)))
                {
                    anError = Standard_True;
                }
            }
            for (TopExp_Explorer anEdgeExplorer(aTopoShape, TopAbs_EDGE); anEdgeExplorer.More() && !anError; anEdgeExplorer.Next())
            {
                Standard_Real fd, ld;
                Handle(Geom_Curve) curve = BRep_Tool::Curve(TopoDS::Edge(anEdgeExplorer.Current()), fd, ld);
                if (!curve->IsKind(STANDARD_TYPE(Geom_Line)))
                {
                    anError = Standard_True;
                }
            }
        }
    }
    return !anError;
}
