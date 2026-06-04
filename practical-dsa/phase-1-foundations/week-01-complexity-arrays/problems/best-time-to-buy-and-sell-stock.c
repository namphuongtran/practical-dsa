//Baciscally I ultilize 1 loop to go through every posibility inside an array
//This work because the every time the machine go through an element it find the highest
//posible way to earn interest and renember the lowest price to buy to use in the next loop

//Using greedy to find the most optimize way to calculate the interest
//O(n)

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
int maxProfit(int* prices, int pricesSize) {
    long long buy = prices[0];
    long long profit = 0;
    for(int i = 0; i < pricesSize; i++){
        if(prices[i] < buy){
            buy = prices[i];
        }
        if(prices[i] -  buy > profit){
            profit = prices[i] - buy;
        }
    }
    return profit;
}
int main(void) {

    int prices1[] = {7, 1, 5, 3, 6, 4};
    int size1 = sizeof(prices1) / sizeof(prices1[0]);
    assert(maxProfit(prices1, size1) == 5);

    int prices2[] = {7, 6, 4, 3, 1};
    int size2 = sizeof(prices2) / sizeof(prices2[0]);
    assert(maxProfit(prices2, size2) == 0);

    int prices3[] = {3, 3, 3, 3, 3};
    int size3 = sizeof(prices3) / sizeof(prices3[0]);
    assert(maxProfit(prices3, size3) == 0);

    int prices4[] = {1, 2, 4, 7, 10};
    int size4 = sizeof(prices4) / sizeof(prices4[0]);
    assert(maxProfit(prices4, size4) == 9);

    int prices5[] = {3, 8, 1, 5, 2, 9, 4};
    int size5 = sizeof(prices5) / sizeof(prices5[0]);
    assert(maxProfit(prices5, size5) == 8);

    printf("All test cases passed successfully! OK\n");
    return 0;
}