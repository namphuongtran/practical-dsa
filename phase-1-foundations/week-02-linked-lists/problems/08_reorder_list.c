/*Problem: https://leetcode.com/problems/reorder-list/?envType=problem-list-v2&envId=linked-list
*Given a linked list. Reorder the linked list
*
*Approach: split the linked list into two, reverse the second half, and merge
*
*Time: O(n)
*Space: O(1)
*/

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

struct ListNode{
    int val;
    struct ListNode *next;
};

void reorderList(struct ListNode* head) {
    if (head == NULL || head->next == NULL) {
        return;
    }

    struct ListNode *fast = head;
    struct ListNode *slow = head;

    while (fast->next != NULL && fast->next->next != NULL) {
        fast = fast->next->next;
        slow = slow->next;
    }

    struct ListNode *cur = slow->next;
    slow->next = NULL;

    struct ListNode *prev = NULL;

    while (cur != NULL) {
        struct ListNode *temp = cur->next;
        cur->next = prev;
        prev = cur;
        cur = temp;
    }

    struct ListNode *first = head;
    struct ListNode *second = prev;

    while (second != NULL) {
        struct ListNode *temp1 = first->next;
        struct ListNode *temp2 = second->next;

        first->next = second;
        second->next = temp1;

        first = temp1;
        second = temp2;
    }
}
int main() {
    // 1 -> 2 -> 3 -> 4
    struct ListNode a4 = {4, NULL};
    struct ListNode a3 = {3, &a4};
    struct ListNode a2 = {2, &a3};
    struct ListNode a1 = {1, &a2};

    reorderList(&a1);

    assert(a1.val == 1);
    assert(a1.next->val == 4);
    assert(a1.next->next->val == 2);
    assert(a1.next->next->next->val == 3);
    assert(a1.next->next->next->next == NULL);

    // 1 -> 2 -> 3 -> 4 -> 5
    struct ListNode b5 = {5, NULL};
    struct ListNode b4 = {4, &b5};
    struct ListNode b3 = {3, &b4};
    struct ListNode b2 = {2, &b3};
    struct ListNode b1 = {1, &b2};

    reorderList(&b1);

    assert(b1.val == 1);
    assert(b1.next->val == 5);
    assert(b1.next->next->val == 2);
    assert(b1.next->next->next->val == 4);
    assert(b1.next->next->next->next->val == 3);
    assert(b1.next->next->next->next->next == NULL);

    // 1 -> 2
    struct ListNode c2 = {2, NULL};
    struct ListNode c1 = {1, &c2};

    reorderList(&c1);

    assert(c1.val == 1);
    assert(c1.next->val == 2);
    assert(c1.next->next == NULL);

    // 1 -> 2 -> 3
    struct ListNode d3 = {3, NULL};
    struct ListNode d2 = {2, &d3};
    struct ListNode d1 = {1, &d2};

    reorderList(&d1);

    assert(d1.val == 1);
    assert(d1.next->val == 3);
    assert(d1.next->next->val == 2);
    assert(d1.next->next->next == NULL);

    printf("All tests passed!\n");
    return 0;
}