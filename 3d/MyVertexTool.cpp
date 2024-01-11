#include "MyVertexTool.h"
#include <gp_Pnt.hxx>
#include <BRepBuilderAPI_MakeVertex.hxx>
#include <TopoDS_Vertex.hxx>

TopoDS_Shape MyVertexTool::MakeVertex() {
	gp_Pnt p(0, 0, 10);
	BRepBuilderAPI_MakeVertex mv(p);
	TopoDS_Vertex v = mv.Vertex();;
	return v;
}


