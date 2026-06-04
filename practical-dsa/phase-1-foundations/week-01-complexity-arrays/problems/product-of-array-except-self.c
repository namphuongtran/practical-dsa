//https://leetcode.com/problems/product-of-array-except-self/
//We create a subarray and use the preflix subfix technique.
//To calculate the answer, we take the product of preflix multiple with the product of subfix

//Only using 1 loop -> O(n)

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int* productExceptSelf(int* nums, int numsSize, int* returnSize) {
    *returnSize = numsSize;

    int* answer = (int*)malloc(numsSize * sizeof(int));
    if (answer == NULL) return NULL;

    answer[0] = 1;
    for (int i = 1; i < numsSize; i++) {
        answer[i] = answer[i - 1] * nums[i - 1];
    }

    int right_product = 1;
    for (int i = numsSize - 1; i >= 0; i--) {
        answer[i] = answer[i] * right_product;
        right_product *= nums[i]; 
    }

    return answer;
}

void verify_testcase(int* nums, int numsSize, int* expected) {
    int returnSize;
    int* result = productExceptSelf(nums, numsSize, &returnSize);
    
    assert(returnSize == numsSize);
    assert(result != NULL);

    for (int i = 0; i < numsSize; i++) {
        assert(result[i] == expected[i]);
    }

    free(result);
}

int main() {
    printf("Running test cases for Product of Array Except Self...\n");

    int nums1[] = {1, 2, 3, 4};
    int expected1[] = {24, 12, 8, 6};
    verify_testcase(nums1, 4, expected1);

    int nums2[] = {-1, 1, 0, -3, 3};
    int expected2[] = {0, 0, 9, 0, 0};
    verify_testcase(nums2, 5, expected2);

    int nums3[] = {0, 4, 0, 5};
    int expected3[] = {0, 0, 0, 0};
    verify_testcase(nums3, 4, expected3);

    int nums4[] = {-2, -1, -3};
    int expected4[] = {3, 6, 2};
    verify_testcase(nums4, 3, expected4);

    printf("All test cases passed successfully! OK\n");
    return 0;
}






