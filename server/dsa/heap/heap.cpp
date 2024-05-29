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
#include <math.h>
#include <vector>
#include <stdexcept>
#include "../vector_utils.h"

struct Heap {
    int height;
    std::vector<int> data;
};

Heap initialize() {
    Heap heap;
    heap.height = 0;
    heap.data = {};
    return heap;
}

int parent(int index) {
    return floor(static_cast<double>(index) / 2);
}

int right_child(int index) {
    return (2*index)+1;
}

int left_child(int index) {
    return (2*index) + 2;
}

int last_internal_node(Heap* h) {
    return floor(h->data.size() / 2) - 1;
}

/**
 * Make a node bubble down until its two children are both 
 * smaller than him
 * 
 * Time complexity is O(logn) if the tree is balanced
 */
void max_heapify(Heap* heap, int index) {
    int largest = index;
    int left_index = left_child(index);
    int right_index = right_child(index);
   
    if(index == heap->data.size() -1){
        return;
    }  

    if(left_index < heap->data.size() && heap->data[left_index] > heap->data[index]){
        largest = left_index;
    }

    if(right_index < heap->data.size() && heap->data[right_index] > heap->data[largest]){
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

/**  
 * function build_max_heap
 *
 * To build a max heap from an unsorted array
 * start from the last non-leaf node and bubble it down
 * continue until you bubble down the root node.
 *
 * The give array can't exceed an int in size.
 *
 * The heap produced is balanced, thus it's height is logn
 * Given all the non-leaf nodes will bubble down, thus the number and comparison 
 * will be 2*logn per non-leaf none.
 * The total worst case time complexity is going to be O(2nlogn)
 * which can be simplified to O(nlogn)
 *
 */
Heap build_max_heap(std::vector<int> &v) {
    if(v.size() > std::numeric_limits<int>::max() - 2) {
        throw std::invalid_argument("The vector size can't overlow int");
    }

    Heap heap; 
    heap.data = std::vector<int>{};
    std::copy(v.begin(), v.end(), std::back_inserter(heap.data)); 
    for(int i = last_internal_node(&heap); i >= 0;i--){
        max_heapify(&heap, i);   
    }

    return heap;
}


