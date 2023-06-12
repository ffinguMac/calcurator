#ifndef QUEUE_H
# define QUEUE_H

#include <stdio.h>
#include <stdlib.h>

typedef struct que_Node
{
	double data;
	struct que_Node* next;
} que_Node;

typedef struct queue
{
	que_Node* front;
	int cnt;
}Queue;

void init_queue(Queue* que);
int is_empty(Queue* que);
void enqueue(Queue* que, double data);
double dequeue(Queue* que);

#endif