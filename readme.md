1. class View(对象显示的子窗口) : public QWidget, protected AIS_ViewController  
2. applicationCommonWindow是主窗口, view, viewer2dSamples, viewer3dSamples 都在其上
3. BaseSample.cxx是其他示例类的基类，提供了查找执行的代码、接受执行结果的能力
4. DocumentCommon实现了示例内容的可视化实现，继承自QObject,名字起的不够贴切！！！

创建一个复杂图形的过程
1. 确定基点（point）
2. 有点创建线(edge -> wire)
3. 由线创建面(face -> shell)
4. 由面到实体(solid)
数据 -> 拓扑

# OCC中图形英文名称
- arrow 箭头
- cyliner 圆柱体
- polyLine 折线
- curve 曲线
- triangle 三角形 TriangleFans三角扇区
- quadric 二次曲面
- toruses 圆环
- circle 圆
- ellipse 椭圆
- hyperbola 双曲线
- parabola 抛物面


# OCC中包缩写的含义
Presentation -> Prs  演示类包



# OCC中的名词缩写
AIS -> application interactive service  引用程序交互服务



