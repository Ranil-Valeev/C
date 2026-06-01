#include <stdio.h>

#define NMAX 10

int input(int *data, int *n, int *shift);
void output(int *data, int n);
void cycle_shift(int *data, int n, int shift);

int main() {
    int n, shift, data[NMAX];

    if (input(data, &n, &shift)) {
        printf("n/a");
        return 1;
    }
    cycle_shift(data, n, shift);
    output(data, n);
    return 0;
}

int input(int *data, int *n, int *shift) {
    if (scanf("%d", n) != 1 || *n <= 0 || *n > NMAX) {
        return 1;
    }
    for (int i = 0; i < *n; i++) {
        if (scanf("%d", &data[i]) != 1) {
            return 1;
        }
    }
    if (scanf("%d", shift) != 1) {
        return 1;
    }

    return 0;
}

void output(int *data, int n) {
    for (int i = 0; i < n; i++) {
        printf("%d", data[i]);
        if (i < n - 1) {
            printf(" ");
        }
    }
    printf("\n");
}

void cycle_shift(int *data, int n, int shift) {
    shift %= n;
    if (shift < 0) {
        shift += n;
    }
    int temp[NMAX];
    for (int i = 0; i < n; i++) {
        temp[i] = data[(i + shift) % n];
    }
    for (int i = 0; i < n; i++) {
        data[i] = temp[i];
    }
}