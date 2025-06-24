#include <iostream>
#include <vector>
#include <limits>
#include <stack>
#include "priority_queue.h"

constexpr int INF = std::numeric_limits<int>::max();

struct Edge {
    public:
    int vertex_destination;
    int vertex_source;
    int weight;
    Edge(int vrtx_s, int vrtx_d, int weight_) : vertex_source(vrtx_s), vertex_destination(vrtx_d), weight(weight_) {}
    // too many parameters for this operator function
};

std::ostream& operator<<(std::ostream &os, const Edge& edge) {
    os << "Source Vertex: " << edge.vertex_source << " -> " << "Dest Vertex: " << edge.vertex_destination 
              << " Edge's weight: " << edge.weight << std::endl;
    return os;
}

struct Vertex {
    public:
    int vertex_id;
    int distance;
    std::vector<Edge> neighbour_info;
    Vertex() : vertex_id(-1),distance(INF) {}
    Vertex(int vrtx_id) : vertex_id(vrtx_id), distance(0) {}
    void show_neighbours() const
    {
        int quantity = 0;
        for (const auto& neighbour : neighbour_info)
        {
            ++quantity;
            std::cout << quantity << ":\t" << neighbour << std::endl;
        }
    }
    bool operator<(const Vertex& other) { return this->distance < other.distance; }
};

struct Graph {
    public:
    int V;
    std::vector<Vertex> adjacency_table;
    Graph(int V_) : V(V_) {
        for (int i = 0; i < V_; ++i)
        {
            adjacency_table.emplace_back(Vertex{i});
        }
    }
    void build_graph();
    void show_graph() const;
};

void Graph::build_graph()
{
    adjacency_table[0].neighbour_info.emplace_back(Edge{0,1,10});
    adjacency_table[0].neighbour_info.emplace_back(Edge{0,3,30});
    adjacency_table[0].neighbour_info.emplace_back(Edge{0,4,100});
    adjacency_table[1].neighbour_info.emplace_back(Edge{1,2,50});
    adjacency_table[2].neighbour_info.emplace_back(Edge{2,4,10});
    adjacency_table[3].neighbour_info.emplace_back(Edge{3,2,20});
    adjacency_table[3].neighbour_info.emplace_back(Edge{3,4,60});    
}

void Graph::show_graph() const
{
    for (const auto& vertex : adjacency_table)
    {
        std::cout << "Vertex ID: " <<vertex.vertex_id << std::endl;
        vertex.show_neighbours();
    }
}

void dijkstra(Graph& graph, int start, int end)
{
    std::vector<unsigned int> distances(graph.V,INF);
    std::vector<int> parents(graph.V,-1);

    distances[start] = 0;

    Priority_Queue<Vertex> min_heap;

    min_heap.insert(graph.adjacency_table[start]);

    while (!min_heap.is_empty())
    {
        Vertex current = min_heap.min_peek();
        min_heap.extract_peek();

        int u = current.vertex_id;

        if (current.distance > distances[u]) { continue; }

        for (const auto& edge : graph.adjacency_table[u].neighbour_info)
        {
            // graph.adjacency_table[edge.vertex_destination].distance = current.distance + edge.weight;
            int v = edge.vertex_destination;
            int weight = edge.weight;

            if (distances[u] + weight < distances[v])
            {
                distances[v] = distances[u] + weight;
                parents[v] = u;
                graph.adjacency_table[v].distance = distances[v];
                min_heap.insert(graph.adjacency_table[v]);
            }
        }
    }

    std::cout << "Distances from vertex " << start << ":\n";
    for (int i = 0; i < graph.V; i++)
    {
        std::cout << "To vertex " << i << ": " << ((distances[i] == INF) ? "INF" : std::to_string(distances[i])) << std::endl;
    } 

    std::stack<int> order;
    for (int i = end; i != -1; i = parents[i]) {  order.push(i); }
    while (!order.empty()) 
    {
        std::cout << order.top();
        order.pop();
        if (!order.empty()) std::cout << " -> ";
    }
    std::cout << std::endl;
}

int main()
{
    Graph g(5);
    g.build_graph();
    g.show_graph();
    std::cout << "\nRunning Dijkstra's algorithm...\n";
    dijkstra(g,0,4);
    return 0;
}