#include "matrix.h"

// ============================================
// Тесты для create_matrix
// ============================================

// Тест 1: Создание матрицы 3x3
START_TEST(test_create_matrix_3x3) {
  matrix_t result;
  int rows = 3, cols = 3;

  int status = s21_create_matrix(rows, cols, &result);

  ck_assert_int_eq(status, OK);
  ck_assert_ptr_nonnull(result.matrix);
  ck_assert_int_eq(result.rows, rows);
  ck_assert_int_eq(result.columns, cols);

  // Проверяем, что все элементы инициализированы нулями
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      ck_assert_double_eq_tol(result.matrix[i][j], 0.0, 1e-7);
    }
  }

  s21_remove_matrix(&result);
}
END_TEST

// Тест 2: Создание матрицы 1x1
START_TEST(test_create_matrix_1x1) {
  matrix_t result;
  int rows = 1, cols = 1;

  int status = s21_create_matrix(rows, cols, &result);

  ck_assert_int_eq(status, OK);
  ck_assert_ptr_nonnull(result.matrix);
  ck_assert_int_eq(result.rows, rows);
  ck_assert_int_eq(result.columns, cols);
  ck_assert_double_eq_tol(result.matrix[0][0], 0.0, 1e-7);

  s21_remove_matrix(&result);
}
END_TEST

// Тест 3: Создание матрицы 5x1 (матрица-столбец)
START_TEST(test_create_matrix_5x1) {
  matrix_t result;
  int rows = 5, cols = 1;

  int status = s21_create_matrix(rows, cols, &result);

  ck_assert_int_eq(status, OK);
  ck_assert_ptr_nonnull(result.matrix);
  ck_assert_int_eq(result.rows, rows);
  ck_assert_int_eq(result.columns, cols);

  for (int i = 0; i < rows; i++) {
    ck_assert_double_eq_tol(result.matrix[i][0], 0.0, 1e-7);
  }

  s21_remove_matrix(&result);
}
END_TEST

// Тест 4: Создание матрицы 1x5 (матрица-строка)
START_TEST(test_create_matrix_1x5) {
  matrix_t result;
  int rows = 1, cols = 5;

  int status = s21_create_matrix(rows, cols, &result);

  ck_assert_int_eq(status, OK);
  ck_assert_ptr_nonnull(result.matrix);
  ck_assert_int_eq(result.rows, rows);
  ck_assert_int_eq(result.columns, cols);

  for (int j = 0; j < cols; j++) {
    ck_assert_double_eq_tol(result.matrix[0][j], 0.0, 1e-7);
  }

  s21_remove_matrix(&result);
}
END_TEST

// Тест 5: Создание матрицы с нулевыми строками (ошибка)
START_TEST(test_create_matrix_zero_rows) {
  matrix_t result;
  int status = s21_create_matrix(0, 3, &result);

  ck_assert_int_eq(status, ERROR_INCORRECT_MATRIX);
  // При ошибке матрица должна быть обнулена
  ck_assert_int_eq(result.rows, 0);
  ck_assert_int_eq(result.columns, 0);
  ck_assert_ptr_null(result.matrix);
}
END_TEST

// Тест 6: Создание матрицы с нулевыми столбцами (ошибка)
START_TEST(test_create_matrix_zero_cols) {
  matrix_t result;
  int status = s21_create_matrix(3, 0, &result);

  ck_assert_int_eq(status, ERROR_INCORRECT_MATRIX);
  ck_assert_int_eq(result.rows, 0);
  ck_assert_int_eq(result.columns, 0);
  ck_assert_ptr_null(result.matrix);
}
END_TEST

// Тест 7: Создание матрицы с отрицательными размерами (ошибка)
START_TEST(test_create_matrix_negative) {
  matrix_t result;
  int status = s21_create_matrix(-3, 3, &result);

  ck_assert_int_eq(status, ERROR_INCORRECT_MATRIX);
  ck_assert_int_eq(result.rows, 0);
  ck_assert_int_eq(result.columns, 0);
  ck_assert_ptr_null(result.matrix);
}
END_TEST

// Тест 8: Создание матрицы с NULL указателем (ошибка)
START_TEST(test_create_matrix_null_pointer) {
  int status = s21_create_matrix(3, 3, NULL);

  ck_assert_int_eq(status, ERROR_INCORRECT_MATRIX);
}
END_TEST

// ============================================
// Создание набора тестов для create_matrix
// ============================================

Suite *create_matrix_suite(void) {
  Suite *s = suite_create("create_matrix");
  TCase *tc = tcase_create("core");

  tcase_add_test(tc, test_create_matrix_3x3);
  tcase_add_test(tc, test_create_matrix_1x1);
  tcase_add_test(tc, test_create_matrix_5x1);
  tcase_add_test(tc, test_create_matrix_1x5);
  tcase_add_test(tc, test_create_matrix_zero_rows);
  tcase_add_test(tc, test_create_matrix_zero_cols);
  tcase_add_test(tc, test_create_matrix_negative);
  tcase_add_test(tc, test_create_matrix_null_pointer);

  suite_add_tcase(s, tc);
  return s;
}