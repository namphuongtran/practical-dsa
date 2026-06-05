/*Source: https://leetcode.com/problems/rotate-array/description/
*
*Given an array of intergers, and a positive integer k,return the array after rotating to the right by k
*
*Approach: Because the problem is asking for a right rotation, we can reverse the whole array,
*then reverse the first k element and reverse the rest of the array
*
*Time: O(n)
*Space: O(1)
*/

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

void rotate(int* nums, int numsSize, int k) {
    int r = numsSize - 1;
    int l = 0;
    int rotate = k%numsSize;
    while(l < r){
        int temp = nums[l];
        nums[l] = nums[r];
        nums[r] = temp;
        r--;
        l++;
    }
    l =0;
    r = numsSize - 1;
    rotate = k%numsSize - 1;
    while(l < rotate){
        int temp = nums[l];
        nums[l] = nums[rotate];
        nums[rotate] = temp;
        rotate--;
        l++;
    }
    l =0;
    r = numsSize - 1;
    rotate = k%numsSize;
    while(rotate < r){
        int temp = nums[rotate];
        nums[rotate] = nums[r];
        nums[r] = temp;
        rotate++;
        r--;
    }

}

int main(void){
    {
        int nums[] = {1,2,3,4,5,6,7};
        rotate(nums, 7, 3);
        assert(nums[0] == 5 && nums[1] == 6 && nums[2] == 7 && nums[3] == 1 && nums[4] == 2 && nums[5] == 3 && nums[6] == 4);
    }
    {
        int nums[] = {-1,-100,3,99};
        rotate(nums, 4, 2);
        assert(nums[0] == 3 && nums[1] == 99 && nums[2] == -1 && nums[3] == -100);
    }
    printf("All test cases passed!\n");
    return 0;
}