#include <stdio.h>
#define NMAX 10

int input(int *a, int *n);
void output(int *a, int n);
void squaring(int *a, int n);

int main() {
    int n, data[NMAX];
    if (input(data, &n) == 1) {
        return 1;
    }
    squaring(data, n);
    output(data, n);

    return 0;
}

int input(int *a, int *n) {
    int flag = 0;
    if (scanf("%d", n) != 1 || (*n <= 0 || *n > NMAX)) {
        flag = 1;
    }
    char c;
    for (int i = 0; i < *n; i++) {
        if (scanf("%d%c", &a[i], &c) != 2 || (c != ' ' && c != '\n')) {
            flag = 1;
            break;
        }
    }
    return flag;
}

void output(int *a, int n) {
    for (int i = 0; i < n; i++) {
        printf("%d", a[i]);
        if (a[i] != n - 1) printf(" ");
    }
}

void squaring(int *a, int n) {
    for (int i = 0; i < n; i++) {
        a[i] *= a[i];
    }
}