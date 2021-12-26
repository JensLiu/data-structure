/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "graphwidget.h"
#include "edgeitem.h"

#include <math.h>

#include <QKeyEvent>
#include <QRandomGenerator>
#include <QDebug>
#include <QThread>
#include <QApplication>
//! [0]
GraphWidget::GraphWidget(QWidget *parent)
    : QGraphicsView(parent), timerId(0)
{
    QGraphicsScene *scene = new QGraphicsScene(this);
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);
    scene->setSceneRect(-200, -200, 400, 400);
    setScene(scene);
    setCacheMode(CacheBackground);
    setViewportUpdateMode(BoundingRectViewportUpdate);
    setRenderHint(QPainter::Antialiasing);
    setTransformationAnchor(AnchorUnderMouse);
    scale(qreal(2), qreal(2));
//    setMinimumSize(400, 400);
//! [0]

//! [1]
}
//! [1]

VertexItem* GraphWidget::addVertex(QString value)
{
    VertexItem* newVertex = new VertexItem(this, value.toStdString());
    scene()->addItem(newVertex);
    newVertex->setPos(-50, -50);
    Graph<VertexItem*, EdgeItem*>::addVertex(newVertex);
    this->printAdjList();
    showAdjList();
    return newVertex;
}

EdgeItem *GraphWidget::addEdge(VertexItem *source, VertexItem *dest, const double& weight)
{
    EdgeItem* newEdge = new EdgeItem(source, dest, weight);
    Graph<VertexItem*, EdgeItem*>::addEdge(source, dest, newEdge, weight);
    scene()->addItem(newEdge);
    this->printAdjList();
    showAdjList();
    return newEdge;
}

void GraphWidget::removeEdge(EdgeItem *edge)
{
    scene()->removeItem(edge);
    Graph<VertexItem*, EdgeItem*>::removeEdge(edge->sourceNode(), edge->destNode());
    showAdjList();
    this->printAdjList();
}

void GraphWidget::removeVertex(VertexItem *vertex)
{
    scene()->removeItem(vertex);
    std::vector<Edge<EdgeItem*>> removedEdges = Graph<VertexItem*, EdgeItem*>::removeVertex(vertex);
    for (Edge<EdgeItem*> edge : removedEdges) {
        scene()->removeItem(edge.info);
    }
    showAdjList();
    this->printAdjList();
}

void GraphWidget::doDfs()
{
    std::vector<Edge<EdgeItem*>> edges = Graph<VertexItem*, EdgeItem*>::dfs();
    demonstrate(edges);
}

void GraphWidget::doBfs()
{
    std::vector<Edge<EdgeItem*>> edges = Graph<VertexItem*, EdgeItem*>::bfs();
    demonstrate(edges);
}

void GraphWidget::doPrim()
{
    std::vector<Edge<EdgeItem*>> edges = Graph<VertexItem*, EdgeItem*>::prim();
    demonstrate(edges);
}

void GraphWidget::doKruskal()
{
    std::vector<Edge<EdgeItem*>> edges = Graph<VertexItem*, EdgeItem*>::kruskal();
    demonstrate(edges);
}

void GraphWidget::doDijkstra(VertexItem* source, VertexItem* dest)
{
    using ResultSet = std::vector<std::vector<Edge<EdgeItem*>>>;
    using EachResult = std::vector<Edge<EdgeItem*>>;
    using ThisGraph = Graph<VertexItem*, EdgeItem*>;
    using Edge = Edge<EdgeItem*>;
    ResultSet results = ThisGraph::dijkstra(ThisGraph::idOfVertex(source));


    int done = 0;
    for (int i = 0; !done && i < results.size(); i++) {
        for (int j = 0; !done && j < results[i].size(); j++) {
            if (results[i][j].info->destNode() == dest) {
                demonstrate(results[i], j);
                done = 1;
            }
        }
    }

}

void GraphWidget::demonstrate(std::vector<Edge<EdgeItem*>> edges, int end) {
    for (int i = 0; i <= end; i++) {
        Edge<EdgeItem*> edge = edges[i];
        edge.info->setVisited(true);
        this->vertexMap[edge.destId]->setVisited(true);
        this->vertexMap[edge.sourceId]->setVisited(true);
        vertexMap[edge.destId]->update();
        vertexMap[edge.sourceId]->update();
        edge.info->update();
        QApplication::processEvents();
        QThread::sleep(1);
    }
    for (int i = 0; i <= end; i++) {
        Edge<EdgeItem*> edge = edges[i];
        edge.info->setVisited(false);
        this->vertexMap[edge.destId]->setVisited(false);
        this->vertexMap[edge.sourceId]->setVisited(false);
        vertexMap[edge.destId]->update();
        vertexMap[edge.sourceId]->update();
        edge.info->update();
    }
}

void GraphWidget::demonstrate(std::vector<Edge<EdgeItem*>> edges)
{
    for (Edge<EdgeItem*> edge : edges) {
        edge.info->setVisited(true);
        this->vertexMap[edge.destId]->setVisited(true);
        this->vertexMap[edge.sourceId]->setVisited(true);
        vertexMap[edge.destId]->update();
        vertexMap[edge.sourceId]->update();
        edge.info->update();
        QApplication::processEvents();
        QThread::sleep(1);
    }
    for (Edge<EdgeItem*> edge : edges) {
        edge.info->setVisited(false);
        this->vertexMap[edge.destId]->setVisited(false);
        this->vertexMap[edge.sourceId]->setVisited(false);
        vertexMap[edge.destId]->update();
        vertexMap[edge.sourceId]->update();
        edge.info->update();
    }
}

void GraphWidget::showAdjList()
{
    std::vector<ListEntry<EdgeItem*>>vlist = adjList.srcList;
    QString text;
    QTextStream ts(&text);
    ts << "[\n";
    for (int i = 0; i < vlist.size(); i++) {
        ts << "((id=" << i << ", src=" << QString::fromStdString(vertexMap[i]->getValue()) << "), [";
        EdgeNode<EdgeItem*>* p = vlist[i].destListHead;
        while (p != nullptr) {
            ts << "(id=" << p->destId << ", dest=" << QString::fromStdString(vertexMap[p->destId]->getValue())
                    << ", w=" << p->weight << "), ";
            p = p->next;
        }
        ts << "]), \n";
    }
    ts << "]\n";
    lineEdit_adjList->clear();
    lineEdit_adjList->insertPlainText(text);
}

void GraphWidget::setTextEdit_adjList(QPlainTextEdit *textEdit)
{
    this->lineEdit_adjList = textEdit;
}

void GraphWidget::init()
{
    VertexItem *node0 = addVertex("A");
    VertexItem *node1 = addVertex("B");
    VertexItem *node2 = addVertex("C");
    VertexItem *node3 = addVertex("D");
    VertexItem *node4 = addVertex("E");
    VertexItem *node5 = addVertex("F");
    VertexItem *node6 = addVertex("G");
    addEdge(node0, node1, 4);
    addEdge(node0, node2, 6);
    addEdge(node0, node3, 6);
    addEdge(node1, node4, 7);
    addEdge(node1, node2, 1);
    addEdge(node2, node4, 6);
    addEdge(node2, node5, 4);
    addEdge(node3, node2, 2);
    addEdge(node3, node5, 5);
    addEdge(node4, node6, 6);
    addEdge(node5, node4, 1);
    addEdge(node5, node6, 8);

    // backward
    addEdge(node1, node0, 4);
    addEdge(node2, node0, 6);
    addEdge(node3, node0, 6);
    addEdge(node4, node1, 7);
    addEdge(node2, node1, 1);
    addEdge(node4, node2, 6);
    addEdge(node5, node2, 4);
    addEdge(node2, node3, 2);
    addEdge(node5, node3, 5);
    addEdge(node6, node4, 6);
    addEdge(node4, node5, 1);
    addEdge(node6, node5, 8);
    node0->setPos(-50, -50);
    node1->setPos(0, -50);
    node2->setPos(50, -50);
    node3->setPos(-50, 0);
    node4->setPos(50, 0);
    node5->setPos(-50, 50);
    node6->setPos(0, 50);

    connect(scene(), &QGraphicsScene::selectionChanged, this, [=](){
        QList<QGraphicsItem*> items = scene()->selectedItems();
        if (!items.empty()) {
            if (VertexItem* vertex = dynamic_cast<VertexItem*>(items.at(0))) {
                emit vertexSelected(vertex);
            } else if (EdgeItem* edge = dynamic_cast<EdgeItem*>(items.at(0))) {
                emit edgeSelected(edge);
            }
        }
    });

}

//! [2]
void GraphWidget::itemMoved()
{
    if (!timerId)
        timerId = startTimer(1000 / 25);
}
//! [2]

//! [3]
void GraphWidget::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Up:
        centerNode->moveBy(0, -20);
        break;
    case Qt::Key_Down:
        centerNode->moveBy(0, 20);
        break;
    case Qt::Key_Left:
        centerNode->moveBy(-20, 0);
        break;
    case Qt::Key_Right:
        centerNode->moveBy(20, 0);
        break;
    case Qt::Key_Plus:
        zoomIn();
        break;
    case Qt::Key_Minus:
        zoomOut();
        break;
    case Qt::Key_Space:
    case Qt::Key_Enter:
        shuffle();
        break;
    default:
        QGraphicsView::keyPressEvent(event);
    }
}
//! [3]

//! [4]
void GraphWidget::timerEvent(QTimerEvent *event)
{
    Q_UNUSED(event);

    QList<VertexItem *> nodes;
    foreach (QGraphicsItem *item, scene()->items()) {
        if (VertexItem *node = qgraphicsitem_cast<VertexItem *>(item))
            nodes << node;
    }

    foreach (VertexItem *node, nodes)
        node->calculateForces();

    bool itemsMoved = false;
    foreach (VertexItem *node, nodes) {
        if (node->advancePosition())
            itemsMoved = true;
    }

    if (!itemsMoved) {
        killTimer(timerId);
        timerId = 0;
    }
}
//! [4]

#if QT_CONFIG(wheelevent)
//! [5]
void GraphWidget::wheelEvent(QWheelEvent *event)
{
    scaleView(pow((double)2, -event->delta() / 240.0));
}
//! [5]
#endif

//! [6]
void GraphWidget::drawBackground(QPainter *painter, const QRectF &rect)
{
    Q_UNUSED(rect);

    // Shadow
    QRectF sceneRect = this->sceneRect();
//    QRectF rightShadow(sceneRect.right(), sceneRect.top() + 5, 5, sceneRect.height());
//    QRectF bottomShadow(sceneRect.left() + 5, sceneRect.bottom(), sceneRect.width(), 5);
//    if (rightShadow.intersects(rect) || rightShadow.contains(rect))
//        painter->fillRect(rightShadow, Qt::darkGray);
//    if (bottomShadow.intersects(rect) || bottomShadow.contains(rect))
//        painter->fillRect(bottomShadow, Qt::darkGray);

    // Fill
//    QLinearGradient gradient(sceneRect.topLeft(), sceneRect.bottomRight());
//    gradient.setColorAt(0, Qt::white);
//    gradient.setColorAt(1, Qt::lightGray);
//    painter->fillRect(rect.intersected(sceneRect), gradient);
//    painter->setBrush(Qt::NoBrush);
//    painter->drawRect(sceneRect);

    QFont font = painter->font();
    font.setBold(true);
    font.setPointSize(14);
    painter->setFont(font);
    painter->setPen(Qt::lightGray);
    painter->setPen(Qt::black);
}
//! [6]

//! [7]
void GraphWidget::scaleView(qreal scaleFactor)
{
    qreal factor = transform().scale(scaleFactor, scaleFactor).mapRect(QRectF(0, 0, 1, 1)).width();
    if (factor < 0.07 || factor > 100)
        return;

    scale(scaleFactor, scaleFactor);
}
//! [7]

void GraphWidget::shuffle()
{
    foreach (QGraphicsItem *item, scene()->items()) {
        if (qgraphicsitem_cast<VertexItem *>(item))
            item->setPos(-150 + QRandomGenerator::global()->bounded(300), -150 + QRandomGenerator::global()->bounded(300));
    }
}

void GraphWidget::zoomIn()
{
    scaleView(qreal(1.2));
}

void GraphWidget::zoomOut()
{
    scaleView(1 / qreal(1.2));
}
