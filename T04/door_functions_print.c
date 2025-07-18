#include <math.h>
#include <stdio.h>

#define PI 3.14159265358979323846
#define STEPS 42
#define HEIGHT 21

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

void print_graph(double (*func)(double), char label) {
  char graph[HEIGHT][STEPS + 1] = {0};

  for (int i = 0; i < HEIGHT; i++) {
    for (int j = 0; j < STEPS; j++) {
      graph[i][j] = ' ';
    }
    graph[i][STEPS] = '\0';
  }

  double max_val = 0;
  double min_x = -PI;
  double max_x = PI;
  double step = (max_x - min_x) / (STEPS - 1);

  for (int j = 0; j < STEPS; j++) {
    double x = min_x + j * step;
    double y = func(x);
    if (!isnan(y) && y > max_val) {
      max_val = y;
    }
  }

  for (int j = 0; j < STEPS; j++) {
    double x = min_x + j * step;
    double y = func(x);
    if (!isnan(y)) {
      int row = HEIGHT - 1 - (int)((y / max_val) * (HEIGHT - 1));
      if (row >= 0 && row < HEIGHT) {
        graph[row][j] = '*';
      }
    }
  }

  printf("%c", label);
  for (int i = 0; i < HEIGHT; i++) {
    printf("%s\n", graph[i]);
  }
  printf("\n");
}

int main() {
  double start = -PI;
  double end = PI;
  double step = (end - start) / (STEPS - 1);

  for (int i = 0; i < STEPS; i++) {
    double x = start + i * step;
    printf("%.7f | ", x);

    double a = agnesi(x);
    printf("%.7f | ", a);

    double b = bernoulli(x);
    if (isnan(b) || b <= 0) {
      printf("- | ");
    } else {
      printf("%.7f | ", b);
    }

    double h = hyperbola(x);
    if (isnan(h)) {
      printf("-\n");
    } else {
      printf("%.7f\n", h);
    }
  }
  printf("\n");
  print_graph(agnesi, 'A');
  print_graph(bernoulli, 'B');
  print_graph(hyperbola, 'H');

  return 0;
}