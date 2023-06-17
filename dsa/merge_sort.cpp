/**
 * Merge sorts run in O(nlogn) and Ω(nlogn) for both the worst
 * and average case. Meaning it is asymptotically optimal.
 *
 * But it doesn't sort in place, neaning the space complexity is
 * about O(2n) for both the worst and average/expected case.
 */

/** Sorts an array of integer in a non-decreasing order.*/
int* merge_sort(int* nums, int numsSize) {
    if(numsSize == 1) {
        return 0;
    }
    
    /* If .5, rounds it to the lower value */
    int middle = round(numsSize / 2);  
    int sorted_nums[numsSize];

    sorted_nums = mergeSort(nums, middle);
    sorted_nums[middle] = mergeSort(&nums[middle], numsSize - middle);
    
    int temp_index = 0;
    int pointer_1 = 0;
    int pointer_2 = middle;
    
    while (pointer_2 < numsSize || pointer_1 < middle) {        
        if(pointer_1 >= middle) {
            sorted_nums[temp_index] = nums[pointer_2];
            pointer_2++;
        } else if(pointer_2 >= numsSize) {
            sorted_nums[temp_index] = nums[pointer_1];
            pointer_1++;
        } else if(nums[pointer_1] > nums[pointer_2]) {
            sorted_nums[temp_index] = nums[pointer_2];
            pointer_2++;
        } else if (nums[pointer_2] > nums[pointer_1]) {
            sorted_nums[temp_index] = nums[pointer_1];
            pointer_1++;
        } else if(nums[pointer_2] == nums[pointer_1]) {
            temp[temp_index] = nums[pointer_1];
            temp_index++;
            sorted_nums[temp_index] = nums[pointer_1];
            pointer_1++;
            pointer_2++;
        }
        temp_index++;
    }
    
    return &sorted_nums;
}
