/*Problem: https://leetcode.com/problems/add-two-numbers/?envType=problem-list-v2&envId=linked-list
*Given two linked list that contain integer in reverse order. Return the linked list that have the sum of the two linked list
*
*Approach: plus two value and store them in another pointer. Using Cary to handle when the sum is greater than 10
*
*Time: O(m+ n)
*Space: O(m+n)
*/


#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct ListNode{
    int val;
    struct ListNode *next;
};

struct ListNode* addTwoNumbers(struct ListNode* l1, struct ListNode* l2) {
    int rem = 0;

    struct ListNode dummy;
    dummy.next = NULL;

    struct ListNode *cur = &dummy;

    while (l1 != NULL || l2 != NULL) {
        int val = rem;

        if (l1 != NULL) {
            val += l1->val;
            l1 = l1->next;
        }

        if (l2 != NULL) {
            val += l2->val;
            l2 = l2->next;
        }

        rem = val / 10;
        val = val % 10;

        struct ListNode *node = malloc(sizeof(struct ListNode));
        node->val = val;
        node->next = NULL;

        cur->next = node;
        cur = cur->next;
    }

    if (rem > 0) {
        struct ListNode *node = malloc(sizeof(struct ListNode));
        node->val = rem;
        node->next = NULL;

        cur->next = node;
    }

    return dummy.next;
}

int main() {
    // [2,4,3] + [5,6,4] = [7,0,8]
    struct ListNode a3 = {3, NULL};
    struct ListNode a2 = {4, &a3};
    struct ListNode a1 = {2, &a2};

    struct ListNode b3 = {4, NULL};
    struct ListNode b2 = {6, &b3};
    struct ListNode b1 = {5, &b2};

    struct ListNode *res = addTwoNumbers(&a1, &b1);

    assert(res->val == 7);
    assert(res->next->val == 0);
    assert(res->next->next->val == 8);
    assert(res->next->next->next == NULL);

    // [5] + [5] = [0,1]
    struct ListNode c1 = {5, NULL};
    struct ListNode d1 = {5, NULL};

    res = addTwoNumbers(&c1, &d1);

    assert(res->val == 0);
    assert(res->next->val == 1);
    assert(res->next->next == NULL);

    // [9,9] + [1] = [0,0,1]
    struct ListNode e2 = {9, NULL};
    struct ListNode e1 = {9, &e2};

    struct ListNode f1 = {1, NULL};

    res = addTwoNumbers(&e1, &f1);

    assert(res->val == 0);
    assert(res->next->val == 0);
    assert(res->next->next->val == 1);
    assert(res->next->next->next == NULL);

    // [0] + [0] = [0]
    struct ListNode g1 = {0, NULL};
    struct ListNode h1 = {0, NULL};

    res = addTwoNumbers(&g1, &h1);

    assert(res->val == 0);
    assert(res->next == NULL);

    printf("All tests passed!\n");
    return 0;
}