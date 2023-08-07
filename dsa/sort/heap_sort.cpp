#include "../heap.h"
#include <vector>
#include <iostream>
#include "../vector_utils.h"
#include <string>

void heap_sort(std::vector<int> vec) {
    std::cout << "heap_sort()";
    Heap heap = build_max_heap(vec);

    for(int i=0; i < (int)vec.size(); i++) {
        std::cout << "heap_sort(for)";
        std::cout << "\n";
        int temp = heap.data[1];
        std::cout << "temp = " + std::to_string(temp) + "\n";
        heap.data[1] = heap.data[vec.size() - 1];
        std::cout << "heap.data[vec.size() - 1] = " + std::to_string(heap.data[vec.size() - 1]) + "\n";
        heap.data[vec.size() - 1] = temp;
        printVector(heap.data);
        max_heapify(&heap, 1);
    }
}


