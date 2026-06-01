#include <stdio.h>
int main() {
    int a, b, c;
    char s;
    if (scanf("%d %d %d%c", &a, &b, &c, &s) != 4 || s != '\n') {
        printf("n/a");
        return 1;
    }
    if (c > a && c < b)
        printf("1");
    else
        printf("0");
    return 0;
}