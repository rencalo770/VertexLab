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
* @myWidth ƿ��
* @myHeight ƿ��
* @myThickness ƿ�Ӻ��
*/
TopoDS_Shape MyBottleTool::make(const Standard_Real myWidth, const Standard_Real myHeight, const Standard_Real myThickness) {
	// Profile : Define Support Points
		// ������λ֧�ŵ�
	gp_Pnt aPnt1(-myWidth / 2., 0, 0);
	gp_Pnt aPnt2(-myWidth / 2., -myThickness / 4., 0);
	gp_Pnt aPnt3(0, -myThickness / 2., 0);
	gp_Pnt aPnt4(myWidth / 2., -myThickness / 4., 0);
	gp_Pnt aPnt5(myWidth / 2., 0, 0);

	// Profile : Define the Geometry
	//����:���弸��ͼ�Σ�GC�����������������߸�����
	Handle(Geom_TrimmedCurve) anArcOfCircle = GC_MakeArcOfCircle(aPnt2, aPnt3, aPnt4);//����Բ��
	Handle(Geom_TrimmedCurve) aSegment1 = GC_MakeSegment(aPnt1, aPnt2); //�����߶�
	Handle(Geom_TrimmedCurve) aSegment2 = GC_MakeSegment(aPnt4, aPnt5); //�����߶�

	// Profile : Define the Topology
	// ����: �������˽ṹ
	TopoDS_Edge anEdge1 = BRepBuilderAPI_MakeEdge(aSegment1);
	TopoDS_Edge anEdge2 = BRepBuilderAPI_MakeEdge(anArcOfCircle);
	TopoDS_Edge anEdge3 = BRepBuilderAPI_MakeEdge(aSegment2);
	// �ɶ������ӵı�����
	TopoDS_Wire aWire = BRepBuilderAPI_MakeWire(anEdge1, anEdge2, anEdge3);


	// Complete Profile
	//gp���ж���ļ��γ�������ȡx��
	gp_Ax1 xAxis = gp::OX();

	//���ñ任����һ���Ǵ���任�����ֵ��һ���ǻ��ڷ���
	gp_Trsf aTrsf;

	//���ڷ����任:����x����������
	aTrsf.SetMirror(xAxis);
	//ͼ��ִ�б任
	BRepBuilderAPI_Transform aBRepTrsf(aWire, aTrsf);

	//���ر任���ͼ��
	TopoDS_Shape aMirroredShape = aBRepTrsf.Shape();
	//��ȡ�任�����״
	TopoDS_Wire aMirroredWire = TopoDS::Wire(aMirroredShape);

	//ͨ���ö���ʹ��Add������������ߵ����б�
	BRepBuilderAPI_MakeWire mkWire;
	mkWire.Add(aWire);
	mkWire.Add(aMirroredWire);
	TopoDS_Wire myWireProfile = mkWire.Wire();


	// Body : Prism the Profile
	// ����: �⾵����
	// ͨ���ߴ�����
	TopoDS_Face myFaceProfile = BRepBuilderAPI_MakeFace(myWireProfile);
	gp_Vec aPrismVec(0, 0, myHeight); //sweep�ķ���
	//����ƿ��������������ڶ����ã�
	TopoDS_Shape myBody = BRepPrimAPI_MakePrism(myFaceProfile, aPrismVec);



	// Body : Apply Fillets
	// ����: Ӧ��Բ��
	BRepFilletAPI_MakeFillet mkFillet(myBody);
	TopExp_Explorer anEdgeExplorer(myBody, TopAbs_EDGE);
	while (anEdgeExplorer.More()) {
		TopoDS_Edge anEdge = TopoDS::Edge(anEdgeExplorer.Current());
		//Add edge to fillet algorithm��ָ��Բ�ǰ뾶
		mkFillet.Add(myThickness / 12., anEdge);
		anEdgeExplorer.Next();
	}
	//ʹ��shape������������Բ����״
	myBody = mkFillet.Shape();

	// Body : Add the Neck	
	// ����: ���ƿ��
	gp_Pnt neckLocation(0, 0, myHeight); //������ȫ������ϵ
	gp_Dir neckAxis = gp::DZ();
	gp_Ax2 neckAx2(neckLocation, neckAxis);

	Standard_Real myNeckRadius = myThickness / 4.;
	Standard_Real myNeckHeight = myHeight / 10.;

	//����Բ����
	BRepPrimAPI_MakeCylinder MKCylinder(neckAx2, myNeckRadius, myNeckHeight);
	TopoDS_Shape myNeck = MKCylinder.Shape();
	// �������㣬��״�ں�
	myBody = BRepAlgoAPI_Fuse(myBody, myNeck);


	// Body : Create a Hollowed Solid
	// ����: ��������ʵ��
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
			if (aZ > zMax) { //��zֵ������
				zMax = aZ;
				faceToRemove = aFace;
			}
		}
	}

	TopTools_ListOfShape facesToRemove;
	facesToRemove.Append(faceToRemove);
	BRepOffsetAPI_MakeThickSolid aSolidMaker;
	//��������ʵ��
	// ʵ�塢�Ƴ��桢ʵ���ȡ������غ���״�Ĺ���
	aSolidMaker.MakeThickSolidByJoin(myBody, facesToRemove, -myThickness / 50, 1.e-3);
	myBody = aSolidMaker.Shape();

	// Threading : Create Surfaces
	// ͨ��Բ������Բ����:neckAx2��Բ��
	Handle(Geom_CylindricalSurface) aCyl1 = new Geom_CylindricalSurface(neckAx2, myNeckRadius * 0.99);
	Handle(Geom_CylindricalSurface) aCyl2 = new Geom_CylindricalSurface(neckAx2, myNeckRadius * 1.05);

	// Threading : Define 2D Curves
	//����һ����������ϵͳ
	gp_Pnt2d aPnt(2. * M_PI, myNeckHeight / 2.);// �����
	gp_Dir2d aDir(2. * M_PI, myNeckHeight / 4.); //���巽��/4ռ��neck��һ�룬 /2ռ��ȫ��
	gp_Ax2d anAx2d(aPnt, aDir); // ��������ϵ

	Standard_Real aMajor = 2. * M_PI;
	Standard_Real aMinor = myNeckHeight / 10;

	//������Բ(ellipse)
	Handle(Geom2d_Ellipse) anEllipse1 = new Geom2d_Ellipse(anAx2d, aMajor, aMinor);
	Handle(Geom2d_Ellipse) anEllipse2 = new Geom2d_Ellipse(anAx2d, aMajor, aMinor / 4);

	//��Բ��������: P(U) = O + (MajorRadius * cos(U) * XDirection) + (MinorRadius * sin(U) * YDirection)
	Handle(Geom2d_TrimmedCurve) anArc1 = new Geom2d_TrimmedCurve(anEllipse1, 0, M_PI); //��������0-M_PI֮��
	Handle(Geom2d_TrimmedCurve) anArc2 = new Geom2d_TrimmedCurve(anEllipse2, 0, M_PI); //��������0-M_PI֮��

	gp_Pnt2d anEllipsePnt1 = anEllipse1->Value(0);//��ʼ��
	gp_Pnt2d anEllipsePnt2 = anEllipse1->Value(M_PI);//������
	//����segment
	Handle(Geom2d_TrimmedCurve) aSegment = GCE2d_MakeSegment(anEllipsePnt1, anEllipsePnt2);

	// Threading : Build Edges and Wires
	TopoDS_Edge anEdge1OnSurf1 = BRepBuilderAPI_MakeEdge(anArc1, aCyl1);
	TopoDS_Edge anEdge2OnSurf1 = BRepBuilderAPI_MakeEdge(aSegment, aCyl1);
	TopoDS_Edge anEdge1OnSurf2 = BRepBuilderAPI_MakeEdge(anArc2, aCyl2);
	TopoDS_Edge anEdge2OnSurf2 = BRepBuilderAPI_MakeEdge(aSegment, aCyl2);

	TopoDS_Wire threadingWire1 = BRepBuilderAPI_MakeWire(anEdge1OnSurf1, anEdge2OnSurf1);
	TopoDS_Wire threadingWire2 = BRepBuilderAPI_MakeWire(anEdge1OnSurf2, anEdge2OnSurf2);

	//��BRepLib���߰��У�������ʹ��BuildCurves3d����������״���бߵ� 3D ���ߡ�
	BRepLib::BuildCurves3d(threadingWire1);
	BRepLib::BuildCurves3d(threadingWire2);


	// Create Threading 
	// ������
	BRepOffsetAPI_ThruSections aTool(Standard_True);//����һ����
	aTool.AddWire(threadingWire1);// ���������
	aTool.AddWire(threadingWire2); //  
	aTool.CheckCompatibility(Standard_False);//�����ͣ�ã���鵼���Ƿ������ͬ������ѡ�����������£����߸��������ߣ����������ͣ�ô�ѡ�

	TopoDS_Shape myThreading = aTool.Shape(); //����������״

	// Building the Resulting Compound 
	// ���� ��� ����
	TopoDS_Compound aRes;
	BRep_Builder aBuilder;
	aBuilder.MakeCompound(aRes);
	aBuilder.Add(aRes, myBody); //�������
	aBuilder.Add(aRes, myThreading); //���������

	//����������Դ
	return aRes;
}