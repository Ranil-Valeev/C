#include "s21_decimal.h"

int s21_truncate(s21_decimal value, s21_decimal *result) {
  if (!result)
    return S21_OTHER_ERROR;
  if (!s21_is_valid_decimal(value))
    return S21_OTHER_ERROR;

  *result = value;
  int scale = s21_get_scale(result);

  if (scale == 0)
    return S21_OTHER_OK;

  int sign = s21_get_sign(result);
  s21_set_sign(result, 0);

  // Оптимизация для чисел, помещающихся в младшие 32 бита
  if (result->bits[1] == 0 && result->bits[2] == 0) {
    unsigned long long num = result->bits[0];
    for (int i = 0; i < scale; i++)
      num /= 10;
    result->bits[0] = (unsigned int)num;
  } else {
    // Общий случай для 96-битных чисел
    for (int i = 0; i < scale; i++) {
      unsigned long long remainder = 0;
      for (int j = 2; j >= 0; j--) {
        unsigned long long temp =
            ((unsigned long long)remainder << 32) | result->bits[j];
        result->bits[j] = (unsigned int)(temp / 10);
        remainder = temp % 10;
      }
    }
  }

  s21_set_scale(result, 0);
  if (sign)
    s21_set_sign(result, 1);

  return S21_OTHER_OK;
}

int s21_negate(s21_decimal value, s21_decimal *result) {
  if (result == NULL) {
    return S21_OTHER_ERROR;
  }

  *result = value;

  // Меняем знак (инвертируем 31-й бит)
  if (s21_get_sign(result)) {
    // Если был отрицательный, делаем положительный
    s21_set_sign(result, 0);
  } else {
    // Если был положительный, делаем отрицательный
    s21_set_sign(result, 1);
  }
  if (s21_zero_value(*result)) {
    s21_set_sign(result, 0);
  }

  return S21_OTHER_OK;
}

int s21_floor(s21_decimal value, s21_decimal *result) {

  if (!result)
    return S21_OTHER_ERROR;

  // Получаем целую часть (отбрасываем дробную)
  int truncate_result = s21_truncate(value, result);
  if (truncate_result != S21_OTHER_OK) {
    return truncate_result;
  }

  // Если число положительное или ноль - это и есть floor
  if (s21_get_sign(&value) == 0) {
    // Но нужно проверить, не получился ли -0
    if (s21_zero_value(*result)) {
      s21_set_sign(result, 0); // Нормализуем -0 в +0
    }
    return S21_OTHER_OK;
  }

  // Для отрицательных чисел:
  // Нужно проверить, есть ли дробная часть

  int scale = s21_get_scale(&value);

  if (scale == 0) {
    // Число уже целое: floor(-5) = -5
    // Но если это -0, нормализуем
    if (s21_zero_value(*result)) {
      s21_set_sign(result, 0);
    }
    return S21_OTHER_OK;
  }

  // Создаем копию value для проверки
  s21_decimal value_copy = value;

  s21_set_sign(&value_copy, 0); // Без знака

  // Создаем копию result с тем же scale
  s21_decimal result_copy = *result;
  s21_set_sign(&result_copy, 0);      // Без знака
  s21_set_scale(&result_copy, scale); // Восстанавливаем scale

  // Умножаем result_copy на 10^scale для сравнения
  for (int i = 0; i < scale; i++) {
    s21_decimal temp;
    // Используем умножение на 10
    s21_decimal ten = {{10, 0, 0, 0}};
    int mul_result = s21_mul(result_copy, ten, &temp);
    if (mul_result != S21_OTHER_OK) {
      return mul_result;
    }
    result_copy = temp;
  }

  // Сбрасываем scale для сравнения битов
  s21_set_scale(&value_copy, 0);
  s21_set_scale(&result_copy, 0);

  // Сравниваем биты
  int has_fraction = 0;
  if (value_copy.bits[0] != result_copy.bits[0] ||
      value_copy.bits[1] != result_copy.bits[1] ||
      value_copy.bits[2] != result_copy.bits[2]) {
    has_fraction = 1;
  }

  // Если есть дробная часть - уменьшаем на 1
  if (has_fraction) {
    s21_decimal one = {{1, 0, 0, 0}};
    int sub_result = s21_sub(*result, one, result);
    if (sub_result != S21_OTHER_OK) {
      return sub_result;
    }
  }

  // В конце проверяем, не получился ли -0
  if (s21_zero_value(*result)) {
    s21_set_sign(result, 0); // Нормализуем -0 в +0
  }

  return S21_OTHER_OK;
}

int s21_round(s21_decimal value, s21_decimal *result) {
  if (!result)
    return S21_OTHER_ERROR;

  int scale = s21_get_scale(&value);
  int sign = s21_get_sign(&value);

  // Если число целое
  if (scale == 0) {
    *result = value;
    return S21_OTHER_OK;
  }

  // Работаем с абсолютным значением
  s21_decimal abs_value = value;
  s21_set_sign(&abs_value, 0);

  // Получаем целую часть (положительное число)
  s21_truncate(abs_value, result);

  // НОРМАЛИЗУЕМ: приводим целую часть к тому же scale, что и исходное число
  s21_decimal int_scaled = *result;
  s21_set_scale(&int_scaled, scale);

  // Умножаем на 10^scale
  for (int i = 0; i < scale; i++) {
    s21_decimal ten = {{10, 0, 0, 0}};
    s21_decimal temp;
    s21_mul(int_scaled, ten, &temp);
    int_scaled = temp;
  }

  // Вычитаем
  s21_decimal abs_value_no_scale = abs_value;
  s21_set_scale(&abs_value_no_scale, 0);
  s21_set_scale(&int_scaled, 0);

  s21_decimal fractional;
  s21_sub(abs_value_no_scale, int_scaled, &fractional);

  // Создаем 0.5 * 10^scale
  s21_decimal half = {{5, 0, 0, 0}};
  for (int i = 0; i < scale - 1; i++) {
    s21_decimal ten = {{10, 0, 0, 0}};
    s21_decimal temp;
    s21_mul(half, ten, &temp);
    half = temp;
  }

  // Решаем, нужно ли округление вверх
  int need_round_up = s21_is_greater_or_equal(fractional, half);

  // ПРИМЕНЯЕМ ОКРУГЛЕНИЕ С УЧЕТОМ ЗНАКА
  if (need_round_up) {
    s21_decimal one = {{1, 0, 0, 0}};
    if (sign) {
      // Для отрицательных: -2.5 → -3 (нужно отрицательное число)
      // Сначала делаем целую часть отрицательной
      s21_set_sign(result, 1);
      // Затем вычитаем 1 (что эквивалентно добавлению -1)
      s21_sub(*result, one, result);
    } else {
      // Для положительных: 2.5 → 3
      s21_add(*result, one, result);
    }
  } else {
    // Если не округляем, просто восстанавливаем знак
    if (sign) {
      s21_set_sign(result, 1);
    }
  }

  return S21_OTHER_OK;
}

/*
Возвращаемое значение — код ошибки:

0 — OK;
1 — ошибка вычисления.
*/
