// Kruskal's algorithm is used to compute MST. This algorithm uses a DSU for this purpose.
// DSU signifies Disjoint Set Union.

#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

struct Edge 
{
    public:
    int vertex_from;
    int vertex_to;
    int weight;
    Edge (int vrtx_from, int vrtx_to,int weight_) : vertex_from(vrtx_from), vertex_to(vrtx_to), weight(weight_) {}
    bool operator<(const Edge& other) { return this->weight < other.weight; }
};

std::ostream& operator<<(std::ostream& os, const Edge& edge) {
    os << edge.vertex_from << " -> " << edge.vertex_to << ". Weight: " << edge.weight << '\n';
    return os;
}

struct DSU {
    public:
    std::vector<int> parent;
    std::vector<int> rank;
    DSU(int vertices) : parent(vertices), rank(vertices,0) 
    {
        for (int i = 0; i < vertices; i++) {
            parent[i] = i; // Firstly, each vertex belongs to his own set. Hence, the parent of vertex is a vertex itself.
            // Inside constructor it have been already created an implementation of make_set().
        }
    }

    int find_parent(int current_vertex)
    {
        assert(current_vertex >= 0 && current_vertex != parent.size());
        if (parent[current_vertex] != current_vertex)
            parent[current_vertex] = find_parent(parent[current_vertex]);
        return parent[current_vertex];
    }

    void make_union(int u, int v)
    {
        int a = find_parent(u);
        int b = find_parent(v);

        // If vertex U and vertex V don't belong to the same set - we have ability to unite them.
        // Otherwise, if they already in the same set we cannot unite them because of the loop which will be performed.
        if (a != b) {
            if (rank[a] > rank[b])
                parent[b] = a;
            else if (rank[a] < rank[b])
                parent[a] = b;
            else {
                parent[b] = a;
                rank[a]++;
            }
        }
    }
};

void kruskal(const std::vector<std::vector<Edge>> &graph) {

    // First Step: do edge's sorting.

    std::vector<Edge> all_edges;
    for (const auto& vertex : graph) {
        for (const Edge &edge : vertex) {
            if (edge.vertex_from <= edge.vertex_to) { all_edges.emplace_back(edge); }
        }
    }

    // for (const auto& it : all_edges)
    // {
    //     std::cout << it << std::endl;
    // }
    std::sort(all_edges.begin(), all_edges.end());
    // for (const auto& it : all_edges)
    // {
    //     std::cout << it << std::endl;
    // }

    // Second Step: operate DSU.

    std::vector<Edge> mst;
    DSU dsu(graph.size());
    int total_weight = 0;

    for (const Edge& edge : all_edges)
    {
        if (dsu.find_parent(edge.vertex_from) != dsu.find_parent(edge.vertex_to))
        {
            dsu.make_union(edge.vertex_from,edge.vertex_to);
            total_weight+=edge.weight;
            mst.emplace_back(edge);
        }
    }

    std::cout << "Minimal Spanning Tree using Kruskal's algorithm" << std::endl;
    for (const auto& edge : mst) {
        std::cout << edge;
    }
    std::cout << "Total weight equals to: " << total_weight << std::endl;
}

int main()
{
    std::vector<std::vector<Edge>> graph = 
    {
        {Edge(0, 1, 1), Edge(0, 2, 8)}, // Vertex 0 (A)
        {Edge(1, 0, 1), Edge(1, 2, 6), Edge(1, 5, 4)}, // Vertex 1 (B)
        {Edge(2, 0, 8), Edge(2, 1, 6), Edge(2, 3, 7), Edge(2, 4, 3)}, // Vertex 2 (C)
        {Edge(3, 2, 7), Edge(3, 5, 5)}, // Vertex 3 (D)
        {Edge(4, 2, 3), Edge(4, 5, 2)}, // Vertex 4 (E)
        {Edge(5, 1, 4), Edge(5, 4, 2), Edge(5, 3, 5)} // Vertex 5 (G)
    };

    kruskal(graph);

    return 0;
}


