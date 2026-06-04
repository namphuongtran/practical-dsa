//https://leetcode.com/problems/maximum-subarray/







#include <stdio.h>
#include <stdlib.h>
#include <assert.h>


int maxSubArray(int* nums, int numsSize) {
    int max_sum = nums[0];
    int current_sum = nums[0];

    for (int i = 1; i < numsSize; i++) {
        if (current_sum + nums[i] > nums[i]) {
            current_sum = current_sum + nums[i];
        } else {
            current_sum = nums[i];
        }

        if (current_sum > max_sum) {
            max_sum = current_sum;
        }
    }

    return max_sum;
}

int main(void) {

    int nums1[] = {0, 1, 1, 2, 3, 4, 4, 5, 5, 6};
    int numsSize1 = sizeof(nums1) / sizeof(nums1[0]);
    assert(maxSubArray(nums1, numsSize1) == 31); 

    int nums2[] = {2, -4, 5, 6, -1, 2};
    int numsSize2 = sizeof(nums2) / sizeof(nums2[0]); 
    assert(maxSubArray(nums2, numsSize2) == 12); 

    int nums3[] = {4, -2, 5, -2, 1, -9, 2};
    int numsSize3 = sizeof(nums3) / sizeof(nums3[0]); 
    assert(maxSubArray(nums3, numsSize3) == 7); 

    printf("All test cases passed successfully! OK\n");
    return 0;
}