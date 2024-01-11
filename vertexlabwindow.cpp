#include "vertexlabwindow.h"
#include "./ui_vertexlabwindow.h"
#include <iostream>
#include <qdialog.h>
#include <qdebug.h>
using namespace std;

VertexLabWindow::VertexLabWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::VertexLabWindow)
{
    ui->setupUi(this);

    WId wid = this->winId(); //ui->widget->winId();
    
    this->m_viewer = new Viewer(Aspect_Handle(wid));
    this->m_viewer->resizeView();

}

void VertexLabWindow::paintEvent(QPaintEvent* theEvent) {
    this->m_viewer->redrawView();
};

//! Avoids Qt standard execution of this method, do mustBeResized for V3d view, Init view if it is the first call
//! \param an event
void VertexLabWindow::resizeEvent(QResizeEvent* theEvent) {
    this->m_viewer->resizeView();
};


void VertexLabWindow::drawBottle() {
    cout << "draw a bottle.." << endl;
    /*QDialog *q = new QDialog();
    q->setWindowTitle("just  a title");
    q->show();*/
    qDebug() << this->width() << "  " << this->height();
    this->m_viewer->resizeView();
    this->m_viewer->drawBottle(this->width() / 10 * 6, this->height() / 10 * 8, this->height() / 10 * 3);
}

VertexLabWindow::~VertexLabWindow()
{
    delete ui;
}
