//https://leetcode.com/problems/rotate-array/description/
//For this problem, We have 2 way to approach it. First is using (i+k)%n index to find the new index, second is to reverse all the arry.
//Since I don't renember how to code the second way, we will gone through the first way. 
//The key of this problem is the element in the i th index move + k index. 
//And if it move pass the end of the array we can just ultize % to get the leftove to move it from the beginning of the arry
//Only one loop -> O(n)

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

void rotate(int* nums, int numsSize, int k) {
    int n = numsSize;
    k = k % n; 
    
    int* temp = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        temp[(i + k) % n] = nums[i];
    }

    for (int i = 0; i < n; i++) {
        nums[i] = temp[i];
    }
    free(temp);
}

int main() {

    int nums1[] = {1, 2, 3, 4, 5, 6, 7};
    int expected1[] = {5, 6, 7, 1, 2, 3, 4};
    rotate(nums1, 7, 3);
    assertArrayEquals(nums1, expected1, 7);

    int nums2[] = {-1, -100, 3, 99};
    int expected2[] = {3, 99, -1, -100};
    rotate(nums2, 4, 2);
    assertArrayEquals(nums2, expected2, 4);

    int nums3[] = {1, 2, 3};
    int expected3[] = {1, 2, 3};
    rotate(nums3, 3, 3);
    assertArrayEquals(nums3, expected3, 3);

    int nums4[] = {1, 2};
    int expected4[] = {2, 1};
    rotate(nums4, 2, 5);
    assertArrayEquals(nums4, expected4, 2);

    int nums5[] = {42};
    int expected5[] = {42};
    rotate(nums5, 1, 100);
    assertArrayEquals(nums5, expected5, 1);

    int nums6[] = {8, 8, 8, 8};
    int expected6[] = {8, 8, 8, 8};
    rotate(nums6, 4, 1);
    assertArrayEquals(nums6, expected6, 4);
    
    printf("All test cases passed successfully! OK\n");
    return 0;

}