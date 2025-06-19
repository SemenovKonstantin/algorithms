// BFS. Breadth First Search is an wave's type algorithm. With BFS you can find shortcut for unweight roads.
// BFS usually implemented by queue ( FIFO ).
// Algorithm used by a lot in everywhere: "You might know them: [list of possible friends (friends of your friends)]" and etc. 
// Time Complexity equals to 0(V + E) where V represents vertices and E represents edges.

//           A
//        /     \
//      B        C          =>   A B C D E K F
//    /   \     /  \ 
//   D     E   K    F


#include <iostream>
#include <vector>
#include <queue>

struct Graph
{
    private:
    unsigned int E;
    std::vector<std::vector<int>> adjacency_table;
    // Adjacency table represents itself an list of each and every node with their neighbbours.
    // Instance:    [A] -> [B,C]
    //              [B] -> [D E]
    public:
    Graph(unsigned int E_) : E(E_), adjacency_table(E_) {}

    // Let us assume we have an undirected graph. If we have a road from A to B it means we can go backwards from B to A. 
    void make_bind(int first_node,int second_node)
    {
        adjacency_table[first_node].emplace_back(second_node);
        adjacency_table[second_node].emplace_back(first_node);
    }

    void breadth_first_search(int embarkinng_node)
    {
        std::vector<bool> visited(E,false);
        std::queue<int> q;
        q.push(embarkinng_node);
        visited[embarkinng_node] = true;
        
        while (!q.empty())
        {
            int value = q.front();
            q.pop();

            std::cout << value << '\t';

            for (const auto& it : adjacency_table[value])
            {
                if (visited[it] != true)
                {
                    q.push(it);
                    visited[it] = true;
                }
            }
        }

        std::cout << std::endl;
    }
};


int main()
{
    Graph graph{11}; // From 0 to 10 inclusively

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
 
    graph.breadth_first_search(0);


    //          0
    //       /      \
    //      1        2
    //    /    \    /  \  -> Breadth : 0 1 2 3 4 5 6 7 8 9 10
    //   3     4   5    6
    //  /     /   /    /
    // 7     8   9    10

    return 0;
}