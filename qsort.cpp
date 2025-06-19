// Quick sort is one of the most efficient sort algorithm. Takes 0(n * log n).

#include <iostream>
// 1                2
// 18 81 9         18 9 81
// 18 9  81         9 18 81 
// Time complexity in the good occasion equals to O(n^2), int best time complexity equals to O(n): already sorted.
void bubble_sort(int* array, const int size)
{
    bool swaped = false;
    for (int i = 0; i < size -1 ; i++)
    {
        for (int j = 0; j < size- i - 1; j++)
        {
            if (array[j] > array[j+1])
            {
                std::swap(array[j],array[j+1]);
                swaped = true;
            }
        }

        if (!swaped) break;
    }
}

void print_in_order(int *array,const int size)
{
    for (int i = 0; i < size; i++)
    {
        std::cout << "[" << i << "]: " << *(array + i) << "\t";
    }
    std::cout << std::endl;
}

// Input: 20 10 60 48 90
// Output: 60
int choose_pivot(int *array,const int left_ptr, const int right_ptr)
{
    int pivot_value{}; // Value initialization
    int first_index = left_ptr;
    int last_index = right_ptr;
    int middle_index = left_ptr + right_ptr/ 2;

    constexpr int new_size = 3;
    int new_array[new_size] = {array[first_index],array[middle_index],array[last_index]};
    // print_in_order(new_array,new_size);
    bubble_sort(new_array,new_size);
    // print_in_order(new_array,new_size);

    pivot_value = new_array[new_size/2];

    if (pivot_value == array[first_index]) { return first_index; }
    if (pivot_value == array[middle_index]) { return middle_index; }
    return last_index;

}

// Input: 20 90 60 48 80
int partition(int *array,int l_ptr, int r_ptr)
{
    int pivot_index = choose_pivot(array,l_ptr,r_ptr); // 60
    int pivot_element = array[pivot_index];

    std::swap(array[pivot_index],array[r_ptr]);

    int left_pointer = l_ptr;
    int right_pointer = r_ptr - 1;
    // left_ptr = 0; right_ptr = 4;

    while (left_pointer <= right_pointer)
    {   
        // 1th step commends: 0 <= 4 && 20 < 60 -> true: => left_ptr = 1;
        // 2th step commends: 1 <= 4 && 90 < 60 -> false: => left_ptr = 1 && get out of the loop;

        while (left_pointer < right_pointer && array[left_pointer] < pivot_element)
        {
            left_pointer++;
        }

        // 1th step commends: 4 > 1 && 80 > 60 -> true: => right_ptr = 3;
        // 2th step commends: 3 > 1 && 48 > 60 -> false: => right_ptr = 3 && get out of the loop;

        while (right_pointer > left_pointer && array[right_pointer] >= pivot_element)
        {
            right_pointer--;
        }

        if (left_pointer >= right_pointer) { break; }

        // 1th step commends: 1 <= 3 -> true:
        
        // Was: 20 90 60 48 80 -> 20 90 80 48 [60] -> 20 48 80 90 [60] -> 20 48 [60] 90 80 
        // Became: 20 48 60 90 80

        int temporary = array[left_pointer];
        array[left_pointer] = array[right_pointer];
        array[right_pointer] = temporary;

        left_pointer++; // left_ptr = 2;
        right_pointer--; // right_ptr = 2;


    }

    std::swap(array[left_pointer], array[r_ptr]);
    return left_pointer;
}

void quick_sort(int *array, const int left, const int right)
{
    if (left < right)
    {
        int pivot = partition(array,left,right);
        quick_sort(array,left,pivot -1);
        quick_sort(array,pivot+1,right);
    }
}


int main()
{
    constexpr int size = 10;

    int array[size] = {18,41,11,31,81,12,1,91,8,9};
    
    print_in_order(array,size);

    quick_sort(array,0,size-1);

    print_in_order(array,size);

    return 0;
}