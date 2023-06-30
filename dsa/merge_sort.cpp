#include <math.h>
#include <vector>
#include <iostream>
#include "vector_utils.h"

using namespace std;

/**
 * Merge sorts run in O(nlogn) and Ω(nlogn) for both the worst
 * and average case. Meaning it is asymptotically optimal.
 *
 * But it doesn't sort in place, neaning the space complexity is
 * about O(2n) for both the worst and average/expected case.
 */

/** Sorts an array of integer in a non-decreasing order.*/
void merge_sort(std::vector<int>& nums) {
    int numSize = nums.size();
    if(numSize == 1) {
        return ;
    }
    
    /* If .5, rounds it to the lower value */
    int middle = round(numSize / 2);  
    std::vector<int> sorted_nums;

    std::vector<int> subvector1 = {nums.begin(), nums.begin() + middle}; 
    std::vector<int> subvector2 = {nums.begin() + middle, nums.end()}; 

    merge_sort(subvector1);
    merge_sort(subvector2);
    
    int temp_index = 0;
    int pointer_1 = 0;
    int pointer_2 = middle;
    
    while (pointer_2 < numSize || pointer_1 < middle) {        
        if(pointer_1 >= middle) {
            sorted_nums[temp_index] = nums[pointer_2];
            pointer_2++;
        } else if(pointer_2 >= numSize) {
            sorted_nums[temp_index] = nums[pointer_1];
            pointer_1++;
        } else if(nums[pointer_1] > nums[pointer_2]) {
            sorted_nums[temp_index] = nums[pointer_2];
            pointer_2++;
        } else if (nums[pointer_2] > nums[pointer_1]) {
            sorted_nums[temp_index] = nums[pointer_1];
            pointer_1++;
        } else if(nums[pointer_2] == nums[pointer_1]) {
            sorted_nums[temp_index] = nums[pointer_1];
            temp_index++;
            sorted_nums[temp_index] = nums[pointer_1];
            pointer_1++;
            pointer_2++;
        }
        temp_index++;
    }
}

 
 
// Driver code
int test()
{
    vector<int> arr = { 12, 11, 13, 5, 6, 7 };
    cout << "Given array is \n";
    printVector(arr);
 
    merge_sort(arr);
    cout << "\nSorted array is \n";
    printVector(arr);
    return 0;
}
