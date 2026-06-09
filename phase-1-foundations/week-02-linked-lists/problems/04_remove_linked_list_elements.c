/*Problem: https://leetcode.com/problems/remove-linked-list-elements/?envType=problem-list-v2&envId=linked-list
*Given a linked list and an integer. Return the list without any of the integer value node.
*
*Approach: loop through every element of the linked list and delete every node of the link list that have the same value as the given element
*
*Time: O(n)
*Space: O(1)
*/

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

struct ListNode {
    int val;
    struct ListNode *next;
  };

struct ListNode* removeElements(struct ListNode* head, int val) {
    struct ListNode dummy;
    dummy.next = head;

    struct ListNode *curr = &dummy;

    while (curr->next) {
        if (curr->next->val == val) {
            curr->next = curr->next->next;
        } else {
            curr = curr->next;
        }
    }

    return dummy.next;
}

struct ListNode* createNode(int val) {
    struct ListNode *node = malloc(sizeof(struct ListNode));
    node->val = val;
    node->next = NULL;
    return node;
}

struct ListNode* createList(int arr[], int size) {
    if (size == 0) return NULL;

    struct ListNode *head = createNode(arr[0]);
    struct ListNode *cur = head;

    for (int i = 1; i < size; i++) {
        cur->next = createNode(arr[i]);
        cur = cur->next;
    }

    return head;
}

void assertList(struct ListNode *head, int expected[], int expectedSize) {
    struct ListNode *cur = head;

    for (int i = 0; i < expectedSize; i++) {
        assert(cur != NULL);
        assert(cur->val == expected[i]);
        cur = cur->next;
    }

    assert(cur == NULL);
}

void test_basic() {
    int arr[] = {1, 2, 6, 3, 4, 5, 6};

    struct ListNode *head = createList(arr, 7);
    head = removeElements(head, 6);

    int expected[] = {1, 2, 3, 4, 5};
    assertList(head, expected, 5);
}

void test_remove_head() {
    int arr[] = {7, 1, 2, 3};

    struct ListNode *head = createList(arr, 4);
    head = removeElements(head, 7);

    int expected[] = {1, 2, 3};
    assertList(head, expected, 3);
}

void test_remove_tail() {
    int arr[] = {1, 2, 3, 7};

    struct ListNode *head = createList(arr, 4);
    head = removeElements(head, 7);

    int expected[] = {1, 2, 3};
    assertList(head, expected, 3);
}

void test_remove_middle() {
    int arr[] = {1, 2, 7, 3};

    struct ListNode *head = createList(arr, 4);
    head = removeElements(head, 7);

    int expected[] = {1, 2, 3};
    assertList(head, expected, 3);
}

void test_all_elements_removed() {
    int arr[] = {7, 7, 7, 7};

    struct ListNode *head = createList(arr, 4);
    head = removeElements(head, 7);

    assert(head == NULL);
}

void test_no_elements_removed() {
    int arr[] = {1, 2, 3, 4};

    struct ListNode *head = createList(arr, 4);
    head = removeElements(head, 7);

    int expected[] = {1, 2, 3, 4};
    assertList(head, expected, 4);
}

void test_empty_list() {
    struct ListNode *head = NULL;

    head = removeElements(head, 7);

    assert(head == NULL);
}

void test_single_node_remove() {
    int arr[] = {7};

    struct ListNode *head = createList(arr, 1);
    head = removeElements(head, 7);

    assert(head == NULL);
}

void test_single_node_keep() {
    int arr[] = {1};

    struct ListNode *head = createList(arr, 1);
    head = removeElements(head, 7);

    int expected[] = {1};
    assertList(head, expected, 1);
}

void test_consecutive_duplicates() {
    int arr[] = {1, 7, 7, 7, 2, 3};

    struct ListNode *head = createList(arr, 6);
    head = removeElements(head, 7);

    int expected[] = {1, 2, 3};
    assertList(head, expected, 3);
}

int main() {
    test_basic();
    test_remove_head();
    test_remove_tail();
    test_remove_middle();
    test_all_elements_removed();
    test_no_elements_removed();
    test_empty_list();
    test_single_node_remove();
    test_single_node_keep();
    test_consecutive_duplicates();

    printf("All tests passed!\n");

    return 0;
}