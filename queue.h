#include "drone.h"
#include<stdio.h>
#include<stdlib.h>

struct Node {
  Drone *value;
  struct Node *next;
};

struct Queue {
  struct Node *head;
  struct Node *tail;
};

struct Queue *NewQueue();

void Add(struct Queue *q, Drone *new_node);

void PrintQueue(struct Queue *q);
