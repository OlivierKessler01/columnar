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
#include "vector_utils.h"

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

//bool save_on_disk(Heap*, FILE * fd) {
//    return false;
//}
//
//Heap load_from_disk(FILE *fd) {
//    Heap heap; 
//    return heap;
//}

int parent(int index) {
    return floor(static_cast<double>(index) / 2);
}

int right_child(int index) {
    return 2*index;
}

int left_child(int index) {
    return 2*index + 1;
}

void max_heapify(Heap* heap, int index) {
    /**
     * Make a node bubble down until its two children are both 
     * smaller than him
     */
    assert(index > 0);
    int largest = index;
    if(index >= (int)heap->data.size() / 2) {
        //a leaf node is already the root of a max-heap with level 0
        return;
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

Heap build_max_heap(std::vector<int> v) {
    /**  
     * To build a max heap from an unsorted array
     * start from the last non-leaf node and bubble it down
     * continue until you bubble down the root node.
     */
    int last_nonleaf_node = floor(v.size() / 2) - 1;
    Heap heap; 
    heap.data = v;

    for(int i = last_nonleaf_node; i > 0;i--){
        max_heapify(&heap, i);   
    }

    return heap;
}




bool test_build_max_heap() {
    std::vector<int> expected = {-1, 3, 12, 1, 10, 2, 20, 22};
    std::vector<int> v = {-1, 2, 3, 1, 10, 12 , 20 ,22} ;
    Heap heap = build_max_heap(v);
    printVector(heap.data);
    printVector(expected);
    
    for(unsigned int i=0; i < heap.data.size(); i++){
        assert(heap.data[i] == expected[i]);
    }

    return true;
}

