/*Problem: https://leetcode.com/problems/linked-list-cycle/?envType=problem-list-v2&envId=linked-list
*Given a linked list
*
*Approach: use 2 pointer fast and slow. Fast will travel 2 pointer each time and slow travel 1 pointer each time. if the linked list is a loop, there will be a time that fast and slow meet up with each other.
*
*Time: O(n)
*Space: O(1), Only fast and slow pointer take constant memory
*/

#include <stdbool.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

struct ListNode {
    int val;
   struct ListNode *next;
};

bool hasCycle(struct ListNode *head) {
    struct ListNode *fast = head;
    struct ListNode *slow = head;

    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;

        if (slow == fast)
            return true;
    }

    return false;
}



struct ListNode* createNode(int val) {
    struct ListNode *node = malloc(sizeof(struct ListNode));
    node->val = val;
    node->next = NULL;
    return node;
}

void test_has_cycle_middle() {
    struct ListNode *n1 = createNode(3);
    struct ListNode *n2 = createNode(2);
    struct ListNode *n3 = createNode(0);
    struct ListNode *n4 = createNode(-4);

    n1->next = n2;
    n2->next = n3;
    n3->next = n4;
    n4->next = n2;   

    assert(hasCycle(n1) == true);
}

void test_has_cycle_head() {
    struct ListNode *n1 = createNode(1);
    struct ListNode *n2 = createNode(2);

    n1->next = n2;
    n2->next = n1;   

    assert(hasCycle(n1) == true);
}

void test_single_node_cycle() {
    struct ListNode *n1 = createNode(1);

    n1->next = n1;

    assert(hasCycle(n1) == true);
}

void test_single_node_no_cycle() {
    struct ListNode *n1 = createNode(1);

    assert(hasCycle(n1) == false);
}

void test_no_cycle() {
    struct ListNode *n1 = createNode(1);
    struct ListNode *n2 = createNode(2);
    struct ListNode *n3 = createNode(3);
    struct ListNode *n4 = createNode(4);

    n1->next = n2;
    n2->next = n3;
    n3->next = n4;

    assert(hasCycle(n1) == false);
}

void test_empty_list() {
    assert(hasCycle(NULL) == false);
}

void test_long_cycle() {
    struct ListNode *n1 = createNode(1);
    struct ListNode *n2 = createNode(2);
    struct ListNode *n3 = createNode(3);
    struct ListNode *n4 = createNode(4);
    struct ListNode *n5 = createNode(5);
    struct ListNode *n6 = createNode(6);

    n1->next = n2;
    n2->next = n3;
    n3->next = n4;
    n4->next = n5;
    n5->next = n6;
    n6->next = n3;   

    assert(hasCycle(n1) == true);
}

int main() {
    test_has_cycle_middle();
    test_has_cycle_head();
    test_single_node_cycle();
    test_single_node_no_cycle();
    test_no_cycle();
    test_empty_list();
    test_long_cycle();

    printf("All tests passed!\n");
    return 0;
}
