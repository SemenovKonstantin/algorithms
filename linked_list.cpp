// Actually stack, queue, priority queue - are abstract data structures.
// They cannot be constructed without a concrete data structures. On their own they exist only abstractly.
// For implementation of any of this - have to use linked list, double linked list, binary heaps. (Specified data structures)

// Henceforth, below is implementation of stack and queue (LIFO and FIFO) with linked list.

// Stack - Last In First Out. For maintaing this logic we should implement push_back and and pop_back.
// Instance: 
//      52                  deleted first
//      10 => 80 24 10 52 =>    10
//      24                      24
//      80                      80


// Queue - First In First Out. For maintaining this logic we should implement push_back and pop_first.
// Instance: 
//      52                      52
//      10 => 80 24 10 52 =>    10
//      24                      24
//      80                   deleted first

// Below you can see an fusion between Stack(LIFO) and Queue(FIFO) as a non completed deque.

#include <iostream>

template <typename T>
struct Node {
    T data;
    Node* next_node;
    Node(T data_) : data(data_), next_node(nullptr) {}
};

template <typename T>
class List {
private:
    Node<T>* head;
    Node<T>* tail;

public:
    List() : head(nullptr), tail(nullptr) {}
    ~List() {
        while (!is_empty()) {
            pop_first();
        }
    }

    bool is_empty() const {
        return head == nullptr;
    }

    void push_back(T value) {
        Node<T>* new_node = new Node<T>(value);
        if (is_empty()) {
            head = tail = new_node;
        } else {
            tail->next_node = new_node;
            tail = new_node;
        }
    }

    void push_front(T value) {
        Node<T>* new_node = new Node<T>(value);
        Node<T>* new_second = head;
        head = new_node;
        head->next_node = new_second; 
    }

    void inOrder() const {
        Node<T>* current = head;
        while (current != nullptr) {
            std::cout << current << " " << current->data << " ";
            current = current->next_node;
        }
        std::cout << std::endl;
    }

    Node<T>* search_item(T value) const {
        Node<T>* current = head;
        while (current != nullptr) {
            if (current->data == value) {
                return current;
            }
            current = current->next_node;
        }
        return nullptr;
    }

     void pop_first()
    {
        if (is_empty()) return; 
        Node<T>* delete_node = head;
        head = delete_node->next_node;
        delete delete_node;
        delete_node = nullptr;
    }

    void pop_tail() {
        if (is_empty()) return;
        
        if (head == tail) {
            pop_first();
            return;
        }
        
        Node<T>* current = head;
        while (current->next_node != tail) {
            current = current->next_node;
        }
        
        delete tail;
        tail = current;
        tail->next_node = nullptr;
    }

    void pop_node(T value) {
        if (is_empty()) return;
        
        if (head->data == value) {
            pop_first();
            return;
        }
        
        Node<T>* prev = head;
        Node<T>* current = head->next_node;
        
        while (current != nullptr && current->data != value) {
            prev = current;
            current = current->next_node;
        }
        
        if (current == nullptr) {
            std::cout << "Value not found in list" << std::endl;
            return;
        }
        
        prev->next_node = current->next_node;
        if (current == tail) {
            tail = prev;
        }
        delete current;
    }

    Node<T>* operator[](size_t index) const {
        Node<T>* current = head;
        size_t count = 0;
        
        while (current != nullptr && count < index) {
            current = current->next_node;
            count++;
        }
        
        return current;
    }
};

int main() {
    List<int> list;
    
    list.push_back(10);
    list.push_back(20);
    list.push_back(30);
    list.push_back(40);
    
    std::cout << "Initial list: ";
    list.inOrder();
    
    list.pop_tail();
    std::cout << "After pop_tail: ";
    list.inOrder();
    
    list.pop_first();
    std::cout << "After pop_first: ";
    list.inOrder();
    
    list.pop_node(20);
    std::cout << "After pop_node(20): ";
    list.inOrder();

    list.push_front(98);
    std::cout << "After push_front(98): ";
    list.inOrder();
    
    return 0;
}