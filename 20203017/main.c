#include "calc.h"

int main(void)
{
	Stack stk;
	char infix[SIZE];
	Data postfix[SIZE];
	int length;
	int result = 0;
	int error = TRUE, flag = FALSE;
	char ch;
	while (TRUE)
	{
		init_stack(&stk);
		push(&stk, '_');
		for (int i = 0; i < SIZE; i++)
		{
			infix[i] = '_';
		}

		for (int i = 0; i < SIZE; i++)
		{
			postfix[i].num = -1;
			postfix[i].op = '_';
		}

		printf(">>>");
		fgets(infix, sizeof(infix), stdin);

		if (infix[0] == '\n')
		{
			printf("exit");
			break;
		}

		for (int i = 0; infix[i] != '\n'; i++)
		{
			if (flag == FALSE && (infix[i] == '+' || infix[i] == '-' || infix[i] == '*' || infix[i] == '/' || infix[i] == '%' || infix[i] == '^'))
			{
				printf("Infix error\n");
				error = FALSE;
				flag = TRUE;
				break;
			}
			else if ((infix[i] >= '0' && infix[i] <= '9') || infix[i] == ' ')
				flag = TRUE;
			else if (infix[i] == '+' || infix[i] == '-' || infix[i] == '*' || infix[i] == '/' || infix[i] == '%' || infix[i] == '^')
				flag = FALSE;
			else if (infix[i] == '(')
			{
				ch = infix[i];
				push(&stk, ch);
			}
			else if (infix[i] == ')')
			{
				if (top(&stk) == '_')
				{
					printf("Unmatched pair of parentheses\n");
					error = FALSE;
					flag = TRUE;
					break;
				}
				else
					pop(&stk);
			}
			else
			{
				printf("Input operator and operand\n");
				error = FALSE;
				flag = TRUE;
				break;
			}
		}
		if (top(&stk) != '_')
		{
			printf("Unmatched pair of parentheses\n");
			while (top(&stk) != '_')
				pop(&stk);
			pop(&stk);
			continue;
		}

		if (flag == FALSE)
		{
			printf("Infix error\n");
			flag = FALSE;
			continue;
		}
		else
			flag = FALSE;
		if (error == FALSE)
		{
			error = TRUE;
			flag = FALSE;
			continue;
		}
		length = toPostfix(infix, postfix);
		result = calculator(postfix, length, &error);
		if (error != FALSE)
		{
			printf("result %d\n", result);
			flag = FALSE;
		}
		else
		{
			error = TRUE;
			flag = FALSE;
			continue;
		}
	}
	return 0;
}