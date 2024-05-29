#include "heap.h"
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

