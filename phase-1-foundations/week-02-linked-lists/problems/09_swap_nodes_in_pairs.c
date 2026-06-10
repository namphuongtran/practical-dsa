/*Problem: https://leetcode.com/problems/swap-nodes-in-pairs/description/?envType=problem-list-v2&envId=linked-list
*Given a linked list, return the linked list swap by pairs
*
*Approach: Using 4 different pointer
*
*Time: O(n)
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

struct ListNode* swapPairs(struct ListNode* head) {
    struct ListNode dummy;
    dummy.next = head;

    struct ListNode *prev = &dummy;

    while (prev->next != NULL && prev->next->next != NULL) {
        struct ListNode *first = prev->next;
        struct ListNode *second = first->next;

        first->next = second->next;
        second->next = first;
        prev->next = second;

        prev = first;
    }

    return dummy.next;
}

int main() {
    // 1 -> 2 -> 3 -> 4
    struct ListNode a4 = {4, NULL};
    struct ListNode a3 = {3, &a4};
    struct ListNode a2 = {2, &a3};
    struct ListNode a1 = {1, &a2};

    struct ListNode *res = swapPairs(&a1);

    assert(res->val == 2);
    assert(res->next->val == 1);
    assert(res->next->next->val == 4);
    assert(res->next->next->next->val == 3);
    assert(res->next->next->next->next == NULL);

    // 1 -> 2 -> 3
    struct ListNode b3 = {3, NULL};
    struct ListNode b2 = {2, &b3};
    struct ListNode b1 = {1, &b2};

    res = swapPairs(&b1);

    assert(res->val == 2);
    assert(res->next->val == 1);
    assert(res->next->next->val == 3);
    assert(res->next->next->next == NULL);

    // 1 -> 2
    struct ListNode c2 = {2, NULL};
    struct ListNode c1 = {1, &c2};

    res = swapPairs(&c1);

    assert(res->val == 2);
    assert(res->next->val == 1);
    assert(res->next->next == NULL);

    // 1
    struct ListNode d1 = {1, NULL};

    res = swapPairs(&d1);

    assert(res->val == 1);
    assert(res->next == NULL);

    // NULL
    res = swapPairs(NULL);
    assert(res == NULL);

    printf("All tests passed!\n");
    return 0;
}