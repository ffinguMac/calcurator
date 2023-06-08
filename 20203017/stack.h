#ifndef STACK_H
# define STACK_H

#include <stdio.h>
#include <stdlib.h>

typedef struct stk_Node
{
	int	data;
	struct stk_Node* next;
} stk_Node;

typedef struct stack
{
	stk_Node* top;
	int cnt;
} Stack;

void init_stack(Stack* stk);
void push(Stack* stk, int data);
int pop(Stack* stk);
int top(Stack* stk);

#endif 