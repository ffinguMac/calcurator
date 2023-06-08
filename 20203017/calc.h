#ifndef CALC_H
# define CALC_H

#include "stack.h"
#include "queue.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct data
{
	char op;
	int num;
} Data;

int calculator(Data* postfix, int length, int* error);
int toPostfix(char* infix, Data* postfix);
int stack_op(int tmp);
int new_op(int tmp);
int to_int(char* arr);
int to_pow(int nb, int pow);

#define SIZE 1000
#define TRUE 1
#define FALSE 0

#endif