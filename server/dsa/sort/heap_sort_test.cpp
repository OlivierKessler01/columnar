#include "heap_sort.h"
#include <vector>
#include <cassert>
#include <iostream>
#include "../vector_utils.h"

using std::cout, std::endl; 

int main() 
{
    cout << "TESTING HEAP SORT IN NON-DECREASING ORDER : " << endl;
    std::vector<int> v = {-10, 288, 3, 1, 10, 12 , 20 ,22} ;
    cout << "INPUT : " << endl;
    printVector(v);
    heap_sort(v);
    cout << "RESULT : " << endl;
    printVector(v);

    for(int i=1; i<(int)v.size(); i++){
        assert(v[i-1] < v[i]);
    }
    return 0;
}
