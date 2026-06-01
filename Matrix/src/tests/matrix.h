#ifndef MATRIX_H
#define MATRIX_H

#include <check.h>

#include "../s21_matrix.h"

/* Основные тестовые сьюты */
Suite *create_matrix_suite(void);
Suite *remove_matrix_suite(void);
Suite *equal_matrix_suite(void);
Suite *sum_matrix_suite(void);
Suite *sub_matrix_suite(void);
Suite *mult_number_suite(void);
Suite *mult_matrix_suite(void);
Suite *transpose_suite(void);
Suite *calc_complements_suite(void);
Suite *determinant_suite(void);
Suite *inverse_matrix_suite(void);
Suite *my_functions_suite(void);

// ============================================
// Вспомогательные функции для тестов
// ============================================
void fill_matrix(matrix_t *mat, double start_value);
void fill_matrix_const(matrix_t *mat, double value);

#endif  // MATRIX_H