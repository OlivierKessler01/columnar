#include "../heap.h"
#include <vector>

void heap_sort(std::vector<int> vec) {
    Heap heap = build_max_heap(vec);

    for(int i=0; i < (int)vec.size(); i++) {
        int temp = heap.data[0];
        heap.data[0] = heap.data[vec.size() - 1];
        heap.data[vec.size() - 1] = temp;
        max_heapify(&heap, 1);
    }
}


