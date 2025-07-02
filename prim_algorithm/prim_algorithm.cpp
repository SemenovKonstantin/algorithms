#include <iostream>
#include <vector>
#include "priority_queue.h"

struct Edge
{
    public:
    int vertex_from;
    int vertex_to;
    int weight;
    Edge(int vrtx_from, int vrtx_to,int weight_) : vertex_from(vrtx_from), vertex_to(vrtx_to), weight(weight_) {}
};

std::ostream& operator<<(std::ostream &os,const Edge& edge)
{
    os << edge.vertex_from << " -> " << edge.vertex_to << ". Edge's weight equals to: " << edge.weight << "\n";
    return os;
}

struct Vertex
{
    public:
    int vrtx_id;
    std::vector<Edge> neighbours;
    Vertex(int id) : vrtx_id(id) {}
    void show_neighbours() const
    {
        int quantity = 0;
        for (const auto& neighbour : neighbours)
        {
            ++quantity;
            std::cout << quantity << ":\t" << neighbour << std::endl;
        }
    }
};

struct Graph
{
    public:
    std::vector<Vertex> adjacency_table;
    int V;
    Graph(int V_) : V(V_) 
    {
        for (int i = 0; i < V_; ++i)
        {
            adjacency_table.emplace_back(Vertex{i});
        }
    }

    void build_graph();
    void show_graph() const;
};

// Hence Prim/Kraskal algorithms are dedicated for computing min spanning tree in undirected graph
// - we should add paths between two vertices in either of them. 
void Graph::build_graph()
{
    // Vertex A(0)
    adjacency_table[0].neighbours.emplace_back(Edge{0,1,1}); // A -> B +
    adjacency_table[0].neighbours.emplace_back(Edge{0,2,8}); // A -> C +
    // Vertex B(1)
    adjacency_table[1].neighbours.emplace_back(Edge{1,2,6}); // B -> C +
    adjacency_table[1].neighbours.emplace_back(Edge{1,5,4}); // B -> G +
    adjacency_table[1].neighbours.emplace_back(Edge{1,0,1}); // B -> A +
    // Vertex C(2)
    adjacency_table[2].neighbours.emplace_back(Edge{2,3,7}); // C -> D +
    adjacency_table[2].neighbours.emplace_back(Edge{2,4,3}); // C -> E +
    adjacency_table[2].neighbours.emplace_back(Edge{2,1,6}); // C -> B +
    adjacency_table[2].neighbours.emplace_back(Edge{2,0,8}); // C -> A +
    // Vertex D(3)
    adjacency_table[3].neighbours.emplace_back(Edge{3,2,7}); // D -> C +
    adjacency_table[3].neighbours.emplace_back(Edge{3,5,5}); // D -> G +
    // Vertex E(4)
    adjacency_table[4].neighbours.emplace_back(Edge{4,5,2}); // E -> G +
    adjacency_table[4].neighbours.emplace_back(Edge{4,2,3}); // E -> C +
    // Vertex G(5)
    adjacency_table[5].neighbours.emplace_back(Edge{5,1,4}); // G -> B +
    adjacency_table[5].neighbours.emplace_back(Edge{5,4,2}); // G -> E +
    adjacency_table[5].neighbours.emplace_back(Edge{5,3,5}); // G -> D +
}

void Graph::show_graph() const
{
    for (const auto& vertex : adjacency_table)
    {
        std::cout << "Vertex ID: " <<vertex.vrtx_id << std::endl;
        vertex.show_neighbours();
    }
}

// Struct below is devoted to Edges that will be stored inside Min_Heap. Better do segregation between Edge and HeapEdge.
// They are denote diverse properties.
struct HeapEdge
{
    public:
    int vertex_from;
    int vertex_to;
    int weight;
    HeapEdge() : vertex_from(0),vertex_to(0), weight(0) {}
    HeapEdge(int vrtx_from, int vrtx_to,int weight_) : vertex_from(vrtx_from), vertex_to(vrtx_to), weight(weight_) {}
    bool operator<(const HeapEdge& other) { return this->weight < other.weight; }
    bool operator>(const HeapEdge& other) { return this->weight > other.weight; }
};

void min_spanning_tree(const Graph& graph)
{
    int starting_vertex = 5; // For specific example. Prim's algorithm can start with an arbitrary vertice.
    std::vector<bool> isVisited(graph.V,false);
    std::vector<Edge> mst;
    long long total_min = 0;
    isVisited[starting_vertex] = true;

    Priority_Queue<HeapEdge> min_heap;
    for (const auto& neighbour : graph.adjacency_table[starting_vertex].neighbours)
    {
        min_heap.insert(HeapEdge{neighbour.vertex_from,neighbour.vertex_to,neighbour.weight});
    }

    while (!min_heap.is_empty())
    {
        HeapEdge min_edge = min_heap.min_peek();
        min_heap.extract_peek();

        int u = min_edge.vertex_from;
        int v = min_edge.vertex_to;
        int weight = min_edge.weight;

        if (isVisited[v]) { continue; }

        isVisited[v] = true;
        mst.emplace_back(Edge{u,v,weight});
        total_min += weight;

        for (const auto& edge : graph.adjacency_table[v].neighbours)
        {
            min_heap.insert(HeapEdge{edge.vertex_from,edge.vertex_to,edge.weight});
        }
    }

    std::cout << "Minimum Spanning Tree (Prim's Algorithm):\n";
    for (const auto& edge : mst) {
        std::cout << edge;
    }
    std::cout << "Total weight: " << total_min << std::endl;
}

int main()
{
    Graph g(6);
    g.build_graph();
    
    g.show_graph();

    min_spanning_tree(g);

    return 0;
}