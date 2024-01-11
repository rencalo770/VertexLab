
#include "../header/Viewer2dSamples.h"

#include "../header/Sample2D_Markers.h"
#include "../header/Sample2D_Face.h"
#include "../header/Sample2D_Image.h"

#include <AIS_ColoredShape.hxx>
#include <AIS_TextLabel.hxx>
#include <BRepBuilderAPI_MakeEdge.hxx>
#include <BRepBuilderAPI_MakeWire.hxx>
#include <BRepBuilderAPI_MakeFace.hxx>
#include <TopoDS_Edge.hxx>
#include <TopoDS_Face.hxx>
#include <TopoDS_Wire.hxx>
#include <Quantity_NameOfColor.hxx>
#include <QDebug>

void Viewer2dSamples::ExecuteSample(const TCollection_AsciiString& theSampleName)
{
    Standard_Boolean anIsSamplePresent = Standard_True;
    FindSourceCode(theSampleName);
    if (theSampleName == "TextView2dSample")
        TextView2dSample();
    else if (theSampleName == "MarkerView2dSample")
        MarkerView2dSample();
    else if (theSampleName == "FillAreaView2dSample")
        FillAreaView2dSample();
    else if (theSampleName == "LoopOnFaceView2dSample")
        LoopOnFaceView2dSample();
    else if (theSampleName == "RectagularLineGrid2dSample")
        RectagularLineGrid2dSample();
    else if (theSampleName == "RectagularPointGrid2dSample")
        RectagularPointGrid2dSample();
    else if (theSampleName == "CircularLineGrid2dSample")
        CircularLineGrid2dSample();
    else if (theSampleName == "CircularPointGrid2dSample")
        CircularPointGrid2dSample();
    else if (theSampleName == "ClearGrid2dSample")
        ClearGrid2dSample();
    else if (theSampleName == "BackgroundImage2dSample")
        BackgroundImage2dSample();
    else {
        myResult << "No function found: " << theSampleName;
        myCode += TCollection_AsciiString("No function found: ") + theSampleName;
        anIsSamplePresent = Standard_False;
    }
    myIsProcessed = anIsSamplePresent;
}

void Viewer2dSamples::ClearExtra()
{
    myContext->RemoveAll(Standard_True);
    myViewer->DeactivateGrid();
}

//一行文字的不同样式
void Viewer2dSamples::TextView2dSample()
{
    Standard_Integer aColor = Quantity_NOC_MATRABLUE;
    for (Standard_Integer j = 15; j <= 20; j++)
    {
        Handle(AIS_TextLabel) aText = new AIS_TextLabel();
        aText->SetText(TCollection_AsciiString("font 0 scale ") + (j / 20.0));
        aText->SetPosition(gp_Pnt(0.0, 15.0 * (j - 15.0), 0.0));
        aText->SetAngle(30.0 * M_PI / 180.0);
        aText->SetColor(Quantity_NameOfColor(aColor++));
        aText->SetFontAspect(Font_FA_Regular);
        aText->SetFont("Courier");
        aText->SetHeight(j);
        aText->SetHJustification(Graphic3d_HTA_LEFT);
        aText->SetVJustification(Graphic3d_VTA_BOTTOM);
        aText->SetZoomable(Standard_False);
        myObject2d.Append(aText);
    }

    for (Standard_Real j = 10; j <= 15; j++)
    {
        Handle(AIS_TextLabel) aText = new AIS_TextLabel();
        aText->SetText(TCollection_AsciiString("font 1 scale ") + (j / 10.0));
        aText->SetPosition(gp_Pnt(80.0, 15.0 * (j - 10.0), 0.0));
        aText->SetAngle(0.0);
        aText->SetColor(Quantity_NameOfColor(aColor++));
        aText->SetFontAspect(Font_FA_BoldItalic);
        aText->SetFont("Cambria");
        aText->SetHeight(j * 2);
        aText->SetHJustification(Graphic3d_HTA_LEFT);
        aText->SetVJustification(Graphic3d_VTA_BOTTOM);
        aText->SetZoomable(Standard_False);
        myObject2d.Append(aText);
    }

    aColor = Quantity_NOC_MATRABLUE;
    for (Standard_Real j = 5; j <= 10; j++)
    {
        Handle(AIS_TextLabel) aText = new AIS_TextLabel();
        aText->SetText(TCollection_AsciiString("font 2 scale ") + (j / 10.0));
        aText->SetPosition(gp_Pnt(140.0, 15.0 * (j - 5.0), 0.0));
        aText->SetAngle(0.0);
        aText->SetColor(Quantity_NameOfColor(aColor++));
        aText->SetFontAspect(Font_FA_Bold);
        aText->SetFont("Arial");
        aText->SetHeight(j * 2);
        aText->SetHJustification(Graphic3d_HTA_LEFT);
        aText->SetVJustification(Graphic3d_VTA_BOTTOM);
        aText->SetZoomable(Standard_False);
        myObject2d.Append(aText);
    }
    for (Standard_Real j = 10; j <= 15; j++)
    {
        Handle(AIS_TextLabel) aText = new AIS_TextLabel();
        aText->SetText(TCollection_AsciiString("font 3 scale ") + (j / 10.0));
        aText->SetPosition(gp_Pnt(200.0, 15.0 * (j - 10.0), 0.0));
        aText->SetAngle(0.0);
        aText->SetColor(Quantity_NameOfColor(aColor++));
        aText->SetFontAspect(Font_FA_Italic);
        aText->SetFont("Georgia");
        aText->SetHeight(j * 2);
        aText->SetHJustification(Graphic3d_HTA_LEFT);
        aText->SetVJustification(Graphic3d_VTA_BOTTOM);
        aText->SetZoomable(Standard_False);
        myObject2d.Append(aText);
    }
}

// 俩列标记
void Viewer2dSamples::MarkerView2dSample()
{
    // generic Markers
    Standard_Integer aColor = 20;
    for (int i = 1; i <= 2; i++)
    {
        Handle(Sample2D_Markers) aMarker = new Sample2D_Markers(10 + 5, 5 * i, Aspect_TOM_POINT, Quantity_NOC_YELLOW, 2.0);
        myObject2d.Append(aMarker);
    }
    for (int i = 1; i <= 2; i++)
    {
        Handle(Sample2D_Markers) aMarker = new Sample2D_Markers(10 + 10, 5 * i, Aspect_TOM_O, (Quantity_NameOfColor)(aColor++));
        myObject2d.Append(aMarker);
    }
    for (int i = 1; i <= 2; i++)
    {
        Handle(Sample2D_Markers) aMarker = new Sample2D_Markers(10 + 15, 5 * i, Aspect_TOM_O_PLUS, (Quantity_NameOfColor)(aColor++));
        myObject2d.Append(aMarker);
    }
    for (int i = 1; i <= 2; i++)
    {
        Handle(Sample2D_Markers) aMarker = new Sample2D_Markers(10 + 20, 5 * i, Aspect_TOM_RING1, (Quantity_NameOfColor)(aColor++));
        myObject2d.Append(aMarker);
    }
    for (int i = 1; i <= 2; i++)
    {
        Handle(Sample2D_Markers) aMarker = new Sample2D_Markers(10 + 25, 5 * i, Aspect_TOM_STAR, (Quantity_NameOfColor)(aColor++));
        myObject2d.Append(aMarker);
    }
    for (int i = 1; i <= 2; i++)
    {
        Handle(Sample2D_Markers) aMarker = new Sample2D_Markers(10 + 30, 5 * i, Aspect_TOM_O_X, (Quantity_NameOfColor)(aColor++));
        myObject2d.Append(aMarker);
    }
}

//不同边框线的小长方形
void Viewer2dSamples::FillAreaView2dSample()
{
    for (int i = 0; i <= 13; ++i)
    {
        for (int j = 0; j <= 5; ++j)
        {
            // set of rectangles here
            TopoDS_Edge E1 = BRepBuilderAPI_MakeEdge(gp_Pnt(10 * i, 10 * j, 0.), gp_Pnt(10 * i + 7, 10 * j, 0.));
            TopoDS_Edge E2 = BRepBuilderAPI_MakeEdge(gp_Pnt(10 * i + 7, 10 * j, 0.), gp_Pnt(10 * i + 7, 10 * j + 5, 0.));
            TopoDS_Edge E3 = BRepBuilderAPI_MakeEdge(gp_Pnt(10 * i + 7, 10 * j + 5, 0.), gp_Pnt(10 * i, 10 * j + 5, 0.));
            TopoDS_Edge E4 = BRepBuilderAPI_MakeEdge(gp_Pnt(10 * i, 10 * j + 5, 0.), gp_Pnt(10 * i, 10 * j, 0.));
            TopoDS_Wire W = BRepBuilderAPI_MakeWire(E1, E2, E3, E4);
            TopoDS_Face F = BRepBuilderAPI_MakeFace(W);
            Handle(AIS_Shape) aRect = new AIS_Shape(F);
            // set attributes of boundaries
            Handle(Prs3d_Drawer) aDrawer = new Prs3d_Drawer();
            Handle(Prs3d_LineAspect) aLineAttrib = new Prs3d_LineAspect(Quantity_NOC_YELLOW,
                (Aspect_TypeOfLine)(Aspect_TOL_SOLID + j), 1);
            aDrawer->SetFaceBoundaryAspect(aLineAttrib);
            aDrawer->SetFaceBoundaryDraw(Standard_True);
            aRect->SetAttributes(aDrawer);

            myContext->SetDisplayMode(aRect, 1, Standard_False);
            myContext->SetColor(aRect, (Quantity_NameOfColor)(Quantity_NOC_CADETBLUE + 2 * i), Standard_False);
            myContext->SetMaterial(aRect, Graphic3d_NOM_PLASTIC, Standard_False);
            myObject2d.Append(aRect);

        }
    }
}

//长方形循环箭头边框
void Viewer2dSamples::LoopOnFaceView2dSample()
{
    // Make a flat rectangular face on XY plane.
    gp_Pln aPln(gp::XOY()); //2d平面上
    TopoDS_Face aFaceRect = BRepBuilderAPI_MakeFace(aPln, -10.0, +10.0, -20.0, +20.0); //指定4个顶点的位置

    Handle(AIS_ColoredShape) anAisFaceRect = new AIS_ColoredShape(aFaceRect);
    anAisFaceRect->SetColor(Quantity_Color(Quantity_NOC_RED));
    myObject2d.Append(anAisFaceRect);

    TopoDS_Shape aFaceShape;
    Handle(Sample2D_Face) anAISFace = new Sample2D_Face(aFaceRect);
    myObject2d.Append(anAISFace);
}

// 网格图
void Viewer2dSamples::RectagularLineGrid2dSample()
{
    Handle(Graphic3d_AspectMarker3d) aGridAspect = new Graphic3d_AspectMarker3d(Aspect_TOM_RING1, Quantity_NOC_WHITE, 2);
    myViewer->SetGridEcho(aGridAspect);
    Standard_Integer aWidth = 0, aHeight = 0, anOffset = 0;
    myView->Window()->Size(aWidth, aHeight);
    myViewer->SetRectangularGridGraphicValues(aWidth, aHeight, anOffset);
    myViewer->ActivateGrid(Aspect_GT_Rectangular, Aspect_GDM_Lines); // 长方形线图
    myViewer->Redraw();
}

//上面网格图反选的点图
void Viewer2dSamples::RectagularPointGrid2dSample()
{
    Handle(Graphic3d_AspectMarker3d) aGridAspect = new Graphic3d_AspectMarker3d(Aspect_TOM_RING1, Quantity_NOC_WHITE, 2);
    myViewer->SetGridEcho(aGridAspect);
    Standard_Integer aWidth = 0, aHeight = 0, anOffset = 0;
    myView->Window()->Size(aWidth, aHeight);
    myViewer->SetRectangularGridGraphicValues(aWidth, aHeight, anOffset);
    myViewer->ActivateGrid(Aspect_GT_Rectangular, Aspect_GDM_Points); // 长方形点图
    myViewer->Redraw();
}

// 蜘蛛网图
void Viewer2dSamples::CircularLineGrid2dSample()
{
    Handle(Graphic3d_AspectMarker3d) aGridAspect = new Graphic3d_AspectMarker3d(Aspect_TOM_RING1, Quantity_NOC_WHITE, 2);
    myViewer->SetGridEcho(aGridAspect);
    Standard_Integer aWidth = 0, aHeight = 0, anOffset = 0;
    myView->Window()->Size(aWidth, aHeight);
    myViewer->SetRectangularGridGraphicValues(aWidth, aHeight, anOffset);
    myViewer->ActivateGrid(Aspect_GT_Circular, Aspect_GDM_Lines); // 圆形线图
    myViewer->Redraw();
}

//蜘蛛网图反选的点图
void Viewer2dSamples::CircularPointGrid2dSample()
{
    Handle(Graphic3d_AspectMarker3d) aGridAspect = new Graphic3d_AspectMarker3d(Aspect_TOM_RING1, Quantity_NOC_WHITE, 2);
    myViewer->SetGridEcho(aGridAspect);
    Standard_Integer aWidth = 0, aHeight = 0, anOffset = 0;
    myView->Window()->Size(aWidth, aHeight);
    myViewer->SetRectangularGridGraphicValues(aWidth, aHeight, anOffset);
    myViewer->ActivateGrid(Aspect_GT_Circular, Aspect_GDM_Points); // 圆形点图
    myViewer->Redraw();
}

// 清除网格
void Viewer2dSamples::ClearGrid2dSample()
{
    myViewer->DeactivateGrid(); 
    myViewer->Redraw();
}

// 背景图
void Viewer2dSamples::BackgroundImage2dSample()
{
    myFileName = "F:\\vsproject\\VertexLab\\res\\lamp.png";
    Handle(Sample2D_Image) anImage = new Sample2D_Image(myFileName);
    qDebug() << "start------------------";
    qDebug() << myFileName.ToCString();
    qDebug() << "end------------------";
    anImage->SetCoord(40, 50);
    anImage->SetScale(1.0);
    myObject2d.Append(anImage);
}
