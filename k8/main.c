#include <stdio.h>
#include <stdlib.h>
#include "node.h"

int main() {
    Node* head = NULL;

    head = insertNode(head, 1);
    head = insertNode(head, 2);
    head = insertNode(head, 3);
    head = insertNode(head, 4);
    head = insertNode(head, 5);

    Iterator* it = createIterator(head);
    printf("nodes: ");
    Node* node;
    while ((node = next(it)) != NULL) {
        printf("%zu ", node->data);
    }
    printf("\n");

    int count = countNodes(head);
    printf("#nodes: %d\n", count);

    head = deleteNode(head, 3);
    printf("delete node 3: ");
    printList(head);

    head = rotateList(head);
    printf("rotate list: ");
    printList(head);

    while (head != NULL) {
        Node* temp = head;
        head = head->next;
        free(temp);
    }

    free(it);

    return 0;
}