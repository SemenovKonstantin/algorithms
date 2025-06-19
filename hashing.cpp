// Implementation of hash_table with linked_list inside it due to maintain collisions.
// Collisions are situations when hash_function get the same index for two or more diverse input keys. 
// Hash_function(semenov) -> index:2 && Hash_function(strizhov) -> index:2.
// Hence you have to use a linked_list for storing [key,value] in the same index.

#include <iostream>
#include <string>
#include <vector>

struct Hash_Table;  

template <typename T, typename U>
struct Node
{
    T first;
    U second;
    Node* next;
    Node(T first_value, U second_value) : first(first_value), second(second_value), next(nullptr) {}
};

template <typename T, typename U>
struct List
{
private:
    Node<T,U>* head;
    Node<T,U>* tail;  
    friend struct Hash_Table;  
public:
    List() : head(nullptr), tail(nullptr) {}

    bool is_empty() const { return head == nullptr; }

    void push_back(T first_value, U second_value)  
    {
        Node<T,U>* new_node = new Node<T,U>{first_value, second_value};
        if (is_empty()) {
            head = tail = new_node;
        } else {
            tail->next = new_node;
            tail = new_node;
        }
    }

    void push_front(T first_value, U second_value)
    {
        Node<T,U>* new_node = new Node<T,U>{first_value, second_value};
        if (is_empty()) {
            head = tail = new_node;
        } else {
            new_node->next = head;
            head = new_node;
        }
    }

    void in_order() const
    {
        if (is_empty()) {
            std::cout << "\t[List is empty]\n";
            return;
        }

        std::cout << "\tList content is:\n";
        Node<T,U>* current_node = head;
        int index = 1;
        while (current_node != nullptr) {
            std::cout << "\t" << index << ". Key: " << current_node->first 
                      << "\tValue: " << current_node->second << "\n";
            current_node = current_node->next;
            index++;
        }
        std::cout << "\n";
    }

    Node<T,U>* search_value(T key)
    {
        Node<T,U>* current_node = head;
        while (current_node != nullptr) {
            if (current_node->first == key) {
                return current_node;
            }
            current_node = current_node->next;
        }
        return nullptr;
    }

    void pop_first()
    {
        if (is_empty()) return;
        Node<T,U>* deleted_node = head;
        head = deleted_node->next;
        if (head == nullptr) tail = nullptr;
        delete deleted_node;
    }

    void pop_back()
    {
        if (is_empty()) return;
        if (head == tail) {
            pop_first();
            return;
        }
        
        Node<T,U>* before_tail = head;
        while (before_tail->next != tail) {
            before_tail = before_tail->next;
        }
        delete tail;
        tail = before_tail;
        tail->next = nullptr;   
    }

    void pop_node(T key)
    {
        if (is_empty()) return;

        if (head->first == key) {
            pop_first();
            return;
        }

        if (tail->first == key) {
            pop_back();
            return;
        }

         // Node <T,U>* current_node = head;
        // while (current_node->next != nullptr)
        // {
        //     if (current_node->next->first == key)
        //     {
        //         current_node->next = current_node->next->next;
        //         delete current_node->next;
        //     }

        //     current_node = current_node->next;
        // }

        Node<T,U>* previous = head;
        Node<T,U>* current = previous->next;

        while (current != nullptr && current->first != key) {
            previous = current;
            current = current->next;
        }

        if (current == nullptr) {
            std::cout << "\tValue with this key \"" << key << "\" was not founded.\n\n";
            return;
        }

        previous->next = current->next;
        if (current == tail) {
            tail = previous;
        }
        delete current;
    }

    Node<T,U>* operator[](size_t index) const
    {
        Node<T,U>* current = head;
        size_t count = 0;
        
        while (current != nullptr && count < index) {
            current = current->next;
            count++;
        }
        
        return current;
    }
};

struct Hash_Table
{
    private:
    std::vector<List<std::string,int>> hash_table;
    size_t size;
    size_t released_size;
    float load_factor = 0.75;

    int hash_function(std::string &key)
    {
        int hash = 0;
        for (char ch : key) {
            hash += ch;
        }

        return hash % released_size;
    }

    bool required_rehash() {
        return static_cast<float>(size)/released_size > load_factor;
    }

    void rehashing() {
        std::vector<List<std::string,int>> old_hash_table = hash_table;
        hash_table.clear();
        hash_table.resize(released_size * 2 + 1);
        released_size = hash_table.size();
        size = 0;
        for (const auto& bucket: old_hash_table)
        {
            Node<std::string,int>* current = bucket.head;

            while (current != nullptr )
            {
                insert(current->first,current->second);
                current = current->next;
            }
        }
    }

    public:
    Hash_Table(size_t capacity) : released_size(capacity)
    {
        hash_table.resize(released_size);
    }

    size_t get_size() { return size; }

    size_t get_released_size() { return released_size; }

    // Insertion, deleteion and searching take a constant time O(1) due to hash_function.
    void insert(std::string key,int password)
    {
        if (required_rehash())
        {
            rehashing();
        }
        int index = hash_function(key);
        
        Node<std::string,int>* current = hash_table[index].head;
        while (current != nullptr)
        {
            if (current->first == key)
            {
                current->second = password;
                return;
            }

            current = current->next;
        }    

        hash_table[index].push_back(key,password);
        size++;

        std::cout << "For key: " << "[" << key << "]" << " index equals to: " << "[" << index << "]" << std::endl;
        std::cout << "At this index store " << "key: " << "[" << key << "]" << " password: " << "[" << password << "]" << std::endl; 
    }

    void delete_key(std::string &&key)
    {
        int index = hash_function(key);

        hash_table[index].pop_node(key);

        size--;

    }

    bool search_by_key(std::string &&key)
    {
        int index = hash_function(key);

        Node<std::string,int>* current = hash_table[index].head;
        while (current != nullptr) {
            if (current ->first == key)
                return true;
        }

        return false;

    }

    void print_in_order()
    {
        int index = 0;

        for (const auto& bucket : hash_table)
        {
            std::cout << "[" << index << "]" << std::endl;
            bucket.in_order();
            ++index;
        }
    }
};

int main()
{
    // List<std::string,int> list;
    
    // list.push_back("semenov", 100);
    // list.push_back("klementiev", 210);
    // list.push_back("lochkov", 30);
    // list.push_back(std::string("malekov"), 891);
    
    // std::cout << "Начальный список:\n";
    // list.in_order();
    
    // list.pop_back();
    // std::cout << "После удаления последнего элемента:\n";
    // list.in_order();
    
    // list.pop_first();
    // std::cout << "После удаления первого элемента:\n";
    // list.in_order();
    
    // list.pop_node("klementiev");
    // std::cout << "После удаления узла с ключом \"klementiev\":\n";
    // list.in_order();

    // list.push_front("sharafutdinov", 777);
    // std::cout << "После добавления \"sharafutdinov\" в начало:\n";
    // list.in_order();
    
    Hash_Table hash_table{4};

    hash_table.insert("semenov",1200); 

    hash_table.insert("sharafutdinov",803);

    hash_table.insert("semenov",200); 

    std::cout << "Current size of an array equals to:\t" << hash_table.get_size() << std::endl;

    std::cout << "Released size of an array equals to:\t" << hash_table.get_released_size() << std::endl;


    hash_table.insert("semenova",9100); 

    std::cout << "Current size of an array equals to:\t" << hash_table.get_size() << std::endl;

    std::cout << "Released size of an array equals to:\t" << hash_table.get_released_size() << std::endl;

    hash_table.print_in_order();

    hash_table.delete_key("semenov");

    std::cout << "Current size of an array equals to:\t" << hash_table.get_size() << std::endl;

    std::cout << "Released size of an array equals to:\t" << hash_table.get_released_size() << std::endl;

    hash_table.print_in_order();

    hash_table.search_by_key("semenov") ? std::cout << "Founded!" << std::endl : std::cout << "Didn't find!" << std::endl;

    return 0;
}