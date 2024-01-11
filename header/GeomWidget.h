
#ifndef GEOMWIDGET_H
#define GEOMWIDGET_H

#include "View.h"
#include "DocumentCommon.h"

#include <Standard_WarningsDisable.hxx>
#include <QWidget>
#include <Standard_WarningsRestore.hxx>

class ApplicationCommon;
class QStackedWidget;

//! Qt widget for organize 3D & 2D documents
class GeomWidget : public QWidget
{
    Q_OBJECT
public:
    GeomWidget(DocumentCommon* theDocument3d,
        DocumentCommon* theDocument2d,
        QWidget* theParent = nullptr);

    void FitAll();

    Handle(V3d_View) Get3dView() { return myView3d->getView(); }

    Handle(V3d_View) Get2dView() { return myView2d->getView(); }

    void Show3d();
    void Show2d();

private:
    View* myView3d;
    View* myView2d;

    QWidget* my3dVidget;
    QWidget* my2dVidget;
    QStackedWidget* myStackWidget;

    DocumentCommon* myDocument3d;
    DocumentCommon* myDocument2d;
};

#endif //GEOMWIDGET_H
