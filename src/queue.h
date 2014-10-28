#include <stdio.h>
#include <stdlib.h>

struct Node {
  void *value;
  struct Node *next;
};

struct Queue {
  struct Node *head;
  struct Node *tail;
};

struct Queue *NewQueue();

void Dequeue(struct Queue *q);

void *Peek(struct Queue *q);

void Enqueue(struct Queue *q, void *new_node);

void PrintQueue(struct Queue *q);
