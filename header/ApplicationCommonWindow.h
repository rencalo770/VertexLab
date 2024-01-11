
#ifndef APPLICATION_COMMON_OVERVIEW_H
#define APPLICATION_COMMON_OVERVIEW_H

#include "BaseSample.h"
#include "CommonSample.h"
#include "DataExchangeSamples.h"
#include "DocumentCommon.h"
#include "GeometrySamples.h"
#include "GeomWidget.h"
#include "OcafSamples.h"
#include "OcctHighlighter.h"
#include "TopologySamples.h"
#include "TranslateDialog.h"
#include "TriangulationSamples.h"
#include "View.h"
#include "Viewer2dSamples.h"
#include "Viewer3dSamples.h"

#include <Standard_WarningsDisable.hxx>
#include <QApplication>
#include <QAction>
#include <QDomNode>
#include <QList>
#include <QMainWindow>
#include <QMdiArea>
#include <QMenu>
#include <QSignalMapper>
#include <QToolBar>
#include <QTextEdit>
#include <QWidget>
#include <Standard_WarningsRestore.hxx>

enum StdActions
{
    StdActions_FileQuit,
    StdActions_HelpAbout
};

enum ApplicationType
{
    AppType_Geometry,
    AppType_Topology,
    AppType_Triangulation,
    AppType_DataExchange,
    AppType_Ocaf,
    AppType_Viewer2d,
    AppType_Viewer3d,
    AppType_Unknown
};


//! Main application window
class ApplicationCommonWindow : public QMainWindow
{
    Q_OBJECT

public:
    ApplicationCommonWindow(ApplicationType theCategory);

    ApplicationType GetApplicationType() const { return myAppType; }
    void SetApplicationType(ApplicationType theApplicationType) { myAppType = theApplicationType; }

    static TCollection_AsciiString getSampleSourceDir();

protected:
    virtual DocumentCommon* createNewDocument();

public slots:
    virtual void onAbout();
    virtual void onChangeCategory(const QString& theCategory);

protected:
    QAction* CreateAction(const QString& theActionName,
        const QString& theShortcut = "",
        const QString& theIconName = "");

    template <typename PointerToMemberFunction>
    QAction* CreateSample(PointerToMemberFunction theHandlerMethod,
        const char* theActionName);

    virtual void  resizeEvent(QResizeEvent*);
    QMenu* getFilePopup() { return myFilePopup; }
    QToolBar* getCasCadeBar() { return myCasCadeBar; }

    void MenuFormXml(const QString& thePath,
        QSignalMapper* theMapper,
        QList<QMenu*>& theMunusList);
    QMenu* MenuFromDomNode(QDomElement& theItemElement,
        QWidget* theParent,
        QSignalMapper* theMapper);


private slots:
    void onCloseAllWindows() { qApp->closeAllWindows(); }

    void onProcessSample(const QString& theSampleName);
    void onProcessExchange(const QString& theSampleName);
    void onProcessOcaf(const QString& theSampleName);
    void onProcessViewer3d(const QString& theSampleName);
    void onProcessViewer2d(const QString& theSampleName);

private:

    void RebuildMenu();
    Handle(BaseSample)   GetCurrentSamples();
    const QList<QMenu*>& GetCurrentMenus();

    QString selectFileName(const QString& theSampleName, TranslateDialog* theDialog, int& theMode);
    TranslateDialog* getDataExchangeDialog(const QString& theSampleName);
    TranslateDialog* getOcafDialog(const QString& theSampleName);

private:
    ApplicationType myAppType;
    QMap<ApplicationType, QString> ALL_CATEGORIES;

    Handle(GeometrySamples)      myGeometrySamples;
    Handle(TopologySamples)      myTopologySamples;
    Handle(TriangulationSamples) myTriangulationSamples;
    Handle(DataExchangeSamples)  myDataExchangeSamples;
    Handle(OcafSamples)          myOcafSamples;
    Handle(Viewer3dSamples)      myViewer3dSamples;
    Handle(Viewer2dSamples)      myViewer2dSamples;

    QMap<StdActions, QAction*>  myStdActions;
    QMap<ApplicationType, QAction*>  myCategoryActions;
    QMap<Graphic3d_NameOfMaterial, QAction*>  myMaterialActions;

    QToolBar* myStdToolBar;
    QToolBar* myViewBar;
    QToolBar* myCasCadeBar;
    QMenu* myFilePopup;
    QMenu* myCategoryPopup;

    QList<QMenu*>    myGeometryMenus;
    QList<QMenu*>    myTopologyMenus;
    QList<QMenu*>    myTriangulationMenus;
    QList<QMenu*>    myDataExchangeMenus;
    QList<QMenu*>    myOcafMenus;
    QList<QMenu*>    myViewer3dMenus;
    QList<QMenu*>    myViewer2dMenus;

    QSignalMapper* mySampleMapper;
    QSignalMapper* myExchangeMapper;
    QSignalMapper* myOcafMapper;
    QSignalMapper* myViewer3dMapper;
    QSignalMapper* myViewer2dMapper;

    QSignalMapper* myCategoryMapper;

    QTextEdit* myCodeView;
    QTextEdit* myResultView;
    OcctHighlighter* myCodeViewHighlighter;

    GeomWidget* myGeomWidget;

    DocumentCommon* myDocument3d;
    DocumentCommon* myDocument2d;
};

#endif
