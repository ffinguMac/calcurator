#include "queue.h"

void init_queue(Queue* que)
{
	que->front = NULL;
	que->cnt = 0;
}

int is_empty(Queue* que)
{
	return que->cnt = 0;
}

void enqueue(Queue* que, int data)
{
	que_Node* tmp = (que_Node*)malloc(sizeof(que_Node));
	if (tmp == NULL)
	{
		printf("Queue NULL pointer error\n");
		return;
	}
	tmp->data = data;
	tmp->next = NULL;

	if (que->front == NULL)
	{
		que->front = tmp;
	}
	else
	{
		que_Node* tmp2 = que->front;
		while (tmp2->next != NULL)
			tmp2 = tmp2->next;
		tmp2->next = tmp;
	}
	que->cnt++;
}

int dequeue(Queue* que)
{
	que_Node* tmp = que->front;
	int data = tmp->data;
	que->front = que->front->next;
	free(tmp);
	que->cnt--;
	return data;
}