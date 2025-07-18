#include <stdio.h>

double Fib(int N);

int main() {
  int N = 0;

  if (scanf("%d", &N) != 1) {
    printf("n/a");
    return 1;
  } else if (N < 0) {
    printf("n/a");
    return 1;
  } else {
    printf("%0.1lf", Fib(N));
  }
  return 0;
}

double Fib(int N) {
  if (N == 0) {
    return 0;
  } else if (N == 1) {
    return 1;
  } else {
    return (Fib(N - 1) + Fib(N - 2));
  }
}