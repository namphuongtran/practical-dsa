/*
 * Problem: Two Sum
 * Source:  https://leetcode.com/problems/two-sum/
 *
 * Given an array `nums` and a target `t`, return the two indices i < j such
 * that nums[i] + nums[j] == t. Exactly one solution is guaranteed.
 *
 * Approach (this file): naive O(n^2) — for each i, scan j > i for the
 * complement. Returns the FIRST valid pair encountered.
 *
 * Why the naive version first: in Week 1 we only know arrays. The clean
 * O(n) solution uses a hash table, which we will revisit in Week 7. Saving
 * the hash version under `solutions/hash/two_sum.c` later is a good
 * exercise.
 *
 * Time:  O(n^2)
 * Space: O(1) auxiliary
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

/*
 * out[0], out[1] are set to the two indices.
 * Returns 1 if a pair was found, 0 otherwise.
 */
int two_sum(const int *nums, size_t n, int target, size_t out[2]) {
    for (size_t i = 0; i + 1 < n; i++) {
        for (size_t j = i + 1; j < n; j++) {
            if (nums[i] + nums[j] == target) {
                out[0] = i;
                out[1] = j;
                return 1;
            }
        }
    }
    return 0;
}

int main(void) {
    {
        int nums[] = {2, 7, 11, 15};
        size_t out[2];
        assert(two_sum(nums, 4, 9, out));
        assert(out[0] == 0 && out[1] == 1);
    }
    {
        int nums[] = {3, 2, 4};
        size_t out[2];
        assert(two_sum(nums, 3, 6, out));
        assert(out[0] == 1 && out[1] == 2);
    }
    {
        int nums[] = {3, 3};
        size_t out[2];
        assert(two_sum(nums, 2, 6, out));
        assert(out[0] == 0 && out[1] == 1);
    }
    {
        /* no solution case */
        int nums[] = {1, 2, 3};
        size_t out[2];
        assert(!two_sum(nums, 3, 100, out));
    }
    printf("two_sum: OK\n");
    return 0;
}
