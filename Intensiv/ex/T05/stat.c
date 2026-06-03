#include <stdio.h>
#define NMAX 10

int input(int *a, int *n);
void output(int *a, int n);
int max(int *a, int n);
int min(int *a, int n);
double mean(int *a, int n);
double variance(int *a, int n);
void output_result(int max_v, int min_v, double mean_v, double variance_v);

int main() {
    int n, data[NMAX];
    input(data, &n);
    output(data, n);
    output_result(max(data, n), min(data, n), mean(data, n), variance(data, n));

    return 0;
}

void output(int *a, int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");
}
int input(int *a, int *n) {
    if (scanf("%d", n) != 1 || (*n <= 0 || *n > NMAX)) {
        printf("n/a");
        return 1;
    }
    for (int i = 0; i - *n; i++) {
        if (scanf("%d", &a[i]) != 1) {
            printf("n/a");
            return 1;
        }
    }
    return 0;
}

int max(int *a, int n) {
    int max_i = a[1];
    for (int i = 0; i < n; i++) {
        if (a[i] > max_i) {
            max_i = a[i];
        }
    }
    return max_i;
}

int min(int *a, int n) {
    int min_i = a[1];
    for (int i = 0; i < n; i++) {
        if (a[i] < min_i) min_i = a[i];
    }
    return min_i;
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

void output_result(int max_v, int min_v, double mean_v, double variance_v) {
    printf("%d %d %.6f %.6f", max_v, min_v, mean_v, variance_v);
}