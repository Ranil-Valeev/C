#include <stdio.h>
#include <stdlib.h>

void free_matrix(int **matrix, int rows) {
    if (matrix != NULL) {
        for (int i = 0; i < rows; i++) {
            if (matrix[i] != NULL) {
                free(matrix[i]);
            }
        }
        free(matrix);
    }
}

int main() {
    int n;
    char s;
    
    if (scanf("%d%c", &n, &s) != 2 || (s != ' ' && s != '\n') || n <= 0) {
        printf("n/a");
        return 1;
    }
    
    int **a = malloc(sizeof(int*) * n);
    int **b = malloc(sizeof(int*) * n);
    int **c = malloc(sizeof(int*) * n);

    if (a == NULL || b == NULL || c == NULL) {
        printf("n/a");
        free(a);
        free(b);
        free(c);
        return 1;
    }
    for (int i = 0; i < n; i++) {
        a[i] = malloc(sizeof(int) * n);
        b[i] = malloc(sizeof(int) * n);
        c[i] = malloc(sizeof(int) * n);
        if (a[i] == NULL || b[i] == NULL || c[i] == NULL) {
            printf("n/a");
            free_matrix(a, i + 1);
            free_matrix(b, i + 1);
            free_matrix(c, i + 1);
            return 1;
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (scanf("%d", &a[i][j]) != 1) {
                printf("n/a");
                free_matrix(a, n);
                free_matrix(b, n);
                free_matrix(c, n);
                return 1;
            }
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (scanf("%d", &b[i][j]) != 1) {
                printf("n/a");
                free_matrix(a, n);
                free_matrix(b, n);
                free_matrix(c, n);
                return 1;
            }
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            c[i][j] = 0;
            for (int k = 0; k < n; k++) {
                c[i][j] += a[i][k] * b[k][j];
            }
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d", c[i][j]);
            if (j < n - 1) printf(" ");
        }
        if (i < n - 1) printf("\n");
    }
    free_matrix(a, n);
    free_matrix(b, n);
    free_matrix(c, n);
    return 0;
}
