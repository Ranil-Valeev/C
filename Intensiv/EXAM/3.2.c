#include <stdio.h>

int main(void) {
    double rad;
    double deg;
    char c;
    if (scanf("%lf%c", &rad, &c) != 2 || c != '\n') {
        printf("n/a");
        return 1;
    }
    deg = 57.29 * rad;
    printf("%.0lf", deg);
}