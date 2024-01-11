#ifndef VERTEXLABWINDOW_H
#define VERTEXLABWINDOW_H

#include <QMainWindow>
#include "casview/Viewer.h"




QT_BEGIN_NAMESPACE
namespace Ui { class VertexLabWindow; }
QT_END_NAMESPACE


class VertexLabWindow : public QMainWindow
{
    Q_OBJECT

public:
    VertexLabWindow(QWidget *parent = nullptr);
    ~VertexLabWindow();
public slots:
    void drawBottle();

public:

    virtual void paintEvent(QPaintEvent* theEvent) override;

    //! Avoids Qt standard execution of this method, do mustBeResized for V3d view, Init view if it is the first call
    //! \param an event
    virtual void resizeEvent(QResizeEvent* theEvent) override;



private:
    Ui::VertexLabWindow *ui;

    Viewer* m_viewer;
};
#endif // VERTEXLABWINDOW_H
