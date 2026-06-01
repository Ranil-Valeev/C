#include <math.h>
#include <stdio.h>

int main(void) {
    int x, a, b, s;
    char c;
    if (scanf("%d%c", &x, &c) != 2 || (c != '\n' && c == ' ')) {
        printf("n/a");
        return 1;
    }
    a = x % 10;
    b = x / 10 % 10;
    s = x / 100;
    int sum = a * 100 + b * 10 + s;
    printf("%3d", sum);
    return 0;
}