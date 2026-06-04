//Using two distinct pointer to address two different index in the array
//While i loop through the array, j only move when it met an non-zero elements
//After that add all zeros until the array is full

//Using 1 loop through all the array -> O(n)


#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

void moveZeroes(int* nums, int numsSize) {
    int zeros = 0;
    int j = 0;
    for(int i = 0; i < numsSize; i++){
        if(nums[i] != 0){
            nums[j] = nums[i];
            j += 1;
        }
    }
    for (int i = j; i < numsSize; i++) {
        nums[i] = 0;
    }
}

int main(void){
int nums1[] = {0, 1, 0, 3, 12};
    moveZeroes(nums1, 5);
    
    assert(nums1[0] == 1);
    assert(nums1[1] == 3);
    assert(nums1[2] == 12);
    assert(nums1[3] == 0);
    assert(nums1[4] == 0);

    int nums2[] = {0};
    moveZeroes(nums2, 1);
    assert(nums2[0] == 0);

    int nums3[] = {4, 2, 1};
    moveZeroes(nums3, 3);
    assert(nums3[0] == 4);
    assert(nums3[1] == 2);
    assert(nums3[2] == 1);

    int nums4[] = {0, 0, 0};
    moveZeroes(nums4, 3);
    assert(nums4[0] == 0);
    assert(nums4[1] == 0);
    assert(nums4[2] == 0);

    int nums5[] = {1, 5, 0, 0};
    moveZeroes(nums5, 4);
    assert(nums5[0] == 1);
    assert(nums5[1] == 5);
    assert(nums5[2] == 0);
    assert(nums5[3] == 0);

    printf("All test cases passed successfully! OK\n");
    return 0;


}
