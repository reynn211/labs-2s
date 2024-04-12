#ifndef _NODE_H
#define _NODE_H

typedef struct Node {
    size_t data;
    struct Node* next;
} Node;

typedef struct Iterator {
    Node* current;
} Iterator;

Node* createNode(size_t data);
Node* insertNode(Node* head, size_t data);
Node* deleteNode(Node* head, size_t key);
int countNodes(Node* head);
void printList(Node* node);
Node* rotateList(Node* head);

Iterator* createIterator(Node* head);
Node* next(Iterator* it);

#endif