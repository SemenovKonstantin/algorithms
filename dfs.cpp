// DFS. Depth First Search is an algorithm.
// DFS usually implemented by stack or recursively.
// DFS algorithms are commonly used in the tasks where you need to know all vertices, getting deep to the end before returning.
// For instance: DFS is used in maze-solving algorithms. If you get into dead end you should return to the next path.

#include <iostream>
#include <vector>
#include <stack>

struct Graph
{
    private:
    unsigned int V; // stands for Vertices
    std::vector<std::vector<int>> adjacency_table;
    std::vector<bool> is_visited_recursive; // [false,false,fale,false,false]

    public:
    Graph(unsigned int V_) : V(V_), adjacency_table(V_), is_visited_recursive(V_,false) {}
    
    // Let us assume we have an undericted graph.
    void make_bind(int first_node, int second_node)
    {
        adjacency_table[first_node].emplace_back(second_node);
        adjacency_table[second_node].emplace_back(first_node);
    }

    // Instance: start with vertex: 0
    void depth_first_search(int embarking_node)
    {
        std::stack<int> stack;
        std::vector<bool> is_visited(V,false); // [false,false,fale,false,false]

        stack.push(embarking_node);
        is_visited[embarking_node] = true; // [true,false,fale,false,false]

        while (!stack.empty())
        {
            int value = stack.top(); 
            stack.pop();
            std::cout << value << "\t";
            // Check adjacency table for each node where neighbours of nodes are stored.
            // But in stack we would add them in the reverse order.
            for (auto it = adjacency_table[value].rbegin(); it != adjacency_table[value].rend(); it++)
            {
                if (!is_visited[*it])
                {
                    stack.push(*it);
                    is_visited[*it] = true;
                }
            }
        }

        std::cout << std::endl;
    }

    // Instance: start with vertex: 0
    void depth_first_search_recursive(int embarking_node)
    {
        std::cout << embarking_node << '\t';

        is_visited_recursive[embarking_node] = true;

        // Adjacency table: 1 && 2
        for (const auto& it : adjacency_table[embarking_node])
        {
            if (!is_visited_recursive[it])
                depth_first_search_recursive(it);
        }
    }
};

int main()
{
    Graph graph(11); // From 0 to 10 inclusively
    
    graph.make_bind(0,1);
    graph.make_bind(0,2);
    graph.make_bind(1,3);
    graph.make_bind(1,4);
    graph.make_bind(2,5);
    graph.make_bind(2,6);
    graph.make_bind(3,7);
    graph.make_bind(4,8);
    graph.make_bind(5,9);
    graph.make_bind(6,10);

    graph.depth_first_search(0);

    graph.depth_first_search_recursive(0);

    //          0            stack:     stack:     stack:    stack:     stack:    stack:    stack:      stack:   stack:     stack:
    //       /      \           
    //      1        2
    //    /    \    /  \  ->        ->          ->        ->        ->         ->        ->         ->        ->        ->      
    //   3     4   5    6                            3          7               
    //  /     /   /    /                   1         4          4          4        8                    5          9
    // 7     8   9    10       0           2         2          2          2        2         2          6          6          6                


    // Output:                 0           1         3          7          4        8         2          5          9          6 

    // Result: 0 1 3 7 4 8 2 5 9 6 10
    
    return 0;
}