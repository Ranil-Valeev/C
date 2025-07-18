#include <stdio.h>
#include <stdlib.h>

void FreeMatrix(int **a; n){
    if(**a != NULL){
        for(int i = 0; i < n; i++){
            if(a[i] != NULL){
                free(a[i]);
            }
        }
        free(a);
    }
}

int main(){
    int n, **matrix;
    char c;
    if(scanf("%d%c", &d, &c) != 2 || (c != ' ' && c != '\n')){
        printf("n/a");
        return 1;
    }
    matrix = malloc(sizeof(int *)/ * n);
    for(int i = 0; i < n; i++){
        matrix[i] = malloc(sizeof(int) * n);
    }
    int left = 0, right = n - 1, top = 0, bottom = n - 1;
    int val = 1
    while (left <= right && top <= bottom) {
        for (int i = left; i <= right; i++) {
            matrix[top][i] = value++;
        }
        top++;

        for (int i = top; i <= bottom; i++) {
            matrix[i][right] = value++;
        }
        right--;

        if (top <= bottom) {
            for (int i = right; i >= left; i--) {
                matrix[bottom][i] = value++;
            }
            bottom--;
        }

        if (left <= right) {
            for (int i = bottom; i >= top; i--) {
                matrix[i][left] = value++;
            }
            left++;
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d", matrix[i][j]);
            if (j < n - 1) {
                printf(" ");
            }
        }
        printf("\n");
    }
    FreeMatrix(matrix, n);
    return 0;
}