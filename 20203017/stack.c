#include "stack.h"

void init_stack(Stack* stk)
{
	stk->cnt = 0;
	stk->top = NULL;
}

void push(Stack* stk, int data)
{
	stk_Node* tmp = (stk_Node*)malloc(sizeof(stk_Node));
	if (tmp == NULL)
	{
		printf("Stack NULL pointer error\n");
		return;
	}
	tmp->data = data;
	tmp->next = stk->top;
	stk->top = tmp;
	stk->cnt++;
}

int pop(Stack* stk)
{
	int data = stk->top->data;
	stk_Node* tmp = stk->top;
	stk->top = stk->top->next;
	stk->cnt--;
	free(tmp);

	return data;
}

int top(Stack* stk)
{
	return (stk->top->data);
}