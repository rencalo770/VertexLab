#include "MyRotationObjectTool.h"
#include <Standard_Real.hxx>
#include <gp_Ax2.hxx>
#include <TopoDS_Face.hxx>
#include <BRepPrimAPI_MakeCylinder.hxx>
#include <gp_Vec.hxx>
#include <BRepPrimAPI_MakeCone.hxx>
#include <BRepPrimAPI_MakeSphere.hxx>
#include <BRepPrimAPI_MakeTorus.hxx>

TopoDS_Shape MyRotationObjectTool::MakeFullCylinder() {
	Standard_Real X = 10, Y = 10, Z = 10, Radius = 10, Height = 30;
	// Make the system of coordinates 
	gp_Ax2 axes = gp::ZOX();
	axes.Translate(gp_Vec(X, Y, Z));

	TopoDS_Face F = BRepPrimAPI_MakeCylinder(axes, Radius, Height);
	return F;

}

TopoDS_Shape MyRotationObjectTool::MakePortionCylinder() {
	Standard_Real X = 20, Y = 10, Z = 15, Radius = 10, Height = 30;
	// Make the system of coordinates 
	gp_Ax2 axes = gp::ZOX();
	axes.Translate(gp_Vec(X, Y, Z));

	Standard_Real angle = M_PI / 2.;
	TopoDS_Face F =	BRepPrimAPI_MakeCylinder(axes, Radius, Height, angle);
	return F;
}


TopoDS_Shape MyRotationObjectTool::MakeSharpCone() {

	Standard_Real R1 = 30, R2 = 0, H = 15;
	TopoDS_Solid S = BRepPrimAPI_MakeCone(R1, R2,  H);
	return S;
}

TopoDS_Shape MyRotationObjectTool::MakeTruncatedCone() {
	Standard_Real R1 = 30, R2 = 10, H = 15;
	TopoDS_Solid S = BRepPrimAPI_MakeCone(R1, R2, H);
	return S;
}


TopoDS_Shape MyRotationObjectTool::MakeSphere() {
	Standard_Real R = 30, ang = M_PI / 2, a1 = -M_PI / 2.3, a2 = M_PI / 4;
	TopoDS_Solid S1 = BRepPrimAPI_MakeSphere(R);
	return S1;
}


// 月牙体
TopoDS_Shape MyRotationObjectTool::MakeLune() {
	Standard_Real R = 30, ang = M_PI / 2, a1 = -M_PI / 2.3, a2 = M_PI / 4;
	TopoDS_Solid S1 = BRepPrimAPI_MakeSphere(R, ang);
	return S1;
};

// 截球体
TopoDS_Shape MyRotationObjectTool::MakeSphericalSegment() {
	Standard_Real R = 30, ang = M_PI / 2, a1 = -M_PI / 2.3, a2 = M_PI / 4;
	TopoDS_Solid S1 = BRepPrimAPI_MakeSphere(R, a1, a2);
	return S1;

};

// 截月牙体
TopoDS_Shape MyRotationObjectTool::MakeSphericalSegmentLune() {
	Standard_Real R = 30, ang = M_PI / 2, a1 = -M_PI / 2.3, a2 = M_PI / 4;
	TopoDS_Solid S1 = BRepPrimAPI_MakeSphere(R,a1,a2,ang);
	return S1;
};


// 圆环
TopoDS_Shape MyRotationObjectTool::MakeFullTours() {
	Standard_Real R1 = 30, R2 = 10, ang = M_PI, a1 = 0,a2 = M_PI / 2;
	TopoDS_Shell S1 = BRepPrimAPI_MakeTorus(R1, R2);
	return S1;
};

// 部分圆环
TopoDS_Shape MyRotationObjectTool::MakeSegmentTours() {
	Standard_Real R1 = 30, R2 = 10, ang = M_PI, a1 = 0, a2 = M_PI / 2;
	TopoDS_Shell S1 = BRepPrimAPI_MakeTorus(R1, R2, ang);
	return S1;
};

// 满圆切环
TopoDS_Shape MyRotationObjectTool::MakeFullPortionTours() {
	Standard_Real R1 = 30, R2 = 10, ang = M_PI, a1 = 0, a2 = M_PI / 2;
	TopoDS_Shell S1 = BRepPrimAPI_MakeTorus(R1, R2, a1, a2);
	return S1;
};

// 片段切环
TopoDS_Shape MyRotationObjectTool::MakeSegmentPortionTours() {
	Standard_Real R1 = 30, R2 = 10, ang = M_PI, a1 = 0, a2 = M_PI / 2;
	TopoDS_Shell S1 = BRepPrimAPI_MakeTorus(R1, R2, a1, a2, ang);
	return S1;
};
