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

static int parent(int index) {
    return floor(static_cast<double>(index) / 2);
}

static int right_child(int index) {
    return (2*index)+1;
}

static int left_child(int index) {
    return (2*index) + 2;
}

static int last_internal_node(Heap* h) {
    return floor(h->data.size() / 2) - 1;
}

/**
 * Make a node bubble down until its two children are both 
 * smaller than him
 * 
 * Time complexity is O(logn) if the tree is balanced
 */
static void max_heapify(Heap* heap, int index) {
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
 *
 * build_max_heap - To build a max heap from an unsorted array
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


#ifdef TEST
#include <cassert>

bool check_max_heap_vector(std::vector<int> v, int index) {
    //check that a vector is a true max_heap using dfs
    bool result = false;
    int vec_size = (int)v.size();
    if(index > vec_size - 1){
        return true;
    }

    int left_child_index = left_child(index);
    int right_child_index = right_child(index);
    int has_right_child = right_child_index <=  vec_size - 1;
    int has_left_child = left_child_index <= vec_size - 1;

    if((!has_right_child || v[right_child(index)] < v[index]) 
        && 
        (!has_left_child || v[left_child(index)] < v[index])){
        result = true;
    }

    if(result == true){
        result = result && check_max_heap_vector(v, left_child_index);
        result = result && check_max_heap_vector(v, right_child_index);
    }
    
    return result;
}

bool check_max_heap(Heap heap) {
    return check_max_heap_vector(heap.data, 1);
}

/**
 * MAIN TEST FUNCTION
 */
bool test_build_max_heap() {
    std::vector<int> v = {2, 3, 1, 10, 12 , 20 ,22} ;
    std::vector<int> v3 = {211, 3, 12, 10, 120 , 200 ,22} ;
    std::vector<int> v2 = {21, 3, 81, 10, 12 , 20 ,22} ;
    Heap heap = build_max_heap(v);
    Heap heap2 = build_max_heap(v2);
    Heap heap3 = build_max_heap(v3);

    assert(check_max_heap(heap) == true);
    assert(check_max_heap(heap2) == true);
    assert(check_max_heap(heap3) == true);

    return true;
}

int main() 
{
    test_build_max_heap();
    return 0;
}
#endif
