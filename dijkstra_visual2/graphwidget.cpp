#include "graphwidget.h"
#include <QPainter>
#include <QMessageBox>
#include <QMouseEvent>
#include <limits>
#include <QThread>
#include <QApplication>

constexpr int NODE_RADIUS = 20;
constexpr int INF  =std::numeric_limits<int>::max();

GraphWidget::GraphWidget(QWidget *parent) : QWidget(parent)
{
    vertexs.append({QPoint(100,100),"A",false});
    vertexs.append({QPoint(300,100),"B",false});
    vertexs.append({QPoint(100, 300), "C",false});
    vertexs.append({QPoint(300, 300), "D",false});
    vertexs.append({QPoint(500, 200), "E",false});

    edges.append({0,1,4});
    edges.append({0,2,1});
    edges.append({1, 3, 1});
    edges.append({2, 1, 2});
    edges.append({2, 3, 5});
    edges.append({3, 4, 3});

    updateGraph();
}

void GraphWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    for (const Edge& edge : edges)
    {
        GraphWidget::paintEdge(painter,edge);
    }

    for (const Vertex& vertex : vertexs)
    {
        GraphWidget::paintVertex(painter,vertex);
    }

    painter.setPen(Qt::black);
    for (int i = 0; i < vertexs.size(); ++i) {
        QString distText = distances.size() > i ?
                               (distances[i] == INF ? "∞" : QString::number(distances[i])) : "";
        painter.drawText(vertexs[i].position.x() - NODE_RADIUS,
                         vertexs[i].position.y() - NODE_RADIUS - 5,
                         distText);
    }
    painter.drawText(10,20,"Firstly you should click on the starting vertex, secondly on the ending vertex. Press Enter to jumpstart the engine!");
}

void GraphWidget::paintVertex(QPainter &painter, const Vertex& vertex)
{
    QColor color = Qt::lightGray;

    int index = -1;
    for (int i = 0; i < vertexs.size(); ++i) {
        if (&vertex == &vertexs[i]) {
            index = i;
            break;
        }
    }

    if (vertex.isSelected)
        color = Qt::green;
    else if (visitedVertexs.contains(index))
        color = Qt::yellow;
    else if (vertex_current == index)
        color = Qt::blue;


    painter.setBrush(color);
    painter.setPen(Qt::black);
    painter.drawEllipse(vertex.position,NODE_RADIUS,NODE_RADIUS);

    painter.drawText(vertex.position.x() - 5,vertex.position.y() + 5, vertex.label);
}

void GraphWidget::paintEdge(QPainter &painter, const Edge& edge)
{
    QPoint from = vertexs[edge.vertex_from].position;
    QPoint to = vertexs[edge.vertex_to].position;

    QPen pen(Qt::black);

    if (edge.isPath)
    {
        pen.setColor(Qt::red);
        pen.setWidth(2);
    }

    painter.setPen(pen);

    painter.drawLine(from,to);

    QPoint mid = (from + to) / 2;

    painter.drawText(mid,QString::number(edge.weight));
}

void GraphWidget::mousePressEvent(QMouseEvent *event)
{
    if (isRunning) return;

    int index = findAt(event->pos());

    if (index == -1) return;

    if (vertex_start == -1)
    {
        vertex_start = index;
        vertexs[index].isSelected = true;
    }

    if (index != vertex_start && vertex_end == -1)
    {
        vertex_end = index;
        vertexs[index].isSelected = true;
    }

    update();
}

void GraphWidget::keyPressEvent(QKeyEvent *event)
{
    if ((event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return)
        && vertex_start != -1 && vertex_end != -1 && !isRunning)
    {
        isRunning = true;
        runDijkstra();
    }
    else if (event->key() == Qt::Key_R)
    {
        resetAlgorithm();
    }

    update();
}

int GraphWidget::findAt(const QPoint &point)
{
    for (int i = 0; i < vertexs.size(); ++i)
    {
        if (QVector2D(point - vertexs[i].position).length() <= NODE_RADIUS)
        {
            return i;
        }
    }

    return -1;
}

void GraphWidget::runDijkstra()
{
    if (vertexs.empty() || edges.empty()) {
        QMessageBox::warning(this, "Ошибка", "Граф не содержит вершин или ребер");
        isRunning = false;
        return;
    }

    distances.fill(INF,vertexs.size());
    distances[vertex_start] = 0;

    QVector<int> parents(vertexs.size(),-1);
    QVector<bool> isVisited(vertexs.size(),false);

    for (int i = 0; i < vertexs.size(); ++i)
    {
        int u = -1;
        for (int j = 0; j < vertexs.size(); ++j) {
            if (!isVisited[j] && (u == -1 || distances[j] < distances[u])) {
                u = j;
            }
        }

        if (u == -1 && distances[u] == INF) break;

        isVisited[u] = true;
        visitedVertexs.append(u);

        vertex_current = u;

        update();
        QApplication::processEvents();
        QThread::msleep(4000);

        for (const auto& edge : adjacency_table[u])
        {
            int v = edge.first;
            int weight = edge.second;

            if (distances[v] > weight + distances[u])
            {
                distances[v] = weight + distances[u];
                parents[v] = u;
            }
        }
    }

    for (int v = vertex_end; v != -1; v = parents[v])
    {
        path.prepend(v);
    }

    for (int i = 0; i < path.size() - 1; ++i) {
        int from = path[i];
        int to = path[i+1];

        for (Edge &edge : edges) {
            if ((edge.vertex_from == from && edge.vertex_to == to) ||
                (edge.vertex_from == to && edge.vertex_to == from))
            {
                edge.isPath = true;
                break;
            }
        }
    }

    isRunning = false;
    update();
}

void GraphWidget::resetAlgorithm()
{
    vertex_start = -1;
    vertex_end = -1;
    vertex_current = -1;
    isRunning = false;
    visitedVertexs.clear();
    distances.clear();
    path.clear();

    for (Edge &edge : edges)
    {
        edge.isPath = false;
    }

    for (Vertex &vertex: vertexs)
    {
        vertex.isSelected = false;
    }

    update();
}

void GraphWidget::updateGraph()
{
    adjacency_table.clear();

    for (const Edge& edge : edges)
    {
        adjacency_table[edge.vertex_from].append({edge.vertex_to,edge.weight});
    }
}