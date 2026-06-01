#include <stdio.h>

int main(void) {
    long int n = 0;
    int max = 0;
    char c;
    if (scanf("%lf%c", &n, &c) != 2 || (c != ' ' && c != '\n')) {
        printf("n/a");
        return 1;
    }
    n = (n < 0) ? -n : n;
    while (n > 0) {
        if (n % 10 > max) max = n % 10;
        n = n / 10;
    }
    printf("%d", max);
}