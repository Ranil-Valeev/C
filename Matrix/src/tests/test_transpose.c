#include <check.h>

#include "matrix.h"

// ============================================
// Тесты для transpose
// ============================================

// ----- Валидные тесты -----

// Транспонирование матрицы 2x3
START_TEST(test_transpose_2x3) {
  matrix_t A, result;
  int rows = 2, cols = 3;

  s21_create_matrix(rows, cols, &A);

  // Заполняем матрицу A
  int count = 1;
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      A.matrix[i][j] = count++;
    }
  }

  int status = s21_transpose(&A, &result);

  ck_assert_int_eq(status, OK);
  ck_assert_int_eq(result.rows, cols);     // 3
  ck_assert_int_eq(result.columns, rows);  // 2

  // Проверяем транспонированную матрицу
  ck_assert_double_eq_tol(result.matrix[0][0], 1.0, 1e-7);
  ck_assert_double_eq_tol(result.matrix[0][1], 4.0, 1e-7);
  ck_assert_double_eq_tol(result.matrix[1][0], 2.0, 1e-7);
  ck_assert_double_eq_tol(result.matrix[1][1], 5.0, 1e-7);
  ck_assert_double_eq_tol(result.matrix[2][0], 3.0, 1e-7);
  ck_assert_double_eq_tol(result.matrix[2][1], 6.0, 1e-7);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

// Транспонирование матрицы 3x3 (квадратная)
START_TEST(test_transpose_3x3) {
  matrix_t A, result;
  int size = 3;

  s21_create_matrix(size, size, &A);

  // Заполняем матрицу A
  int count = 1;
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      A.matrix[i][j] = count++;
    }
  }

  int status = s21_transpose(&A, &result);

  ck_assert_int_eq(status, OK);
  ck_assert_int_eq(result.rows, size);
  ck_assert_int_eq(result.columns, size);

  // Проверяем транспонированную матрицу
  double expected[3][3] = {{1, 4, 7}, {2, 5, 8}, {3, 6, 9}};

  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      ck_assert_double_eq_tol(result.matrix[i][j], expected[i][j], 1e-7);
    }
  }

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

// Транспонирование матрицы 1x5 (вектор-строка)
START_TEST(test_transpose_1x5) {
  matrix_t A, result;
  int rows = 1, cols = 5;

  s21_create_matrix(rows, cols, &A);

  // Заполняем вектор-строку
  for (int j = 0; j < cols; j++) {
    A.matrix[0][j] = j + 1;
  }

  int status = s21_transpose(&A, &result);

  ck_assert_int_eq(status, OK);
  ck_assert_int_eq(result.rows, cols);     // 5
  ck_assert_int_eq(result.columns, rows);  // 1

  // Проверяем вектор-столбец
  for (int i = 0; i < cols; i++) {
    ck_assert_double_eq_tol(result.matrix[i][0], i + 1, 1e-7);
  }

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

// Транспонирование матрицы 5x1 (вектор-столбец)
START_TEST(test_transpose_5x1) {
  matrix_t A, result;
  int rows = 5, cols = 1;

  s21_create_matrix(rows, cols, &A);

  // Заполняем вектор-столбец
  for (int i = 0; i < rows; i++) {
    A.matrix[i][0] = i + 1;
  }

  int status = s21_transpose(&A, &result);

  ck_assert_int_eq(status, OK);
  ck_assert_int_eq(result.rows, cols);     // 1
  ck_assert_int_eq(result.columns, rows);  // 5

  // Проверяем вектор-строку
  for (int j = 0; j < rows; j++) {
    ck_assert_double_eq_tol(result.matrix[0][j], j + 1, 1e-7);
  }

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

// Транспонирование единичной матрицы
START_TEST(test_transpose_identity) {
  matrix_t A, result;
  int size = 4;

  s21_create_matrix(size, size, &A);

  // Создаем единичную матрицу
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      A.matrix[i][j] = (i == j) ? 1.0 : 0.0;
    }
  }

  int status = s21_transpose(&A, &result);

  ck_assert_int_eq(status, OK);

  // Единичная матрица не меняется при транспонировании
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      ck_assert_double_eq_tol(result.matrix[i][j], A.matrix[i][j], 1e-7);
    }
  }

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

// Транспонирование матрицы с нулевыми элементами
START_TEST(test_transpose_with_zeros) {
  matrix_t A, result;
  int rows = 3, cols = 4;

  s21_create_matrix(rows, cols, &A);

  // Заполняем матрицу с нулями
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      A.matrix[i][j] = (i + j) % 2 == 0 ? i * cols + j : 0.0;
    }
  }

  int status = s21_transpose(&A, &result);

  ck_assert_int_eq(status, OK);
  ck_assert_int_eq(result.rows, cols);
  ck_assert_int_eq(result.columns, rows);

  // Проверяем правильность транспонирования
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      ck_assert_double_eq_tol(result.matrix[j][i], A.matrix[i][j], 1e-7);
    }
  }

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

// Двойное транспонирование (должно вернуть исходную матрицу)
START_TEST(test_transpose_twice) {
  matrix_t A, transposed, result;
  int rows = 2, cols = 4;

  s21_create_matrix(rows, cols, &A);

  // Заполняем матрицу
  int count = 1;
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      A.matrix[i][j] = count++;
    }
  }

  // Первое транспонирование
  int status1 = s21_transpose(&A, &transposed);
  ck_assert_int_eq(status1, OK);

  // Второе транспонирование
  int status2 = s21_transpose(&transposed, &result);
  ck_assert_int_eq(status2, OK);

  // Результат должен быть равен исходной матрице
  ck_assert_int_eq(result.rows, rows);
  ck_assert_int_eq(result.columns, cols);

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      ck_assert_double_eq_tol(result.matrix[i][j], A.matrix[i][j], 1e-7);
    }
  }

  s21_remove_matrix(&A);
  s21_remove_matrix(&transposed);
  s21_remove_matrix(&result);
}
END_TEST

// ----- Невалидные тесты -----

// NULL матрица A
START_TEST(test_transpose_null_A) {
  matrix_t result;
  int status = s21_transpose(NULL, &result);
  ck_assert_int_eq(status, ERROR_INCORRECT_MATRIX);
}
END_TEST

// NULL результат
START_TEST(test_transpose_null_result) {
  matrix_t A;
  s21_create_matrix(2, 2, &A);

  int status = s21_transpose(&A, NULL);
  ck_assert_int_eq(status, ERROR_INCORRECT_MATRIX);

  s21_remove_matrix(&A);
}
END_TEST

// Некорректная матрица (NULL matrix)
START_TEST(test_transpose_invalid_matrix) {
  matrix_t A, result;
  A.matrix = NULL;
  A.rows = 2;
  A.columns = 2;

  int status = s21_transpose(&A, &result);
  ck_assert_int_eq(status, ERROR_INCORRECT_MATRIX);
}
END_TEST

// Матрица с нулевыми размерами
START_TEST(test_transpose_zero_size) {
  matrix_t A, result;
  s21_create_matrix(0, 0, &A);  // Должно вернуть ошибку, но проверим

  // Создаем некорректную матрицу напрямую
  A.rows = 0;
  A.columns = 0;
  A.matrix = NULL;

  int status = s21_transpose(&A, &result);
  ck_assert_int_eq(status, ERROR_INCORRECT_MATRIX);
}
END_TEST

// ============================================
// Создание набора тестов
// ============================================

Suite *transpose_suite(void) {
  Suite *s = suite_create("transpose");
  TCase *tc_core = tcase_create("core");

  // Валидные тесты
  tcase_add_test(tc_core, test_transpose_2x3);
  tcase_add_test(tc_core, test_transpose_3x3);
  tcase_add_test(tc_core, test_transpose_1x5);
  tcase_add_test(tc_core, test_transpose_5x1);
  tcase_add_test(tc_core, test_transpose_identity);
  tcase_add_test(tc_core, test_transpose_with_zeros);
  tcase_add_test(tc_core, test_transpose_twice);

  // Невалидные тесты
  tcase_add_test(tc_core, test_transpose_null_A);
  tcase_add_test(tc_core, test_transpose_null_result);
  tcase_add_test(tc_core, test_transpose_invalid_matrix);
  tcase_add_test(tc_core, test_transpose_zero_size);

  suite_add_tcase(s, tc_core);

  return s;
}