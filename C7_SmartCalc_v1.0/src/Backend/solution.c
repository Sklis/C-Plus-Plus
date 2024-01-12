#include "smartCalc.h"

long double calculation(char op, char dop, stack_num **head) {
  long double temp = 0;
  long double result = 0;
  switch (op) {
    case '+':
      result = use_top_stack_num(head) + use_top_stack_num(head);
      break;
    case '*':
      result = use_top_stack_num(head) * use_top_stack_num(head);
      break;
    case '-':
      temp = use_top_stack_num(head);
      result = use_top_stack_num(head) - temp;
      break;
    case '/':
      temp = use_top_stack_num(head);
      result = use_top_stack_num(head) / temp;
      break;
    case '^':
      temp = use_top_stack_num(head);
      result = powl(use_top_stack_num(head), temp);
      break;
    case 'm':
      temp = use_top_stack_num(head);
      result = fmodl(use_top_stack_num(head), temp);
      break;
    case 's':
      switch (dop) {
        case 'q':
          result = sqrtl(use_top_stack_num(head));
          break;
        default:
          result = sinl(use_top_stack_num(head));
          break;
      }
      break;
    case 'c':
      result = cosl(use_top_stack_num(head));
      break;
    case 't':
      result = tanl(use_top_stack_num(head));
      break;
    case 'a':
      switch (dop) {
        case 's':
          result = asinl(use_top_stack_num(head));
          break;
        case 'c':
          result = acosl(use_top_stack_num(head));
          break;
        case 't':
          result = atanl(use_top_stack_num(head));
          break;
      }
      break;
    case 'l':
      switch (dop) {
        case 'n':
          result = logl(use_top_stack_num(head));
          break;
        case 'o':
          result = log10l(use_top_stack_num(head));
          break;
      }
      break;
  }
  return result;
}

int separation(char op) {
  int result = 0;
  switch (op) {
    case '+':
    case '*':
    case '-':
    case '/':
    case '^':
    case 'm':
      result = 2;
      break;
    case 's':
    case 'c':
    case 't':
    case 'a':
    case 'l':
      result = 1;
      break;
  }
  return result;
}

long double answer(char **str, double x, int *flag) {
  long double result = 0;
  stack_num *head = NULL;
  int stacksize = 0;
  long double temp;
  char op, dop = ' ';

  for (int i = 0; str[i]; i++) {
    char *token = str[i];

    if (is_number(token)) {
      if (!(strcmp(token, "x"))) {
        temp = x;
      } else if (!(strcmp(token, "-x"))) {
        temp = x;
        temp *= -1;
      } else if (!(strcmp(token, "pi"))) {
        temp = M_PI;
      } else if (!(strcmp(token, "-pi"))) {
        temp = M_PI;
        temp *= -1;
      } else {
        temp = atof(token);
      }
      creating_top_stack_num(&head, temp);
      stacksize++;
    } else {
      op = token[0];
      if (stacksize < separation(op)) {
        *flag = CALCULATION_ERROR;
        break;
      }
      if (strlen(token) > 1) dop = token[1];
      creating_top_stack_num(&head, calculation(op, dop, &head));
      stacksize -= separation(op) - 1;
    }
  }
  if (stacksize == 1) {
    result = use_top_stack_num(&head);
  } else {
    *flag = 1;
    while (stacksize) {
      use_top_stack_num(&head);
      stacksize--;
    }
  }

  return result;
}
