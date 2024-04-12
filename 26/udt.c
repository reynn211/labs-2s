#include "udt.h"
#include <stdlib.h>
#include <stdio.h>

udt* udt_create(int capacity) {
	udt* queue = (udt*)malloc(sizeof(udt));
	queue->capacity = capacity;
	queue->front = queue->size = 0;
	queue->rear = capacity - 1;
	queue->data = (int*)malloc(queue->capacity * sizeof(int));
	return queue;
}

bool udt_is_empty(const udt *queue) {
	return (queue->size == 0);
}

void udt_push(udt *queue, int item) {
	if (queue->size == queue->capacity) return;
	queue->rear = (queue->rear + 1)%queue->capacity;
	queue->data[queue->rear] = item;
	queue->size = queue->size + 1;
}

void udt_pop(udt *queue) {
	if (udt_is_empty(queue)) return;
	queue->front = (queue->front + 1)%queue->capacity;
	queue->size = queue->size - 1;
}

int udt_get(const udt* queue) {
	return queue->data[queue->front];
}

void udt_print(const udt* queue) {
	int i;
	for (i = 0; i < queue->size; i++) {
		printf("%d ", queue->data[i]);
	}
	printf("\n");
}

int udt_size(const udt *queue) {
	return queue->size;
}

void udt_destroy(udt* queue) {
    free(queue->data);
    free(queue);
}

// dp
void udt_shift_smaller(udt *queue) {
    if (udt_is_empty(queue) || queue->size == 1) return;

    int i, j;
    for (i = 1; i < queue->size; i++) {
        if (queue->data[i] < queue->data[i-1]) {
            int temp = queue->data[i];
            for (j = i; j > 0 && queue->data[j-1] > temp; j--) {
                queue->data[j] = queue->data[j-1];
            }
            queue->data[j] = temp;
			break;
        }
    }
}

// sort
void udt_insertion_sort(udt *queue) {
    int size = udt_size(queue);
    for (int i = 0; i < size; i++) {
        udt_shift_smaller(queue);
    }
}