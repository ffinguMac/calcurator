#ifndef QUEUE_H
# define QUEUE_H

#include <stdio.h>
#include <stdlib.h>

typedef struct que_Node
{
	int	data;
	struct que_Node* next;
} que_Node;

typedef struct queue
{
	que_Node* front;
	int cnt;
}Queue;

void init_queue(Queue* que);
int is_empty(Queue* que);
void enqueue(Queue* que, int data);
int dequeue(Queue* que);

#endif