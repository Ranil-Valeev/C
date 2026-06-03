#include <math.h>
#include <stdio.h>
#define NMAX 30

int input(int *a, int *n);
int search(int *a, int n);
void output(int result);
double mean(int *a, int n);
double variance(int *a, int n);

int main() {
    int n, data[NMAX];
    if (input(data, &n) == 1) {
        return 1;
    }
    int result = search(data, n);
    output(result);
    return 0;
}

int search(int *a, int n) {
    double mean_v = mean(a, n);
    double variance_v = variance(a, n);
    for (int i = 0; i < n; i++) {
        if (a[i] % 2 == 0 && a[i] > mean_v && a[i] <= (mean_v + 3 * sqrt(variance_v)) && a[i] != 0) {
            return a[i];
        }
    }
    return 0;
}

void output(int result) { printf("%d", result); }

int input(int *a, int *n) {
    if (scanf("%d", n) != 1 || (*n <= 0) || (*n > NMAX)) {
        printf("n/a");
        return 1;
    }
    char c;
    for (int i = 0; i < *n; i++) {
        if (scanf("%d%c", &a[i], &c) != 2 || (c != ' ' && c != '\n')) {
            printf("n/a");
            return 1;
        }
    }
    return 0;
}

double mean(int *a, int n) {
    double mat = 0.0;
    double mat_res = 0.0;
    for (int i = 0; i < n; i++) {
        mat += a[i];
    }
    mat_res = mat / n;
    return mat_res;
}

double variance(int *a, int n) {
    double mat_res = mean(a, n);
    double var_res = 0.0;
    for (int i = 0; i < n; i++) {
        var_res += (a[i] - mat_res) * (a[i] - mat_res);
    }
    return var_res / n;
}