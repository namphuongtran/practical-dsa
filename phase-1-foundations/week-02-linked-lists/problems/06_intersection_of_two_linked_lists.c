/*Problem: https://leetcode.com/problems/intersection-of-two-linked-lists/?envType=problem-list-v2&envId=linked-list
*Given two pointer, find the most 
*
*Approach: Go through booth linked list at the same time
*
*Time: O(1)
*Space: O(1)
*/

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

struct ListNode {
    int val;
    struct ListNode *next;
};

struct ListNode *getIntersectionNode(struct ListNode *headA, struct ListNode *headB) {
    struct ListNode *pA = headA;
    struct ListNode *pB = headB;

    while (pA != pB) {
        if (pA == NULL) {
            pA = headB;
        } else {
            pA = pA->next;
        }

        if (pB == NULL) {
            pB = headA;
        } else {
            pB = pB->next;
        }
    }

    return pA;
}

struct ListNode* createNode(int val) {
    struct ListNode *node = malloc(sizeof(struct ListNode));
    node->val = val;
    node->next = NULL;
    return node;
}

void test_intersection() {
    struct ListNode *n8 = createNode(8);
    struct ListNode *n4 = createNode(4);
    struct ListNode *n5 = createNode(5);

    n8->next = n4;
    n4->next = n5;

    struct ListNode *a1 = createNode(4);
    struct ListNode *a2 = createNode(1);

    a1->next = a2;
    a2->next = n8;

    struct ListNode *b1 = createNode(5);
    struct ListNode *b2 = createNode(6);
    struct ListNode *b3 = createNode(1);

    b1->next = b2;
    b2->next = b3;
    b3->next = n8;

    assert(getIntersectionNode(a1, b1) == n8);
}