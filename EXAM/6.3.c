#include <stdio.h>
#include <stdlib.h>

void free_matrix(int **a, int m) {
    if (a != NULL) {
        for (int i = 0; i < m; i++) {
            if (a[i] != NULL) {
                free(a[i]);
            }
        }
        free(a);
    }
}

int main() {
    int m, n;
    char c;
    if (scanf("%d %d%c", &m, &n, &c) != 3 || (c != ' ' && c != '\n') || m <= 0 || n <= 0) {
        printf("n/a");
        return 1;
    }

    int **mat = malloc(sizeof(int *) * m);
    for (int i = 0; i < m; i++) {
        mat[i] = malloc(sizeof(int) * n);
    }

    for (int i = 0; i < m ; i++) {
        for (int j = 0; j < n; j++) {
            if (scanf("%d%c", &mat[i][j], &c) != 2 || (c != ' ' && c != '\n')) {
                printf("n/a");
                free_matrix(mat, m);
                return 1;
            }
        }
    }

    int **t = malloc(sizeof(int *) * n);
    for (int i = 0; i < n; i++) {
        t[i] = malloc(sizeof(int) * m);
    }

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            t[j][i] = mat[i][j];
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m / 2; j++) {
            int temp = t[i][j];
            t[i][j] = t[i][m - 1 - j];
            t[i][m - 1 - j] = temp;
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            printf("%d", t[i][j]);
            if (j < m - 1) {
                printf(" ");
            }
        }
        printf("\n");
    }
    free_matrix(t, m);
    free_matrix(mat, m);
    return 0;
}