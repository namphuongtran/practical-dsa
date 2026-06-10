/*Problem: https://leetcode.com/problems/convert-binary-number-in-a-linked-list-to-integer/submissions/2027569541/?envType=problem-list-v2&envId=linked-list
*Given a linked list that contain binary numbers, return the decimal version of that numbers
*
*Approach: using the binary*k formula to solve this problems
*
*Time:; O(n)
*Space: O(1)
*/

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct ListNode{
    int val;
    struct ListNode *next;
};

int getDecimalValue(struct ListNode* head) {
    struct ListNode *h = head;
    int k =0;
    while(h != NULL){
        k++;
        h = h->next;
    }
    k--;
    int res = 0;
    while(head != NULL){
        res += head->val * pow(2,k);
        k--;
        head = head->next;
    }
    return res;
}

int main() {
    struct ListNode a3 = {1, NULL};
    struct ListNode a2 = {0, &a3};
    struct ListNode a1 = {1, &a2};
    assert(getDecimalValue(&a1) == 5);

    struct ListNode b1 = {0, NULL};
    assert(getDecimalValue(&b1) == 0);

    struct ListNode c1 = {1, NULL};
    assert(getDecimalValue(&c1) == 1);

    struct ListNode d5 = {0, NULL};
    struct ListNode d4 = {0, &d5};
    struct ListNode d3 = {0, &d4};
    struct ListNode d2 = {0, &d3};
    struct ListNode d1 = {1, &d2};
    assert(getDecimalValue(&d1) == 16);

    struct ListNode e4 = {1, NULL};
    struct ListNode e3 = {1, &e4};
    struct ListNode e2 = {1, &e3};
    struct ListNode e1 = {1, &e2};
    assert(getDecimalValue(&e1) == 15);

    printf("All tests passed!\n");
    return 0;
}