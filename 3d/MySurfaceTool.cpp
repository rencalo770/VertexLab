#include "MySurfaceTool.h"
#include <Standard_Integer.hxx>
#include <gp_Pnt.hxx>
#include <BRepBuilderAPI_MakePolygon.hxx>
#include <GeomPlate_BuildPlateSurface.hxx>
#include <BRepTools_WireExplorer.hxx>
#include <Standard_Handle.hxx>
#include <BRepAdaptor_Curve.hxx>
#include <BRepFill_CurveConstraint.hxx>
#include <GeomPlate_MakeApprox.hxx>
#include <BRepBuilderAPI_MakeFace.hxx>
#include <GeomPlate_Surface.hxx>
#include <Geom_BSplineSurface.hxx>
#include <Geom_Surface.hxx>

MySurfaceTool::MySurfaceTool() {
};

MySurfaceTool::~MySurfaceTool() {
};

TopoDS_Shape MySurfaceTool::MakeSurfaceWithConstrains() {
	Standard_Integer NbCurFront = 4, NbPointConstraint = 1;
	gp_Pnt P1(0., 0., 0.);
	gp_Pnt P2(0., 10., 0.);
	gp_Pnt P3(0., 10., 10.);
	gp_Pnt P4(0., 0., 10.);
	gp_Pnt P5(5., 5., 5.);
	
	// 创建一个多边形
	BRepBuilderAPI_MakePolygon W;
	W.Add(P1);
	W.Add(P2);
	W.Add(P3);
	W.Add(P4);
	W.Add(P1);

	// Initialize a BuildPlateSurface 
	GeomPlate_BuildPlateSurface BPSurf(3, 15, 2);
	// Create the curve constraints 
	BRepTools_WireExplorer anExp;
	for (anExp.Init(W.Wire()); anExp.More(); anExp.Next())
	{
		TopoDS_Edge E = anExp.Current();
		Handle(BRepAdaptor_Curve) C = new BRepAdaptor_Curve();
		
		C -> Initialize(E);
		Handle(BRepFill_CurveConstraint) Cont = new
			BRepFill_CurveConstraint(C, 0);
		BPSurf.Add(Cont);
	}
	// Point constraint 
	Handle(GeomPlate_PointConstraint) PCont = new
		GeomPlate_PointConstraint(P5, 0);
	BPSurf.Add(PCont);
	// Compute the Plate surface 
	BPSurf.Perform();
	// Approximation of the Plate surface 
	Standard_Integer MaxSeg = 9;
	Standard_Integer MaxDegree = 8;
	Standard_Integer CritOrder = 0;
	Standard_Real dmax, Tol;
	Handle(GeomPlate_Surface) PSurf = BPSurf.Surface();
	dmax = Max(0.0001, 10 * BPSurf.G0Error());
	Tol = 0.0001;
	GeomPlate_MakeApprox Mapp(PSurf, Tol, MaxSeg, MaxDegree, dmax, CritOrder);
	
	Handle(Geom_Surface) Surf = Mapp.Surface();
	// create a face corresponding to the approximated Plate Surface 
	Standard_Real Umin = 0, Umax = 0, Vmin=0, Vmax=0;
	PSurf->Bounds(Umin, Umax, Vmin, Vmax);
	BRepBuilderAPI_MakeFace mf(Surf, Umin, Umax, Vmin, Vmax, Tol);
	return mf.Shape();
};

