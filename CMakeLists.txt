cmake_minimum_required(VERSION 3.16)

project(VertexLab VERSION 0.1 LANGUAGES CXX)

# ui文件
set(CMAKE_AUTOUIC ON)
# moc文件
set(CMAKE_AUTOMOC ON)
#qrc文件
set(CMAKE_AUTORCC ON)

# qrc文件
set(QRC_SOURCE_FILES VertexLab.qrc)

set(QT5_DIR "H:\\Qt\\Qt5.11.2\\5.11.2\\msvc2017_64\\lib\\cmake\\Qt5")
find_package(Qt5 COMPONENTS Widgets xml REQUIRED)

set(OpenCASCADE_DIR "E:\\OpenCASCADE-7.7.0-vc14-64\\opencascade-7.7.0\\cmake")
find_package(OpenCASCADE)
include_directories(SYSTEM ${OpenCASCADE_INCLUDE_DIR})


add_executable(VertexLab 
        "source/main.cxx"
        "res/VertexLab.qrc"  #5 
        "res/Samples.qrc"
#        vertexlabwindow.cpp
#        vertexlabwindow.h
#        vertexlabwindow.ui 
        "3d/MyBottleTool.cpp" 
        "3d/MyBottleTool.h"
        "header/AdaptorCurve2d_AIS.h" 
        "header/AdaptorPnt2d_AIS.h" 
        "header/AdaptorVec_AIS.h"
        "header/BaseSample.h" 
        "header/CommonSample.h" 
        "header/DataExchangeSamples.h" 
        "header/DocumentCommon.h" 
        "header/GeometrySamples.h" 
        "header/GeomWidget.h" 
        "header/OcafSamples.h" 
        "header/OcctHighlighter.h" 
        "header/OcctWindow.h" 
        "header/Sample2D_Face.h" 
        "header/Sample2D_Image.h" 
        "header/Sample2D_Markers.h" 
        "header/TOcaf_Application.h" 
        "header/TOcafFunction_BoxDriver.h" 
        "header/TOcafFunction_CutDriver.h" 
        "header/TOcafFunction_CylDriver.h" 
        "header/TopologySamples.h" 
        "header/TranslateDialog.h" 
        "header/DialogTransparency.h" 
        "header/TriangulationSamples.h" 
        "header/Viewer2dSamples.h" 
        "header/View.h" 
        "header/ApplicationCommonWindow.h"
        "source/AdaptorCurve_AIS.cxx" 
        "source/AdaptorCurve2d_AIS.cxx" 
        "source/AdaptorPnt2d_AIS.cxx" 
        "source/AdaptorVec_AIS.cxx" 
        "source/ApplicationCommonWindow.cxx" 
        "source/BaseSample.cxx" 
        "source/DataExchangeSamples.cxx" 
        "source/DocumentCommon.cxx" 
        "source/GeometrySamples.cxx" 
        "source/GeomWidget.cxx" 
        "source/OcafSamples.cxx" 
        "source/OcctHighlighter.cxx" 
        "source/OcctWindow.cxx" 
        "source/Sample2D_Face.cxx" 
        "source/Sample2D_Image.cxx" 
        "source/Sample2D_Markers.cxx" 
        "source/TOcaf_Application.cxx" 
        "source/TOcafFunction_BoxDriver.cxx" 
        "source/TOcafFunction_CutDriver.cxx" 
        "source/TOcafFunction_CylDriver.cxx" 
        "source/TopologySamples.cxx" 
        "source/TranslateDialog.cxx" 
        "source/DialogTransparency.cxx" 
        "source/TriangulationSamples.cxx" 
        "source/View.cxx" 
        "source/Viewer2dSamples.cxx" 
        "source/Viewer3dSamples.cxx" 
         "3d/MySurfaceTool.h" 
         "3d/MySurfaceTool.cpp" 
         "3d/MyVertexTool.h" 
         "3d/MyVertexTool.cpp"
         "3d/MyEdgeTool.h"
         "3d/MyRotationObjectTool.h"
         "3d/MyRotationObjectTool.cpp"
)


#qt5_use_modules(VertexLab ${QT})

foreach (LIB ${OpenCASCADE_LIBRARIES})
  target_link_libraries(VertexLab PRIVATE ${OpenCASCADE_LIBRARY_DIR}/${LIB}.lib)
endforeach()

# target_link_libraries 需要配合find package使用;  
#target_link_libraries(VertexLab PRIVATE Qt${QT_VERSION_MAJOR}::Widgets  PRIVATE Qt${QT_VERSION_MAJOR}::Core PRIVATE Qt${QT_VERSION_MAJOR}::Gui PRIVATE Qt${QT_VERSION_MAJOR}::OpenGLWidgets PRIVATE Qt${QT_VERSION_MAJOR}::OpenGL PRIVATE Qt${QT_VERSION_MAJOR}::Network )
target_link_libraries(VertexLab PRIVATE Qt5::Widgets PRIVATE Qt5::Xml) # PRIVATE Qt5::OpenGLWidgets


#set_target_properties(${PROJECT_NAME} PROPERTIES AUTOMOC TRUE)

set_target_properties(VertexLab PROPERTIES
    MACOSX_BUNDLE ON
    WIN32_EXECUTABLE ON
)

install(TARGETS VertexLab
    BUNDLE DESTINATION "F:\\vsproject\\VertextLab_bundle"
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

#qt_finalize_executable(VertexLab)
