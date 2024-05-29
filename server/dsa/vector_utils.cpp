#include <iostream>
#include <vector>

using std::cout; 

void printVector(std::vector<int> A)
{
    int size = A.size();
    for (int i = 0; i < size; i++)
        cout << A[i] << " ";
    return;
}
