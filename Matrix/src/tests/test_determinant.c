#include <check.h>

#include "matrix.h"

// ============================================
// Тесты для determinant
// ============================================

// ----- Валидные матрицы -----

// Матрица 1x1
START_TEST(test_determinant_1x1) {
  matrix_t A;
  double result;

  s21_create_matrix(1, 1, &A);
  A.matrix[0][0] = 5.0;

  int status = s21_determinant(&A, &result);

  ck_assert_int_eq(status, OK);
  ck_assert_double_eq_tol(result, 5.0, 1e-6);

  s21_remove_matrix(&A);
}
END_TEST

// Матрица 2x2
START_TEST(test_determinant_2x2) {
  matrix_t A;
  double result;

  s21_create_matrix(2, 2, &A);
  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[1][0] = 3;
  A.matrix[1][1] = 4;

  int status = s21_determinant(&A, &result);

  ck_assert_int_eq(status, OK);
  ck_assert_double_eq_tol(result, -2.0, 1e-6);  // 1*4 - 2*3 = -2

  s21_remove_matrix(&A);
}
END_TEST

// Матрица 2x2 с нулями
START_TEST(test_determinant_2x2_zero) {
  matrix_t A;
  double result;

  s21_create_matrix(2, 2, &A);
  A.matrix[0][0] = 2;
  A.matrix[0][1] = 4;
  A.matrix[1][0] = 1;
  A.matrix[1][1] = 2;

  int status = s21_determinant(&A, &result);

  ck_assert_int_eq(status, OK);
  ck_assert_double_eq_tol(result, 0.0, 1e-6);  // 2*2 - 4*1 = 0

  s21_remove_matrix(&A);
}
END_TEST

// Матрица 3x3 (правило Саррюса)
START_TEST(test_determinant_3x3) {
  matrix_t A;
  double result;

  s21_create_matrix(3, 3, &A);
  A.matrix[0][0] = 2;
  A.matrix[0][1] = 1;
  A.matrix[0][2] = 3;
  A.matrix[1][0] = 4;
  A.matrix[1][1] = 2;
  A.matrix[1][2] = 2;
  A.matrix[2][0] = 1;
  A.matrix[2][1] = 3;
  A.matrix[2][2] = 4;

  int status = s21_determinant(&A, &result);

  ck_assert_int_eq(status, OK);
  ck_assert_double_eq_tol(result, 20.0, 1e-6);

  s21_remove_matrix(&A);
}
END_TEST

// Матрица 3x3 с нулевым определителем
START_TEST(test_determinant_3x3_zero) {
  matrix_t A;
  double result;

  s21_create_matrix(3, 3, &A);
  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[0][2] = 3;
  A.matrix[1][0] = 4;
  A.matrix[1][1] = 5;
  A.matrix[1][2] = 6;
  A.matrix[2][0] = 7;
  A.matrix[2][1] = 8;
  A.matrix[2][2] = 9;

  int status = s21_determinant(&A, &result);

  ck_assert_int_eq(status, OK);
  ck_assert_double_eq_tol(result, 0.0, 1e-6);

  s21_remove_matrix(&A);
}
END_TEST

// Матрица 4x4 (метод Гаусса)
START_TEST(test_determinant_4x4) {
  matrix_t A;
  double result;

  s21_create_matrix(4, 4, &A);
  A.matrix[0][0] = 2;
  A.matrix[0][1] = 1;
  A.matrix[0][2] = 3;
  A.matrix[0][3] = 1;
  A.matrix[1][0] = 4;
  A.matrix[1][1] = 2;
  A.matrix[1][2] = 2;
  A.matrix[1][3] = 5;
  A.matrix[2][0] = 1;
  A.matrix[2][1] = 3;
  A.matrix[2][2] = 4;
  A.matrix[2][3] = 2;
  A.matrix[3][0] = 3;
  A.matrix[3][1] = 1;
  A.matrix[3][2] = 2;
  A.matrix[3][3] = 3;

  int status = s21_determinant(&A, &result);

  ck_assert_int_eq(status, OK);
  ck_assert_double_eq_tol(result, 6.0, 1e-6);

  s21_remove_matrix(&A);
}
END_TEST

// Матрица 4x4 с нулевым определителем
START_TEST(test_determinant_4x4_zero) {
  matrix_t A;
  double result;

  s21_create_matrix(4, 4, &A);
  // Две одинаковые строки
  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[0][2] = 3;
  A.matrix[0][3] = 4;
  A.matrix[1][0] = 5;
  A.matrix[1][1] = 6;
  A.matrix[1][2] = 7;
  A.matrix[1][3] = 8;
  A.matrix[2][0] = 1;
  A.matrix[2][1] = 2;
  A.matrix[2][2] = 3;
  A.matrix[2][3] = 4;  // копия строки 0
  A.matrix[3][0] = 9;
  A.matrix[3][1] = 10;
  A.matrix[3][2] = 11;
  A.matrix[3][3] = 12;

  int status = s21_determinant(&A, &result);

  ck_assert_int_eq(status, OK);
  ck_assert_double_eq_tol(result, 0.0, 1e-6);

  s21_remove_matrix(&A);
}
END_TEST

// Единичная матрица 5x5
START_TEST(test_determinant_5x5_identity) {
  matrix_t A;
  double result;

  s21_create_matrix(5, 5, &A);
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 5; j++) {
      A.matrix[i][j] = (i == j) ? 1.0 : 0.0;
    }
  }

  int status = s21_determinant(&A, &result);

  ck_assert_int_eq(status, OK);
  ck_assert_double_eq_tol(result, 1.0, 1e-6);

  s21_remove_matrix(&A);
}
END_TEST

// Матрица 3x3 с отрицательными числами
START_TEST(test_determinant_3x3_negative) {
  matrix_t A;
  double result;

  s21_create_matrix(3, 3, &A);
  A.matrix[0][0] = -1;
  A.matrix[0][1] = 2;
  A.matrix[0][2] = -3;
  A.matrix[1][0] = 4;
  A.matrix[1][1] = -5;
  A.matrix[1][2] = 6;
  A.matrix[2][0] = -7;
  A.matrix[2][1] = 8;
  A.matrix[2][2] = -9;

  int status = s21_determinant(&A, &result);

  ck_assert_int_eq(status, OK);
  ck_assert_double_eq_tol(result, 0.0, 1e-6);  // Определитель = 0

  s21_remove_matrix(&A);
}
END_TEST

// ----- Невалидные матрицы -----

// Неквадратная матрица 2x5
START_TEST(test_determinant_2x5) {
  matrix_t A;
  double result;

  s21_create_matrix(2, 5, &A);

  int status = s21_determinant(&A, &result);

  ck_assert_int_eq(status, ERROR_INCORRECT_MATRIX);  // должна вернуть ошибку

  s21_remove_matrix(&A);
}
END_TEST

// Неквадратная матрица 5x1
START_TEST(test_determinant_5x1) {
  matrix_t A;
  double result;

  s21_create_matrix(5, 1, &A);

  int status = s21_determinant(&A, &result);

  ck_assert_int_eq(status, ERROR_INCORRECT_MATRIX);

  s21_remove_matrix(&A);
}
END_TEST

// NULL указатель на матрицу
START_TEST(test_determinant_null_matrix) {
  double result;
  int status = s21_determinant(NULL, &result);
  ck_assert_int_eq(status, ERROR_INCORRECT_MATRIX);
}
END_TEST

// NULL указатель на результат
START_TEST(test_determinant_null_result) {
  matrix_t A;
  s21_create_matrix(2, 2, &A);

  int status = s21_determinant(&A, NULL);

  ck_assert_int_eq(status, ERROR_INCORRECT_MATRIX);

  s21_remove_matrix(&A);
}
END_TEST

// Матрица с нулевыми размерами
START_TEST(test_determinant_zero_size) {
  matrix_t A;
  double result;

  A.rows = 0;
  A.columns = 0;
  A.matrix = NULL;

  int status = s21_determinant(&A, &result);
  ck_assert_int_eq(status, ERROR_INCORRECT_MATRIX);
}
END_TEST

// ============================================
// Создание набора тестов
// ============================================

Suite *determinant_suite(void) {
  Suite *s = suite_create("determinant");
  TCase *tc_core = tcase_create("core");

  // Валидные тесты
  tcase_add_test(tc_core, test_determinant_1x1);
  tcase_add_test(tc_core, test_determinant_2x2);
  tcase_add_test(tc_core, test_determinant_2x2_zero);
  tcase_add_test(tc_core, test_determinant_3x3);
  tcase_add_test(tc_core, test_determinant_3x3_zero);
  tcase_add_test(tc_core, test_determinant_4x4);
  tcase_add_test(tc_core, test_determinant_4x4_zero);
  tcase_add_test(tc_core, test_determinant_5x5_identity);
  tcase_add_test(tc_core, test_determinant_3x3_negative);

  // Невалидные тесты
  tcase_add_test(tc_core, test_determinant_2x5);
  tcase_add_test(tc_core, test_determinant_5x1);
  tcase_add_test(tc_core, test_determinant_null_matrix);
  tcase_add_test(tc_core, test_determinant_null_result);
  tcase_add_test(tc_core, test_determinant_zero_size);

  suite_add_tcase(s, tc_core);

  return s;
}