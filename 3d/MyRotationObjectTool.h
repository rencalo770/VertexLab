#include <TopoDS_Shape.hxx>


class MyRotationObjectTool {

public:

	//�뾶 + �߶� ����һ��������Բ����
	TopoDS_Shape MakeFullCylinder();

	// �뾶 + �߶� + ��ת�Ƕȣ�����һ������Բ����
	TopoDS_Shape MakePortionCylinder();

	// ��׶��, ��ò�Ҫ��ô�� Two radii and height, to build a full cone. One of the radii can be null to make a sharp cone
	TopoDS_Shape MakeSharpCone();

	// ��׶�� Radii, height and angle to build a truncated cone
	TopoDS_Shape MakeTruncatedCone();

	// ����
	TopoDS_Shape MakeSphere();

	// ������
	TopoDS_Shape MakeLune();

	// ������
	TopoDS_Shape MakeSphericalSegment();

	// ��������
	TopoDS_Shape MakeSphericalSegmentLune();

	// Բ��
	TopoDS_Shape MakeFullTours();

	// ����Բ��
	TopoDS_Shape MakeSegmentTours();

	// ��Բ�л�,���API�����⣡����
	TopoDS_Shape MakeFullPortionTours();

	// Ƭ���л������API�����⣡����
	TopoDS_Shape MakeSegmentPortionTours();


};