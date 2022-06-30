
/** Sorts an array of integer in a non-decreasing order.*/
int mergeSortIntArray(int* nums, int numsSize) {
    int middle;
    int pointer_2;
    int pointer_1;
    
    if(numsSize == 1) {
        return 0;
    }
    
    /* If .5, rounds it to the lower value */
    middle = round(numsSize / 2);  
    mergeSort(nums, middle);
    mergeSort(&nums[middle], numsSize - middle);
    
    int temp[numsSize];
    int temp_index = 0;
    pointer_1 = 0;
    pointer_2 = middle;
    
    while (pointer_2 < numsSize || pointer_1 < middle) {        
        if(pointer_1 >= middle) {
            temp[temp_index] = nums[pointer_2];
            pointer_2++;
        } else if(pointer_2 >= numsSize) {
            temp[temp_index] = nums[pointer_1];
            pointer_1++;
        } else if(nums[pointer_1] > nums[pointer_2]) {
            temp[temp_index] = nums[pointer_2];
            pointer_2++;
        } else if (nums[pointer_2] > nums[pointer_1]) {
            temp[temp_index] = nums[pointer_1];
            pointer_1++;
        } else if(nums[pointer_2] == nums[pointer_1]) {
            temp[temp_index] = nums[pointer_1];
            temp_index++;
            temp[temp_index] = nums[pointer_1];
            pointer_1++;
            pointer_2++;
        }
        temp_index++;
    }

    for(int i = 0; i < numsSize; i++) {
        nums[i] = temp[i];
    }
    
    return 0;
}
