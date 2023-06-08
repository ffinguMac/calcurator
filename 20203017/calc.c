#include "calc.h"

int calculator(Data* postfix, int length, int* error)
{
	Stack stk;
	int first_num, second_num, tmp;
	char op;
	int i;

	init_stack(&stk);
	for (i = 0; i < length; i++)
	{
		if (postfix[i].num == -1)
		{
			op = postfix[i].op;
			switch (op)
			{
			case '+':
				first_num = pop(&stk);
				second_num = pop(&stk);
				tmp = second_num + first_num;
				push(&stk, tmp);
				break;
			case '-':
				first_num = pop(&stk);
				second_num = pop(&stk);
				tmp = second_num - first_num;
				push(&stk, tmp);
				break;
			case '*':
				first_num = pop(&stk);
				second_num = pop(&stk);
				tmp = second_num * first_num;
				push(&stk, tmp);
				break;
			case '/':
				first_num = pop(&stk);
				second_num = pop(&stk);
				if (first_num == 0)
				{
					printf("Division by zero\n");
					*error = FALSE;
					return 0;
				}
				tmp = second_num / first_num;
				push(&stk, tmp);
				break;
			case '%':
				first_num = pop(&stk);
				second_num = pop(&stk);
				if (first_num == 0)
				{
					printf("Modulo by zero\n");
					*error = FALSE;
					return 0;
				}
				tmp = second_num % first_num;
				push(&stk, tmp);
				break;
			case '^':
				first_num = pop(&stk);
				second_num = pop(&stk);
				if (first_num < 0)
				{
					printf("Not negetive num\n");
					*error = FALSE;
					return 0;
				}
				tmp = to_pow(second_num, first_num);
				push(&stk, tmp);
				break;
			default:
				break;
			}
		}
		else
			push(&stk, postfix[i].num);
	}

	return pop(&stk);
}

int toPostfix(char* infix, Data* postfix)
{
	Queue que;
	Stack stk;
	int infix_idx = 0, postfix_idx = 0, num;
	int	flag_num = TRUE;
	char data, ch_data;
	init_queue(&que);
	init_stack(&stk);
	push(&stk, '_');
	while (TRUE)
	{
		data = infix[infix_idx++];
		switch (data)
		{
		case ' ':
			continue;
		case '_':
			while (top(&stk) != '_')
				postfix[postfix_idx++].op = pop(&stk);
			return postfix_idx;
		case ')':
			while ((ch_data = pop(&stk)) != '(')
				postfix[postfix_idx++].op = ch_data;
			break;
		case '+':
		case '-':
		case '*':
		case '/':
		case '%':
		case '^':
		case '(':
			while (stack_op(top(&stk)) >= new_op(data))
				postfix[postfix_idx++].op = pop(&stk);
			push(&stk, data);
			flag_num = TRUE;
			break;
		default:
			if (flag_num == TRUE)
			{
				num = to_int(&infix[infix_idx - 1]);
				enqueue(&que, num);
				postfix[postfix_idx++].num = dequeue(&que);
				flag_num = FALSE;
			}
			break;
		}
	}
	return postfix_idx;
}

int stack_op(int oper)
{
	int op;
	if (oper == '^')
		op = 4;
	else if (oper == '*' || oper == '/' || oper == '%')
		op = 3;
	else if (oper == '+' || oper == '-')
		op = 2;
	else if (oper == '(')
		op = 1;
	else if (oper == '_')
		op = 0;
	return op;
}

int new_op(int oper)
{
	int op;
	if (oper == '^' || oper == '(')
		op = 4;
	else if (oper == '*' || oper == '/' || oper == '%')
		op = 3;
	else if (oper == '+' || oper == '-')
		op = 2;
	return op;
}

int to_int(char* arr)
{
	int num = 0, idx = 0;
	while (arr[idx] && (arr[idx] >= '0' && arr[idx] <= '9'))
	{
		num = num * 10 + (arr[idx] - '0');
		idx++;
	}

	return num;
}

int to_pow(int nb, int pow)
{
	int	i = 0, result = 1;

	if (pow < 0)
		return (0);
	if (pow == 0)
		return (1);
	while (i < pow)
	{
		result *= nb;
		i++;
	}
	return result;
}