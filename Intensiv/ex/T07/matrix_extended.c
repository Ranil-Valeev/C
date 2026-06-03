#include <stdio.h>
#include <stdlib.h>

#define MAXIM 100

void static_arrayf(int str, int col);
void array(int str, int col);
void dinamic_array(int str, int col);
void hard_array(int str, int col);
void print_row_max_col_min(int** matrix, int rows, int cols);

int main() {
    int number, str, col;
    scanf("%d", &number);
    if (number == 1) {
        if (scanf("%d%d", &str, &col) != 2 || str <= 0 || col <= 0 || str > 100 || col > 100) {
            printf("n/a");
            return 1;
        }
        static_arrayf(str, col);
    } else if (number == 2) {
        if (scanf("%d%d", &str, &col) != 2 || str <= 0 || col <= 0) {
            printf("n/a");
            return 1;
        }
        array(str, col);
    } else if (number == 3) {
        if (scanf("%d%d", &str, &col) != 2 || str <= 0 || col <= 0) {
            printf("n/a");
            return 1;
        }
        dinamic_array(str, col);
    } else if (number == 4) {
        if (scanf("%d%d", &str, &col) != 2 || str <= 0 || col <= 0) {
            printf("n/a");
            return 1;
        }
        hard_array(str, col);
    } else {
        printf("n/a");
    }
    return 0;
}

void print_row_max_col_min(int** matrix, int rows, int cols) {
    // Array for row maximums
    int* row_max = malloc(rows * sizeof(int));
    // Array for column minimums
    int* col_min = malloc(cols * sizeof(int));

    // Initialize column minimums with first element of each column
    for (int j = 0; j < cols; j++) {
        col_min[j] = matrix[0][j];
    }

    for (int i = 0; i < rows; i++) {
        row_max[i] = matrix[i][0];  // Initialize with first element of row
        for (int j = 0; j < cols; j++) {
            // Find row maximum
            if (matrix[i][j] > row_max[i]) {
                row_max[i] = matrix[i][j];
            }
            // Find column minimum
            if (matrix[i][j] < col_min[j]) {
                col_min[j] = matrix[i][j];
            }
        }
    }

    // Print row maximums
    for (int i = 0; i < rows; i++) {
        printf("%d", row_max[i]);
        if (i != rows - 1) {
            printf(" ");
        }
    }
    printf("\n");

    // Print column minimums
    for (int j = 0; j < cols; j++) {
        printf("%d", col_min[j]);
        if (j != cols - 1) {
            printf(" ");
        }
    }

    free(row_max);
    free(col_min);
}

void hard_array(int str, int col) {
    const int M = str, N = col;
    int** single_array_matrix = malloc(M * N * sizeof(int) + M * sizeof(int*));
    int* ptr = (int*)(single_array_matrix + M);
    int count = 0;

    for (int i = 0; i < M; i++) {
        single_array_matrix[i] = ptr + N * i;
    }

    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            if (scanf("%d", &single_array_matrix[i][j]) != 1) {
                printf("n/a");
                free(single_array_matrix);
                return;
            }
            count++;
        }
    }

    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            printf("%d", single_array_matrix[i][j]);
            if (j != col - 1) {
                printf(" ");
            }
        }
        if (i != str - 1) {
            printf("\n");
        }
    }

    printf("\n");
    print_row_max_col_min(single_array_matrix, M, N);

    free(single_array_matrix);
}

void array(int str, int col) {
    const int M = str, N = col;
    int count = 0;

    int** pointer_array = malloc(M * sizeof(int*));
    for (int i = 0; i < M; i++) {
        pointer_array[i] = malloc(N * sizeof(int));
    }

    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            count++;
            if (scanf("%d", &pointer_array[i][j]) != 1) {
                printf("n/a");
                for (int k = 0; k < M; k++) {
                    free(pointer_array[k]);
                }
                free(pointer_array);
                return;
            }
        }
    }

    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            printf("%d", pointer_array[i][j]);
            if (j != col - 1) {
                printf(" ");
            }
        }
        if (i != str - 1) {
            printf("\n");
        }
    }

    printf("\n");
    print_row_max_col_min(pointer_array, M, N);

    for (int i = 0; i < M; i++) {
        free(pointer_array[i]);
    }
    free(pointer_array);
}

void dinamic_array(int str, int col) {
    const int M = str, N = col;
    int** pointer_array = malloc(M * sizeof(int*));
    int* values_array = malloc(M * N * sizeof(int));
    int count = 0;

    for (int i = 0; i < M; i++) {
        pointer_array[i] = values_array + N * i;
    }

    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            count++;
            if (scanf("%d", &pointer_array[i][j]) != 1) {
                printf("n/a");
                free(values_array);
                free(pointer_array);
                return;
            }
        }
    }

    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            printf("%d", pointer_array[i][j]);
            if (j != col - 1) {
                printf(" ");
            }
        }
        if (i != str - 1) {
            printf("\n");
        }
    }

    printf("\n");
    print_row_max_col_min(pointer_array, M, N);

    free(values_array);
    free(pointer_array);
}

void static_arrayf(int str, int col) {
    int static_array[str][col];
    int** dynamic_view = malloc(str * sizeof(int*));

    for (int i = 0; i < str; i++) {
        dynamic_view[i] = static_array[i];
        for (int j = 0; j < col; j++) {
            if (scanf("%d", &static_array[i][j]) != 1) {
                printf("n/a");
                free(dynamic_view);
                return;
            }
        }
    }

    for (int i = 0; i < str; i++) {
        for (int j = 0; j < col; j++) {
            printf("%d", static_array[i][j]);
            if (j != col - 1) {
                printf(" ");
            }
        }
        if (i != str - 1) {
            printf("\n");
        }
    }

    printf("\n");
    print_row_max_col_min(dynamic_view, str, col);

    free(dynamic_view);
}
