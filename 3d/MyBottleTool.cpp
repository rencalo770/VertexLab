#include "MyBottleTool.h"

#include <BRep_Tool.hxx>

#include <BRepAlgoAPI_Fuse.hxx>

#include <BRepBuilderAPI_MakeEdge.hxx>
#include <BRepBuilderAPI_MakeFace.hxx>
#include <BRepBuilderAPI_MakeWire.hxx>
#include <BRepBuilderAPI_Transform.hxx>

#include <BRepFilletAPI_MakeFillet.hxx>

#include <BRepLib.hxx>

#include <BRepOffsetAPI_MakeThickSolid.hxx>
#include <BRepOffsetAPI_ThruSections.hxx>

#include <BRepPrimAPI_MakeCylinder.hxx>
#include <BRepPrimAPI_MakePrism.hxx>

#include <GC_MakeArcOfCircle.hxx>
#include <GC_MakeSegment.hxx>

#include <GCE2d_MakeSegment.hxx>

#include <gp.hxx>
#include <gp_Ax1.hxx>
#include <gp_Ax2.hxx>
#include <gp_Ax2d.hxx>
#include <gp_Dir.hxx>
#include <gp_Dir2d.hxx>
#include <gp_Pnt.hxx>
#include <gp_Pnt2d.hxx>
#include <gp_Trsf.hxx>
#include <gp_Vec.hxx>

#include <Geom_CylindricalSurface.hxx>
#include <Geom_Plane.hxx>
#include <Geom_Surface.hxx>
#include <Geom_TrimmedCurve.hxx>

#include <Geom2d_Ellipse.hxx>
#include <Geom2d_TrimmedCurve.hxx>

#include <TopExp_Explorer.hxx>

#include <TopoDS.hxx>
#include <TopoDS_Edge.hxx>
#include <TopoDS_Face.hxx>
#include <TopoDS_Wire.hxx>
#include <TopoDS_Shape.hxx>
#include <TopoDS_Compound.hxx>

#include <TopTools_ListOfShape.hxx>


/**
* @myWidth 瓶宽
* @myHeight 瓶高
* @myThickness 瓶子厚度
*/
TopoDS_Shape MyBottleTool::make(const Standard_Real myWidth, const Standard_Real myHeight, const Standard_Real myThickness) {
	// Profile : Define Support Points
		// 轮廓定位支撑点
	gp_Pnt aPnt1(-myWidth / 2., 0, 0);
	gp_Pnt aPnt2(-myWidth / 2., -myThickness / 4., 0);
	gp_Pnt aPnt3(0, -myThickness / 2., 0);
	gp_Pnt aPnt4(myWidth / 2., -myThickness / 4., 0);
	gp_Pnt aPnt5(myWidth / 2., 0, 0);

	// Profile : Define the Geometry
	//轮廓:定义几何图形，GC包计算基本曲面和曲线更容易
	Handle(Geom_TrimmedCurve) anArcOfCircle = GC_MakeArcOfCircle(aPnt2, aPnt3, aPnt4);//创建圆弧
	Handle(Geom_TrimmedCurve) aSegment1 = GC_MakeSegment(aPnt1, aPnt2); //创建线段
	Handle(Geom_TrimmedCurve) aSegment2 = GC_MakeSegment(aPnt4, aPnt5); //创建线段

	// Profile : Define the Topology
	// 轮廓: 定义拓扑结构
	TopoDS_Edge anEdge1 = BRepBuilderAPI_MakeEdge(aSegment1);
	TopoDS_Edge anEdge2 = BRepBuilderAPI_MakeEdge(anArcOfCircle);
	TopoDS_Edge anEdge3 = BRepBuilderAPI_MakeEdge(aSegment2);
	// 由顶点连接的边序列
	TopoDS_Wire aWire = BRepBuilderAPI_MakeWire(anEdge1, anEdge2, anEdge3);


	// Complete Profile
	//gp包中定义的几何常量，获取x轴
	gp_Ax1 xAxis = gp::OX();

	//设置变换矩阵，一种是传入变换矩阵的值，一种是基于方法
	gp_Trsf aTrsf;

	//基于方法变换:基于x轴制作镜像
	aTrsf.SetMirror(xAxis);
	//图形执行变换
	BRepBuilderAPI_Transform aBRepTrsf(aWire, aTrsf);

	//返回变换后的图形
	TopoDS_Shape aMirroredShape = aBRepTrsf.Shape();
	//获取变换后的形状
	TopoDS_Wire aMirroredWire = TopoDS::Wire(aMirroredShape);

	//通过该对象，使用Add方法添加两条线的所有边
	BRepBuilderAPI_MakeWire mkWire;
	mkWire.Add(aWire);
	mkWire.Add(aMirroredWire);
	TopoDS_Wire myWireProfile = mkWire.Wire();


	// Body : Prism the Profile
	// 主体: 棱镜轮廓
	// 通过线创建面
	TopoDS_Face myFaceProfile = BRepBuilderAPI_MakeFace(myWireProfile);
	gp_Vec aPrismVec(0, 0, myHeight); //sweep的方向
	//创建瓶子主体的数据现在都可用，
	TopoDS_Shape myBody = BRepPrimAPI_MakePrism(myFaceProfile, aPrismVec);



	// Body : Apply Fillets
	// 主体: 应用圆角
	BRepFilletAPI_MakeFillet mkFillet(myBody);
	TopExp_Explorer anEdgeExplorer(myBody, TopAbs_EDGE);
	while (anEdgeExplorer.More()) {
		TopoDS_Edge anEdge = TopoDS::Edge(anEdgeExplorer.Current());
		//Add edge to fillet algorithm，指定圆角半径
		mkFillet.Add(myThickness / 12., anEdge);
		anEdgeExplorer.Next();
	}
	//使用shape方法请求生成圆角形状
	myBody = mkFillet.Shape();

	// Body : Add the Neck	
	// 主体: 添加瓶颈
	gp_Pnt neckLocation(0, 0, myHeight); //这里是全局坐标系
	gp_Dir neckAxis = gp::DZ();
	gp_Ax2 neckAx2(neckLocation, neckAxis);

	Standard_Real myNeckRadius = myThickness / 4.;
	Standard_Real myNeckHeight = myHeight / 10.;

	//创建圆柱体
	BRepPrimAPI_MakeCylinder MKCylinder(neckAx2, myNeckRadius, myNeckHeight);
	TopoDS_Shape myNeck = MKCylinder.Shape();
	// 布尔运算，形状融合
	myBody = BRepAlgoAPI_Fuse(myBody, myNeck);


	// Body : Create a Hollowed Solid
	// 主体: 创建空心实体
	TopoDS_Face   faceToRemove;
	Standard_Real zMax = -1;

	for (TopExp_Explorer aFaceExplorer(myBody, TopAbs_FACE); aFaceExplorer.More(); aFaceExplorer.Next()) {
		TopoDS_Face aFace = TopoDS::Face(aFaceExplorer.Current());
		// Check if <aFace> is the top face of the bottle neck 
		Handle(Geom_Surface) aSurface = BRep_Tool::Surface(aFace);
		if (aSurface->DynamicType() == STANDARD_TYPE(Geom_Plane)) {
			Handle(Geom_Plane) aPlane = Handle(Geom_Plane)::DownCast(aSurface);
			gp_Pnt aPnt = aPlane->Location();
			Standard_Real aZ = aPnt.Z();
			if (aZ > zMax) { //找z值最大的面
				zMax = aZ;
				faceToRemove = aFace;
			}
		}
	}

	TopTools_ListOfShape facesToRemove;
	facesToRemove.Append(faceToRemove);
	BRepOffsetAPI_MakeThickSolid aSolidMaker;
	//创建空心实体
	// 实体、移除面、实体厚度、生成重合形状的公差
	aSolidMaker.MakeThickSolidByJoin(myBody, facesToRemove, -myThickness / 50, 1.e-3);
	myBody = aSolidMaker.Shape();

	// Threading : Create Surfaces
	// 通过圆柱创建圆柱面:neckAx2是圆柱
	Handle(Geom_CylindricalSurface) aCyl1 = new Geom_CylindricalSurface(neckAx2, myNeckRadius * 0.99);
	Handle(Geom_CylindricalSurface) aCyl2 = new Geom_CylindricalSurface(neckAx2, myNeckRadius * 1.05);

	// Threading : Define 2D Curves
	//定义一个右手坐标系统
	gp_Pnt2d aPnt(2. * M_PI, myNeckHeight / 2.);// 定义点
	gp_Dir2d aDir(2. * M_PI, myNeckHeight / 4.); //定义方向，/4占据neck的一半， /2占据全部
	gp_Ax2d anAx2d(aPnt, aDir); // 定义坐标系

	Standard_Real aMajor = 2. * M_PI;
	Standard_Real aMinor = myNeckHeight / 10;

	//定义椭圆(ellipse)
	Handle(Geom2d_Ellipse) anEllipse1 = new Geom2d_Ellipse(anAx2d, aMajor, aMinor);
	Handle(Geom2d_Ellipse) anEllipse2 = new Geom2d_Ellipse(anAx2d, aMajor, aMinor / 4);

	//椭圆参数方程: P(U) = O + (MajorRadius * cos(U) * XDirection) + (MinorRadius * sin(U) * YDirection)
	Handle(Geom2d_TrimmedCurve) anArc1 = new Geom2d_TrimmedCurve(anEllipse1, 0, M_PI); //被限制在0-M_PI之间
	Handle(Geom2d_TrimmedCurve) anArc2 = new Geom2d_TrimmedCurve(anEllipse2, 0, M_PI); //被限制在0-M_PI之间

	gp_Pnt2d anEllipsePnt1 = anEllipse1->Value(0);//起始点
	gp_Pnt2d anEllipsePnt2 = anEllipse1->Value(M_PI);//结束点
	//制作segment
	Handle(Geom2d_TrimmedCurve) aSegment = GCE2d_MakeSegment(anEllipsePnt1, anEllipsePnt2);

	// Threading : Build Edges and Wires
	TopoDS_Edge anEdge1OnSurf1 = BRepBuilderAPI_MakeEdge(anArc1, aCyl1);
	TopoDS_Edge anEdge2OnSurf1 = BRepBuilderAPI_MakeEdge(aSegment, aCyl1);
	TopoDS_Edge anEdge1OnSurf2 = BRepBuilderAPI_MakeEdge(anArc2, aCyl2);
	TopoDS_Edge anEdge2OnSurf2 = BRepBuilderAPI_MakeEdge(aSegment, aCyl2);

	TopoDS_Wire threadingWire1 = BRepBuilderAPI_MakeWire(anEdge1OnSurf1, anEdge2OnSurf1);
	TopoDS_Wire threadingWire2 = BRepBuilderAPI_MakeWire(anEdge1OnSurf2, anEdge2OnSurf2);

	//在BRepLib工具包中，您可以使用BuildCurves3d方法计算形状所有边的 3D 曲线。
	BRepLib::BuildCurves3d(threadingWire1);
	BRepLib::BuildCurves3d(threadingWire2);


	// Create Threading 
	// 创建线
	BRepOffsetAPI_ThruSections aTool(Standard_True);//构建一个壳
	aTool.AddWire(threadingWire1);// 添加连续线
	aTool.AddWire(threadingWire2); //  
	aTool.CheckCompatibility(Standard_False);//激活（或停用）检查导线是否具有相同边数的选项。在这种情况下，导线各有两条边，因此您可以停用此选项。

	TopoDS_Shape myThreading = aTool.Shape(); //生成螺旋形状

	// Building the Resulting Compound 
	// 构建 结果 集合
	TopoDS_Compound aRes;
	BRep_Builder aBuilder;
	aBuilder.MakeCompound(aRes);
	aBuilder.Add(aRes, myBody); //添加主体
	aBuilder.Add(aRes, myThreading); //添加螺旋线

	//返回所需资源
	return aRes;
}