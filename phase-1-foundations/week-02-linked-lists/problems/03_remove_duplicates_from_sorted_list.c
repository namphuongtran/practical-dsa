/*Problem: https://leetcode.com/problems/remove-duplicates-from-sorted-list/description/?envType=problem-list-v2&envId=linked-list
*Given the head of a sorted linked list, return the head of the sorted linked list without duplicate
*
*Approach: Go through all the node inside the list and compare it with the previous node, if they have the same value, delete this one
*
*Time: O(n), only 1 loop
*Space: O(1), only a *cur pointer that cost constant memory
*/

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

struct ListNode* createNode(int val);
struct ListNode* createList(int arr[], int size);

struct ListNode{
    int val;
    struct ListNode *next;
};

struct ListNode* deleteDuplicates(struct ListNode* head) {
    struct ListNode *cur = head;
    while(cur && cur->next){
        if(cur->val == cur->next->val){
            cur->next=cur->next->next;
        }
        else{
            cur = cur->next;
        }
    }
    return head;
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
    int arr[] = {1, 1, 2};

    struct ListNode *head = createList(arr, 3);
    head = deleteDuplicates(head);

    int expected[] = {1, 2};
    assertList(head, expected, 2);
}

void test_multiple_duplicates() {
    int arr[] = {1, 1, 2, 3, 3};

    struct ListNode *head = createList(arr, 5);
    head = deleteDuplicates(head);

    int expected[] = {1, 2, 3};
    assertList(head, expected, 3);
}

void test_all_duplicates() {
    int arr[] = {1, 1, 1, 1, 1};

    struct ListNode *head = createList(arr, 5);
    head = deleteDuplicates(head);

    int expected[] = {1};
    assertList(head, expected, 1);
}

void test_no_duplicates() {
    int arr[] = {1, 2, 3, 4, 5};

    struct ListNode *head = createList(arr, 5);
    head = deleteDuplicates(head);

    int expected[] = {1, 2, 3, 4, 5};
    assertList(head, expected, 5);
}

void test_single_node() {
    int arr[] = {1};

    struct ListNode *head = createList(arr, 1);
    head = deleteDuplicates(head);

    int expected[] = {1};
    assertList(head, expected, 1);
}

void test_empty_list() {
    struct ListNode *head = NULL;

    head = deleteDuplicates(head);

    assert(head == NULL);
}

void test_duplicates_at_end() {
    int arr[] = {1, 2, 3, 3};

    struct ListNode *head = createList(arr, 4);
    head = deleteDuplicates(head);

    int expected[] = {1, 2, 3};
    assertList(head, expected, 3);
}

void test_duplicates_at_beginning() {
    int arr[] = {1, 1, 2, 3};

    struct ListNode *head = createList(arr, 4);
    head = deleteDuplicates(head);

    int expected[] = {1, 2, 3};
    assertList(head, expected, 3);
}

void test_many_duplicates() {
    int arr[] = {1, 1, 1, 2, 2, 3, 3, 3, 4, 4};

    struct ListNode *head = createList(arr, 10);
    head = deleteDuplicates(head);

    int expected[] = {1, 2, 3, 4};
    assertList(head, expected, 4);
}

int main() {
    test_basic();
    test_multiple_duplicates();
    test_all_duplicates();
    test_no_duplicates();
    test_single_node();
    test_empty_list();
    test_duplicates_at_end();
    test_duplicates_at_beginning();
    test_many_duplicates();

    printf("All tests passed!\n");

    return 0;
}