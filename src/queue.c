#include "queue.h"

/*
 * This is the TakeOff Queue implementation. I deided to reimplement a basic queue
 * with a peek function included to look at the first element. 
 *
 * Below is a basic queue implementation. 
 * 
 */
 
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
