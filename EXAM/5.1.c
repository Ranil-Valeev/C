#include <stdio.h>
#include <stdlib.h>

int main() {
    int n;
    char c;
    if (scanf("%d%c", &n, &c) != 2 || (c != ' ' && c != '\n') || n <= 0) {
        printf("n/a");
        return 1;
    }

    int *mass1 = malloc(n * sizeof(int));
    int *mass2 = malloc(n * sizeof(int));

    if (mass1 == NULL || mass2 == NULL) {
        printf("n/a");
        return 1;
    }

    for (int i = 0; i < n; i++) {
        if (scanf("%d", &mass1[i]) != 1) {
            printf("n/a");
            if (mass1 != NULL) {
                free(mass1);
            }
            if (mass2 != NULL) {
                free(mass2);
            }
            return 1;
        }
    }

    for (int j = 0; j < n; j++) {
        if (scanf("%d", &mass2[j]) != 1) {
            printf("n/a");
            if (mass1 != NULL) {
                free(mass1);
            }
            if (mass2 != NULL) {
                free(mass2);
            }
            return 1;
        }
    }

    int sum = 0;
    for (int k = 0; k < n; k++) {
        sum += mass1[k] * mass2[k];
    }

    printf("%d", sum);

    if (mass1 != NULL) {
        free(mass1);
    }
    if (mass2 != NULL) {
        free(mass2);
    }
    return 0;
}