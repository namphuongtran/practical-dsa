//https://leetcode.com/problems/remove-duplicates-from-sorted-array/description/
//Using 2 different pointer to solve this problem, j and i work as 2 distinct pointer
//j will get to the next index each time i encouter a new element in the array and change
//element at that index to the new element
//After calculating all distint element apart from the first element, we have to account for the first element

//Only 1 for loop go through the list -> O(n)

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

int removeDuplicates(int* nums, int numsSize) {
    if (numsSize == 0) {
        return 0;
    }

    int j = 0;
    for (int i = 1; i < numsSize; i++) {
        if (nums[i] != nums[j]) {
            j += 1;          
            nums[j] = nums[i]; 
        }
    }

    return j + 1; 
}

int main(void) {
    
    int nums1[] ={0, 1, 1, 2, 3, 4, 4, 5, 5, 6};
    int numsSize1 = sizeof(nums1)/sizeof(nums1[0]);
    assert(removeDuplicates(nums1, numsSize1) == 7);


    int nums2[] ={0, 0, 0, 0, 0, 0};
    int numsSize2 = sizeof(nums2)/sizeof(nums2[0]);
    assert(removeDuplicates(nums2, numsSize2) == 1);

    int nums3[] ={0, 1, 1, 1, 1, 2, 2, 3, 3, 4};
    int numsSize3 = sizeof(nums3)/sizeof(nums3[0]);
    assert(removeDuplicates(nums3, numsSize3) == 5);


    printf("All test cases passed successfully! OK\n");
    return 0;



}