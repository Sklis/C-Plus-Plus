#ifndef TO_RPN_H
#define TO_RPN_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef M_PI
#define M_PI (3.14159265358979323846)
#endif

enum Error { OK, CALCULATION_ERROR, EXTRA_BRACKET, BRACKET_MISSING };

/// @brief Структура стека чисел
typedef struct stack_num {
  long double data;
  struct stack_num *next;
} stack_num;

/// @brief Стуктура стека строк
typedef struct stack_char {
  char *action;
  struct stack_char *next;
} stack_char;

/// @brief Проверяет количество правых и левых скобок
/// @param input_str Входная строка
/// @return Код ошибки и их разницу
int check_brackets_result(char *input_str, int *quantity);

/// @brief Преобразовывает входную строку в ликсемы
/// @param inpun_str входная строка
/// @param lexemas массим ликсем
void to_lexems(char *inpun_str, char **lexems);

/// @brief Создает новый верхний стек чисел
/// @param head Верхний стек
/// @param value переменная для создания нового элемента стека
void creating_top_stack_num(stack_num **head, long double value);

/// @brief Извлечение информации из верхнего стека чисел и его стирание
/// @param head Верхний стек
/// @return Значение верхнего стека
long double use_top_stack_num(stack_num **head);

/// @brief Производит вычисление
/// @param op Значение оператора
/// @param dop Значение функции
/// @param head стек чисел
/// @return Результат вычисления
long double calculation(char op, char dop, stack_num **head);

/// @brief Разделяет операторы от функций
/// @param op Входящее значение
/// @return Код оператора или функции
int separation(char op);

/// @brief Проверяет, является ли лексема цифрой
/// @param number Лексема
/// @return Код ошибки
int is_number(char *number);

/// @brief Обрабатывает обратную польскую нотацию
/// @param str Обратная польская нотация
/// @param x Значение переменной х
/// @param flag Контрольный флаг
/// @return Результат вычисления
long double answer(char **str, double x, int *flag);

/// @brief Смотрим на значение верхнего стека строк
/// @param head Верхний стек
/// @return Значение стека
char *look_last_char(stack_char **head);

/// @brief Создает новый верхний стек строк
/// @param head Верхний стек
/// @param value переменная для создания нового элемента стека
void creating_top_stack_char(stack_char **head, char *value);

/// @brief Извлечение информации из верхнего стека строк и его стирание
/// @param head Верхний стек
/// @return Значение верхнего стека
char *use_top_stack_char(stack_char **head);

/// @brief Проверяет, является ли лексема функцией
/// @param string Лексема
/// @return Код ошибки
int is_function(char *string);

/// @brief Проверяет, является ли лексема оператором
/// @param string Лексема
/// @return Код ошибки
int is_operator(char *string);

/// @brief Устанавливает приоритет выполнения операцый
/// @param string оператор или фкнкция
/// @return Код приоритета
int priority(char *string);

/// @brief Преобразовывает лексемы в обратную польскую нотацию
/// @param lexems Лексемы
/// @param tmp_out Временный массив
/// @param RPN Обратная польская нотация
/// @return Код ошибки
int lexems_to_RPN(char **lexems, char **tmp_out, char **RPN);
#endif  // TO_RPN_H
