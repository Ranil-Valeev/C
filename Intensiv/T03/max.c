#include <stdio.h>

Int max(int a, int b);

int main() {
    int a, b;
    if (scanf("%d %d", &a, &b) != 2) {
        printf("n/a");
        return 1;
    }
      
	int res=max(a, b);
	printf("%d", res);
    return 0;
}
Int max(int a, int b) {
    if (a > b) {
        return a; 
    } else {
        return b;
    }
}