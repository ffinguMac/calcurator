#include "calc.h"

double calculator(Data* postfix, int length, int* error)
{
  Stack stk;
  double first_num, second_num, tmp;
  char op;
  int log_flag = 0;
  init_stack(&stk);
  for (int i = 0; i < length; i++)
  {
    if (postfix[i].num == -1)
    {
      op = postfix[i].op;
      switch (op)
      {
      case '~':
        first_num = pop(&stk);
        second_num = 0;
        tmp = second_num - first_num;
        push(&stk, tmp);
        break;
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
        tmp = fmod(second_num, first_num);
        push(&stk, tmp);
        break;
      case '^':
        first_num = pop(&stk);
        second_num = pop(&stk);
        if (first_num < 0)
        {
          printf("Not negative num\n");
          *error = FALSE;
          return 0;
        }
        tmp = to_pow(second_num, first_num);
        push(&stk, tmp);
        break;
      case '!':
        if (log_flag == 10)
        {
          first_num = pop(&stk);
          if (first_num <= 0)
          {
            printf("Log10 value error\n");
            *error = FALSE;
            return 0;
          }
          tmp = log10(first_num);
          push(&stk, tmp);
          break;
        }
        else if (log_flag == 2)
        {
          first_num = pop(&stk);
          if (first_num <= 0)
          {
            printf("Log2 value error\n");
            *error = FALSE;
            return 0;
          }
          tmp = log2(first_num);
          push(&stk, tmp);
          break;
        }
      case 'L':
        log_flag = 10;
        continue;
      case 'l':
        log_flag = 2;
        continue;
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
  int infix_idx = 0, postfix_idx = 0;
  double num = 0;
  int flag_num = TRUE, flag_log = FALSE;
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
      if (flag_log == TRUE)
      {
        postfix[postfix_idx++].op = '!';
        flag_log = FALSE;
      }
      break;
    case '+':
    case '-':
      if (infix_idx == 1 || infix[infix_idx - 2] == '(')
        data = '~';
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
    case 'l':
      if (infix[infix_idx] == 'o' && infix[infix_idx + 1] == 'g')
      {
        infix_idx += 2;
        if (infix[infix_idx] == '1' && infix[infix_idx + 1] == '0')
        {
          flag_log = TRUE;
          infix_idx += 2;
          push(&stk, 'L');
          flag_num = FALSE;
        }
        else if (infix[infix_idx] == '2')
        {
          flag_log = TRUE;
          infix_idx++;
          push(&stk, 'l');
          flag_num = FALSE;
        }
      }
      break;
    default:
      if (flag_num == TRUE)
      {
        num = atof(&infix[infix_idx - 1]);
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
  if (oper == '^' || oper == 'L' || oper == 'l')
    op = 4;
  else if (oper == '*' || oper == '/' || oper == '%')
    op = 3;
  else if (oper == '+' || oper == '-' || oper == '~')
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
  if (oper == '^' || oper == '(' || oper == 'L' || oper == 'l')
    op = 4;
  else if (oper == '*' || oper == '/' || oper == '%')
    op = 3;
  else if (oper == '+' || oper == '-' || oper == '~')
    op = 2;
  return op;
}

double to_pow(double nb, double pow)
{
  int i = 0;
  double result = 1;

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