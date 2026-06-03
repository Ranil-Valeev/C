#include <stdio.h>

int main() {
    int a, b, sum, diff, mult, div;
    char c;
    if (scanf("%d %d%c", &a, &b, &c) != 3 || c != '\n') {
        printf("n/a");
        return 1;
    }
    sum = a + b;
    diff = a - b;
    mult = a * b;
    if (b == 0) {
        printf("%d %d %d n/a", sum, diff, mult);
    } else {
        div = a / b;
        printf("%d %d %d %d", sum, diff, mult, div);
    }
}