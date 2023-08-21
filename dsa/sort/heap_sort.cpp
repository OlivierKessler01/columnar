#include "../heap.h"
#include <vector>
#include <iostream>
#include "../vector_utils.h"
#include <string>

void heap_sort(std::vector<int> &vec) {
    std::cout << "INPUT : ";
    printVector(vec);
    std::cout << '\n';
    std::cout << "build_max_heap()";
    std::cout << '\n';
    Heap heap = build_max_heap(vec);
    printVector(heap.data);
    std::vector<int> result;

    for(int i=(int)vec.size()-1; i > -1; i--) {
        std::cout << "heap_sort(for)";
        std::cout << "\n";
        int temp = heap.data[0];
        heap.data[0] = heap.data[heap.data.size() - 1];
        heap.data.pop_back(); 
        vec[i] = temp;

        printVector(heap.data);
        std::cout << "max_heapify";
        std::cout << "\n";
        max_heapify(&heap, 1);
        printVector(heap.data);
    }
}


