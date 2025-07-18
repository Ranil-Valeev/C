#include <stdio.h>

int main() {
    long int n = 0;
    int mul = 0;
    char c;
    if (scanf("%ld%c", &n, &c) != 2 || (c != ' ' && c != '\n')) {
        printf("n/a");
        return 1;
    }
    n = (n < 0) ? -n : n;
    while (n > 0) {
        int digit = (n % 10);
        if ((digit % 2) > 0) {
            mul = (mul == 0 ? 1 : mul) * digit;
        }
        n = n / 10;
    }
    printf("%d", mul);
}