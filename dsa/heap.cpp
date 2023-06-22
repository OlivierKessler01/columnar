/**
 * HEAP datastructure
 * Materialized as a vector
 */

#include <stdio.h>
#include <math.h>
#include <stdio.h>

typedef struct {
    int height;
    std::vector<int> * data;
} Heap;

Heap* initialize() {
    Heap heap;
    heap.height = 0;
    heap.data = NULL;
    return &heap;
}

Heap* max_heapify(Heap* heap, int index) {
    int largest = index;
    if(index >= heap.length / 2) {
        //a leaf node is already the root of a max-heap with level 0
        return heap;
    } 
    int left_index = left_child(index);
    int right_index = right_child(index);
    
    if(heap[left_index] > heap[index]){
        largest = left_index;
    }

    if(heap[right_index] > heap[largest]){
        largest = right_index;
    }

    if(largest != index){
        int temp = heap[index];
        heap[index] = heap[largest];
        heap[largest] = temp;
        //recursively call to make the node bubble-down
        max_heapify(heap, largest)
    }

    return heap;
}

bool save_on_disk(Heap*, FILE * fd) {
    return false;
}

Heap* load_from_disk(FILE *fd) {
    Heap heap; 
    return &heap;
}

int parent(int index) {
    return floor(static_cast<double>(i) / 2);
}

int right_child(int index) {
    return 2*index;
}

int left_child(int index) {
    return 2*index + 1;
}
