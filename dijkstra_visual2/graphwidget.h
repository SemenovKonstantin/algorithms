#ifndef GRAPH_WIDGET_H
#define GRAPH_WIDGET_H

#include <QWidget>
#include <QPair>
#include <QPoint>
#include <QVector>
#include <QMap>

struct GraphWidget : public QWidget
{
private:
    Q_OBJECT; // Responsible for signals && slots.
public:
    explicit GraphWidget(QWidget* parent = nullptr);
protected:
    void keyPressEvent(QKeyEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *event) override;
private:
    struct Vertex
    {
        QPoint position;
        QString label;
        bool isSelected;
    };
    struct Edge
    {
        int vertex_from;
        int vertex_to;
        int weight;
        bool isPath = false;
    };

    QVector<Vertex> vertexs;
    QVector<Edge> edges;
    QMap<int,QVector<QPair<int,int>>> adjacency_table;

    int vertex_start = -1;
    int vertex_end = -1;
    int vertex_current = -1;
    bool isRunning = false;
    QVector<int> distances;
    QVector<int> path;
    QVector<int> visitedVertexs;


    void runDijkstra();
    void resetAlgorithm();
    void paintEdge(QPainter &painter, const Edge &edge);
    void paintVertex(QPainter &painter, const Vertex &vertex);
    int findAt(const QPoint& position);
    void updateGraph();
};

#endif // GRAPH_WIDGET_H