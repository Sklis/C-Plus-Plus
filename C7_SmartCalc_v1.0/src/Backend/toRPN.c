#include "smartCalc.h"

int lexems_to_RPN(char **lexems, char **tmp_out, char **RPN) {
  int flag = OK;
  stack_char *stack = NULL;
  for (int i = 0, j = 0; lexems[i]; i++) {
    char *token = lexems[i];
    if (is_number(token)) {
      tmp_out[j++] = lexems[i];
    } else if (is_function(token) || !strcmp(token, "(")) {
      creating_top_stack_char(&stack, token);
    } else if (stack && !strcmp(token, ")")) {
      while (stack && strcmp(stack->action, "(")) {
        tmp_out[j++] = use_top_stack_char(&stack);
      }
      if (stack) use_top_stack_char(&stack);
    } else if (is_operator(token)) {
      int score = priority(token);
      if (stack) {
        while (stack &&
               !(!strcmp(token, "^") && !strcmp(look_last_char(&stack), "^")) &&
               priority(look_last_char(&stack)) >= score) {
          tmp_out[j++] = use_top_stack_char(&stack);
        }
      }
      creating_top_stack_char(&stack, token);
    } else {
      flag = CALCULATION_ERROR;
      break;
    }
  }
  if (flag == OK) {
    for (int i = 0; tmp_out[i] || stack; i++) {
      if (tmp_out[i]) {
        RPN[i] = tmp_out[i];
      } else if (stack)
        RPN[i] = use_top_stack_char(&stack);
    }
  }

  return flag;
}
