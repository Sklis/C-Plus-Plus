#include <check.h>

#include "../Backend/smartCalc.h"

START_TEST(test_01) {
  int code = 0;
  long double result;
  char str[] = "1|+|2|+|3|+|4|*|7|*|8|^|3|^|2|";
  char* lexems[255] = {0};
  char* temp_out[255] = {0};
  char* RPN[255] = {0};
  to_lexems(str, lexems);
  lexems_to_RPN(lexems, temp_out, RPN);
  result = answer(RPN, 0, &code);
  ck_assert_ldouble_eq(result, 3758096390);
}
END_TEST

START_TEST(test_02) {
  int code = 0;
  long double result;
  char str[] = "-1|*|(|888.22|*|sin|(|888|-|+6|)|/|(|85|-|6|)|)";
  char* lexems[255] = {0};
  char* temp_out[255] = {0};
  char* RPN[255] = {0};
  to_lexems(str, lexems);
  lexems_to_RPN(lexems, temp_out, RPN);
  result = answer(RPN, 0, &code);
  ck_assert_ldouble_eq_tol(result, -7.9671827, 7);
}
END_TEST

START_TEST(test_03) {
  int code = 0;
  long double result;
  char str[] = "-1|*|(|888.22|*|sin|(|(|888|-|+6|)|^|3|^|2|)|/|(|85|-|6|)|)";
  char* lexems[255] = {0};
  char* temp_out[255] = {0};
  char* RPN[255] = {0};
  to_lexems(str, lexems);
  lexems_to_RPN(lexems, temp_out, RPN);
  result = answer(RPN, 0, &code);
  ck_assert_ldouble_eq_tol(result, -1.06930, 7);
}
END_TEST

START_TEST(test_04) {
  int code = 0;
  long double result;
  char str[] = "6.3|*|(|7.2|-|sqrt|(|5.6|)|)|*|6|mod|2";
  char* lexems[255] = {0};
  char* temp_out[255] = {0};
  char* RPN[255] = {0};
  to_lexems(str, lexems);
  lexems_to_RPN(lexems, temp_out, RPN);
  result = answer(RPN, 0, &code);
  ck_assert_ldouble_eq_tol(result, 0.708874, 7);
}
END_TEST

START_TEST(test_05) {
  int code = 0;
  long double result;
  char str[] = "sin|(|5|)|*|cos|(|10|)|-|tan|(|10|)";
  char* lexems[255] = {0};
  char* temp_out[255] = {0};
  char* RPN[255] = {0};
  to_lexems(str, lexems);
  lexems_to_RPN(lexems, temp_out, RPN);
  result = answer(RPN, 0, &code);
  ck_assert_ldouble_eq_tol(result, 0.1562452, 7);
}
END_TEST

START_TEST(test_06) {
  int code = 0;
  long double result;
  char str[] = "asin|(|0.68|)|*|acos|(|-0.2224|)|*|atan|(|0.00005|)";
  char* lexems[255] = {0};
  char* temp_out[255] = {0};
  char* RPN[255] = {0};
  to_lexems(str, lexems);
  lexems_to_RPN(lexems, temp_out, RPN);
  result = answer(RPN, 0, &code);
  ck_assert_ldouble_eq_tol(result, 0.0000671, 7);
}
END_TEST

START_TEST(test_07) {
  int code = 0;
  long double result;
  char str[] = "log|(|0.68|)|*|ln|(|0.2224|)|^|1|^|1|^|2";
  char* lexems[255] = {0};
  char* temp_out[255] = {0};
  char* RPN[255] = {0};
  to_lexems(str, lexems);
  lexems_to_RPN(lexems, temp_out, RPN);
  result = answer(RPN, 0, &code);
  ck_assert_ldouble_eq_tol(result, 0.2517856, 7);
}
END_TEST

START_TEST(test_08) {
  int code = 0;
  long double result;
  char str[] = "(|6.4|*|(|6|-|2|*|(|6|^|(|2|-|0|)|)|)|)";
  char* lexems[255] = {0};
  char* temp_out[255] = {0};
  char* RPN[255] = {0};
  to_lexems(str, lexems);
  lexems_to_RPN(lexems, temp_out, RPN);
  result = answer(RPN, 0, &code);
  ck_assert_ldouble_eq_tol(result, -422.4, 7);
}
END_TEST

START_TEST(test_09) {
  int code = 0;
  long double result;
  char str[] = "1|+|2";
  char* lexems[255] = {0};
  char* temp_out[255] = {0};
  char* RPN[255] = {0};
  to_lexems(str, lexems);
  lexems_to_RPN(lexems, temp_out, RPN);
  result = answer(RPN, 0, &code);
  ck_assert_ldouble_eq_tol(result, 3, 7);
}
END_TEST

START_TEST(test_10) {
  int code = 0;
  double x = 2;
  long double result;
  char str[] = "1|+|X|-|X";
  char* lexems[255] = {0};
  char* temp_out[255] = {0};
  char* RPN[255] = {0};
  to_lexems(str, lexems);
  lexems_to_RPN(lexems, temp_out, RPN);
  result = answer(RPN, x, &code);
  ck_assert_ldouble_eq_tol(result, 3, 7);
}
END_TEST

START_TEST(test_11) {
  int code = 0;
  double x = 2;
  char str[] = "1|+|1|-|";
  char* lexems[255] = {0};
  char* temp_out[255] = {0};
  char* RPN[255] = {0};
  to_lexems(str, lexems);
  lexems_to_RPN(lexems, temp_out, RPN);
  answer(RPN, x, &code);
  ck_assert_int_eq(code, 1);
}
END_TEST

START_TEST(test_12) {
  int code = 0;
  double x = 2;

  char str[] = "1|2|1|";
  char* lexems[255] = {0};
  char* temp_out[255] = {0};
  char* RPN[255] = {0};
  to_lexems(str, lexems);
  lexems_to_RPN(lexems, temp_out, RPN);
  answer(RPN, x, &code);
  ck_assert_int_eq(code, 1);
}
END_TEST

START_TEST(test_13) {
  int code = 0;
  char str[] = "1|+|1|-|(|(|1|-|1|)|";
  check_brackets_result(str, &code);
  ck_assert_int_eq(code, 1);
}
END_TEST

START_TEST(test_14) {
  int code = 0;
  char str[] = "1|+|1|-|(|1|-|1|)|)|";
  check_brackets_result(str, &code);
  ck_assert_int_eq(code, -1);
}
END_TEST

START_TEST(test_15) {
  int code = 0;
  double x = 2;

  char str[] = ")";
  char* lexems[255] = {0};
  char* temp_out[255] = {0};
  char* RPN[255] = {0};
  to_lexems(str, lexems);
  lexems_to_RPN(lexems, temp_out, RPN);
  answer(RPN, x, &code);
  ck_assert_int_eq(code, 1);
}
END_TEST

START_TEST(test_16) {
  int code = 0;
  long double result;
  char str[] = "1|+|-pi|";
  char* lexems[255] = {0};
  char* temp_out[255] = {0};
  char* RPN[255] = {0};
  to_lexems(str, lexems);
  lexems_to_RPN(lexems, temp_out, RPN);
  result = answer(RPN, 0, &code);
  ck_assert_ldouble_eq_tol(result, -2.141593, 7);
}
END_TEST

START_TEST(test_17) {
  int code = 0;
  long double result;
  char str[] = "1|+|pi|";
  char* lexems[255] = {0};
  char* temp_out[255] = {0};
  char* RPN[255] = {0};
  to_lexems(str, lexems);
  lexems_to_RPN(lexems, temp_out, RPN);
  result = answer(RPN, 0, &code);
  ck_assert_ldouble_eq_tol(result, 4.141593, 7);
}
END_TEST

START_TEST(test_18) {
  int code = 0;
  double x = -M_PI;
  long double result;
  char str[] = "1|+|-x|";
  char* lexems[255] = {0};
  char* temp_out[255] = {0};
  char* RPN[255] = {0};
  to_lexems(str, lexems);
  lexems_to_RPN(lexems, temp_out, RPN);
  result = answer(RPN, x, &code);
  ck_assert_ldouble_eq_tol(result, -2.141593, 7);
}
END_TEST

START_TEST(test_19) {
  int code = 0;
  double x = M_PI;
  long double result;
  char str[] = "1|+|x|";
  char* lexems[255] = {0};
  char* temp_out[255] = {0};
  char* RPN[255] = {0};
  to_lexems(str, lexems);
  lexems_to_RPN(lexems, temp_out, RPN);
  result = answer(RPN, x, &code);
  ck_assert_ldouble_eq_tol(result, 4.141593, 7);
}
END_TEST

int main(void) {
  Suite* s1 = suite_create("SmartCalc");
  TCase* tc1_1 = tcase_create("SmartCalc");
  SRunner* sr = srunner_create(s1);
  int nf;

  suite_add_tcase(s1, tc1_1);
  tcase_add_test(tc1_1, test_01);
  tcase_add_test(tc1_1, test_02);
  tcase_add_test(tc1_1, test_03);
  tcase_add_test(tc1_1, test_04);
  tcase_add_test(tc1_1, test_05);
  tcase_add_test(tc1_1, test_06);
  tcase_add_test(tc1_1, test_07);
  tcase_add_test(tc1_1, test_08);
  tcase_add_test(tc1_1, test_09);
  tcase_add_test(tc1_1, test_10);
  tcase_add_test(tc1_1, test_11);
  tcase_add_test(tc1_1, test_12);
  tcase_add_test(tc1_1, test_13);
  tcase_add_test(tc1_1, test_14);
  tcase_add_test(tc1_1, test_15);
  tcase_add_test(tc1_1, test_16);
  tcase_add_test(tc1_1, test_17);
  tcase_add_test(tc1_1, test_18);
  tcase_add_test(tc1_1, test_19);

  srunner_set_fork_status(sr, CK_NOFORK);
  srunner_run_all(sr, CK_VERBOSE);
  nf = srunner_ntests_failed(sr);
  srunner_free(sr);

  return nf == 0 ? 0 : 1;
}
