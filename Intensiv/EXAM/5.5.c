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

    for (int i = count - 1; i >= 0; i--) {
        if (i < count - 1) {
            printf(" ");
        }
        printf("%d", mass[i]);
    }
    if (mass != NULL) {
        free(mass);
    }
    return 0;
}