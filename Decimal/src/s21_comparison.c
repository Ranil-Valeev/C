#include "s21_decimal.h"

// Меньше <
int s21_is_less(s21_decimal value_1, s21_decimal value_2) {
  if (s21_zero_value(value_1) && s21_zero_value(value_2)) {
    return FALSE;
  }

  if (!s21_is_valid_decimal(value_1) || !s21_is_valid_decimal(value_2)) {
    return FALSE;
  }

  int sign_value_1 = s21_get_sign(&value_1);
  int sign_value_2 = s21_get_sign(&value_2);

  if (sign_value_1 == 1 && sign_value_2 == 0) {
    return TRUE;
  }
  if (sign_value_2 == 1 && sign_value_1 == 0) {
    return FALSE;
  }

  s21_decimal normal_value_1, normal_value_2;
  int normal_scale;

  int normalization_successful = s21_normal_scale_decimal(
      &value_1, &value_2, &normal_value_1, &normal_value_2, &normal_scale);

  if (!normalization_successful) {
    int scale1 = s21_get_scale(&value_1);
    int scale2 = s21_get_scale(&value_2);

    for (int i = 2; i >= 0; i--) {
      if (value_1.bits[i] != value_2.bits[i]) {
        if (scale1 < scale2) {
          return sign_value_1 == 0 ? FALSE : TRUE;
        } else if (scale1 > scale2) {
          return sign_value_1 == 0 ? TRUE : FALSE;
        } else {
          return sign_value_1 == 0 ? (value_1.bits[i] < value_2.bits[i])
                                   : (value_1.bits[i] > value_2.bits[i]);
        }
      }
    }
    return FALSE;
  }

  for (int i = 2; i >= 0; i--) {
    if (normal_value_1.bits[i] < normal_value_2.bits[i]) {
      return sign_value_1 == 0 ? TRUE : FALSE;
    }
    if (normal_value_1.bits[i] > normal_value_2.bits[i]) {
      return sign_value_1 == 0 ? FALSE : TRUE;
    }
  }

  return FALSE;
}

// Меньше или равно <=
int s21_is_less_or_equal(s21_decimal value_1, s21_decimal value_2) {
  return s21_is_less(value_1, value_2) || s21_is_equal(value_1, value_2);
}

// Больше >
int s21_is_greater(s21_decimal value_1, s21_decimal value_2) {
  return !s21_is_less(value_1, value_2) && !s21_is_equal(value_1, value_2);
}

// Больше или равно >=
int s21_is_greater_or_equal(s21_decimal value_1, s21_decimal value_2) {
  return !s21_is_less(value_1, value_2);
}

// Равно ==
int s21_is_equal(s21_decimal value_1, s21_decimal value_2) {
  // проверка на ноль
  if (s21_zero_value(value_1) && s21_zero_value(value_2)) {
    return TRUE;
  }
  // проверка валидности шкалы
  if (!s21_is_valid_decimal(value_1) || !s21_is_valid_decimal(value_2)) {
    return FALSE;
  }
  // проверка знака
  if (s21_get_sign(&value_1) != s21_get_sign(&value_2)) {
    return FALSE;
  }

  s21_decimal normal_value_1, normal_value_2;
  int normal_scale;

  if (!s21_normal_scale_decimal(&value_1, &value_2, &normal_value_1,
                                &normal_value_2, &normal_scale)) {
    return FALSE;
  }

  for (int i = 0; i < 3; ++i) {
    if (normal_value_1.bits[i] != normal_value_2.bits[i]) {
      return FALSE;
    }
  }
  return TRUE;
}

// Не равно !=
int s21_is_not_equal(s21_decimal value_1, s21_decimal value_2) {
  return !s21_is_equal(value_1, value_2);
}

/*
Возвращаемое значение:

0 — FALSE;
1 — TRUE.
*/
