#include <stdio.h>
#include <stdlib.h>

struct Node{
    int data;
    struct Node *link;
};
struct Node *l = NULL;
struct Node *r = NULL;
void Enqueue(int x){
    struct Node *temp = (struct Node*)malloc(sizeof(struct Node));
    if(l == NULL && r == NULL){
        temp->data= x;
        r = temp;
        l = temp;
        temp->link = NULL;
    }
    else{
        temp->data= x;
        r->link = temp;
        temp->link = NULL;
        r = temp;
    }
}
void Dequeue(){
    if(l == NULL){
        return;
    }
    struct Node *temp = l;
    l = l->link;

    if(l == NULL){
        r = NULL;
    }

    free(temp);
}
int IsEmpty(){
    return l == NULL;
}

void PrintQueue(){
    if(IsEmpty()){
        printf("Queue is empty\n");
        return;
    }

    struct Node *temp = l;

    printf("Queue: ");
    while(temp != NULL){
        printf("%d ", temp->data);
        temp = temp->link;
    }
    printf("\n");
}

int Size(){
    int count = 0;
    struct Node *temp = l;

    while(temp != NULL){
        count++;
        temp = temp->link;
    }

    return count;
}