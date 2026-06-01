#include "s21_matrix.h"

int s21_create_matrix(int rows, int columns, matrix_t *result) {
  if (result == NULL) {
    return ERROR_INCORRECT_MATRIX;
  }

  result->rows = 0;
  result->columns = 0;
  result->matrix = NULL;

  if (rows <= 0 || columns <= 0) {
    return ERROR_INCORRECT_MATRIX;
  }

  result->matrix = (double **)calloc(rows, sizeof(double *));
  if (result->matrix == NULL) {
    return ERROR_INCORRECT_MATRIX;
  }

  for (int i = 0; i < rows; i++) {
    result->matrix[i] = (double *)calloc(columns, sizeof(double));
    if (result->matrix[i] == NULL) {
      for (int j = 0; j < i; j++) {
        free(result->matrix[j]);
      }
      free(result->matrix);
      result->matrix = NULL;
      return ERROR_INCORRECT_MATRIX;
    }
  }

  result->rows = rows;
  result->columns = columns;

  return OK;
}

void s21_remove_matrix(matrix_t *A) {
  if (A != NULL) {
    if (A->matrix != NULL) {
      for (int i = 0; i < A->rows; i++) {
        if (A->matrix[i] != NULL) {
          free(A->matrix[i]);
          A->matrix[i] = NULL;
        }
      }
      free(A->matrix);
      A->matrix = NULL;
    }
    A->rows = 0;
    A->columns = 0;
  }
}

int s21_eq_matrix(const matrix_t *A, const matrix_t *B) {
  if (!s21_matrix_verification(A, B)) {
    return FAILURE;
  }

  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      if (fabs(A->matrix[i][j] - B->matrix[i][j]) > 1e-7) {
        return FAILURE;
      }
    }
  }
  return SUCCESS;
}

int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  if (!s21_matrix_verification(A, B)) {
    return ERROR_INCORRECT_MATRIX;
  }

  if (result == NULL) {
    return ERROR_INCORRECT_MATRIX;
  }

  int status = s21_create_matrix(A->rows, A->columns, result);

  if (status != OK) {
    return ERROR_INCORRECT_MATRIX;
  }

  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      result->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
    }
  }
  return OK;
}

int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  if (!s21_matrix_verification(A, B)) {
    return ERROR_INCORRECT_MATRIX;
  }

  if (result == NULL) {
    return ERROR_INCORRECT_MATRIX;
  }

  int status = s21_create_matrix(A->rows, A->columns, result);

  if (status != OK) {
    return ERROR_INCORRECT_MATRIX;
  }

  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      result->matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];
    }
  }
  return OK;
}

int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  if (!s21_valid_matrix(A)) {
    return ERROR_INCORRECT_MATRIX;
  }

  if (result == NULL) {
    return ERROR_INCORRECT_MATRIX;
  }

  int status = s21_create_matrix(A->rows, A->columns, result);

  if (status != OK) {
    return ERROR_INCORRECT_MATRIX;
  }

  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      result->matrix[i][j] = A->matrix[i][j] * number;
    }
  }
  return OK;
}

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  if (!s21_valid_matrix(A) || !s21_valid_matrix(B)) {
    return ERROR_INCORRECT_MATRIX;
  }

  if (result == NULL) {
    return ERROR_INCORRECT_MATRIX;
  }

  if (A->columns != B->rows) {
    return ERROR_CALCULATION;
  }

  int status = s21_create_matrix(A->rows, B->columns, result);

  if (status != OK) {
    return status;
  }

  s21_reset_matrix(result);

  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < B->columns; j++) {
      for (int k = 0; k < A->columns; k++) {
        result->matrix[i][j] += A->matrix[i][k] * B->matrix[k][j];
      }
    }
  }
  return OK;
}

int s21_transpose(matrix_t *A, matrix_t *result) {
  if (!s21_valid_matrix(A)) {
    return ERROR_INCORRECT_MATRIX;
  }

  if (result == NULL) {
    return ERROR_INCORRECT_MATRIX;
  }

  int status = s21_create_matrix(A->columns, A->rows, result);
  if (status != OK) {
    return status;
  }

  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      result->matrix[j][i] = A->matrix[i][j];
    }
  }

  return OK;
}

int s21_calc_complements(matrix_t *A, matrix_t *result) {
  int status = s21_set_of_checks(A, result);
  if (status != OK) {
    return status;
  }

  status = s21_create_matrix(A->rows, A->columns, result);
  if (status != OK) {
    return status;
  }

  if (A->rows == 1) {
    result->matrix[0][0] = 1.0;
    return OK;
  }

  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      matrix_t minor;
      status = s21_minor_matrix(A, i, j, &minor);
      if (status != OK) {
        s21_remove_matrix(result);
        return status;
      }

      double minor_det = 0.0;
      status = s21_determinant(&minor, &minor_det);
      if (status != OK) {
        s21_remove_matrix(&minor);
        s21_remove_matrix(result);
        return status;
      }

      double sign = ((i + j) % 2 == 0) ? 1.0 : -1.0;
      result->matrix[i][j] = sign * minor_det;

      s21_remove_matrix(&minor);
    }
  }

  return OK;
}

int s21_determinant(matrix_t *A, double *result) {
  int valid_result = s21_valid_determinant(A, result);
  if (valid_result != OK) {
    return valid_result;
  }

  matrix_t temp_matrix;
  s21_create_matrix(A->rows, A->columns, &temp_matrix);

  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      temp_matrix.matrix[i][j] = A->matrix[i][j];
    }
  }

  double determinant = 1.0;
  int sign = 1;

  // 1x1
  if (temp_matrix.rows == 1) {
    s21_determinant_1x1(&temp_matrix, &determinant);
  }
  // 2x2
  else if (temp_matrix.rows == 2) {
    s21_determinant_2x2(&temp_matrix, &determinant);
  }
  // 3x3 правило Саррюса
  else if (temp_matrix.rows == 3) {
    s21_rule_of_sarrus(&temp_matrix, &determinant);
  }
  // метод Гаусса
  else {
    s21_method_gauss(&temp_matrix, &determinant, &sign);
  }

  *result = determinant;
  s21_remove_matrix(&temp_matrix);
  return OK;
}

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  int status = s21_set_of_checks(A, result);
  if (status != OK) {
    return status;
  }

  double new_determinant = 0.0;

  status = s21_determinant(A, &new_determinant);
  if (status != OK) {
    return status;
  }

  if (fabs(new_determinant) < 1e-7) {
    return ERROR_CALCULATION;
  }

  if (A->rows == 1) {
    s21_create_matrix(1, 1, result);
    result->matrix[0][0] = 1.0 / A->matrix[0][0];
    return OK;
  }

  matrix_t complements;
  status = s21_calc_complements(A, &complements);
  if (status != OK) {
    return status;
  }

  matrix_t union_matrix;
  status = s21_transpose(&complements, &union_matrix);
  s21_remove_matrix(&complements);

  if (status != OK) {
    return status;
  }

  status = s21_create_matrix(A->rows, A->columns, result);
  if (status != OK) {
    s21_remove_matrix(&union_matrix);
    return status;
  }

  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      result->matrix[i][j] = union_matrix.matrix[i][j] / new_determinant;
    }
  }

  s21_remove_matrix(&union_matrix);
  return OK;
}

int s21_valid_matrix(const matrix_t *matrix) {
  if (matrix == NULL) return FAILURE;
  if (matrix->matrix == NULL) return FAILURE;
  if (matrix->rows <= 0 || matrix->columns <= 0) return FAILURE;
  return SUCCESS;
}

int s21_matrix_verification(const matrix_t *A, const matrix_t *B) {
  if (!s21_valid_matrix(A) || !s21_valid_matrix(B)) {
    return FAILURE;
  }

  if (A->rows != B->rows || A->columns != B->columns) {
    return FAILURE;
  }

  return SUCCESS;
}

int s21_reset_matrix(matrix_t *matrix) {
  if (matrix == NULL) {
    return ERROR_INCORRECT_MATRIX;
  }

  if (matrix->matrix != NULL) {
    for (int i = 0; i < matrix->rows; i++) {
      for (int j = 0; j < matrix->columns; j++) {
        matrix->matrix[i][j] = 0.0;
      }
    }
  }
  return OK;
}

int s21_valid_determinant(const matrix_t *A, double *result) {
  if (A == NULL || result == NULL) {
    return ERROR_INCORRECT_MATRIX;
  }

  if (A->matrix == NULL || A->rows <= 0 || A->columns <= 0) {
    return ERROR_INCORRECT_MATRIX;
  }

  if (A->rows != A->columns) {
    return ERROR_INCORRECT_MATRIX;
  }
  return OK;
}

void s21_determinant_1x1(matrix_t *temp_matrix, double *determinant) {
  *determinant = temp_matrix->matrix[0][0];
}

void s21_determinant_2x2(matrix_t *temp_matrix, double *determinant) {
  *determinant = (temp_matrix->matrix[0][0] * temp_matrix->matrix[1][1]) -
                 (temp_matrix->matrix[0][1] * temp_matrix->matrix[1][0]);
}

void s21_rule_of_sarrus(matrix_t *temp_matrix, double *determinant) {
  *determinant = (temp_matrix->matrix[0][0] * temp_matrix->matrix[1][1] *
                      temp_matrix->matrix[2][2] +
                  temp_matrix->matrix[0][1] * temp_matrix->matrix[1][2] *
                      temp_matrix->matrix[2][0] +
                  temp_matrix->matrix[0][2] * temp_matrix->matrix[1][0] *
                      temp_matrix->matrix[2][1]) -
                 (temp_matrix->matrix[0][2] * temp_matrix->matrix[1][1] *
                      temp_matrix->matrix[2][0] +
                  temp_matrix->matrix[0][0] * temp_matrix->matrix[1][2] *
                      temp_matrix->matrix[2][1] +
                  temp_matrix->matrix[0][1] * temp_matrix->matrix[1][0] *
                      temp_matrix->matrix[2][2]);
}

void s21_method_gauss(matrix_t *temp_matrix, double *determinant, int *sign) {
  *determinant = 1.0;

  for (int i = 0; i < temp_matrix->rows; i++) {
    if (temp_matrix->matrix[i][i] == 0) {
      int found = 0;
      for (int k = i + 1; k < temp_matrix->rows; k++) {
        if (temp_matrix->matrix[k][i] != 0) {
          double *temp = temp_matrix->matrix[i];
          temp_matrix->matrix[i] = temp_matrix->matrix[k];
          temp_matrix->matrix[k] = temp;
          *sign *= -1;
          found = 1;
          break;
        }
      }
      if (!found) {
        *determinant = 0.0;
        return;
      }
    }
    for (int k = i + 1; k < temp_matrix->rows; k++) {
      double set_zero = temp_matrix->matrix[k][i] / temp_matrix->matrix[i][i];
      for (int j = i; j < temp_matrix->columns; j++) {
        temp_matrix->matrix[k][j] -= set_zero * temp_matrix->matrix[i][j];
      }
    }
  }
  for (int i = 0; i < temp_matrix->rows; i++) {
    *determinant *= temp_matrix->matrix[i][i];
  }
  *determinant *= *sign;
}

int s21_minor_matrix(matrix_t *A, int excluded_row, int excluded_column,
                     matrix_t *result) {
  if (!s21_valid_matrix(A) || result == NULL) {
    return ERROR_INCORRECT_MATRIX;
  }

  if (A->rows <= 1 || A->columns <= 1) {
    return ERROR_CALCULATION;
  }

  int status = s21_create_matrix(A->rows - 1, A->columns - 1, result);
  if (status != OK) {
    return status;
  }

  for (int i = 0, minor_rows = 0; i < A->rows; i++) {
    if (i == excluded_row) continue;

    for (int j = 0, minor_columns = 0; j < A->columns; j++) {
      if (j == excluded_column) continue;

      result->matrix[minor_rows][minor_columns] = A->matrix[i][j];
      minor_columns++;
    }
    minor_rows++;
  }

  return OK;
}

int s21_set_of_checks(const matrix_t *A, const matrix_t *result) {
  if (!s21_valid_matrix(A)) {
    return ERROR_INCORRECT_MATRIX;
  }

  if (result == NULL) {
    return ERROR_INCORRECT_MATRIX;
  }

  if (A->rows != A->columns) {
    return ERROR_CALCULATION;
  }

  return OK;
}