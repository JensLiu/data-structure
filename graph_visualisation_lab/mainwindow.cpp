#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QAbstractButton>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    init();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::init()
{
    selectedEdge = nullptr;
    selectedVertex = nullptr;

    ui->m_graphView->setTextEdit_adjList(ui->plainTextEdit_adjList);
    ui->m_graphView->init();

    connect(ui->btn_addVertex, &QAbstractButton::clicked, this, [=](){
        ui->m_graphView->addVertex(ui->lineEdit_vertexValue->text());
    });

    connect(ui->m_graphView, &GraphWidget::vertexSelected, this, [=](VertexItem* vertex) {
        ui->lineEdit_vertexValue->setText(QString::fromStdString(vertex->getValue()));
        ui->label_vertexValue->setText(QString::fromStdString(vertex->getValue()));
        selectedVertex = vertex;
        ui->tabWidget_vertex->setCurrentIndex(0);
    });

    connect(ui->m_graphView, &GraphWidget::edgeSelected, this, [=](EdgeItem* edge) {
        ui->label_sourceVertex->setText(QString::fromStdString(edge->sourceNode()->getValue()));
        ui->label_destVertex->setText(QString::fromStdString(edge->destNode()->getValue()));
        ui->label_edgeWeight->setText(QString::number(edge->getWeight()));
        selectedEdge = edge;
        ui->tabWidget_edge->setCurrentIndex(0);
    });

    connect(ui->btn_removeEdge, &QPushButton::clicked, ui->m_graphView, [=](){
        if (selectedEdge != nullptr) {
            ui->m_graphView->removeEdge(selectedEdge);
            selectedEdge = nullptr;
        }
    });

    connect(ui->btn_removeVertex, &QPushButton::clicked, ui->m_graphView, [=](){
        if (selectedVertex != nullptr) {
            ui->m_graphView->removeVertex(selectedVertex);
            selectedVertex = nullptr;
        }
    });

    connect(ui->btn_sourceVertexSelect, &QPushButton::clicked, this, [=](){
        if (selectedVertex) {
            ui->label_selectedSourceVertex->setText(QString::fromStdString(selectedVertex->getValue()));
        } else {
            ui->label_selectedSourceVertex->setText("select");
        }
        this->toAddSourceVertex = this->selectedVertex;
    });

    connect(ui->btn_destVertexSelect, &QPushButton::clicked, this, [=](){
        if (selectedVertex) {
            ui->label_selectedDestVertex->setText(QString::fromStdString(selectedVertex->getValue()));
        } else {
            ui->label_selectedDestVertex->setText("select");
        }
        this->toAddDestVertex = this->selectedVertex;
    });

    connect(ui->btn_addEdge, &QPushButton::clicked, ui->m_graphView, [=](){
        if (this->toAddSourceVertex && this->toAddDestVertex) {
            if (ui->doubleSpinBox_edgeWeight->hasAcceptableInput()) {
                ui->m_graphView->addEdge(toAddSourceVertex, toAddDestVertex,
                                         ui->doubleSpinBox_edgeWeight->value());
            } else {
                ui->m_graphView->addEdge(toAddSourceVertex, toAddDestVertex, 0);
            }
        }
    });

    connect(ui->btn_spSourceVertex, &QPushButton::clicked, this, [=](){
        if (selectedVertex) {
            ui->label_spSelectedSourceVertex->setText(QString::fromStdString(selectedVertex->getValue()));
        } else {
            ui->label_spSelectedSourceVertex->setText("select");
        }
        this->spSourceVertex = this->selectedVertex;
    });

    connect(ui->btn_spDestVertex, &QPushButton::clicked, this, [=](){
        if (selectedVertex) {
            ui->label_spSelectedDestVertex->setText(QString::fromStdString(selectedVertex->getValue()));
        } else {
            ui->label_spSelectedDestVertex->setText("select");
        }
        this->spDestVertex = this->selectedVertex;
    });


    connect(ui->btn_bfs, &QPushButton::clicked, ui->m_graphView, &GraphWidget::doBfs);
    connect(ui->btn_dfs, &QPushButton::clicked, ui->m_graphView, &GraphWidget::doDfs);
    connect(ui->btn_prim, &QPushButton::clicked, ui->m_graphView, &GraphWidget::doPrim);
    connect(ui->btn_kruskal, &QPushButton::clicked, ui->m_graphView, &GraphWidget::doKruskal);
    connect(ui->btn_dijkstra, &QPushButton::clicked, ui->m_graphView, [=](){
        if (this->spSourceVertex && this->spDestVertex)
            ui->m_graphView->doDijkstra(this->spSourceVertex, this->spDestVertex);
    });

}

