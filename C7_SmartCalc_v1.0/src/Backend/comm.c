#include "smartCalc.h"

int check_brackets_result(char *input_str, int *quantity) {
  int flag = OK;
  int left = 0;
  int right = 0;

  for (int i = 0; input_str[i] != '\0'; i++) {
    if (input_str[i] == '(')
      left++;
    else if (input_str[i] == ')') {
      right++;
      if (right > left) {
        *quantity = left - right;
        return EXTRA_BRACKET;
      }
    }
  }

  if (left > right) {
    flag = BRACKET_MISSING;
    *quantity = left - right;
  }

  return flag;
}

void to_lexems(char *input_str, char **lexems) {
  int lexcount = 0;
  char *del = strtok(input_str, "|");
  while (del != NULL) {
    lexems[lexcount++] = del;
    del = strtok(NULL, "|");
  }
}

char *look_last_char(stack_char **head) {
  stack_char *top = *head;
  return top->action;
}

void creating_top_stack_char(stack_char **head, char *value) {
  stack_char *node = malloc(sizeof(stack_char));

  if (node != NULL) {
    node->action = value;
    node->next = *head;
    *head = node;
  }
}

char *use_top_stack_char(stack_char **head) {
  stack_char *top = *head;
  char *value = top->action;
  *head = top->next;
  free(top);
  return value;
}

int is_number(char *number) {
  int flag = 1;
  char *str = number;

  if (strcmp(str, "-pi") == 0 || strcmp(str, "pi") == 0 ||
      strcmp(str, "-x") == 0) {
    return flag;
  }

  for (; *number; number++) {
    if ((*number == '-' || *number == '+') && strlen(str) == 1) {
      flag = 0;
      break;
    }
    if (*number != '.' && *number != '0' && *number != '1' && *number != '2' &&
        *number != '3' && *number != '4' && *number != '5' && *number != '6' &&
        *number != '7' && *number != '8' && *number != '9' && *number != '-' &&
        *number != '+' && *number != 'x') {
      flag = 0;
      break;
    }
  }

  return flag;
}

int is_function(char *string) {
  int flag = 0;
  if (!strcmp(string, "sin") || !strcmp(string, "cos") ||
      !strcmp(string, "tan") || !strcmp(string, "asin") ||
      !strcmp(string, "acos") || !strcmp(string, "atan") ||
      !strcmp(string, "sqrt") || !strcmp(string, "ln") ||
      !strcmp(string, "log")) {
    flag = 1;
  }

  return flag;
}

int is_operator(char *string) {
  int flag = 0;
  if (!strcmp(string, "+") || !strcmp(string, "-") || !strcmp(string, "*") ||
      !strcmp(string, "/") || !strcmp(string, "^") || !strcmp(string, "mod")) {
    flag = 1;
  }

  return flag;
}

int priority(char *string) {
  int result = 0;
  if (!strcmp(string, "-") || !strcmp(string, "+")) result = 1;
  if (!strcmp(string, "/") || !strcmp(string, "*") || !strcmp(string, "mod"))
    result = 2;
  if (!strcmp(string, "^")) result = 3;
  if (!strcmp(string, "sin") || !strcmp(string, "cos") ||
      !strcmp(string, "tan") || !strcmp(string, "asin") ||
      !strcmp(string, "acos") || !strcmp(string, "atan") ||
      !strcmp(string, "sqrt") || !strcmp(string, "ln") ||
      !strcmp(string, "log")) {
    result = 5;
  }
  return result;
}

void creating_top_stack_num(stack_num **head, long double value) {
  stack_num *node = malloc(sizeof(stack_num));

  if (node != NULL) {
    node->data = value;
    node->next = *head;
    *head = node;
  }
}

long double use_top_stack_num(stack_num **head) {
  long double value = 0;
  if (*head != NULL) {
    stack_num *top = *head;
    value = top->data;
    *head = top->next;
    free(top);
  }
  return value;
}
