#ifndef S21_MATRIX_H
#define S21_MATRIX_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define WIEGHT 10
#define HIEGHT 10

#define OK 0
#define ERROR_INCORRECT_MATRIX 1
#define ERROR_CALCULATION 2

#define SUCCESS 1
#define FAILURE 0

typedef struct matrix_struct {
  double **matrix;
  int rows;
  int columns;
} matrix_t;

// Создание матриц (create_matrix)
int s21_create_matrix(int rows, int columns, matrix_t *result);
// Очистка матриц (remove_matrix)
void s21_remove_matrix(matrix_t *A);
// Сравнение матриц (eq_matrix)
int s21_eq_matrix(const matrix_t *A, const matrix_t *B);
// Сложение (sum_matrix)
int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
// вычитание матриц (sub_matrix)
int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
// Умножение матрицы на число (mult_number)
int s21_mult_number(matrix_t *A, double number, matrix_t *result);
// Умножение двух матриц (mult_matrix)
int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
// Транспонирование матрицы (transpose)
int s21_transpose(matrix_t *A, matrix_t *result);
// Минор матрицы и матрица алгебраических дополнений (calc_complements)
int s21_calc_complements(matrix_t *A, matrix_t *result);
// Определитель матрицы (determinant)
int s21_determinant(matrix_t *A, double *result);
// Обратная матрица (inverse_matrix)
int s21_inverse_matrix(matrix_t *A, matrix_t *result);

int s21_valid_matrix(const matrix_t *matrix);
int s21_matrix_verification(const matrix_t *A, const matrix_t *B);
int s21_reset_matrix(matrix_t *matrix);
int s21_minor_matrix(matrix_t *A, int excluded_row, int excluded_column,
                     matrix_t *result);
int s21_set_of_checks(const matrix_t *A, const matrix_t *result);

int s21_valid_determinant(const matrix_t *A, double *result);
void s21_determinant_1x1(matrix_t *temp_matrix, double *determinant);
void s21_determinant_2x2(matrix_t *temp_matrix, double *determinant);
void s21_rule_of_sarrus(matrix_t *temp_matrix, double *determinant);
void s21_method_gauss(matrix_t *temp_matrix, double *determinant, int *sign);

#endif