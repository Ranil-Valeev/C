#include "matrix.h"

// ============================================
// Тесты для remove_matrix
// ============================================

// Тест 1: Удаление существующей матрицы 3x3
START_TEST(test_remove_matrix_3x3) {
  matrix_t A;
  s21_create_matrix(3, 3, &A);

  // Проверяем, что матрица создана
  ck_assert_ptr_nonnull(A.matrix);

  s21_remove_matrix(&A);

  // Проверяем, что матрица очищена
  ck_assert_ptr_null(A.matrix);
  ck_assert_int_eq(A.rows, 0);
  ck_assert_int_eq(A.columns, 0);
}
END_TEST

// Тест 2: Удаление матрицы 1x1
START_TEST(test_remove_matrix_1x1) {
  matrix_t A;
  s21_create_matrix(1, 1, &A);

  ck_assert_ptr_nonnull(A.matrix);

  s21_remove_matrix(&A);

  ck_assert_ptr_null(A.matrix);
  ck_assert_int_eq(A.rows, 0);
  ck_assert_int_eq(A.columns, 0);
}
END_TEST

// Тест 3: Удаление матрицы-столбца 5x1
START_TEST(test_remove_matrix_5x1) {
  matrix_t A;
  s21_create_matrix(5, 1, &A);

  ck_assert_ptr_nonnull(A.matrix);

  s21_remove_matrix(&A);

  ck_assert_ptr_null(A.matrix);
  ck_assert_int_eq(A.rows, 0);
  ck_assert_int_eq(A.columns, 0);
}
END_TEST

// Тест 4: Удаление матрицы-строки 1x5
START_TEST(test_remove_matrix_1x5) {
  matrix_t A;
  s21_create_matrix(1, 5, &A);

  ck_assert_ptr_nonnull(A.matrix);

  s21_remove_matrix(&A);

  ck_assert_ptr_null(A.matrix);
  ck_assert_int_eq(A.rows, 0);
  ck_assert_int_eq(A.columns, 0);
}
END_TEST

// Тест 5: Удаление уже пустой матрицы (должно работать без ошибок)
START_TEST(test_remove_matrix_empty) {
  matrix_t A = {NULL, 0, 0};

  // Просто проверяем, что функция не падает
  s21_remove_matrix(&A);

  ck_assert_ptr_null(A.matrix);
  ck_assert_int_eq(A.rows, 0);
  ck_assert_int_eq(A.columns, 0);
}
END_TEST

// Тест 6: Удаление матрицы с NULL указателем (должно работать без ошибок)
START_TEST(test_remove_matrix_null_pointer) {
  // Проверяем, что функция не падает при передаче NULL
  s21_remove_matrix(NULL);

  // Если дошли сюда - тест пройден
  ck_assert_int_eq(1, 1);
}
END_TEST

// Тест 7: Удаление матрицы, у которой matrix == NULL, но rows/cols не нули
START_TEST(test_remove_matrix_invalid_state) {
  matrix_t A = {NULL, 3, 3};  // Некорректное состояние

  // Функция должна безопасно обработать
  s21_remove_matrix(&A);

  // Проверяем, что теперь всё обнулено
  ck_assert_ptr_null(A.matrix);
  ck_assert_int_eq(A.rows, 0);
  ck_assert_int_eq(A.columns, 0);
}
END_TEST

// Тест 8: Повторное удаление уже удаленной матрицы
START_TEST(test_remove_matrix_twice) {
  matrix_t A;
  s21_create_matrix(3, 3, &A);

  // Первое удаление
  s21_remove_matrix(&A);
  ck_assert_ptr_null(A.matrix);
  ck_assert_int_eq(A.rows, 0);
  ck_assert_int_eq(A.columns, 0);

  // Второе удаление (должно работать без ошибок)
  s21_remove_matrix(&A);
  ck_assert_ptr_null(A.matrix);
  ck_assert_int_eq(A.rows, 0);
  ck_assert_int_eq(A.columns, 0);
}
END_TEST

// ============================================
// Создание набора тестов для remove_matrix
// ============================================

Suite *remove_matrix_suite(void) {
  Suite *s = suite_create("remove_matrix");
  TCase *tc = tcase_create("core");

  tcase_add_test(tc, test_remove_matrix_3x3);
  tcase_add_test(tc, test_remove_matrix_1x1);
  tcase_add_test(tc, test_remove_matrix_5x1);
  tcase_add_test(tc, test_remove_matrix_1x5);
  tcase_add_test(tc, test_remove_matrix_empty);
  tcase_add_test(tc, test_remove_matrix_null_pointer);
  tcase_add_test(tc, test_remove_matrix_invalid_state);
  tcase_add_test(tc, test_remove_matrix_twice);

  suite_add_tcase(s, tc);
  return s;
}