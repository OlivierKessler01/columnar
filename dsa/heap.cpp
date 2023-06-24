/**
 * HEAP datastructure
 * Materialized as a vector
 *          
 *                     _____L______ 
 *                    |            |
 *                _R_ |___R___     |
 *               |   ||       |    |
 *       [NULL, 14,  12 , 13, 11, 10 ... n] 
 *               |__L_____|
 * 
 */

#include <stdio.h>
#include <math.h>
#include <stdio.h>
#include <cassert>
#include <vector>
#include <iostream>

typedef struct {
    int height;
    std::vector<int> data;
} Heap;

Heap initialize() {
    Heap heap;
    heap.height = 0;
    heap.data = {};
    return heap;
}

void max_heapify(Heap* heap, int index) {
    assert(index > 0);
    int largest = index;
    if(index >= heap->data.size() / 2) {
        //a leaf node is already the root of a max-heap with level 0
        return heap;
    } 
    int left_index = left_child(index);
    int right_index = right_child(index);
    
    if(heap->data[left_index] > heap->data[index]){
        largest = left_index;
    }

    if(heap->data[right_index] > heap->data[largest]){
        largest = right_index;
    }

    if(largest != index){
        int temp = heap->data[index];
        heap->data[index] = heap->data[largest];
        heap->data[largest] = temp;
        //recursively call to make the node bubble-down
        max_heapify(heap, largest);
    }
}


bool test_max_heapify() {
    std::vector<int> expected = {-1, 3, 12, 1, 10, 2, 20, 22};
    Heap* heap = &initialize();
    heap->data = {-1, 2, 3, 1, 10, 12 , 20 } ;
    max_heapify(heap, 1);
    
    for(unsigned int i=0; i < heap->data.size(); i++){
        assert(heap->data[i] == expected[i]);
    }

    return true;
}

bool save_on_disk(Heap*, FILE * fd) {
    return false;
}

Heap load_from_disk(FILE *fd) {
    Heap heap; 
    return heap;
}

int parent(int index) {
    return floor(static_cast<double>(index) / 2);
}

int right_child(int index) {
    return 2*index;
}

int left_child(int index) {
    return 2*index + 1;
}
