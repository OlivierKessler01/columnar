#include "../heap.h"
#include <vector>
#include <cassert>

void heap_sort(std::vector<int> vec) {
    Heap heap = build_max_heap(vec);

    for(int i=0; i < (int)vec.size(); i++) {
        int temp = heap.data[0];
        heap.data[0] = heap.data[vec.size() - 1];
        heap.data[vec.size() - 1] = temp;
        max_heapify(&heap, 0);
    }
}

void test_heap_sort(){
    std::vector<int> v = {2, 3, 1, 10, 12 , 20 ,22} ;
    heap_sort(v);
    for(int i=1; i<(int)v.size(); i++){
        assert(v[i-1] < v[i]);
    }
}

