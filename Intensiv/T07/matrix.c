#include <stdio.h>
#include <stdlib.h>

#define N_MAX 100

int memory_allocation_method(int a);
int static_matrix(int row, int column);
int dynamic_matrix_1(int row, int column);
int dynamic_matrix_2(int row, int column);
int dynamic_matrix_3(int row, int column);

int main() {
    int a = 0;
    int result = memory_allocation_method(a);

    return result;
}
int memory_allocation_method(int a) {
    if (scanf("%d", &a) != 1) {
        printf("n/a");
        return 1;
    }
    if (a == 1) {
        int row = 0;
        int column = 0;
        return static_matrix(row, column);
    } else if (a == 2) {
        int row = 0;
        int column = 0;
        return dynamic_matrix_1(row, column);
    } else if (a == 3) {
        int row = 0;
        int column = 0;
        return dynamic_matrix_2(row, column);
    } else if (a == 4) {
        int row = 0;
        int column = 0;
        return dynamic_matrix_3(row, column);
    } else {
        printf("n/a");
        return 1;
    }
}
int static_matrix(int row, int column) {
    if (scanf("%d %d", &row, &column) != 2 || row > N_MAX || column > N_MAX) {
        printf("n/a");
        return 1;
    }
    int st_mat[row][column];
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < column; j++)
            if (scanf("%d", &st_mat[i][j]) != 1) {
                printf("n/a");
                return 1;
            }
    }
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < column; j++) {
            printf("%d", st_mat[i][j]);
            if (j < column - 1) {
                printf(" ");
            }
        }
        printf("\n");
    }
    return 0;
}
int dynamic_matrix_1(int row, int column) {
    if (scanf("%d %d", &row, &column) != 2 || row <= 0 || column <= 0) {
        printf("n/a");
        return 1;
    }
    int **dyn_mat_1 = malloc(row * column * sizeof(int) + row * sizeof(int *));
    if (dyn_mat_1 == NULL) {
        printf("n/a");
        return 1;
    }
    int *ptr = (int *)(dyn_mat_1 + row);
    for (int i = 0; i < row; i++) {
        dyn_mat_1[i] = ptr + column * i;
    }
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < column; j++)
            if (scanf("%d", &dyn_mat_1[i][j]) != 1) {
                printf("n/a");
                free(dyn_mat_1);
                return 1;
            }
    }
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < column; j++) {
            printf("%d", dyn_mat_1[i][j]);
            if (j < column - 1) {
                printf(" ");
            }
        }
        printf("\n");
    }
    free(dyn_mat_1);
    return 0;
}
int dynamic_matrix_2(int row, int column) {
    if (scanf("%d %d", &row, &column) != 2 || row <= 0 || column <= 0) {
        printf("n/a");
        return 1;
    }
    int **dyn_mat_2 = malloc(row * sizeof(int *));
    if (dyn_mat_2 == NULL) {
        printf("n/a");
        free(dyn_mat_2);
        return 1;
    }
    for (int i = 0; i < row; i++) {
        dyn_mat_2[i] = malloc(column * sizeof(int));
        if (dyn_mat_2[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(dyn_mat_2[j]);
            }
            printf("n/a");
            free(dyn_mat_2);
            return 1;
        }
    }
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < column; j++) {
            if (scanf("%d", &dyn_mat_2[i][j]) != 1) {
                printf("n/a");
                free(dyn_mat_2);
                return 1;
            }
        }
    }
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < column; j++) {
            printf("%d", dyn_mat_2[i][j]);
            if (j < column - 1) {
                printf(" ");
            }
        }
        printf("\n");
    }
    for (int i = 0; i < row; i++) {
        free(dyn_mat_2[i]);
    }
    free(dyn_mat_2);
    return 0;
}
int dynamic_matrix_3(int row, int column) {
    if (scanf("%d %d", &row, &column) != 2 || row <= 0 || column <= 0) {
        printf("n/a");
        return 1;
    }
    int **pointer_mat = malloc(row * sizeof(int *));
    if (pointer_mat == NULL) {
        printf("n/a");
        return 1;
    }
    int *values_mat = malloc(row * column * sizeof(int));
    if (values_mat == NULL) {
        free(pointer_mat);
        printf("n/a");
        return 1;
    }
    for (int i = 0; i < row; i++) {
        pointer_mat[i] = values_mat + column * i;
    }
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < column; j++) {
            if (scanf("%d", &pointer_mat[i][j]) != 1) {
                free(values_mat);
                free(pointer_mat);
                printf("n/a");
                return 1;
            }
        }
    }
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < column; j++) {
            printf("%d", pointer_mat[i][j]);
            if (j < column - 1) {
                printf(" ");
            }
        }
        printf("\n");
    }
    free(values_mat);
    free(pointer_mat);
    return 0;
}