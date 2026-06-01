#include "matrix.h"

// ============================================
// Создание набора тестов для eq_matrix
// ============================================

// 1) Две одинаковые квадратные матрицы
START_TEST(test_eq_matrix_identical_square) {
  matrix_t A, B;
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &B);

  // Заполняем одинаковыми значениями
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      A.matrix[i][j] = i * 3 + j + 1.0;
      B.matrix[i][j] = i * 3 + j + 1.0;
    }
  }

  int result = s21_eq_matrix(&A, &B);
  ck_assert_int_eq(result, SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

// 2) Две прямоугольные одинаковые матрицы (2x4)
START_TEST(test_eq_matrix_identical_rectangular) {
  matrix_t A, B;
  s21_create_matrix(2, 4, &A);
  s21_create_matrix(2, 4, &B);

  // Заполняем одинаковыми значениями
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 4; j++) {
      A.matrix[i][j] = i * 4 + j + 1.123456;
      B.matrix[i][j] = i * 4 + j + 1.123456;
    }
  }

  int result = s21_eq_matrix(&A, &B);
  ck_assert_int_eq(result, SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

// 3) Две невалидные матрицы
START_TEST(test_eq_matrix_both_invalid) {
  matrix_t A, B;
  A.matrix = NULL;
  A.rows = 3;
  A.columns = 3;
  B.matrix = NULL;
  B.rows = 3;
  B.columns = 3;

  int result = s21_eq_matrix(&A, &B);
  ck_assert_int_eq(result, FAILURE);
}
END_TEST

// 4) Одинаковые вектор-строки (1x5)
START_TEST(test_eq_matrix_identical_row_vector) {
  matrix_t A, B;
  s21_create_matrix(1, 5, &A);
  s21_create_matrix(1, 5, &B);

  for (int j = 0; j < 5; j++) {
    A.matrix[0][j] = j * 1.5;
    B.matrix[0][j] = j * 1.5;
  }

  int result = s21_eq_matrix(&A, &B);
  ck_assert_int_eq(result, SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

// 5) Одинаковые вектор-столбцы (4x1)
START_TEST(test_eq_matrix_identical_column_vector) {
  matrix_t A, B;
  s21_create_matrix(4, 1, &A);
  s21_create_matrix(4, 1, &B);

  for (int i = 0; i < 4; i++) {
    A.matrix[i][0] = i * 2.5;
    B.matrix[i][0] = i * 2.5;
  }

  int result = s21_eq_matrix(&A, &B);
  ck_assert_int_eq(result, SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

// 6) Разные вектор-строки
START_TEST(test_eq_matrix_different_row_vectors) {
  matrix_t A, B;
  s21_create_matrix(1, 3, &A);
  s21_create_matrix(1, 3, &B);

  A.matrix[0][0] = 1.0;
  A.matrix[0][1] = 2.0;
  A.matrix[0][2] = 3.0;
  B.matrix[0][0] = 1.0;
  B.matrix[0][1] = 2.0;
  B.matrix[0][2] = 3.5;

  int result = s21_eq_matrix(&A, &B);
  ck_assert_int_eq(result, FAILURE);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

// 7) Разные вектор-столбцы
START_TEST(test_eq_matrix_different_column_vectors) {
  matrix_t A, B;
  s21_create_matrix(3, 1, &A);
  s21_create_matrix(3, 1, &B);

  A.matrix[0][0] = 1.0;
  A.matrix[1][0] = 2.0;
  A.matrix[2][0] = 3.0;
  B.matrix[0][0] = 1.0;
  B.matrix[1][0] = 2.0;
  B.matrix[2][0] = 3.5;

  int result = s21_eq_matrix(&A, &B);
  ck_assert_int_eq(result, FAILURE);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

// 8) Квадратная vs прямоугольная (разные размеры)
START_TEST(test_eq_matrix_square_vs_rectangular) {
  matrix_t A, B;
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 4, &B);

  fill_matrix_const(&A, 5.0);
  fill_matrix_const(&B, 5.0);

  int result = s21_eq_matrix(&A, &B);
  ck_assert_int_eq(result, FAILURE);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

// 9) Вектор-строка vs вектор-столбец
START_TEST(test_eq_matrix_row_vs_column_vector) {
  matrix_t A, B;
  s21_create_matrix(1, 3, &A);
  s21_create_matrix(3, 1, &B);

  fill_matrix_const(&A, 5.0);
  fill_matrix_const(&B, 5.0);

  int result = s21_eq_matrix(&A, &B);
  ck_assert_int_eq(result, FAILURE);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

// 10) Почти равные матрицы (разница < 1e-7)
START_TEST(test_eq_matrix_almost_equal) {
  matrix_t A, B;
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &B);

  A.matrix[0][0] = 1.23456789;
  B.matrix[0][0] = 1.23456791;  // разница 2e-8 < 1e-7

  A.matrix[0][1] = 2.34567890;
  B.matrix[0][1] = 2.34567889;  // разница 1e-8 < 1e-7

  A.matrix[1][0] = 3.45678901;
  B.matrix[1][0] = 3.45678902;  // разница 1e-8 < 1e-7

  A.matrix[1][1] = 4.56789012;
  B.matrix[1][1] = 4.56789013;  // разница 1e-8 < 1e-7

  int result = s21_eq_matrix(&A, &B);
  ck_assert_int_eq(result, SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

// 11) Чуть разные матрицы (разница > 1e-7)
START_TEST(test_eq_matrix_slightly_different) {
  matrix_t A, B;
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &B);

  A.matrix[0][0] = 1.23456789;
  B.matrix[0][0] = 1.23457789;  // разница 1e-5 > 1e-7

  A.matrix[0][1] = 2.34567890;
  B.matrix[0][1] = 2.34567890;  // одинаковые

  A.matrix[1][0] = 3.45678901;
  B.matrix[1][0] = 3.45678901;  // одинаковые

  A.matrix[1][1] = 4.56789012;
  B.matrix[1][1] = 4.56789012;  // одинаковые

  int result = s21_eq_matrix(&A, &B);
  ck_assert_int_eq(result, FAILURE);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

// 12) Одна матрица валидная, другая NULL
START_TEST(test_eq_matrix_one_null) {
  matrix_t A;
  s21_create_matrix(2, 2, &A);
  fill_matrix_const(&A, 5.0);

  int result = s21_eq_matrix(&A, NULL);
  ck_assert_int_eq(result, FAILURE);

  s21_remove_matrix(&A);
}
END_TEST

// 13) Разные квадратные матрицы
START_TEST(test_eq_matrix_different_square) {
  matrix_t A, B;
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &B);

  fill_matrix(&A, 1.0);
  fill_matrix(&B, 2.0);

  int result = s21_eq_matrix(&A, &B);
  ck_assert_int_eq(result, FAILURE);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

// 14) Матрицы с отрицательными числами
START_TEST(test_eq_matrix_negative_numbers) {
  matrix_t A, B;
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &B);

  A.matrix[0][0] = -1.23456789;
  B.matrix[0][0] = -1.23456791;  // разница 2e-8 < 1e-7

  A.matrix[0][1] = -2.34567890;
  B.matrix[0][1] = -2.34567890;

  A.matrix[1][0] = -3.45678901;
  B.matrix[1][0] = -3.45678901;

  A.matrix[1][1] = -4.56789012;
  B.matrix[1][1] = -4.56789012;

  int result = s21_eq_matrix(&A, &B);
  ck_assert_int_eq(result, SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

Suite *equal_matrix_suite(void) {
  Suite *s = suite_create("equal_matrix");
  TCase *tc = tcase_create("core");

  // Тесты для eq_matrix согласно заданию
  tcase_add_test(tc, test_eq_matrix_identical_square);
  tcase_add_test(tc, test_eq_matrix_identical_rectangular);
  tcase_add_test(tc, test_eq_matrix_both_invalid);
  tcase_add_test(tc, test_eq_matrix_identical_row_vector);
  tcase_add_test(tc, test_eq_matrix_identical_column_vector);
  tcase_add_test(tc, test_eq_matrix_different_row_vectors);
  tcase_add_test(tc, test_eq_matrix_different_column_vectors);
  tcase_add_test(tc, test_eq_matrix_square_vs_rectangular);
  tcase_add_test(tc, test_eq_matrix_row_vs_column_vector);
  tcase_add_test(tc, test_eq_matrix_almost_equal);
  tcase_add_test(tc, test_eq_matrix_slightly_different);
  tcase_add_test(tc, test_eq_matrix_one_null);
  tcase_add_test(tc, test_eq_matrix_different_square);
  tcase_add_test(tc, test_eq_matrix_negative_numbers);

  suite_add_tcase(s, tc);
  return s;
}