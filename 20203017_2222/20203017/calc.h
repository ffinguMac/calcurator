#ifndef CALC_H
# define CALC_H

#include "stack.h"
#include "queue.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct data
{
	char op;
	double num;
} Data;

double calculator(Data* postfix, int length, int* error);
int toPostfix(char* infix, Data* postfix);
int stack_op(int tmp);
int new_op(int tmp);
double to_pow(double nb, double pow);

#define SIZE 1000
#define TRUE 1
#define FALSE 0

#endif