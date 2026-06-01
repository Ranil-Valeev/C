#include "matrix.h"

// ============================================
// Тесты для sub_matrix
// ============================================

// Тест 1: Вычитание двух матриц 2x2
START_TEST(test_sub_matrix_2x2) {
  matrix_t A, B, result;

  // Инициализация result
  result.matrix = NULL;
  result.rows = 0;
  result.columns = 0;

  ck_assert_int_eq(s21_create_matrix(2, 2, &A), OK);
  ck_assert_int_eq(s21_create_matrix(2, 2, &B), OK);

  A.matrix[0][0] = 5;
  A.matrix[0][1] = 6;
  A.matrix[1][0] = 7;
  A.matrix[1][1] = 8;

  B.matrix[0][0] = 1;
  B.matrix[0][1] = 2;
  B.matrix[1][0] = 3;
  B.matrix[1][1] = 4;

  int status = s21_sub_matrix(&A, &B, &result);

  ck_assert_int_eq(status, OK);
  ck_assert_int_eq(result.rows, 2);
  ck_assert_int_eq(result.columns, 2);

  ck_assert_double_eq_tol(result.matrix[0][0], 4.0, 1e-7);
  ck_assert_double_eq_tol(result.matrix[0][1], 4.0, 1e-7);
  ck_assert_double_eq_tol(result.matrix[1][0], 4.0, 1e-7);
  ck_assert_double_eq_tol(result.matrix[1][1], 4.0, 1e-7);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
}
END_TEST

// Тест 2: Вычитание двух матриц 3x3
START_TEST(test_sub_matrix_3x3) {
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

  int status = s21_sub_matrix(&A, &B, &result);

  ck_assert_int_eq(status, OK);

  // Проверка значений
  ck_assert_double_eq_tol(result.matrix[0][0], 0.0, 1e-7);
  ck_assert_double_eq_tol(result.matrix[0][1], 2.0, 1e-7);
  ck_assert_double_eq_tol(result.matrix[0][2], 3.0, 1e-7);
  ck_assert_double_eq_tol(result.matrix[1][0], -2.0, 1e-7);
  ck_assert_double_eq_tol(result.matrix[1][1], 4.0, 1e-7);
  ck_assert_double_eq_tol(result.matrix[1][2], 5.0, 1e-7);
  ck_assert_double_eq_tol(result.matrix[2][0], -3.0, 1e-7);
  ck_assert_double_eq_tol(result.matrix[2][1], -4.0, 1e-7);
  ck_assert_double_eq_tol(result.matrix[2][2], 5.0, 1e-7);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
}
END_TEST

// Тест 3: Вычитание матриц 1x1
START_TEST(test_sub_matrix_1x1) {
  matrix_t A, B, result;

  result.matrix = NULL;
  result.rows = 0;
  result.columns = 0;

  ck_assert_int_eq(s21_create_matrix(1, 1, &A), OK);
  ck_assert_int_eq(s21_create_matrix(1, 1, &B), OK);

  A.matrix[0][0] = 8.8;
  B.matrix[0][0] = 3.3;

  int status = s21_sub_matrix(&A, &B, &result);

  ck_assert_int_eq(status, OK);
  ck_assert_double_eq_tol(result.matrix[0][0], 5.5, 1e-7);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
}
END_TEST

// Тест 4: Вычитание с отрицательными числами
START_TEST(test_sub_matrix_negative) {
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

  int status = s21_sub_matrix(&A, &B, &result);

  ck_assert_int_eq(status, OK);
  ck_assert_double_eq_tol(result.matrix[0][0], -6.0, 1e-7);
  ck_assert_double_eq_tol(result.matrix[0][1], 4.0, 1e-7);
  ck_assert_double_eq_tol(result.matrix[1][0], 4.0, 1e-7);
  ck_assert_double_eq_tol(result.matrix[1][1], -12.0, 1e-7);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
}
END_TEST

// Тест 5: Вычитание матриц разных размеров (ошибка)
START_TEST(test_sub_matrix_different_sizes) {
  matrix_t A, B, result;

  result.matrix = NULL;
  result.rows = 0;
  result.columns = 0;

  ck_assert_int_eq(s21_create_matrix(2, 2, &A), OK);
  ck_assert_int_eq(s21_create_matrix(3, 3, &B), OK);

  int status = s21_sub_matrix(&A, &B, &result);

  ck_assert_int_eq(status, ERROR_INCORRECT_MATRIX);
  ck_assert_ptr_null(result.matrix);  // result не должен быть создан

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

// Тест 6: Вычитание с некорректной матрицей B
START_TEST(test_sub_matrix_invalid_B) {
  matrix_t A, B, result;

  result.matrix = NULL;
  result.rows = 0;
  result.columns = 0;

  ck_assert_int_eq(s21_create_matrix(2, 2, &A), OK);

  // Создаем корректную матрицу B, потом "портим" её
  ck_assert_int_eq(s21_create_matrix(2, 2, &B), OK);
  s21_remove_matrix(&B);  // Теперь B некорректна

  int status = s21_sub_matrix(&A, &B, &result);

  ck_assert_int_eq(status, ERROR_INCORRECT_MATRIX);
  ck_assert_ptr_null(result.matrix);

  s21_remove_matrix(&A);
}
END_TEST

// Тест 7: Вычитание с NULL указателем result
START_TEST(test_sub_matrix_null_result) {
  matrix_t A, B;

  ck_assert_int_eq(s21_create_matrix(2, 2, &A), OK);
  ck_assert_int_eq(s21_create_matrix(2, 2, &B), OK);

  int status = s21_sub_matrix(&A, &B, NULL);

  ck_assert_int_eq(status, ERROR_INCORRECT_MATRIX);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

// Тест 8: Вычитание одинаковых матриц (результат - нулевая матрица)
START_TEST(test_sub_matrix_equal) {
  matrix_t A, B, result;

  result.matrix = NULL;
  result.rows = 0;
  result.columns = 0;

  ck_assert_int_eq(s21_create_matrix(2, 2, &A), OK);
  ck_assert_int_eq(s21_create_matrix(2, 2, &B), OK);

  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[1][0] = 3;
  A.matrix[1][1] = 4;

  B.matrix[0][0] = 1;
  B.matrix[0][1] = 2;
  B.matrix[1][0] = 3;
  B.matrix[1][1] = 4;

  int status = s21_sub_matrix(&A, &B, &result);

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

// Тест 9: Вычитание с матрицей A, содержащей нули
START_TEST(test_sub_matrix_with_zeros) {
  matrix_t A, B, result;

  result.matrix = NULL;
  result.rows = 0;
  result.columns = 0;

  ck_assert_int_eq(s21_create_matrix(2, 2, &A), OK);
  ck_assert_int_eq(s21_create_matrix(2, 2, &B), OK);

  A.matrix[0][0] = 0;
  A.matrix[0][1] = 0;
  A.matrix[1][0] = 0;
  A.matrix[1][1] = 0;

  B.matrix[0][0] = 1;
  B.matrix[0][1] = 2;
  B.matrix[1][0] = 3;
  B.matrix[1][1] = 4;

  int status = s21_sub_matrix(&A, &B, &result);

  ck_assert_int_eq(status, OK);
  ck_assert_double_eq_tol(result.matrix[0][0], -1.0, 1e-7);
  ck_assert_double_eq_tol(result.matrix[0][1], -2.0, 1e-7);
  ck_assert_double_eq_tol(result.matrix[1][0], -3.0, 1e-7);
  ck_assert_double_eq_tol(result.matrix[1][1], -4.0, 1e-7);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
}
END_TEST

// ============================================
// Создание набора тестов для sub_matrix
// ============================================

Suite *sub_matrix_suite(void) {
  Suite *s = suite_create("sub_matrix");
  TCase *tc = tcase_create("core");

  tcase_add_test(tc, test_sub_matrix_2x2);
  tcase_add_test(tc, test_sub_matrix_3x3);
  tcase_add_test(tc, test_sub_matrix_1x1);
  tcase_add_test(tc, test_sub_matrix_negative);
  tcase_add_test(tc, test_sub_matrix_different_sizes);
  tcase_add_test(tc, test_sub_matrix_invalid_B);
  tcase_add_test(tc, test_sub_matrix_null_result);
  tcase_add_test(tc, test_sub_matrix_equal);
  tcase_add_test(tc, test_sub_matrix_with_zeros);

  suite_add_tcase(s, tc);
  return s;
}