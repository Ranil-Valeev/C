#include <check.h>

#include "matrix.h"

// ============================================
// Тесты для s21_minor_matrix
// ============================================

// Тест 1: Создание минора 2x2 из матрицы 3x3
START_TEST(test_minor_matrix_3x3_to_2x2) {
  matrix_t A, result;
  s21_create_matrix(3, 3, &A);

  // Заполняем матрицу
  int count = 1;
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      A.matrix[i][j] = count++;
    }
  }

  int status = s21_minor_matrix(&A, 1, 1, &result);

  ck_assert_int_eq(status, OK);
  ck_assert_int_eq(result.rows, 2);
  ck_assert_int_eq(result.columns, 2);

  // Проверяем значения минора (без строки 1 и столбца 1)
  ck_assert_double_eq_tol(result.matrix[0][0], 1.0, 1e-7);
  ck_assert_double_eq_tol(result.matrix[0][1], 3.0, 1e-7);
  ck_assert_double_eq_tol(result.matrix[1][0], 7.0, 1e-7);
  ck_assert_double_eq_tol(result.matrix[1][1], 9.0, 1e-7);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

// Тест 2: Создание минора с исключением первой строки и первого столбца
START_TEST(test_minor_matrix_exclude_0_0) {
  matrix_t A, result;
  s21_create_matrix(3, 3, &A);

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      A.matrix[i][j] = i * 3 + j + 1;
    }
  }

  int status = s21_minor_matrix(&A, 0, 0, &result);

  ck_assert_int_eq(status, OK);

  // Ожидаемый минор: [[5, 6], [8, 9]]
  ck_assert_double_eq_tol(result.matrix[0][0], 5.0, 1e-7);
  ck_assert_double_eq_tol(result.matrix[0][1], 6.0, 1e-7);
  ck_assert_double_eq_tol(result.matrix[1][0], 8.0, 1e-7);
  ck_assert_double_eq_tol(result.matrix[1][1], 9.0, 1e-7);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

// Тест 3: Создание минора с исключением последней строки и последнего столбца
START_TEST(test_minor_matrix_exclude_last) {
  matrix_t A, result;
  s21_create_matrix(3, 3, &A);

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      A.matrix[i][j] = i * 3 + j + 1;
    }
  }

  int status = s21_minor_matrix(&A, 2, 2, &result);

  ck_assert_int_eq(status, OK);

  // Ожидаемый минор: [[1, 2], [4, 5]]
  ck_assert_double_eq_tol(result.matrix[0][0], 1.0, 1e-7);
  ck_assert_double_eq_tol(result.matrix[0][1], 2.0, 1e-7);
  ck_assert_double_eq_tol(result.matrix[1][0], 4.0, 1e-7);
  ck_assert_double_eq_tol(result.matrix[1][1], 5.0, 1e-7);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

// Тест 4: Создание минора из неквадратной матрицы 3x4
START_TEST(test_minor_matrix_3x4) {
  matrix_t A, result;
  s21_create_matrix(3, 4, &A);

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 4; j++) {
      A.matrix[i][j] = i * 4 + j + 1;
    }
  }

  int status = s21_minor_matrix(&A, 1, 2, &result);

  ck_assert_int_eq(status, OK);
  ck_assert_int_eq(result.rows, 2);
  ck_assert_int_eq(result.columns, 3);

  // Проверяем несколько значений
  ck_assert_double_eq_tol(result.matrix[0][0], 1.0, 1e-7);   // [0][0]
  ck_assert_double_eq_tol(result.matrix[0][1], 2.0, 1e-7);   // [0][1]
  ck_assert_double_eq_tol(result.matrix[0][2], 4.0, 1e-7);   // [0][3]
  ck_assert_double_eq_tol(result.matrix[1][0], 9.0, 1e-7);   // [2][0]
  ck_assert_double_eq_tol(result.matrix[1][2], 12.0, 1e-7);  // [2][3]

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

// Тест 5: Ошибка - матрица 1x1 (нельзя создать минор)
START_TEST(test_minor_matrix_1x1_error) {
  matrix_t A, result;
  s21_create_matrix(1, 1, &A);
  A.matrix[0][0] = 5.0;

  int status = s21_minor_matrix(&A, 0, 0, &result);

  ck_assert_int_eq(status, ERROR_CALCULATION);

  s21_remove_matrix(&A);
}
END_TEST

// Тест 6: Ошибка - NULL матрица
START_TEST(test_minor_matrix_null) {
  matrix_t result;
  int status = s21_minor_matrix(NULL, 0, 0, &result);
  ck_assert_int_eq(status, ERROR_INCORRECT_MATRIX);
}
END_TEST

// ============================================
// Тесты для s21_calc_complements
// ============================================

// Тест 7: Матрица 1x1
START_TEST(test_calc_complements_1x1) {
  matrix_t A, result;
  s21_create_matrix(1, 1, &A);
  A.matrix[0][0] = 5.0;

  int status = s21_calc_complements(&A, &result);

  ck_assert_int_eq(status, OK);
  ck_assert_int_eq(result.rows, 1);
  ck_assert_int_eq(result.columns, 1);
  ck_assert_double_eq_tol(result.matrix[0][0], 1.0, 1e-7);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

// Тест 8: Матрица 2x2
START_TEST(test_calc_complements_2x2) {
  matrix_t A, result;
  s21_create_matrix(2, 2, &A);
  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[1][0] = 3;
  A.matrix[1][1] = 4;

  int status = s21_calc_complements(&A, &result);

  ck_assert_int_eq(status, OK);

  // Ожидаемый результат: [[4, -3], [-2, 1]]
  ck_assert_double_eq_tol(result.matrix[0][0], 4.0, 1e-7);
  ck_assert_double_eq_tol(result.matrix[0][1], -3.0, 1e-7);
  ck_assert_double_eq_tol(result.matrix[1][0], -2.0, 1e-7);
  ck_assert_double_eq_tol(result.matrix[1][1], 1.0, 1e-7);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

// Тест 9: Матрица 3x3
START_TEST(test_calc_complements_3x3) {
  matrix_t A, result;
  s21_create_matrix(3, 3, &A);
  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[0][2] = 3;
  A.matrix[1][0] = 0;
  A.matrix[1][1] = 4;
  A.matrix[1][2] = 5;
  A.matrix[2][0] = 1;
  A.matrix[2][1] = 0;
  A.matrix[2][2] = 6;

  int status = s21_calc_complements(&A, &result);

  ck_assert_int_eq(status, OK);

  // Ожидаемые значения (вычислены вручную или через известные формулы)
  ck_assert_double_eq_tol(result.matrix[0][0], 24.0, 1e-7);
  ck_assert_double_eq_tol(result.matrix[0][1], 5.0, 1e-7);
  ck_assert_double_eq_tol(result.matrix[0][2], -4.0, 1e-7);
  ck_assert_double_eq_tol(result.matrix[1][0], -12.0, 1e-7);
  ck_assert_double_eq_tol(result.matrix[1][1], 3.0, 1e-7);
  ck_assert_double_eq_tol(result.matrix[1][2], 2.0, 1e-7);
  ck_assert_double_eq_tol(result.matrix[2][0], -2.0, 1e-7);
  ck_assert_double_eq_tol(result.matrix[2][1], -5.0, 1e-7);
  ck_assert_double_eq_tol(result.matrix[2][2], 4.0, 1e-7);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

// Тест 10: Матрица 3x3 с нулевым определителем
START_TEST(test_calc_complements_3x3_zero_det) {
  matrix_t A, result;
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

  int status = s21_calc_complements(&A, &result);

  ck_assert_int_eq(status, OK);

  // Проверяем несколько значений (они могут быть ненулевыми даже при det=0)
  ck_assert_double_eq_tol(result.matrix[0][0], -3.0, 1e-7);
  ck_assert_double_eq_tol(result.matrix[0][1], 6.0, 1e-7);
  ck_assert_double_eq_tol(result.matrix[0][2], -3.0, 1e-7);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

// Тест 11: Неквадратная матрица 2x3 (ошибка)
START_TEST(test_calc_complements_not_square) {
  matrix_t A, result;
  s21_create_matrix(2, 3, &A);

  int status = s21_calc_complements(&A, &result);

  ck_assert_int_eq(status, ERROR_CALCULATION);

  s21_remove_matrix(&A);
}
END_TEST

// Тест 12: NULL матрица
START_TEST(test_calc_complements_null_matrix) {
  matrix_t result;
  int status = s21_calc_complements(NULL, &result);
  ck_assert_int_eq(status, ERROR_INCORRECT_MATRIX);
}
END_TEST

// Тест 13: NULL результат
START_TEST(test_calc_complements_null_result) {
  matrix_t A;
  s21_create_matrix(2, 2, &A);

  int status = s21_calc_complements(&A, NULL);
  ck_assert_int_eq(status, ERROR_INCORRECT_MATRIX);

  s21_remove_matrix(&A);
}
END_TEST

// Тест 14: Матрица 2x2 с отрицательными числами
START_TEST(test_calc_complements_2x2_negative) {
  matrix_t A, result;
  s21_create_matrix(2, 2, &A);
  A.matrix[0][0] = -1;
  A.matrix[0][1] = 2;
  A.matrix[1][0] = 3;
  A.matrix[1][1] = -4;

  int status = s21_calc_complements(&A, &result);

  ck_assert_int_eq(status, OK);

  // Ожидаемый результат: [[-4, -3], [-2, -1]]???
  // Проверим вычисления:
  // A11 = +det([-4]) = -4
  // A12 = -det([3]) = -3
  // A21 = -det([2]) = -2
  // A22 = +det([-1]) = -1
  ck_assert_double_eq_tol(result.matrix[0][0], -4.0, 1e-7);
  ck_assert_double_eq_tol(result.matrix[0][1], -3.0, 1e-7);
  ck_assert_double_eq_tol(result.matrix[1][0], -2.0, 1e-7);
  ck_assert_double_eq_tol(result.matrix[1][1], -1.0, 1e-7);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

// Тест 15: Матрица 4x4 (проверка на небольшой матрице)
START_TEST(test_calc_complements_4x4) {
  matrix_t A, result;
  s21_create_matrix(4, 4, &A);

  // Заполняем единичную матрицу
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      A.matrix[i][j] = (i == j) ? 2.0 : 0.0;
    }
  }

  int status = s21_calc_complements(&A, &result);

  ck_assert_int_eq(status, OK);

  // Для диагональной матрицы алгебраические дополнения:
  // На диагонали - произведение остальных диагональных элементов
  // Вне диагонали - нули
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (i == j) {
        // Для элемента (i,i): произведение остальных диагональных элементов
        // 2*2*2 = 8 для каждого, но с учетом знака (-1)^(i+i)=+
        ck_assert_double_eq_tol(result.matrix[i][j], 8.0, 1e-7);
      } else {
        ck_assert_double_eq_tol(result.matrix[i][j], 0.0, 1e-7);
      }
    }
  }

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

// ============================================
// Создание набора тестов
// ============================================

Suite *calc_complements_suite(void) {
  Suite *s = suite_create("calc_complements");
  TCase *tc_minor = tcase_create("minor_matrix");
  TCase *tc_calc = tcase_create("calc_complements");

  // Тесты для s21_minor_matrix
  tcase_add_test(tc_minor, test_minor_matrix_3x3_to_2x2);
  tcase_add_test(tc_minor, test_minor_matrix_exclude_0_0);
  tcase_add_test(tc_minor, test_minor_matrix_exclude_last);
  tcase_add_test(tc_minor, test_minor_matrix_3x4);
  tcase_add_test(tc_minor, test_minor_matrix_1x1_error);
  tcase_add_test(tc_minor, test_minor_matrix_null);

  // Тесты для s21_calc_complements
  tcase_add_test(tc_calc, test_calc_complements_1x1);
  tcase_add_test(tc_calc, test_calc_complements_2x2);
  tcase_add_test(tc_calc, test_calc_complements_3x3);
  tcase_add_test(tc_calc, test_calc_complements_3x3_zero_det);
  tcase_add_test(tc_calc, test_calc_complements_not_square);
  tcase_add_test(tc_calc, test_calc_complements_null_matrix);
  tcase_add_test(tc_calc, test_calc_complements_null_result);
  tcase_add_test(tc_calc, test_calc_complements_2x2_negative);
  tcase_add_test(tc_calc, test_calc_complements_4x4);

  suite_add_tcase(s, tc_minor);
  suite_add_tcase(s, tc_calc);

  return s;
}