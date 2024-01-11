
#include "../header/TriangulationSamples.h"


#include "../3d/MyBottleTool.h"

#include <AIS_Shape.hxx>
#include <AIS_Triangulation.hxx>
#include <BRepMesh_IncrementalMesh.hxx>
#include <BRep_Tool.hxx>
#include <BRep_Builder.hxx>
#include <BRepBuilderAPI_MakeEdge.hxx>
#include <Poly_Triangulation.hxx>
#include <TopExp_Explorer.hxx>
#include <TopoDS.hxx>
#include <TopoDS_Compound.hxx>
#include <TopoDS_Edge.hxx>
#include <TopoDS_Face.hxx>
#include <TopoDS_Shape.hxx>

void TriangulationSamples::ExecuteSample(const TCollection_AsciiString& theSampleName)
{
    Standard_Boolean anIsSamplePresent = Standard_True;
    FindSourceCode(theSampleName);
    if (theSampleName == "Triangulation3dSample")
    {
        Triangulation3dSample();
    }
    else
    {
        myResult << "No function found: " << theSampleName;
        myCode += TCollection_AsciiString("No function found: ") + theSampleName;
        anIsSamplePresent = Standard_False;
    }
    myIsProcessed = anIsSamplePresent;
}

void TriangulationSamples::Triangulation3dSample()
{
    //TopoDS_Shape aBottle = MakeBottle(50, 70, 30);
    MyBottleTool* bt = new MyBottleTool();
    TopoDS_Shape aBottle = bt->make(50, 70, 30);

    BRepMesh_IncrementalMesh(aBottle, 1, Standard_False, 0.3, Standard_False);

    BRep_Builder aBuilder;
    TopoDS_Compound aCompound;
    aBuilder.MakeCompound(aCompound);

    Standard_Integer aNbTriangles(0);
    for (TopExp_Explorer anExplorer(aBottle, TopAbs_FACE); anExplorer.More(); anExplorer.Next())
    {
        TopoDS_Face aFace = TopoDS::Face(anExplorer.Current());
        TopLoc_Location aLocation;
        Handle(Poly_Triangulation) aTriangulation = BRep_Tool::Triangulation(aFace, aLocation);

        for (Standard_Integer i = 1; i <= aTriangulation->NbTriangles(); i++)
        {
            const Poly_Triangle trian = aTriangulation->Triangle(i);
            Standard_Integer index1, index2, index3, M = 0, N = 0;
            trian.Get(index1, index2, index3);

            for (Standard_Integer j = 1; j <= 3; j++)
            {
                switch (j)
                {
                case 1:
                    M = index1;
                    N = index2;
                    break;
                case 2:
                    N = index3;
                    break;
                case 3:
                    M = index2;
                }

                BRepBuilderAPI_MakeEdge anEdgeMaker(aTriangulation->Node(M), aTriangulation->Node(N));
                if (anEdgeMaker.IsDone())
                {
                    aBuilder.Add(aCompound, anEdgeMaker.Edge());
                }
            }
        }
        Handle(AIS_Triangulation) anAisTriangulation = new AIS_Triangulation(aTriangulation);
        aNbTriangles += aTriangulation->NbTriangles();
        myObject3d.Append(anAisTriangulation);
    }

    Handle(AIS_Shape)  anAisCompound = new AIS_Shape(aCompound);
    myObject3d.Append(anAisCompound);

    Handle(AIS_Shape) AISBottle = new AIS_Shape(aBottle);
    myObject3d.Append(AISBottle);

    myResult << "Compute the triangulation on a shape: " << aNbTriangles;
}
