#include <math.h>
#include <stdio.h>

#define PI 3.14159265358979323846
#define STEPS 42

// Верзьера Аньези
double agnesi(double x) { return 1.0 / (1.0 + x * x); }

// Лемниската Бернулли (только для y > 0)
double bernoulli(double x) {
  double x_sq = x * x;
  double denom = 1.0 + x_sq * x_sq;
  if (denom == 0)
    return NAN;
  double under_root = (1.0 - x_sq * x_sq) / denom;
  if (under_root < 0)
    return NAN;
  return sqrt(under_root);
}

// Квадратичная гипербола
double hyperbola(double x) {
  if (x == 0)
    return NAN;
  return 1.0 / (x * x);
}

int main() {
  double start = -PI;
  double end = PI;
  double step = (end - start) / (STEPS - 1);

  for (int i = 0; i < STEPS; i++) {
    double x = start + i * step;

    // Вывод x с точностью 7 знаков
    printf("%.7f | ", x);

    // Верзьера Аньези
    double a = agnesi(x);
    printf("%.7f | ", a);

    // Лемниската Бернулли
    double b = bernoulli(x);
    if (isnan(b) || b <= 0) {
      printf("- | ");
    } else {
      printf("%.7f | ", b);
    }

    // Квадратичная гипербола
    double h = hyperbola(x);
    if (isnan(h)) {
      printf("-\n");
    } else {
      printf("%.7f\n", h);
    }
  }

  return 0;
}