// A binary heap is commonly used to implement a priority queue ( abstract data type ).
// There are two types of binary heaps: max_heap (root = max_node), min_heap (root = min_node).
// Binary heaps are efficient when you want to retrieve max/min element.
// It takes constant time O(1) to see max/min value in tree. However, if you want to delete max/min node or insert a new node
// you should do sifting and it take O (log n).
// Typically stored as an array for memory efficiency.

#include <iostream>

struct Max_Heap
{
    private:
    size_t capacity;
    size_t size;
    int* heap_array;

    int left_child(int index) { return 2 * index + 1; }

    int right_child(int index) {  return 2 * index + 2; }

    int parent(int index) {  return (index - 1) / 2; }

    size_t get_size() {  return size;  }

    void print_heap() const
    {
        std::cout << "[\t";
        for (int i = 0; i < size; i++)
        {
            std::cout << heap_array[i] << "\t";
        }
        std::cout << "]" << std::endl;
    }

    // Sifting up is used when you are inserting a new element inside a heap. To maintain proper logic should use sift_up().
    //          40                          40
    //        /     \                     /     \ 
    //      30      21        ->        30      38
    //    /   \    /   \               /  \    /  \ 
    //  12    6   18    38            12   6  18   21
    //
    //  40 30 21 12 6 18 38   ->   40 30 38 12 6 18 21

    void sift_up(int index)
    {
        std::cout << std::endl;

        std::cout << "Sift up!\t" << "Starting to sift from a node with index:\t" << index << std::endl;
        
        while (index > 0 && heap_array[parent(index)] < heap_array[index])
        {
            std::cout << "Compare heap_array[" << index << "],\t with priority equals to\t" << heap_array[index] << std::endl;
            std::cout << "With parent of that node heap_array[" << parent(index) << "],\t with priority equals to\t" << heap_array[parent(index)] << std::endl; 
            
            std::cout << "Change a parent with his child." << std::endl;
            std::swap(heap_array[parent(index)],heap_array[index]);

            index = parent(index);

            std::cout << "New index equals to:\t" << index << std::endl;
            
            print_heap();
        } 

        std::cout << "Sifting up is over! Heap in the right order!" << std::endl;
        print_heap();

        std::cout << std::endl;

    }

    //          40                          18                        18                         30
    //        /     \                     /     \                   /    \                     /     \ 
    //      30      21        ->        30      21          ->    30   21           ->      18      21 
    //    /   \    /   \               /  \    /  \              /  \                        /  \ 
    //  12    6   18                  12   6  40                12   6                       12   6
    //
    //  40 30 21 12 6 18      ->   40 30 38 12 6 18 21  ->   18 30 21 12 6 (Violation!)   ->    30 18 21 12 6 

    void sift_down(int index)
    {
        std::cout << std::endl;
        std::cout << "Sift down!\t" << "Starting to sift from a node with index:\t" << index << std::endl;
        int max_index = index;
        int left = left_child(index);
        int right = right_child(index);

        //Compare with a left-child of the node
        while (left < size && heap_array[left] > heap_array[max_index])
        {
            std::cout << "Compare heap_array[" << index << "],\t with priority equals to\t" << heap_array[index] << std::endl;
            std::cout << "With left child: heap_array[" << left << "],\t with priority equals to\t" << heap_array[left] << std::endl; 
            max_index = left;
        }

        //Compare with a right-child of the node
        while (right < size && heap_array[right] > heap_array[max_index])
        {
            std::cout << "Compare heap_array[" << index << "],\t with priority equals to\t" << heap_array[index] << std::endl;
            std::cout << "With right child: heap_array[" << right << "],\t with priority equals to\t" << heap_array[right] << std::endl; 
            max_index = right;
        }

        if (max_index != index)
        {
            std::cout << "Change a parent with his child." << std::endl;
            std::swap(heap_array[max_index],heap_array[index]);
            sift_down(max_index);
        }
        else 
        {
            std::cout << "Heap is over!" << std::endl;
            print_heap();
        }
        
        std::cout << std::endl;

    }

    public:
    Max_Heap(size_t capacity_) : capacity(capacity_)
    {
        size = 0;
        heap_array = new int[capacity];
    }

    void insert(int priority)
    {
        heap_array[size] = priority;
        size++;
        std::cout << "Before sifting up!" << std::endl;
        print_heap();
        std::cout << "After sifting up!" << std::endl;
        sift_up(size - 1);
    }

    int peek()
    {
        return heap_array[0];
    }

    // Main difference between method below and above is: in peek() we merely access the max element.
    // In extract_peek() we extract max element and delete it. Hence to maintain proper logic of binary heap - do sift_down().
    void extract_peek()    
    {
        std::cout << std::endl;

        std::swap(heap_array[0],heap_array[size-1]); // Exchange the max element with last insrted element for maintain easier logic.
     
        print_heap();
     
        int *old_heap_array = new int[size]; // Create a new array in order to store previous array
        
        for (int i = 0; i < size; i++)
        {
            old_heap_array[i] = heap_array[i];
        }
        
        delete[] heap_array;
        size--;

        for (int i = 0; i < size; i++)
        {
            heap_array[i] = old_heap_array[i];
        }

        delete[] old_heap_array;

        old_heap_array = nullptr;
    
        std::cout << "Before sifting up!" << std::endl;
     
        print_heap();
     
        sift_down(0);
    }
};

int main()
{
    Max_Heap heap(100);

    heap.insert(20);
    heap.insert(10);
    heap.insert(80);
    heap.insert(90);
    heap.insert(30);

    std::cout << "Max element in binary heap equals to:\t" << heap.peek() << std::endl;

    heap.extract_peek();

    return 0;
}