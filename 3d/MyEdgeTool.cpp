#include "MyEdgeTool.h"
#include <gp_Ax2.hxx>
#include <gp_Vec.hxx>
#include <gp_Circ.hxx>
#include <TopTools_Array1OfShape.hxx>
#include <BRepBuilderAPI_MakeWire.hxx>

MyEdgeTool::MyEdgeTool() {
}

MyEdgeTool::~MyEdgeTool() {
}

TopoDS_Shape MyEdgeTool::MakeEdge() {
	//Handle(Geom_Curve) C = ...; // a curve 
	//TopoDS_Vertex V1 = ..., V2 = ...;// two Vertices 
	//Standard_Real p1 = ..., p2 = ..;// two parameters 
	//TopoDS_Edge E = BRepBuilderAPI_MakeEdge(C, V1, V2, p1, p2);

	return NULL;
}


void MyEdgeTool::MakeArc(Standard_Real x, Standard_Real y, Standard_Real R, Standard_Real ang, TopoDS_Shape& E, TopoDS_Shape& V1, TopoDS_Shape& V2) {
	gp_Ax2 Origin = gp::XOY();
	gp_Vec Offset(x, y, 0.);
	Origin.Translate(Offset);
	BRepBuilderAPI_MakeEdge	ME(gp_Circ(Origin, R), ang, ang + PI / 2);
	E = ME;
	V1 = ME.Vertex1();
	V2 = ME.Vertex2();
};

TopoDS_Wire MyEdgeTool::MakeFilletedRectangle(const Standard_Real H, const Standard_Real L, const Standard_Real R) {
	{
		TopTools_Array1OfShape theEdges(1, 8);
		TopTools_Array1OfShape theVertices(1, 8);
		Standard_Real x = L / 2 - R, y = H / 2 - R;
		this->MakeArc(x, -y, R, 3. * PI / 2., theEdges(2), theVertices(2),theVertices(3));
		this->MakeArc(x, y, R, 0., theEdges(4), theVertices(4),			theVertices(5));
		this->MakeArc(-x, y, R, PI / 2., theEdges(6), theVertices(6),			theVertices(7));
		this->MakeArc(-x, -y, R, PI, theEdges(8), theVertices(8),			theVertices(1));
		// Create the linear edges 
		for (Standard_Integer i = 1; i <= 7; i += 2)
		{
			theEdges(i) = BRepBuilderAPI_MakeEdge(TopoDS::Vertex(theVertices(i)), TopoDS::Vertex(theVertices(i + 1)));
		}
		// Create the wire using the BRepBuilderAPI_MakeWire 
		BRepBuilderAPI_MakeWire MW;
		for (i = 1; i <= 8; i++)
		{
			MW.Add(TopoDS::Edge(theEdges(i)));
		}
		return MW.Wire();
};
