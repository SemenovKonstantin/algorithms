#ifndef PRIORITY_QUEUE_HPP
#define PRIORITY_QUEUE_HPP

#include <iostream>
#include <climits>

template <typename T>
class Priority_Queue {
private:
    T* heap_array;
    int capacity;
    int size;

    int parent(int index) { return (index - 1) / 2; }
    int left_child(int index) { return 2 * index + 1; }
    int right_child(int index) { return 2 * index + 2; }

    void sift_up(int index) {
        while (index > 0 && heap_array[index] < heap_array[parent(index)]) 
        {
            std::swap(heap_array[parent(index)], heap_array[index]);
            index = parent(index);
        }
    }

    void sift_down(int index) {
        int min_index = index;
        int left = left_child(index);
        int right = right_child(index);

        if (left < size && heap_array[left] < heap_array[min_index]) {
            min_index = left;
        }

        if (right < size && heap_array[right] < heap_array[min_index]) {
            min_index = right;
        }

        if (index != min_index) {
            std::swap(heap_array[index], heap_array[min_index]);
            sift_down(min_index);
        }
    }

public:
    Priority_Queue() : size(0), capacity(20) {
        heap_array = new T[capacity];
    }

    Priority_Queue(size_t capacity_) : size(0), capacity(capacity_) {
        heap_array = new T[capacity];
    }

    ~Priority_Queue() {
        delete[] heap_array;
    }

    void insert(const T& element) {
        if (size == capacity) {
            throw std::out_of_range("Heap is full");
        }
        heap_array[size] = element;
        sift_up(size);
        size++;
    }

    T min_peek() const {
        if (size == 0) {
            throw std::out_of_range("Heap is empty");
        }
        return heap_array[0];
    }

    void extract_peek() {
        if (size == 0) {
            throw std::out_of_range("Heap is empty");
        }
        heap_array[0] = heap_array[size - 1];
        size--;
        sift_down(0);
    }

    bool is_empty() const { return size == 0; }
};

#endif // PRIORITY_QUEUE_HPP