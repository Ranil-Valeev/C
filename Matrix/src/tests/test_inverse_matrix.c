#include <check.h>

#include "matrix.h"

// ============================================
// Тесты для inverse_matrix
// ============================================

// ----- Валидные тесты -----

// Тест 1: Матрица 1x1
START_TEST(test_inverse_1x1) {
  matrix_t A, result;
  s21_create_matrix(1, 1, &A);
  A.matrix[0][0] = 5.0;

  int status = s21_inverse_matrix(&A, &result);

  ck_assert_int_eq(status, OK);
  ck_assert_int_eq(result.rows, 1);
  ck_assert_int_eq(result.columns, 1);
  ck_assert_double_eq_tol(result.matrix[0][0], 0.2, 1e-7);  // 1/5 = 0.2

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

// Тест 2: Матрица 2x2
START_TEST(test_inverse_2x2) {
  matrix_t A, result;
  s21_create_matrix(2, 2, &A);
  A.matrix[0][0] = 4;
  A.matrix[0][1] = 7;
  A.matrix[1][0] = 2;
  A.matrix[1][1] = 6;

  int status = s21_inverse_matrix(&A, &result);

  ck_assert_int_eq(status, OK);

  // Ожидаемая обратная матрица:
  // 1/(4*6 - 7*2) = 1/(24 - 14) = 1/10 = 0.1
  // [6, -7; -2, 4] * 0.1 = [0.6, -0.7; -0.2, 0.4]
  ck_assert_double_eq_tol(result.matrix[0][0], 0.6, 1e-7);
  ck_assert_double_eq_tol(result.matrix[0][1], -0.7, 1e-7);
  ck_assert_double_eq_tol(result.matrix[1][0], -0.2, 1e-7);
  ck_assert_double_eq_tol(result.matrix[1][1], 0.4, 1e-7);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

// Тест 3: Единичная матрица 3x3
START_TEST(test_inverse_identity_3x3) {
  matrix_t A, result;
  s21_create_matrix(3, 3, &A);

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      A.matrix[i][j] = (i == j) ? 1.0 : 0.0;
    }
  }

  int status = s21_inverse_matrix(&A, &result);

  ck_assert_int_eq(status, OK);

  // Обратная единичной - тоже единичная
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      double expected = (i == j) ? 1.0 : 0.0;
      ck_assert_double_eq_tol(result.matrix[i][j], expected, 1e-7);
    }
  }

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

// Тест 4: Матрица 3x3
START_TEST(test_inverse_3x3) {
  matrix_t A, result;
  s21_create_matrix(3, 3, &A);
  A.matrix[0][0] = 2;
  A.matrix[0][1] = 5;
  A.matrix[0][2] = 7;
  A.matrix[1][0] = 6;
  A.matrix[1][1] = 3;
  A.matrix[1][2] = 4;
  A.matrix[2][0] = 5;
  A.matrix[2][1] = -2;
  A.matrix[2][2] = -3;

  int status = s21_inverse_matrix(&A, &result);

  ck_assert_int_eq(status, OK);

  // Ожидаемая обратная матрица (вычислено заранее)
  double expected[3][3] = {{1, -1, 1}, {-38, 41, -34}, {27, -29, 24}};

  // Проверяем с погрешностью
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      ck_assert_double_eq_tol(result.matrix[i][j], expected[i][j], 1e-6);
    }
  }

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

// Тест 5: Проверка A * A^(-1) = I для матрицы 2x2
START_TEST(test_inverse_multiply_check) {
  matrix_t A, inverse, product;
  s21_create_matrix(2, 2, &A);
  A.matrix[0][0] = 4;
  A.matrix[0][1] = 3;
  A.matrix[1][0] = 3;
  A.matrix[1][1] = 2;

  int status = s21_inverse_matrix(&A, &inverse);
  ck_assert_int_eq(status, OK);

  status = s21_mult_matrix(&A, &inverse, &product);
  ck_assert_int_eq(status, OK);

  // Проверяем, что A * A^(-1) = I
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      double expected = (i == j) ? 1.0 : 0.0;
      ck_assert_double_eq_tol(product.matrix[i][j], expected, 1e-7);
    }
  }

  s21_remove_matrix(&A);
  s21_remove_matrix(&inverse);
  s21_remove_matrix(&product);
}
END_TEST

// Тест 6: Диагональная матрица 4x4
START_TEST(test_inverse_diagonal_4x4) {
  matrix_t A, result;
  s21_create_matrix(4, 4, &A);

  // Заполняем диагональную матрицу
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      A.matrix[i][j] = (i == j) ? (i + 2) : 0.0;
    }
  }

  int status = s21_inverse_matrix(&A, &result);
  ck_assert_int_eq(status, OK);

  // Обратная диагональной - диагональная с обратными элементами
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (i == j) {
        ck_assert_double_eq_tol(result.matrix[i][j], 1.0 / (i + 2), 1e-7);
      } else {
        ck_assert_double_eq_tol(result.matrix[i][j], 0.0, 1e-7);
      }
    }
  }

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

// ----- Невалидные тесты -----

// Тест 7: Неквадратная матрица 2x3
START_TEST(test_inverse_not_square) {
  matrix_t A, result;
  s21_create_matrix(2, 3, &A);

  int status = s21_inverse_matrix(&A, &result);
  ck_assert_int_eq(status, ERROR_CALCULATION);

  s21_remove_matrix(&A);
}
END_TEST

// Тест 8: Матрица с нулевым определителем
START_TEST(test_inverse_zero_det) {
  matrix_t A, result;
  s21_create_matrix(2, 2, &A);
  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[1][0] = 2;
  A.matrix[1][1] = 4;  // det = 0

  int status = s21_inverse_matrix(&A, &result);
  ck_assert_int_eq(status, ERROR_CALCULATION);

  s21_remove_matrix(&A);
}
END_TEST

// Тест 9: NULL матрица
START_TEST(test_inverse_null_matrix) {
  matrix_t result;
  int status = s21_inverse_matrix(NULL, &result);
  ck_assert_int_eq(status, ERROR_INCORRECT_MATRIX);
}
END_TEST

// Тест 10: NULL результат
START_TEST(test_inverse_null_result) {
  matrix_t A;
  s21_create_matrix(2, 2, &A);

  int status = s21_inverse_matrix(&A, NULL);
  ck_assert_int_eq(status, ERROR_INCORRECT_MATRIX);

  s21_remove_matrix(&A);
}
END_TEST

// Тест 11: Матрица с некорректными данными
START_TEST(test_inverse_invalid_matrix) {
  matrix_t A, result;
  A.matrix = NULL;
  A.rows = 2;
  A.columns = 2;

  int status = s21_inverse_matrix(&A, &result);
  ck_assert_int_eq(status, ERROR_INCORRECT_MATRIX);
}
END_TEST

// Тест 12: Матрица с отрицательными размерами
START_TEST(test_inverse_negative_size) {
  matrix_t A, result;
  A.matrix = NULL;
  A.rows = -2;
  A.columns = 2;

  int status = s21_inverse_matrix(&A, &result);
  ck_assert_int_eq(status, ERROR_INCORRECT_MATRIX);
}
END_TEST

// ============================================
// Создание набора тестов
// ============================================

Suite *inverse_matrix_suite(void) {
  Suite *s = suite_create("inverse_matrix");
  TCase *tc_core = tcase_create("core");

  // Валидные тесты
  tcase_add_test(tc_core, test_inverse_1x1);
  tcase_add_test(tc_core, test_inverse_2x2);
  tcase_add_test(tc_core, test_inverse_identity_3x3);
  tcase_add_test(tc_core, test_inverse_3x3);
  tcase_add_test(tc_core, test_inverse_multiply_check);
  tcase_add_test(tc_core, test_inverse_diagonal_4x4);

  // Невалидные тесты
  tcase_add_test(tc_core, test_inverse_not_square);
  tcase_add_test(tc_core, test_inverse_zero_det);
  tcase_add_test(tc_core, test_inverse_null_matrix);
  tcase_add_test(tc_core, test_inverse_null_result);
  tcase_add_test(tc_core, test_inverse_invalid_matrix);
  tcase_add_test(tc_core, test_inverse_negative_size);

  suite_add_tcase(s, tc_core);

  return s;
}