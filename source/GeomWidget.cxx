
#include "../header/GeomWidget.h"

#include <Standard_WarningsDisable.hxx>
#include <QFrame>
#include <QBoxLayout>
#include <QTextEdit>
#include <QStackedLayout>
#include <QToolBar>
#include <QStackedWidget>
#include <Standard_WarningsRestore.hxx>

GeomWidget::GeomWidget(DocumentCommon* theDocument3d,
    DocumentCommon* theDocument2d,
    QWidget* theParent)
    : QWidget(theParent),
    myDocument3d(theDocument3d),
    myDocument2d(theDocument2d)
{
    QVBoxLayout* aMainLayout = new QVBoxLayout(this);
    aMainLayout->setContentsMargins(0, 0, 0, 0);

    my2dVidget = new QWidget;
    QVBoxLayout* a2dLayout = new QVBoxLayout(my2dVidget);
    a2dLayout->setContentsMargins(0, 0, 0, 0);
    a2dLayout->setSpacing(0);
    myView2d = new View(myDocument2d->getContext(), false, my2dVidget);
    QToolBar* aToolBar2d = new QToolBar;
    aToolBar2d->addActions(myView2d->getViewActions());
    a2dLayout->addWidget(aToolBar2d);
    a2dLayout->addWidget(myView2d);

    my3dVidget = new QWidget;
    QVBoxLayout* a3dLayout = new QVBoxLayout(my3dVidget);
    a3dLayout->setContentsMargins(0, 0, 0, 0);
    a3dLayout->setSpacing(0);
    myView3d = new View(myDocument3d->getContext(), true, my3dVidget);
    QToolBar* aToolBar3d = new QToolBar;
    aToolBar3d->addActions(myView3d->getViewActions());
    aToolBar3d->addSeparator();
    aToolBar3d->addActions(myView3d->getRaytraceActions());
    a3dLayout->addWidget(aToolBar3d);
    a3dLayout->addWidget(myView3d);

    myStackWidget = new QStackedWidget(this);
    aMainLayout->addWidget(myStackWidget);
    myStackWidget->addWidget(my2dVidget);
    myStackWidget->addWidget(my3dVidget);

    FitAll();
}

void GeomWidget::FitAll()
{
    if (myDocument2d->IsEmpty())
        Show3d();
    else
        Show2d();
}

void GeomWidget::Show3d()
{
    myView3d->axo();//代表坐标轴展示方向
    myView3d->fitAll(); 
    QAction* aShadingAction = myView3d->getViewAction(ViewAction_Shading);
    aShadingAction->trigger();
    aShadingAction->setChecked(true);
    QAction* aHlrOffAction = myView3d->getViewAction(ViewAction_HlrOff);
    aHlrOffAction->trigger();
    aHlrOffAction->setChecked(true);
    myStackWidget->setCurrentWidget(my3dVidget);
    setStatusTip("Mouse buttons: Right-Zoom, Middle-Pan, Left-Rotate");
}

void GeomWidget::Show2d()
{
    myView2d->fitAll();
    myStackWidget->setCurrentWidget(my2dVidget);
    setStatusTip("Mouse buttons: Right-Zoom, Middle-Pan");
}
