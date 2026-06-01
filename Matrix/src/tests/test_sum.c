#include "matrix.h"

// ============================================
// Тесты для sum_matrix
// ============================================

// Тест 1: Сложение двух матриц 2x2
START_TEST(test_sum_matrix_2x2) {
  matrix_t A, B, result;

  // Инициализация
  result.matrix = NULL;
  result.rows = 0;
  result.columns = 0;

  // Создание матриц
  ck_assert_int_eq(s21_create_matrix(2, 2, &A), OK);
  ck_assert_int_eq(s21_create_matrix(2, 2, &B), OK);

  // Заполнение матриц
  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[1][0] = 3;
  A.matrix[1][1] = 4;

  B.matrix[0][0] = 5;
  B.matrix[0][1] = 6;
  B.matrix[1][0] = 7;
  B.matrix[1][1] = 8;

  // Выполнение сложения
  int status = s21_sum_matrix(&A, &B, &result);

  // Проверка результата
  ck_assert_int_eq(status, OK);
  ck_assert_int_eq(result.rows, 2);
  ck_assert_int_eq(result.columns, 2);

  // Проверка значений
  ck_assert_double_eq_tol(result.matrix[0][0], 6.0, 1e-7);
  ck_assert_double_eq_tol(result.matrix[0][1], 8.0, 1e-7);
  ck_assert_double_eq_tol(result.matrix[1][0], 10.0, 1e-7);
  ck_assert_double_eq_tol(result.matrix[1][1], 12.0, 1e-7);

  // Очистка
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
}
END_TEST

// Тест 2: Сложение двух матриц 3x3
START_TEST(test_sum_matrix_3x3) {
  matrix_t A, B, result;

  result.matrix = NULL;
  result.rows = 0;
  result.columns = 0;

  ck_assert_int_eq(s21_create_matrix(3, 3, &A), OK);
  ck_assert_int_eq(s21_create_matrix(3, 3, &B), OK);

  // Заполнение матрицы A
  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[0][2] = 3;
  A.matrix[1][0] = 0;
  A.matrix[1][1] = 4;
  A.matrix[1][2] = 5;
  A.matrix[2][0] = 0;
  A.matrix[2][1] = 0;
  A.matrix[2][2] = 6;

  // Заполнение матрицы B
  B.matrix[0][0] = 1;
  B.matrix[0][1] = 0;
  B.matrix[0][2] = 0;
  B.matrix[1][0] = 2;
  B.matrix[1][1] = 0;
  B.matrix[1][2] = 0;
  B.matrix[2][0] = 3;
  B.matrix[2][1] = 4;
  B.matrix[2][2] = 1;

  int status = s21_sum_matrix(&A, &B, &result);

  ck_assert_int_eq(status, OK);

  // Проверка значений (пример из задания)
  ck_assert_double_eq_tol(result.matrix[0][0], 2.0, 1e-7);
  ck_assert_double_eq_tol(result.matrix[0][1], 2.0, 1e-7);
  ck_assert_double_eq_tol(result.matrix[0][2], 3.0, 1e-7);
  ck_assert_double_eq_tol(result.matrix[1][0], 2.0, 1e-7);
  ck_assert_double_eq_tol(result.matrix[1][1], 4.0, 1e-7);
  ck_assert_double_eq_tol(result.matrix[1][2], 5.0, 1e-7);
  ck_assert_double_eq_tol(result.matrix[2][0], 3.0, 1e-7);
  ck_assert_double_eq_tol(result.matrix[2][1], 4.0, 1e-7);
  ck_assert_double_eq_tol(result.matrix[2][2], 7.0, 1e-7);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
}
END_TEST

// Тест 3: Сложение матриц 1x1
START_TEST(test_sum_matrix_1x1) {
  matrix_t A, B, result;

  result.matrix = NULL;
  result.rows = 0;
  result.columns = 0;

  ck_assert_int_eq(s21_create_matrix(1, 1, &A), OK);
  ck_assert_int_eq(s21_create_matrix(1, 1, &B), OK);

  A.matrix[0][0] = 5.5;
  B.matrix[0][0] = 3.3;

  int status = s21_sum_matrix(&A, &B, &result);

  ck_assert_int_eq(status, OK);
  ck_assert_double_eq_tol(result.matrix[0][0], 8.8, 1e-7);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
}
END_TEST

// Тест 4: Сложение с отрицательными числами
START_TEST(test_sum_matrix_negative) {
  matrix_t A, B, result;

  result.matrix = NULL;
  result.rows = 0;
  result.columns = 0;

  ck_assert_int_eq(s21_create_matrix(2, 2, &A), OK);
  ck_assert_int_eq(s21_create_matrix(2, 2, &B), OK);

  A.matrix[0][0] = -1;
  A.matrix[0][1] = -2;
  A.matrix[1][0] = -3;
  A.matrix[1][1] = -4;

  B.matrix[0][0] = 5;
  B.matrix[0][1] = -6;
  B.matrix[1][0] = -7;
  B.matrix[1][1] = 8;

  int status = s21_sum_matrix(&A, &B, &result);

  ck_assert_int_eq(status, OK);
  ck_assert_double_eq_tol(result.matrix[0][0], 4.0, 1e-7);
  ck_assert_double_eq_tol(result.matrix[0][1], -8.0, 1e-7);
  ck_assert_double_eq_tol(result.matrix[1][0], -10.0, 1e-7);
  ck_assert_double_eq_tol(result.matrix[1][1], 4.0, 1e-7);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
}
END_TEST

// Тест 5: Сложение матриц разных размеров (ошибка)
START_TEST(test_sum_matrix_different_sizes) {
  matrix_t A, B, result;

  result.matrix = NULL;
  result.rows = 0;
  result.columns = 0;

  ck_assert_int_eq(s21_create_matrix(2, 2, &A), OK);
  ck_assert_int_eq(s21_create_matrix(3, 3, &B), OK);

  int status = s21_sum_matrix(&A, &B, &result);

  ck_assert_int_eq(status, ERROR_INCORRECT_MATRIX);
  ck_assert_ptr_null(result.matrix);  // result не должен быть создан

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

// Тест 6: Сложение с некорректной матрицей A
START_TEST(test_sum_matrix_invalid_A) {
  matrix_t A, B, result;

  result.matrix = NULL;
  result.rows = 0;
  result.columns = 0;

  ck_assert_int_eq(s21_create_matrix(2, 2, &A), OK);
  ck_assert_int_eq(s21_create_matrix(2, 2, &B), OK);

  // "Портим" матрицу A
  s21_remove_matrix(&A);

  int status = s21_sum_matrix(&A, &B, &result);

  ck_assert_int_eq(status, ERROR_INCORRECT_MATRIX);
  ck_assert_ptr_null(result.matrix);

  s21_remove_matrix(&B);
}
END_TEST

// Тест 7: Сложение с NULL указателем result
START_TEST(test_sum_matrix_null_result) {
  matrix_t A, B;

  ck_assert_int_eq(s21_create_matrix(2, 2, &A), OK);
  ck_assert_int_eq(s21_create_matrix(2, 2, &B), OK);

  int status = s21_sum_matrix(&A, &B, NULL);

  ck_assert_int_eq(status, ERROR_INCORRECT_MATRIX);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

// Тест 8: Сложение с нулевыми матрицами
START_TEST(test_sum_matrix_zero) {
  matrix_t A, B, result;

  result.matrix = NULL;
  result.rows = 0;
  result.columns = 0;

  ck_assert_int_eq(s21_create_matrix(2, 2, &A), OK);
  ck_assert_int_eq(s21_create_matrix(2, 2, &B), OK);

  // Матрицы уже заполнены нулями при создании

  int status = s21_sum_matrix(&A, &B, &result);

  ck_assert_int_eq(status, OK);
  ck_assert_double_eq_tol(result.matrix[0][0], 0.0, 1e-7);
  ck_assert_double_eq_tol(result.matrix[0][1], 0.0, 1e-7);
  ck_assert_double_eq_tol(result.matrix[1][0], 0.0, 1e-7);
  ck_assert_double_eq_tol(result.matrix[1][1], 0.0, 1e-7);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
}
END_TEST

// ============================================
// Создание набора тестов для sum_matrix
// ============================================

Suite *sum_matrix_suite(void) {
  Suite *s = suite_create("sum_matrix");
  TCase *tc = tcase_create("core");

  tcase_add_test(tc, test_sum_matrix_2x2);
  tcase_add_test(tc, test_sum_matrix_3x3);
  tcase_add_test(tc, test_sum_matrix_1x1);
  tcase_add_test(tc, test_sum_matrix_negative);
  tcase_add_test(tc, test_sum_matrix_different_sizes);
  tcase_add_test(tc, test_sum_matrix_invalid_A);
  tcase_add_test(tc, test_sum_matrix_null_result);
  tcase_add_test(tc, test_sum_matrix_zero);

  suite_add_tcase(s, tc);
  return s;
}