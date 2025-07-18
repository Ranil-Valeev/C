#include <stdio.h>

int main() {
    int x, y, z;
    char c;

    scanf("%d%d%d%c", &x, &y, &z, &c);
    if (c == ' ' || c == '\n') {
        if (x && (z || y) == 1) {
            printf("1");
        } else {
            printf("0");
        }
    } else {
        printf("n/a");
        return 1;
    }
    return 0;
}