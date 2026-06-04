//https://leetcode.com/problems/container-with-most-water/description/
//Basically this is a famous greedy problem. By squeezing the distance between left and right, 
//we can continuously update the area value

//Only 1 while loop -> O(n)

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define min(x, y) ((x) < (y) ? (x) : (y))
#define max(x, y) ((x) > (y) ? (x) : (y))

int maxArea(int* height, int heightSize) {
    int max_water = 0;
    int L = 0;
    int R = heightSize - 1;

    while (L < R) {
        int current_water = min(height[L], height[R]) * (R - L);
        max_water = max(max_water, current_water);

        if (height[L] < height[R]) {
            L += 1;
        } else {
            R -= 1;
        }
    }
    return max_water;
}

int main(void) {

    int nums1[] = {0, 1, 1, 2, 3, 4, 4, 5, 5, 6};
    int numsSize1 = sizeof(nums1) / sizeof(nums1[0]);
    assert(maxArea(nums1, numsSize1) == 16); 

    int nums2[] = {2, 4, 5, 6, 1, 2};
    int numsSize2 = sizeof(nums2) / sizeof(nums2[0]); 
    assert(maxArea(nums2, numsSize2) == 10); 

    int nums3[] = {4, 2, 5, 2, 1, 9, 2};
    int numsSize3 = sizeof(nums3) / sizeof(nums3[0]); 
    assert(maxArea(nums3, numsSize3) == 20); 

    printf("All test cases passed successfully! OK\n");
    return 0;
}