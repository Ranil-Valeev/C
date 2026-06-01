#include <stdio.h>
#include <stdlib.h>

void free_matrix(int **a, int n) {
    if (a != NULL) {
        for (int i = 0; i < n; i++) {
            if (a[i] != NULL) {
                free(a[i]);
            }
        }
        free(a);
    }
}

int main() {
    int n, m;
    char c;
    if (scanf("%d %d%c", &m, &n, &c) != 3 || (c != ' ' && c != '\n') || n <= 0 || m <= 0) {
        printf("n/a");
        return 1;
    }
    int **mat;
    mat = malloc(sizeof(int) * m);
    for (int i = 0; i < m; i++) {
        mat[i] = malloc(sizeof(int) * n);
    }
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (scanf("%d%c", &mat[i][j], &c) != 2 || (c != ' ' && c != '\n')) {
                printf("n/a");
                free_matrix(mat, m);
                return 1;
            }
        }
    }
    int min = mat[0][0], max = mat[0][0], min_i = 0, max_i = 0;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (min > mat[i][j]) {
                min = mat[i][j];
                min_i = i;
            }
            if (max < mat[i][j]) {
                max = mat[i][j];
                max_i = i;
            }
        }
    }
    int *temp;
    temp = mat[min_i];
    mat[min_i] = mat[max_i];
    mat[max_i] = temp;

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d", mat[i][j]);
            if (j < n - 1) printf(" ");
        }
        if (i < n) printf("\n");
    }
    free_matrix(mat, m);
    return 0;
}