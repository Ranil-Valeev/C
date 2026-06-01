#include "matrix.h"

// ============================================
// Тесты для my functions
// ============================================

// ============================================
// Тесты для s21_valid_matrix
// ============================================

START_TEST(test_valid_matrix_normal) {
  matrix_t A;
  s21_create_matrix(3, 3, &A);

  int result = s21_valid_matrix(&A);
  ck_assert_int_eq(result, SUCCESS);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_valid_matrix_null_ptr) {
  int result = s21_valid_matrix(NULL);
  ck_assert_int_eq(result, FAILURE);
}
END_TEST

START_TEST(test_valid_matrix_null_matrix_ptr) {
  matrix_t A;
  A.rows = 3;
  A.columns = 3;
  A.matrix = NULL;

  int result = s21_valid_matrix(&A);
  ck_assert_int_eq(result, FAILURE);
}
END_TEST

START_TEST(test_valid_matrix_zero_rows) {
  matrix_t A;
  s21_create_matrix(3, 3, &A);
  A.rows = 0;

  int result = s21_valid_matrix(&A);
  ck_assert_int_eq(result, FAILURE);

  // Восстанавливаем для корректного удаления
  A.rows = 3;
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_valid_matrix_zero_columns) {
  matrix_t A;
  s21_create_matrix(3, 3, &A);
  A.columns = 0;

  int result = s21_valid_matrix(&A);
  ck_assert_int_eq(result, FAILURE);

  // Восстанавливаем для корректного удаления
  A.columns = 3;
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_valid_matrix_negative_rows) {
  matrix_t A;
  s21_create_matrix(3, 3, &A);
  A.rows = -1;

  int result = s21_valid_matrix(&A);
  ck_assert_int_eq(result, FAILURE);

  // Восстанавливаем для корректного удаления
  A.rows = 3;
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_valid_matrix_negative_columns) {
  matrix_t A;
  s21_create_matrix(3, 3, &A);
  A.columns = -1;

  int result = s21_valid_matrix(&A);
  ck_assert_int_eq(result, FAILURE);

  // Восстанавливаем для корректного удаления
  A.columns = 3;
  s21_remove_matrix(&A);
}
END_TEST

// ============================================
// Тесты для s21_matrix_verification
// ============================================

START_TEST(test_matrix_verification_both_valid_same_size) {
  matrix_t A, B;
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &B);

  int result = s21_matrix_verification(&A, &B);
  ck_assert_int_eq(result, SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_matrix_verification_both_valid_different_rows) {
  matrix_t A, B;
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(4, 3, &B);

  int result = s21_matrix_verification(&A, &B);
  ck_assert_int_eq(result, FAILURE);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_matrix_verification_both_valid_different_columns) {
  matrix_t A, B;
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 4, &B);

  int result = s21_matrix_verification(&A, &B);
  ck_assert_int_eq(result, FAILURE);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_matrix_verification_first_invalid) {
  matrix_t A, B;
  s21_create_matrix(3, 3, &B);
  A.matrix = NULL;
  A.rows = 3;
  A.columns = 3;

  int result = s21_matrix_verification(&A, &B);
  ck_assert_int_eq(result, FAILURE);

  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_matrix_verification_second_invalid) {
  matrix_t A, B;
  s21_create_matrix(3, 3, &A);
  B.matrix = NULL;
  B.rows = 3;
  B.columns = 3;

  int result = s21_matrix_verification(&A, &B);
  ck_assert_int_eq(result, FAILURE);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_matrix_verification_both_invalid) {
  matrix_t A, B;
  A.matrix = NULL;
  A.rows = 3;
  A.columns = 3;
  B.matrix = NULL;
  B.rows = 3;
  B.columns = 3;

  int result = s21_matrix_verification(&A, &B);
  ck_assert_int_eq(result, FAILURE);
}
END_TEST

START_TEST(test_matrix_verification_first_null) {
  matrix_t B;
  s21_create_matrix(3, 3, &B);

  int result = s21_matrix_verification(NULL, &B);
  ck_assert_int_eq(result, FAILURE);

  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_matrix_verification_second_null) {
  matrix_t A;
  s21_create_matrix(3, 3, &A);

  int result = s21_matrix_verification(&A, NULL);
  ck_assert_int_eq(result, FAILURE);

  s21_remove_matrix(&A);
}
END_TEST

// ============================================
// Тесты для s21_reset_matrix
// ============================================

// Исправленный тест для reset_matrix
START_TEST(test_reset_matrix_normal) {
  matrix_t A;
  s21_create_matrix(3, 3, &A);

  // Заполняем значениями
  for (int i = 0; i < A.rows; i++) {
    for (int j = 0; j < A.columns; j++) {
      A.matrix[i][j] = i * A.columns + j + 1;
    }
  }

  // Сбрасываем значения (обнуляем)
  s21_reset_matrix(&A);

  // Проверяем, что все элементы стали 0
  for (int i = 0; i < A.rows; i++) {
    for (int j = 0; j < A.columns; j++) {
      ck_assert_double_eq_tol(A.matrix[i][j], 0.0, 1e-7);
    }
  }

  // Проверяем, что указатель НЕ обнулился
  ck_assert_ptr_nonnull(A.matrix);
  ck_assert_int_eq(A.rows, 3);
  ck_assert_int_eq(A.columns, 3);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_reset_matrix_null_pointer) {
  // Просто проверяем, что функция не падает с NULL
  s21_reset_matrix(NULL);

  // Если дошли сюда - тест пройден
  ck_assert_int_eq(1, 1);
}
END_TEST

START_TEST(test_reset_matrix_empty) {
  matrix_t A = {NULL, 0, 0};

  s21_reset_matrix(&A);

  // Проверяем, что состояние не изменилось (осталось нулевым)
  ck_assert_ptr_null(A.matrix);
  ck_assert_int_eq(A.rows, 0);
  ck_assert_int_eq(A.columns, 0);
}
END_TEST

START_TEST(test_reset_matrix_partial) {
  matrix_t A;
  s21_create_matrix(3, 3, &A);

  // Заполняем значениями
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      A.matrix[i][j] = i * 3 + j + 1;
    }
  }

  // Сбрасываем значения в 0
  s21_reset_matrix(&A);

  // Проверяем, что все элементы стали 0
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      ck_assert_double_eq_tol(A.matrix[i][j], 0.0, 1e-7);
    }
  }

  // Указатель должен остаться ненулевым
  ck_assert_ptr_nonnull(A.matrix);
  ck_assert_int_eq(A.rows, 3);
  ck_assert_int_eq(A.columns, 3);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_reset_matrix_after_remove) {
  matrix_t A;
  s21_create_matrix(3, 3, &A);

  // Удаляем матрицу
  s21_remove_matrix(&A);

  // Проверяем, что remove_matrix обнулил поля
  ck_assert_ptr_null(A.matrix);
  ck_assert_int_eq(A.rows, 0);
  ck_assert_int_eq(A.columns, 0);

  // Сбрасываем еще раз (должно работать без ошибок)
  s21_reset_matrix(&A);

  // Проверяем, что состояние не изменилось
  ck_assert_ptr_null(A.matrix);
  ck_assert_int_eq(A.rows, 0);
  ck_assert_int_eq(A.columns, 0);
}
END_TEST

// ============================================
// Сьют для my_functions
// ============================================

Suite *my_functions_suite(void) {
  Suite *s = suite_create("my_functions");
  TCase *tc = tcase_create("core");

  // Тесты для s21_valid_matrix
  tcase_add_test(tc, test_valid_matrix_normal);
  tcase_add_test(tc, test_valid_matrix_null_ptr);
  tcase_add_test(tc, test_valid_matrix_null_matrix_ptr);
  tcase_add_test(tc, test_valid_matrix_zero_rows);
  tcase_add_test(tc, test_valid_matrix_zero_columns);
  tcase_add_test(tc, test_valid_matrix_negative_rows);
  tcase_add_test(tc, test_valid_matrix_negative_columns);

  // Тесты для s21_matrix_verification
  tcase_add_test(tc, test_matrix_verification_both_valid_same_size);
  tcase_add_test(tc, test_matrix_verification_both_valid_different_rows);
  tcase_add_test(tc, test_matrix_verification_both_valid_different_columns);
  tcase_add_test(tc, test_matrix_verification_first_invalid);
  tcase_add_test(tc, test_matrix_verification_second_invalid);
  tcase_add_test(tc, test_matrix_verification_both_invalid);
  tcase_add_test(tc, test_matrix_verification_first_null);
  tcase_add_test(tc, test_matrix_verification_second_null);

  // Тесты для s21_reset_matrix
  tcase_add_test(tc, test_reset_matrix_normal);
  tcase_add_test(tc, test_reset_matrix_null_pointer);
  tcase_add_test(tc, test_reset_matrix_empty);
  tcase_add_test(tc, test_reset_matrix_partial);
  tcase_add_test(tc, test_reset_matrix_after_remove);

  suite_add_tcase(s, tc);
  return s;
}