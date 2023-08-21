#include "heap_sort.h"
#include <vector>
#include <cassert>
#include <iostream>
#include "../vector_utils.h"

int main() 
{
    std::vector<int> v = {-10, 288, 3, 1, 10, 12 , 20 ,22} ;
    printVector(v);
    heap_sort(v);
    printVector(v);

    for(int i=1; i<(int)v.size(); i++){
        assert(v[i-1] < v[i]);
    }
    assert(1==2);
    return 0;
}
