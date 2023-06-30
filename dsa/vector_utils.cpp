#include <iostream>

void printVector(vector<int> A)
{
    int size = A.size();
    for (int i = 0; i < size; i++)
        std::cout << A[i] << " ";
    std::cout << endl;
}
