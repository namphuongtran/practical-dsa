//https://leetcode.com/problems/find-all-numbers-disappeared-in-an-array/
//For this problem I ulitize the malloc and calloc funtion to help me create 2 different dynamics arrays(or vector I so called) named v and result
//The first for loop will go through every element on the nums list. Now because every numbers have a distinct value, so every time we met an different value, we mark "1" on that v index
//On the other hand, the second loop will go through the the v index and for every index that didn't marked "1", we add that value to our other vector name result
//2 loop through the whole array -> O(n)

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>


int* findDisappearedNumbers(int* nums, int numsSize, int* returnSize) {
    long long n = numsSize;
    int *v = calloc(n + 1,sizeof(nums[0]));
    for(int k = 0; k < n; k++){
        int a = nums[k];
        v[a] = 1;
    }
    int *result = (int*)malloc(n * sizeof(nums[0]));
    int count =0;
    for (int k = 1; k <= n; k++) {
        if (v[k] == 0) {      
            result[count] = k; 
            count++;          
        }
    }
    free(v);
    *returnSize = count;
    return result;
}


void assertArrayEquals(int* actual, int actualSize, int* expected, int expectedSize) {
    assert(actualSize == expectedSize);
    for (int i = 0; i < actualSize; i++) {
        assert(actual[i] == expected[i]);
    }
}

int main() {
    int nums1[] = {4, 3, 2, 7, 8, 2, 3, 1};
    int returnSize1;
    int* result1 = findDisappearedNumbers(nums1, 8, &returnSize1);
    int expected1[] = {5, 6};
    assertArrayEquals(result1, returnSize1, expected1, 2);
    free(result1);

    int nums2[] = {1, 1};
    int returnSize2;
    int* result2 = findDisappearedNumbers(nums2, 2, &returnSize2);
    int expected2[] = {2};
    assertArrayEquals(result2, returnSize2, expected2, 1);
    free(result2);

    int nums3[] = {4, 3, 1, 2};
    int returnSize3;
    int* result3 = findDisappearedNumbers(nums3, 4, &returnSize3);
    assert(returnSize3 == 0);
    free(result3);

    int nums4[] = {1};
    int returnSize4;
    int* result4 = findDisappearedNumbers(nums4, 1, &returnSize4);
    assert(returnSize4 == 0);
    free(result4);

    int nums5[] = {1, 1, 1, 1, 1};
    int returnSize5;
    int* result5 = findDisappearedNumbers(nums5, 5, &returnSize5);
    int expected5[] = {2, 3, 4, 5};
    assertArrayEquals(result5, returnSize5, expected5, 4);
    free(result5);

    printf("All test cases passed successfully! OK\n");
    return 0;
}