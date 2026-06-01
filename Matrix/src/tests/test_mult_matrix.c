#include <check.h>

#include "matrix.h"

// ============================================
// Тесты для mult_matrix
// ============================================

// ----- Валидные тесты -----

// Умножение двух квадратных матриц 2x2
START_TEST(test_mult_matrix_2x2) {
  matrix_t A, B, result;
  double res_origin[2][2] = {{19, 22}, {43, 50}};

  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &B);

  // A = [[1, 2], [3, 4]]
  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[1][0] = 3;
  A.matrix[1][1] = 4;

  // B = [[5, 6], [7, 8]]
  B.matrix[0][0] = 5;
  B.matrix[0][1] = 6;
  B.matrix[1][0] = 7;
  B.matrix[1][1] = 8;

  int status = s21_mult_matrix(&A, &B, &result);

  ck_assert_int_eq(status, OK);
  ck_assert_int_eq(result.rows, 2);
  ck_assert_int_eq(result.columns, 2);

  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      ck_assert_double_eq_tol(result.matrix[i][j], res_origin[i][j], 1e-6);
    }
  }

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
}
END_TEST

// Умножение матрицы 2x3 на 3x2
START_TEST(test_mult_matrix_2x3_3x2) {
  matrix_t A, B, result;

  s21_create_matrix(2, 3, &A);
  s21_create_matrix(3, 2, &B);

  // A = [[1, 2, 3], [4, 5, 6]]
  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[0][2] = 3;
  A.matrix[1][0] = 4;
  A.matrix[1][1] = 5;
  A.matrix[1][2] = 6;

  // B = [[7, 8], [9, 10], [11, 12]]
  B.matrix[0][0] = 7;
  B.matrix[0][1] = 8;
  B.matrix[1][0] = 9;
  B.matrix[1][1] = 10;
  B.matrix[2][0] = 11;
  B.matrix[2][1] = 12;

  // Ожидаемый результат: [[58, 64], [139, 154]]
  double expected[2][2] = {{58, 64}, {139, 154}};

  int status = s21_mult_matrix(&A, &B, &result);

  ck_assert_int_eq(status, OK);
  ck_assert_int_eq(result.rows, 2);
  ck_assert_int_eq(result.columns, 2);

  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      ck_assert_double_eq_tol(result.matrix[i][j], expected[i][j], 1e-6);
    }
  }

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
}
END_TEST

// Умножение матрицы 3x2 на 2x3
START_TEST(test_mult_matrix_3x2_2x3) {
  matrix_t A, B, result;

  s21_create_matrix(3, 2, &A);
  s21_create_matrix(2, 3, &B);

  // A = [[1, 2], [3, 4], [5, 6]]
  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[1][0] = 3;
  A.matrix[1][1] = 4;
  A.matrix[2][0] = 5;
  A.matrix[2][1] = 6;

  // B = [[7, 8, 9], [10, 11, 12]]
  B.matrix[0][0] = 7;
  B.matrix[0][1] = 8;
  B.matrix[0][2] = 9;
  B.matrix[1][0] = 10;
  B.matrix[1][1] = 11;
  B.matrix[1][2] = 12;

  // Ожидаемый результат: [[27, 30, 33], [61, 68, 75], [95, 106, 117]]
  double expected[3][3] = {{27, 30, 33}, {61, 68, 75}, {95, 106, 117}};

  int status = s21_mult_matrix(&A, &B, &result);

  ck_assert_int_eq(status, OK);
  ck_assert_int_eq(result.rows, 3);
  ck_assert_int_eq(result.columns, 3);

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      ck_assert_double_eq_tol(result.matrix[i][j], expected[i][j], 1e-6);
    }
  }

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
}
END_TEST

// Умножение на единичную матрицу
START_TEST(test_mult_matrix_identity) {
  matrix_t A, I, result;

  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &I);

  // Заполняем A случайными числами
  double count = 1.0;
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      A.matrix[i][j] = count++;
    }
  }

  // Единичная матрица
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      I.matrix[i][j] = (i == j) ? 1.0 : 0.0;
    }
  }

  int status = s21_mult_matrix(&A, &I, &result);

  ck_assert_int_eq(status, OK);

  // A * I = A
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      ck_assert_double_eq_tol(result.matrix[i][j], A.matrix[i][j], 1e-6);
    }
  }

  s21_remove_matrix(&A);
  s21_remove_matrix(&I);
  s21_remove_matrix(&result);
}
END_TEST

// Умножение на нулевую матрицу
START_TEST(test_mult_matrix_zero) {
  matrix_t A, Zero, result;

  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &Zero);

  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[1][0] = 3;
  A.matrix[1][1] = 4;

  // Нулевая матрица
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      Zero.matrix[i][j] = 0.0;
    }
  }

  int status = s21_mult_matrix(&A, &Zero, &result);

  ck_assert_int_eq(status, OK);

  // A * 0 = 0
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      ck_assert_double_eq_tol(result.matrix[i][j], 0.0, 1e-6);
    }
  }

  s21_remove_matrix(&A);
  s21_remove_matrix(&Zero);
  s21_remove_matrix(&result);
}
END_TEST

// Умножение матрицы 2x5 на 5x2
START_TEST(test_mult_matrix_2x5_5x2) {
  matrix_t A, B, result;

  s21_create_matrix(2, 5, &A);
  s21_create_matrix(5, 2, &B);

  double count = 1.0;
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 5; j++) {
      A.matrix[i][j] = count++;
    }
  }

  count = 1.0;
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 2; j++) {
      B.matrix[i][j] = count++;
    }
  }

  double expected[2][2] = {{95, 110}, {220, 260}};

  int status = s21_mult_matrix(&A, &B, &result);

  ck_assert_int_eq(status, OK);
  ck_assert_int_eq(result.rows, 2);
  ck_assert_int_eq(result.columns, 2);

  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      ck_assert_double_eq_tol(result.matrix[i][j], expected[i][j], 1e-6);
    }
  }

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
}
END_TEST

// Векторные матрицы: A = 1x3 (вектор-строка), B = 5x1 (вектор-столбец) -
// НЕСОВМЕСТИМЫ!
START_TEST(test_mult_matrix_vector_incompatible) {
  matrix_t A, B, result;

  s21_create_matrix(1, 3, &A);  // вектор-строка
  s21_create_matrix(5, 1, &B);  // вектор-столбец

  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[0][2] = 3;

  B.matrix[0][0] = 4;
  B.matrix[1][0] = 5;
  B.matrix[2][0] = 6;
  B.matrix[3][0] = 7;
  B.matrix[4][0] = 8;

  // Несовместимы: A->columns = 3, B->rows = 5 → 3 ≠ 5
  int status = s21_mult_matrix(&A, &B, &result);

  ck_assert_int_eq(status, ERROR_CALCULATION);  // Должна быть ошибка

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

// Совместимые векторные матрицы: A = 1x3 (вектор-строка), B = 3x1
// (вектор-столбец)
START_TEST(test_mult_matrix_vector_compatible) {
  matrix_t A, B, result;

  s21_create_matrix(1, 3, &A);  // вектор-строка
  s21_create_matrix(3, 1, &B);  // вектор-столбец

  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[0][2] = 3;

  B.matrix[0][0] = 4;
  B.matrix[1][0] = 5;
  B.matrix[2][0] = 6;

  // Результат: 1x3 * 3x1 = 1x1 (скаляр)
  double expected = 32.0;  // 1*4 + 2*5 + 3*6 = 4 + 10 + 18 = 32

  int status = s21_mult_matrix(&A, &B, &result);

  ck_assert_int_eq(status, OK);
  ck_assert_int_eq(result.rows, 1);
  ck_assert_int_eq(result.columns, 1);

  ck_assert_double_eq_tol(result.matrix[0][0], expected, 1e-6);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
}
END_TEST

// Матрица A = 3x1 (вектор-столбец), B = 1x4 (вектор-строка)
START_TEST(test_mult_matrix_vector_3x1_1x4) {
  matrix_t A, B, result;

  s21_create_matrix(3, 1, &A);  // вектор-столбец
  s21_create_matrix(1, 4, &B);  // вектор-строка

  A.matrix[0][0] = 1;
  A.matrix[1][0] = 2;
  A.matrix[2][0] = 3;

  B.matrix[0][0] = 4;
  B.matrix[0][1] = 5;
  B.matrix[0][2] = 6;
  B.matrix[0][3] = 7;

  // Результат: 3x1 * 1x4 = 3x4 (матрица)
  double expected[3][4] = {{4, 5, 6, 7}, {8, 10, 12, 14}, {12, 15, 18, 21}};

  int status = s21_mult_matrix(&A, &B, &result);

  ck_assert_int_eq(status, OK);
  ck_assert_int_eq(result.rows, 3);
  ck_assert_int_eq(result.columns, 4);

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 4; j++) {
      ck_assert_double_eq_tol(result.matrix[i][j], expected[i][j], 1e-6);
    }
  }

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
}
END_TEST

// ----- Невалидные тесты -----

// Несовместимые размеры: A 2x3, B 2x2
START_TEST(test_mult_matrix_incompatible) {
  matrix_t A, B, result;

  s21_create_matrix(2, 3, &A);
  s21_create_matrix(2, 2, &B);

  int status = s21_mult_matrix(&A, &B, &result);

  ck_assert_int_eq(status, ERROR_CALCULATION);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

// NULL матрица A
START_TEST(test_mult_matrix_null_A) {
  matrix_t B, result;
  s21_create_matrix(2, 2, &B);

  int status = s21_mult_matrix(NULL, &B, &result);

  ck_assert_int_eq(status, ERROR_INCORRECT_MATRIX);

  s21_remove_matrix(&B);
}
END_TEST

// NULL матрица B
START_TEST(test_mult_matrix_null_B) {
  matrix_t A, result;
  s21_create_matrix(2, 2, &A);

  int status = s21_mult_matrix(&A, NULL, &result);

  ck_assert_int_eq(status, ERROR_INCORRECT_MATRIX);

  s21_remove_matrix(&A);
}
END_TEST

// NULL результат
START_TEST(test_mult_matrix_null_result) {
  matrix_t A, B;
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &B);

  int status = s21_mult_matrix(&A, &B, NULL);

  ck_assert_int_eq(status, ERROR_INCORRECT_MATRIX);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

// Матрица с нулевыми размерами
START_TEST(test_mult_matrix_zero_size) {
  matrix_t A, B, result;

  A.rows = 0;
  A.columns = 2;
  A.matrix = NULL;
  B.rows = 2;
  B.columns = 2;
  s21_create_matrix(2, 2, &B);

  int status = s21_mult_matrix(&A, &B, &result);

  ck_assert_int_eq(status, ERROR_INCORRECT_MATRIX);

  s21_remove_matrix(&B);
}
END_TEST

// ============================================
// Создание набора тестов
// ============================================

Suite *mult_matrix_suite(void) {
  Suite *s = suite_create("mult_matrix");
  TCase *tc_core = tcase_create("core");

  // Валидные тесты
  tcase_add_test(tc_core, test_mult_matrix_2x2);
  tcase_add_test(tc_core, test_mult_matrix_2x3_3x2);
  tcase_add_test(tc_core, test_mult_matrix_3x2_2x3);
  tcase_add_test(tc_core, test_mult_matrix_identity);
  tcase_add_test(tc_core, test_mult_matrix_zero);
  tcase_add_test(tc_core, test_mult_matrix_2x5_5x2);
  tcase_add_test(tc_core, test_mult_matrix_vector_incompatible);
  tcase_add_test(tc_core, test_mult_matrix_vector_compatible);
  tcase_add_test(tc_core, test_mult_matrix_vector_3x1_1x4);

  // Невалидные тесты
  tcase_add_test(tc_core, test_mult_matrix_incompatible);
  tcase_add_test(tc_core, test_mult_matrix_null_A);
  tcase_add_test(tc_core, test_mult_matrix_null_B);
  tcase_add_test(tc_core, test_mult_matrix_null_result);
  tcase_add_test(tc_core, test_mult_matrix_zero_size);

  suite_add_tcase(s, tc_core);

  return s;
}