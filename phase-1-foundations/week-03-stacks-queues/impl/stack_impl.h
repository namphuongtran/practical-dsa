#include <stdio.h>
#include <stdlib.h>


struct Node {
    int data;
    struct Node* link;
};
struct Node* top = NULL;
void Push(int x){
    struct Node* temp = (struct Node*)malloc(sizeof(struct Node));
    temp->data = x;
    temp->link = top;
    top = temp;
}
void Pop(){
    if(top == NULL) return;
    struct Node* temp = top;
    top = top->link;
    free(temp);
}
int Peak(){
    if(top == NULL) return -1;
    return top->data;
}
void Isempty(){
    if(top == NULL) printf("Empty Stack");
}
int Size(){
    int count = 0;

    struct Node* temp = top;
    while(temp != NULL){
        count++;
        temp = temp->link;
    }
    return count;
}
void Print(){
    struct Node *temp = top;
    while(temp != NULL){
        printf("%d", temp->data);
        temp= temp->link;
    }
    printf("\n");
}
void Clear() {
    while (top != NULL) {
        struct Node* temp = top;
        top = top->link;
        free(temp);
    }
}