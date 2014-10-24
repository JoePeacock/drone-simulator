#include "queue.h"

struct Queue *NewQueue() {
	struct Queue *q = (struct Queue *) malloc(sizeof(struct Queue));
	q->head = NULL;
	q->tail = NULL;
	return q;
}

void Enqueue(struct Queue *q, void *drone) {

	struct Node *n = (struct Node *) malloc(sizeof(struct Node));
	n->value = drone;
	n->next = NULL;
	if (q->head == NULL) {
		q->head = q->tail = n;
	} else {
		q->tail->next = n;
		q->tail = n;
	}

	return;
}

void Dequeue(struct Queue *q) {
	struct Node *n = q->head->next;
	q->head = n;
	return;
}

void *Peek(struct Queue *q) {
	return q->head->value;
}

void PrintQueue(struct Queue *q) {

	struct Node *ptr = q->head;
	// while(ptr != NULL) {
	// 	printf(" %s -> ",);
	// 	ptr = ptr->next;
	// }
	return;

}
