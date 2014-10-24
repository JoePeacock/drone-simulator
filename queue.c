#include "queue.h"

struct Queue *NewQueue() {
	struct Queue *q = (struct Queue *) malloc(sizeof(struct Queue));
	q->head = NULL;
	q->tail = NULL;
	// q->head = q->tail = NULL;
	return q;
}

void Add(struct Queue *q, Drone *drone) {

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

void PrintQueue(struct Queue *q) {

	struct Node *ptr = q->head;
	while(ptr != NULL) {
		Drone* d = ptr->value;
		printf(" %s -> ", d->drone_id);
		ptr = ptr->next;
	}
	return;

}
