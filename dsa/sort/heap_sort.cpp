#include "../heap/heap.h"
#include <vector>
#include <iostream>
#include "../vector_utils.h"
#include <string>

void heap_sort(std::vector<int> &vec) {
    Heap heap = build_max_heap(vec);
    std::vector<int> result;

    for(int i=(int)vec.size()-1; i > -1; i--) {
        int temp = heap.data[0];
        heap.data[0] = heap.data[heap.data.size() - 1];
        heap.data.pop_back(); 
        vec[i] = temp;

        max_heapify(&heap, 0);
    }
}


