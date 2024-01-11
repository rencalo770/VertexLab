#include <TopoDS_Shape.hxx>
#include <TopoDS_Wire.hxx>
#include <Standard_Real.hxx>
#include


class MyEdgeTool
{
public:
	MyEdgeTool();
	~MyEdgeTool();
	TopoDS_Shape MakeEdge();

	// Use MakeArc method to make an edge and two vertices 
	void MakeArc(Standard_Real x, Standard_Real y, Standard_Real R, Standard_Real ang, TopoDS_Shape& E, TopoDS_Shape& V1, TopoDS_Shape& V2);
	TopoDS_Wire MakeFilletedRectangle(const Standard_Real H, const Standard_Real L, const Standard_Real R);

private:

};
