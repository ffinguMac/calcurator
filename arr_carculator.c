#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#define MAX 100

int stack[MAX];
int top;

int push(int);
int pop(void);
int operator(int);
int PostfixCalculator(char*);
void InfixToPostfix(char*, char*);

int main(void) {
	char postfix_exp[MAX];
	char infix_exp[MAX];
	int result = 0;

	printf("Input Expression : ");
	gets(infix_exp);

	InfixToPostfix(infix_exp, postfix_exp);
	result = PostfixCalculator(postfix_exp);

	printf("= %d", result);
	printf("\n\n");

	return 0;
}

int push(int c) {
	if (top >= MAX - 1) {
		printf("\nStack overflow");
		exit(1);
	}
	stack[++top] = c;

	return c;
}

int pop(void) {
	if (top < 0) {
		printf("\nStack is empty");
		exit(1);
	}
	return stack[top--];
}

int operator(int op) {
	if (op == '(') return 0;
	if (op == '+' || op == '-') return 1;
	if (op == '*' || op == '/') return 2;
	else return 3;
}

int PostfixCalculator(char* postfix) {
	int i;
	top = -1;
	while (*postfix) {
		if (*postfix >= '0' && *postfix <= '9') {
			i = 0;
			do {
				i = i * 10 + *postfix - '0';
				postfix++;
			} while (*postfix >= '0' && *postfix <= '9');
			push(i);
		}
		else if (*postfix == '+') {
			push(pop() + pop());
			postfix++;
		}

		else if (*postfix == '-') {
			i = pop();
			push(pop() - i);
			postfix++;
		}

		else if (*postfix == '*') {
			push(pop() * pop());
			postfix++;
		}

		else if (*postfix == '/') {
			i = pop();
			push(pop() / i);
			postfix++;
		}

		else postfix++;
	}
	return pop();
}

void InfixToPostfix(char* infix, char* postfix) {
	//char c = 0;
	top = -1;

	while (*infix) {
		if (*infix == '(') {
			push(*infix);
			infix++;
		}
		else if (*infix == ')') {
			while (stack[top] != '(') {
				*postfix++ = pop();
				*postfix++ = ' ';
			}
			pop();
			infix++;
		}
		else if (*infix == '+' || *infix == '-' || *infix == '*' || *infix == '/') {
			while (top >= 0 && operator(stack[top]) >= operator(*infix)) {
				*postfix++ = pop();
				*postfix++ = ' ';
			}
			push(*infix);
			infix++;
		}
		else if (*infix >= '0' && *infix <= '9') {
			do { *postfix++ = *infix++; } while (*infix >= '0' && *infix <= '9');
			*postfix++ = ' ';

		}
		else infix++;
	}
	while (top >= 0) {
		*postfix++ = pop();
		*postfix++ = ' ';
	}
	postfix--;
	*postfix = 0;
}
