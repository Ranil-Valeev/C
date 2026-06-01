#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, count = 0;
    int *mass = NULL;
    while (scanf("%d", &n) == 1 && n != -1) {
        int *temp = realloc(mass, (count + 1) * sizeof(int));
        if (temp == NULL) {
            if (mass != NULL) {
                free(mass);
            }
            printf("n/a");
            return 1;
        }
        mass = temp;
        mass[count++] = n;
    }
    if (n != -1) {
        if (mass != NULL) {
            free(mass);
        }
        printf("n/a");
        return 1;
    }
    int *result = malloc(count * sizeof(int));
    int result_count = 0;
    for (int i = 0; i < count; i++) {
        int duplicate = 0;
        for (int j = 0; j < result_count; j++) {
            if (mass[i] == result[j]) {
                duplicate = 1;
                break;
            }
        }
        if (!duplicate) {
            result[result_count++] = mass[i];
        }
    }
    for (int k = 0; k < result_count; k++) {
        if (k > 0) {
            printf(" ");
        }
        printf("%d", result[k]);
    }
    if (mass != NULL) {
        free(mass);
    }
    if (result != NULL) {
        free(result);
    }
    return 0;
}