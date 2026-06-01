#include "matrix.h"

// Вспомогательная функция для заполнения матрицы значениями
void fill_matrix(matrix_t *mat, double start_value) {
  for (int i = 0; i < mat->rows; i++) {
    for (int j = 0; j < mat->columns; j++) {
      mat->matrix[i][j] = start_value + i * mat->columns + j;
    }
  }
}

// Вспомогательная функция для заполнения матрицы одинаковыми значениями
void fill_matrix_const(matrix_t *mat, double value) {
  for (int i = 0; i < mat->rows; i++) {
    for (int j = 0; j < mat->columns; j++) {
      mat->matrix[i][j] = value;
    }
  }
}