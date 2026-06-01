#include <check.h>
#include <stdlib.h>

#include "matrix.h"

// ============================================
// Тесты для mult_number
// ============================================

// Тест 1: Умножение матрицы 2x2 на положительное число
START_TEST(test_mult_number_2x2_positive) {
  matrix_t A = {0};
  matrix_t result = {0};

  ck_assert_int_eq(s21_create_matrix(2, 2, &A), OK);

  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[1][0] = 3;
  A.matrix[1][1] = 4;

  double number = 5;
  int status = s21_mult_number(&A, number, &result);

  ck_assert_int_eq(status, OK);
  ck_assert_int_eq(result.rows, 2);
  ck_assert_int_eq(result.columns, 2);

  ck_assert_double_eq_tol(result.matrix[0][0], 5.0, 1e-7);
  ck_assert_double_eq_tol(result.matrix[0][1], 10.0, 1e-7);
  ck_assert_double_eq_tol(result.matrix[1][0], 15.0, 1e-7);
  ck_assert_double_eq_tol(result.matrix[1][1], 20.0, 1e-7);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

// Тест 2: Умножение матрицы 3x3 на отрицательное число
START_TEST(test_mult_number_3x3_negative) {
  matrix_t A = {0};
  matrix_t result = {0};

  ck_assert_int_eq(s21_create_matrix(3, 3, &A), OK);

  A.matrix[0][0] = 1;
  A.matrix[0][1] = -2;
  A.matrix[0][2] = 3;
  A.matrix[1][0] = -4;
  A.matrix[1][1] = 5;
  A.matrix[1][2] = -6;
  A.matrix[2][0] = 7;
  A.matrix[2][1] = -8;
  A.matrix[2][2] = 9;

  double number = -2;
  int status = s21_mult_number(&A, number, &result);

  ck_assert_int_eq(status, OK);
  ck_assert_int_eq(result.rows, 3);
  ck_assert_int_eq(result.columns, 3);

  ck_assert_double_eq_tol(result.matrix[0][0], -2.0, 1e-7);
  ck_assert_double_eq_tol(result.matrix[0][1], 4.0, 1e-7);
  ck_assert_double_eq_tol(result.matrix[0][2], -6.0, 1e-7);
  ck_assert_double_eq_tol(result.matrix[1][0], 8.0, 1e-7);
  ck_assert_double_eq_tol(result.matrix[1][1], -10.0, 1e-7);
  ck_assert_double_eq_tol(result.matrix[1][2], 12.0, 1e-7);
  ck_assert_double_eq_tol(result.matrix[2][0], -14.0, 1e-7);
  ck_assert_double_eq_tol(result.matrix[2][1], 16.0, 1e-7);
  ck_assert_double_eq_tol(result.matrix[2][2], -18.0, 1e-7);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

// Тест 3: Умножение матрицы 1x1 на число
START_TEST(test_mult_number_1x1) {
  matrix_t A = {0};
  matrix_t result = {0};

  ck_assert_int_eq(s21_create_matrix(1, 1, &A), OK);

  A.matrix[0][0] = 8.8;

  double number = 2.5;
  int status = s21_mult_number(&A, number, &result);

  ck_assert_int_eq(status, OK);
  ck_assert_int_eq(result.rows, 1);
  ck_assert_int_eq(result.columns, 1);
  ck_assert_double_eq_tol(result.matrix[0][0], 22.0, 1e-7);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

// Тест 4: Умножение матрицы на ноль
START_TEST(test_mult_number_zero) {
  matrix_t A = {0};
  matrix_t result = {0};

  ck_assert_int_eq(s21_create_matrix(2, 2, &A), OK);

  A.matrix[0][0] = 5;
  A.matrix[0][1] = -3;
  A.matrix[1][0] = 2.5;
  A.matrix[1][1] = 7;

  double number = 0;
  int status = s21_mult_number(&A, number, &result);

  ck_assert_int_eq(status, OK);
  ck_assert_int_eq(result.rows, 2);
  ck_assert_int_eq(result.columns, 2);

  ck_assert_double_eq_tol(result.matrix[0][0], 0.0, 1e-7);
  ck_assert_double_eq_tol(result.matrix[0][1], 0.0, 1e-7);
  ck_assert_double_eq_tol(result.matrix[1][0], 0.0, 1e-7);
  ck_assert_double_eq_tol(result.matrix[1][1], 0.0, 1e-7);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

// Тест 5: Умножение матрицы на единицу
START_TEST(test_mult_number_one) {
  matrix_t A = {0};
  matrix_t result = {0};

  ck_assert_int_eq(s21_create_matrix(2, 2, &A), OK);

  A.matrix[0][0] = 3.5;
  A.matrix[0][1] = -2.1;
  A.matrix[1][0] = 7.8;
  A.matrix[1][1] = 4.3;

  double number = 1;
  int status = s21_mult_number(&A, number, &result);

  ck_assert_int_eq(status, OK);
  ck_assert_int_eq(result.rows, 2);
  ck_assert_int_eq(result.columns, 2);

  ck_assert_double_eq_tol(result.matrix[0][0], 3.5, 1e-7);
  ck_assert_double_eq_tol(result.matrix[0][1], -2.1, 1e-7);
  ck_assert_double_eq_tol(result.matrix[1][0], 7.8, 1e-7);
  ck_assert_double_eq_tol(result.matrix[1][1], 4.3, 1e-7);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

// Тест 6: Умножение на дробное число
START_TEST(test_mult_number_fractional) {
  matrix_t A = {0};
  matrix_t result = {0};

  ck_assert_int_eq(s21_create_matrix(2, 2, &A), OK);

  A.matrix[0][0] = 2;
  A.matrix[0][1] = 4;
  A.matrix[1][0] = 6;
  A.matrix[1][1] = 8;

  double number = 1.5;
  int status = s21_mult_number(&A, number, &result);

  ck_assert_int_eq(status, OK);
  ck_assert_int_eq(result.rows, 2);
  ck_assert_int_eq(result.columns, 2);

  ck_assert_double_eq_tol(result.matrix[0][0], 3.0, 1e-7);
  ck_assert_double_eq_tol(result.matrix[0][1], 6.0, 1e-7);
  ck_assert_double_eq_tol(result.matrix[1][0], 9.0, 1e-7);
  ck_assert_double_eq_tol(result.matrix[1][1], 12.0, 1e-7);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

// Тест 7: Умножение с некорректной матрицей A (не создана)
START_TEST(test_mult_number_invalid_A) {
  matrix_t A = {0};
  matrix_t result = {0};

  A.rows = -1;
  A.columns = 2;
  A.matrix = NULL;

  double number = 5;
  int status = s21_mult_number(&A, number, &result);

  ck_assert_int_eq(status, ERROR_INCORRECT_MATRIX);
}
END_TEST

// Тест 8: Умножение с NULL указателем result
START_TEST(test_mult_number_null_result) {
  matrix_t A = {0};

  ck_assert_int_eq(s21_create_matrix(2, 2, &A), OK);

  double number = 5;
  int status = s21_mult_number(&A, number, NULL);

  ck_assert_int_eq(status, ERROR_INCORRECT_MATRIX);

  s21_remove_matrix(&A);
}
END_TEST

// Тест 9: Умножение с NULL указателем A
START_TEST(test_mult_number_null_A) {
  matrix_t result = {0};

  double number = 5;
  int status = s21_mult_number(NULL, number, &result);

  ck_assert_int_eq(status, ERROR_INCORRECT_MATRIX);
}
END_TEST

// Тест 10: Умножение матрицы, содержащей нули
START_TEST(test_mult_number_with_zeros) {
  matrix_t A = {0};
  matrix_t result = {0};

  ck_assert_int_eq(s21_create_matrix(2, 2, &A), OK);

  A.matrix[0][0] = 0;
  A.matrix[0][1] = 5;
  A.matrix[1][0] = -3;
  A.matrix[1][1] = 0;

  double number = 4;
  int status = s21_mult_number(&A, number, &result);

  ck_assert_int_eq(status, OK);
  ck_assert_int_eq(result.rows, 2);
  ck_assert_int_eq(result.columns, 2);

  ck_assert_double_eq_tol(result.matrix[0][0], 0.0, 1e-7);
  ck_assert_double_eq_tol(result.matrix[0][1], 20.0, 1e-7);
  ck_assert_double_eq_tol(result.matrix[1][0], -12.0, 1e-7);
  ck_assert_double_eq_tol(result.matrix[1][1], 0.0, 1e-7);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

// Тест 11: Умножение на очень большое число
START_TEST(test_mult_number_large) {
  matrix_t A = {0};
  matrix_t result = {0};

  ck_assert_int_eq(s21_create_matrix(2, 2, &A), OK);

  A.matrix[0][0] = 1e-5;
  A.matrix[0][1] = 2e-5;
  A.matrix[1][0] = 3e-5;
  A.matrix[1][1] = 4e-5;

  double number = 1e10;
  int status = s21_mult_number(&A, number, &result);

  ck_assert_int_eq(status, OK);
  ck_assert_int_eq(result.rows, 2);
  ck_assert_int_eq(result.columns, 2);

  ck_assert_double_eq_tol(result.matrix[0][0], 1e5, 1e-5);
  ck_assert_double_eq_tol(result.matrix[0][1], 2e5, 1e-5);
  ck_assert_double_eq_tol(result.matrix[1][0], 3e5, 1e-5);
  ck_assert_double_eq_tol(result.matrix[1][1], 4e5, 1e-5);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

// Тест 12: Умножение на очень маленькое число
START_TEST(test_mult_number_small) {
  matrix_t A = {0};
  matrix_t result = {0};

  ck_assert_int_eq(s21_create_matrix(2, 2, &A), OK);

  A.matrix[0][0] = 1e5;
  A.matrix[0][1] = 2e5;
  A.matrix[1][0] = 3e5;
  A.matrix[1][1] = 4e5;

  double number = 1e-10;
  int status = s21_mult_number(&A, number, &result);

  ck_assert_int_eq(status, OK);
  ck_assert_int_eq(result.rows, 2);
  ck_assert_int_eq(result.columns, 2);

  ck_assert_double_eq_tol(result.matrix[0][0], 1e-5, 1e-5);
  ck_assert_double_eq_tol(result.matrix[0][1], 2e-5, 1e-5);
  ck_assert_double_eq_tol(result.matrix[1][0], 3e-5, 1e-5);
  ck_assert_double_eq_tol(result.matrix[1][1], 4e-5, 1e-5);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

// ============================================
// Создание набора тестов для mult_number
// ============================================

Suite *mult_number_suite(void) {
  Suite *s = suite_create("mult_number");
  TCase *tc = tcase_create("core");

  tcase_add_test(tc, test_mult_number_2x2_positive);
  tcase_add_test(tc, test_mult_number_3x3_negative);
  tcase_add_test(tc, test_mult_number_1x1);
  tcase_add_test(tc, test_mult_number_zero);
  tcase_add_test(tc, test_mult_number_one);
  tcase_add_test(tc, test_mult_number_fractional);
  tcase_add_test(tc, test_mult_number_invalid_A);
  tcase_add_test(tc, test_mult_number_null_result);
  tcase_add_test(tc, test_mult_number_null_A);
  tcase_add_test(tc, test_mult_number_with_zeros);
  tcase_add_test(tc, test_mult_number_large);
  tcase_add_test(tc, test_mult_number_small);

  suite_add_tcase(s, tc);
  return s;
}