/*Problems: https://leetcode.com/problems/remove-nth-node-from-end-of-list/description/?envType=problem-list-v2&envId=linked-list
*Given the head of an linked list and an interger n, remove the nth node from the right of the linked list
*
*Approach: dummy node + two pointer(fast and slow).Because this problem requires to remove node so that we need a dummy node.
*And to find the nth node from the end, we can use two pointer to find the nth node from the end.
*
*Time: O(n), only one loop through the linked list
*Space: O(1), no extra memory is needed, only constant memory.
*/



#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

struct ListNode {
    int val;
    struct ListNode *next;
};

struct ListNode* createNode(int val) {
    struct ListNode *node = malloc(sizeof(struct ListNode));
    node->val = val;
    node->next = NULL;
    return node;
}

struct ListNode* createList(int arr[], int size) {
    if (size == 0) return NULL;

    struct ListNode *head = createNode(arr[0]);
    struct ListNode *current = head;

    for (int i = 1; i < size; i++) {
        current->next = createNode(arr[i]);
        current = current->next;
    }

    return head;
}

struct ListNode* removeNthFromEnd(struct ListNode* head, int n) {
    struct ListNode dummy;
    dummy.next = head;

    struct ListNode *fast = &dummy;
    struct ListNode *slow = &dummy;

    for (int i = 0; i < n; i++) {
        fast = fast->next;
    }

    while (fast->next != NULL) {
        fast = fast->next;
        slow = slow->next;
    }

    struct ListNode *deleteNode = slow->next;
    slow->next = slow->next->next;
    free(deleteNode);

    return dummy.next;
}

void assertlist(struct ListNode *head, int *expected, int expectedSize) {
    struct ListNode* current = head;

    for (int i = 0; i < expectedSize; i++) {
        assert(current != NULL);
        assert(current->val == expected[i]);
        current = current->next;
    }

    assert(current == NULL);
}

void test_remove_middle() {
    int arr[] = {1, 2, 3, 4, 5};
    struct ListNode *head = createList(arr, 5);

    head = removeNthFromEnd(head, 2);

    int expected[] = {1, 2, 3, 5};
    assertlist(head, expected, 4);
}

void test_remove_tail() {
    int arr[] = {1, 2, 3, 4, 5};
    struct ListNode *head = createList(arr, 5);

    head = removeNthFromEnd(head, 1);

    int expected[] = {1, 2, 3, 4};
    assertlist(head, expected, 4);
}

void test_remove_head() {
    int arr[] = {1, 2, 3, 4, 5};
    struct ListNode *head = createList(arr, 5);

    head = removeNthFromEnd(head, 5);

    int expected[] = {2, 3, 4, 5};
    assertlist(head, expected, 4);
}

void test_single_node() {
    int arr[] = {1};
    struct ListNode *head = createList(arr, 1);

    head = removeNthFromEnd(head, 1);

    assert(head == NULL);
}

void test_two_nodes_remove_first() {
    int arr[] = {1, 2};
    struct ListNode *head = createList(arr, 2);

    head = removeNthFromEnd(head, 2);

    int expected[] = {2};
    assertlist(head, expected, 1);
}

void test_two_nodes_remove_second() {
    int arr[] = {1, 2};
    struct ListNode *head = createList(arr, 2);

    head = removeNthFromEnd(head, 1);

    int expected[] = {1};
    assertlist(head, expected, 1);
}

int main() {
    test_remove_middle();
    test_remove_tail();
    test_remove_head();
    test_single_node();
    test_two_nodes_remove_first();
    test_two_nodes_remove_second();

    printf("All tests passed!\n");
    return 0;
}
