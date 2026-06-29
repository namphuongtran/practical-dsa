/*Implement hashmap using linked list, by storing every key and value in a node
*
*
*
*
*
*
*/


#include <stdio.h>
#include <stdlib.h>

#define P 1009

typedef struct Node {
    int key;
    int value;
    struct Node *next;
} Node;

typedef struct HashMap {
    Node *table[P];
} HashMap;

int getHash(int key) {
    int index = key % P;

    if (index < 0) {
        index += P;
    }

    return index;
}

void init(HashMap *map) {
    for (int i = 0; i < P; i++) {
        map->table[i] = NULL;
    }
}

void insert(HashMap *map, int key, int value) {
    int index = getHash(key);

    Node *cur = map->table[index];

    while (cur != NULL) {
        if (cur->key == key) {
            cur->value = value;
            return;
        }

        cur = cur->next;
    }

    Node *newNode = malloc(sizeof(Node));

    if (newNode == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }

    newNode->key = key;
    newNode->value = value;

    newNode->next = map->table[index];
    map->table[index] = newNode;
}

int find(HashMap *map, int key, int *result) {
    int index = getHash(key);

    Node *cur = map->table[index];

    while (cur != NULL) {
        if (cur->key == key) {
            *result = cur->value;
            return 1;
        }

        cur = cur->next;
    }

    return 0;
}

void deleteKey(HashMap *map, int key) {
    int index = getHash(key);

    Node *cur = map->table[index];
    Node *prev = NULL;

    while (cur != NULL) {
        if (cur->key == key) {
            if (prev == NULL) {
                map->table[index] = cur->next;
            } else {
                prev->next = cur->next;
            }

            free(cur);
            return;
        }

        prev = cur;
        cur = cur->next;
    }
}

void freeHashMap(HashMap *map) {
    for (int i = 0; i < P; i++) {
        Node *cur = map->table[i];

        while (cur != NULL) {
            Node *temp = cur;
            cur = cur->next;
            free(temp);
        }

        map->table[i] = NULL;
    }
}

int main() {
    HashMap map;
    init(&map);

    insert(&map, 10, 100);
    insert(&map, 20, 200);
    insert(&map, 1019, 300);

    int value;

    if (find(&map, 10, &value)) {
        printf("key 10 = %d\n", value);
    } else {
        printf("key 10 not found\n");
    }

    if (find(&map, 1019, &value)) {
        printf("key 1019 = %d\n", value);
    } else {
        printf("key 1019 not found\n");
    }

    if (find(&map, 99, &value)) {
        printf("key 99 = %d\n", value);
    } else {
        printf("key 99 not found\n");
    }

    deleteKey(&map, 10);

    if (find(&map, 10, &value)) {
        printf("key 10 = %d\n", value);
    } else {
        printf("key 10 not found after delete\n");
    }

    freeHashMap(&map);

    return 0;
}
