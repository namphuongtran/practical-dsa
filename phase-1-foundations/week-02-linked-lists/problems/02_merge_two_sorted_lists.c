/*Problems: https://leetcode.com/problems/merge-two-sorted-lists/description/?envType=problem-list-v2&envId=linked-list
*Given 2 linked list, return the head of the sorted merge link list
*
*Approach: Go through the 2 linked list at the same time and compare each pointer one by one and compare them and using dummy pointer to store the value
*
*Time: O(n). 1 loop go through booth linked list
*Space O(1). Only the dummy pointer cost memory
*/

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

struct ListNode{
    int val;
    struct ListNode *next;
};

struct ListNode* mergeTwoLists(struct ListNode* list1, struct ListNode* list2) {
    struct ListNode dummy;
    dummy.next = NULL;

    struct ListNode *cur = &dummy;

    while (list1 && list2) {
        if (list1->val <= list2->val) {
            cur->next = list1;
            list1 = list1->next;
        } else {
            cur->next = list2;
            list2 = list2->next;
        }

        cur = cur->next;
    }

    if (list1) {
        cur->next = list1;
    } else {
        cur->next = list2;
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
    int arr1[] = {1, 2, 4};
    int arr2[] = {1, 3, 4};

    struct ListNode *list1 = createList(arr1, 3);
    struct ListNode *list2 = createList(arr2, 3);

    struct ListNode *result = mergeTwoLists(list1, list2);

    int expected[] = {1, 1, 2, 3, 4, 4};
    assertList(result, expected, 6);
}

void test_list1_empty() {
    int arr2[] = {1, 2, 3};

    struct ListNode *list1 = NULL;
    struct ListNode *list2 = createList(arr2, 3);

    struct ListNode *result = mergeTwoLists(list1, list2);

    int expected[] = {1, 2, 3};
    assertList(result, expected, 3);
}

void test_list2_empty() {
    int arr1[] = {1, 2, 3};

    struct ListNode *list1 = createList(arr1, 3);
    struct ListNode *list2 = NULL;

    struct ListNode *result = mergeTwoLists(list1, list2);

    int expected[] = {1, 2, 3};
    assertList(result, expected, 3);
}

void test_both_empty() {
    struct ListNode *result = mergeTwoLists(NULL, NULL);

    assert(result == NULL);
}

void test_single_node_lists() {
    int arr1[] = {1};
    int arr2[] = {2};

    struct ListNode *list1 = createList(arr1, 1);
    struct ListNode *list2 = createList(arr2, 1);

    struct ListNode *result = mergeTwoLists(list1, list2);

    int expected[] = {1, 2};
    assertList(result, expected, 2);
}

void test_all_list1_smaller() {
    int arr1[] = {1, 2, 3};
    int arr2[] = {4, 5, 6};

    struct ListNode *list1 = createList(arr1, 3);
    struct ListNode *list2 = createList(arr2, 3);

    struct ListNode *result = mergeTwoLists(list1, list2);

    int expected[] = {1, 2, 3, 4, 5, 6};
    assertList(result, expected, 6);
}

void test_all_list2_smaller() {
    int arr1[] = {4, 5, 6};
    int arr2[] = {1, 2, 3};

    struct ListNode *list1 = createList(arr1, 3);
    struct ListNode *list2 = createList(arr2, 3);

    struct ListNode *result = mergeTwoLists(list1, list2);

    int expected[] = {1, 2, 3, 4, 5, 6};
    assertList(result, expected, 6);
}

void test_duplicate_values() {
    int arr1[] = {1, 1, 2};
    int arr2[] = {1, 1, 3};

    struct ListNode *list1 = createList(arr1, 3);
    struct ListNode *list2 = createList(arr2, 3);

    struct ListNode *result = mergeTwoLists(list1, list2);

    int expected[] = {1, 1, 1, 1, 2, 3};
    assertList(result, expected, 6);
}

void test_negative_values() {
    int arr1[] = {-10, -5, 0};
    int arr2[] = {-6, -3, 2};

    struct ListNode *list1 = createList(arr1, 3);
    struct ListNode *list2 = createList(arr2, 3);

    struct ListNode *result = mergeTwoLists(list1, list2);

    int expected[] = {-10, -6, -5, -3, 0, 2};
    assertList(result, expected, 6);
}

void test_different_lengths() {
    int arr1[] = {1, 3};
    int arr2[] = {2, 4, 5, 6, 7};

    struct ListNode *list1 = createList(arr1, 2);
    struct ListNode *list2 = createList(arr2, 5);

    struct ListNode *result = mergeTwoLists(list1, list2);

    int expected[] = {1, 2, 3, 4, 5, 6, 7};
    assertList(result, expected, 7);
}

int main() {
    test_basic();
    test_list1_empty();
    test_list2_empty();
    test_both_empty();
    test_single_node_lists();
    test_all_list1_smaller();
    test_all_list2_smaller();
    test_duplicate_values();
    test_negative_values();
    test_different_lengths();

    printf("All tests passed!\n");
    return 0;
}