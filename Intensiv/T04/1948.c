#include <stdio.h>

int is_prime(int num);
int find_largest_prime(int a);

int main() {
  int number;
  if (scanf("%d", &number) != 1) {
    printf("n/a");
    return 0;
  }

  int result = find_largest_prime(number);
  if (result == -1) {
    printf("n/a");
  } else {
    printf("%d", result);
  }
  return 0;
}
int is_prime(int num) {
  if (num < 2)
    return 0;

  for (int i = 2; i < num; ++i) {
    int temp = num;
    while (temp > 0)
      temp -= i;
    if (temp == 0)
      return 0;
  }
  return 1;
}

int find_largest_prime(int a) {
  if (a < 0)
    a = -a;
  if (a < 2)
    return -1;

  int largest_prime = -1;
  for (int i = 2; i <= a; ++i) {
    int remainder = a;
    while (remainder >= i)
      remainder -= i;
    if (remainder == 0 && is_prime(i)) {
      largest_prime = i;
    }
  }
  return largest_prime;
}
