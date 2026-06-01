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
    for (int i = 0; i < count / 2; i++) {
        if (i > 0) {
            printf(" ");
        }
        printf("%d %d", mass[i], mass[count - 1 - i]);
    }
    if (count % 2 != 0) {
        if (count > 1) {
            printf(" ");
        }
        printf("%d", mass[count / 2]);
    }
    if (mass != NULL) {
        free(mass);
    }
    return 0;
}