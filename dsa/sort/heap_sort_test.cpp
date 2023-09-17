#include "heap_sort.h"
#include <vector>
#include <cassert>
#include <iostream>
#include "../vector_utils.h"

int main() 
{
    std::cout << "TESTING HEAP SORT IN NON-DECREASING ORDER : ";
    std::cout << '\n';
    std::vector<int> v = {-10, 288, 3, 1, 10, 12 , 20 ,22} ;
    std::cout << "INPUT : ";
    printVector(v);
    heap_sort(v);
    std::cout << "RESULT : ";
    printVector(v);

    for(int i=1; i<(int)v.size(); i++){
        assert(v[i-1] < v[i]);
    }
    return 0;
}
