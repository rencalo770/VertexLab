#include <TopoDS_Shape.hxx>


class MyRotationObjectTool {

public:

	//半径 + 高度 创建一个完整的圆柱体
	TopoDS_Shape MakeFullCylinder();

	// 半径 + 高度 + 旋转角度，创建一个部分圆柱体
	TopoDS_Shape MakePortionCylinder();

	// 尖锥体, 最好不要这么用 Two radii and height, to build a full cone. One of the radii can be null to make a sharp cone
	TopoDS_Shape MakeSharpCone();

	// 截锥体 Radii, height and angle to build a truncated cone
	TopoDS_Shape MakeTruncatedCone();

	// 球体
	TopoDS_Shape MakeSphere();

	// 月牙体
	TopoDS_Shape MakeLune();

	// 截球体
	TopoDS_Shape MakeSphericalSegment();

	// 截月牙体
	TopoDS_Shape MakeSphericalSegmentLune();

	// 圆环
	TopoDS_Shape MakeFullTours();

	// 部分圆环
	TopoDS_Shape MakeSegmentTours();

	// 满圆切环,这个API有问题！！！
	TopoDS_Shape MakeFullPortionTours();

	// 片段切环，这个API有问题！！！
	TopoDS_Shape MakeSegmentPortionTours();


};