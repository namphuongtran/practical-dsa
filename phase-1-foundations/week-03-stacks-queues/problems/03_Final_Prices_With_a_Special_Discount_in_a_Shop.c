/*Problem: https://leetcode.com/problems/final-prices-with-a-special-discount-in-a-shop/?envType=problem-list-v2&envId=stack
*Given an array of price. Return the price of each index after minus the nearest price to the right that lower than the current price.
*
*Approach: u\Using monotonic stack two update a nearest number that lest than the current element in the index.
*
*Time: O(n) or O(m+n)
*Space: O(n)
*/

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

int* finalPrices(int* prices, int pricesSize, int* returnSize) {
    int* ans = malloc(sizeof(int) * pricesSize);
    int* stack = malloc(sizeof(int) * pricesSize);
    int top = -1;

    for (int i = 0; i < pricesSize; i++) {
        ans[i] = prices[i];

        while (top >= 0 && prices[i] <= prices[stack[top]]) {
            ans[stack[top]] = prices[stack[top]] - prices[i];
            top--;
        }

        stack[++top] = i;
    }

    *returnSize = pricesSize;

    free(stack);
    return ans;
}

void run_test(int* prices, int n, int* expected) {
    int returnSize;
    int* result = finalPrices(prices, n, &returnSize);

    assert(returnSize == n);

    for (int i = 0; i < n; i++) {
        assert(result[i] == expected[i]);
    }

    free(result);
}

int main() {
    {
        int prices[]   = {8, 4, 6, 2, 3};
        int expected[] = {4, 2, 4, 2, 3};
        run_test(prices, 5, expected);
    }

    {
        int prices[]   = {1, 2, 3, 4, 5};
        int expected[] = {1, 2, 3, 4, 5};
        run_test(prices, 5, expected);
    }

    {
        int prices[]   = {10, 9, 8, 7};
        int expected[] = {1, 1, 1, 7};
        run_test(prices, 4, expected);
    }

    {
        int prices[]   = {5, 5, 5};
        int expected[] = {0, 0, 5};
        run_test(prices, 3, expected);
    }

    {
        int prices[]   = {42};
        int expected[] = {42};
        run_test(prices, 1, expected);
    }

    printf("All tests passed!\n");
    return 0;
}