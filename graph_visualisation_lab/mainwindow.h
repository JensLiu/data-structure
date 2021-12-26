#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "vertexitem.h"
#include "edgeitem.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void init();

private:
    Ui::MainWindow *ui;
    VertexItem* selectedVertex = nullptr;
    EdgeItem* selectedEdge = nullptr;

    VertexItem* toAddSourceVertex = nullptr;
    VertexItem* toAddDestVertex = nullptr;

    VertexItem* spSourceVertex = nullptr;
    VertexItem* spDestVertex = nullptr;

};
#endif // MAINWINDOW_H
