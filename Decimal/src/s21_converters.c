#include "s21_decimal.h"

// /*
// Преобразователи
// */

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  if (!dst)
    return S21_CONV_ERROR;

  s21_reset_to_zero(dst);
  s21_set_scale(dst, 0);

  if (src == 0) {
    return S21_CONV_OK;
  }

  uint32_t abs_value;
  int sign = 0;

  if (src < 0) {
    if (src == INT_MIN) {
      // Особый случай: INT_MIN = -2147483648
      abs_value = (uint32_t)2147483648u;
    } else {
      abs_value = (uint32_t)(-src);
    }
    sign = 1;
  } else {
    abs_value = (uint32_t)src;
    sign = 0;
  }

  dst->bits[0] = abs_value;
  s21_set_sign(dst, sign);

  return S21_CONV_OK;
}

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  if (!dst)
    return S21_CONV_ERROR;
  if (!s21_is_valid_decimal(src))
    return S21_CONV_ERROR;

  if (s21_zero_value(src)) {
    *dst = 0;
    return S21_CONV_OK;
  }

  int sign = s21_get_sign(&src);
  s21_decimal rounded;

  if (s21_bank_round(src, &rounded) != S21_OTHER_OK) {
    return S21_CONV_ERROR;
  }

  // Проверка на переполнение
  if (rounded.bits[1] != 0 || rounded.bits[2] != 0) {
    return S21_CONV_ERROR;
  }

  uint32_t value = rounded.bits[0];

  if (sign) {
    if (value > (uint32_t)INT_MAX + 1u) {
      return S21_CONV_ERROR;
    }
    if (value == (uint32_t)INT_MAX + 1u) {
      *dst = INT_MIN;
    } else {
      *dst = -(int)value;
    }
  } else {
    if (value > (uint32_t)INT_MAX) {
      return S21_CONV_ERROR;
    }
    *dst = (int)value;
  }

  return S21_CONV_OK;
}

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  if (!dst)
    return S21_CONV_ERROR;
  s21_reset_to_zero(dst);

  if (src == 0.0f) {
    return S21_CONV_OK;
  }

  if (!isfinite(src)) {
    return S21_CONV_ERROR;
  }

  float abs_src = fabsf(src);

  if (abs_src > S21_FLOAT_MAX) {
    return S21_CONV_ERROR;
  }
  if (abs_src < S21_FLOAT_MIN) {
    return S21_CONV_ERROR;
  }

  int sign = (src < 0.0f) ? 1 : 0;
  long double x = fabsl((long double)src);

  // Специальная обработка граничных значений
  if (fabsf(src - 2147483647.0f) < 0.5f) {
    s21_from_int_to_decimal(sign ? -2147483647 : 2147483647, dst);
    return S21_CONV_OK;
  }
  if (fabsf(src - (-2147483648.0f)) < 0.5f) {
    s21_from_int_to_decimal(sign ? -2147483648 : 2147483648, dst);
    return S21_CONV_OK;
  }

  // Проверка на целые числа, которые можно безопасно конвертировать через int
  float int_part;
  float frac_part = modff(abs_src, &int_part);
  if (frac_part == 0.0f && abs_src <= 2147483647.0f) {
    // Только числа <= INT_MAX конвертируем через int
    return s21_from_int_to_decimal((int)(sign ? -abs_src : abs_src), dst);
  }

  int e10 = (int)floorl(log10l(x));
  long double p10 = powl(10.0L, (long double)e10);
  long double m = x / p10;

  long double scaled = m * 1000000.0L;

  uint32_t digits;
  if (scaled >= 9999999.5L) {
    digits = 10000000u;
  } else {
    digits = s21_round_bankers_u32(scaled);
  }

  if (digits >= 10000000u) {
    digits /= 10u;
    e10 += 1;
  }

  int exp_after = e10 - 6;
  int scale = 0;

  s21_decimal out = {{0u, 0u, 0u, 0u}};
  out.bits[0] = digits;

  if (exp_after >= 0) {
    for (int i = 0; i < exp_after; ++i) {
      if (!s21_multiplication_by_10(&out)) {
        return S21_CONV_ERROR;
      }
    }
    scale = 0;
  } else {
    scale = -exp_after;

    // Проверка: если число можно представить с меньшим scale
    uint32_t temp_digits = digits;
    int temp_scale = scale;

    while (temp_scale > 0 && temp_digits % 10 == 0) {
      temp_digits /= 10;
      temp_scale--;
    }

    if (temp_scale < scale) {
      out.bits[0] = temp_digits;
      scale = temp_scale;
    }

    if (scale > 28) {
      int delta = scale - 28;

      uint32_t pow = s21_pow10_u32(delta);
      if (pow >= 10) {
        uint32_t q = digits / pow;
        uint32_t rem = digits % pow;

        uint32_t divisor = pow / 10u;
        if (divisor == 0)
          divisor = 1;

        uint32_t first_digit = rem / divisor;
        int has_tail = (rem % divisor) != 0u;
        int lsd_even = ((q % 2u) == 0u);
        int up =
            s21_need_bankers_round_up((int)first_digit, has_tail, lsd_even);

        if (up) {
          q += 1u;
        }

        out.bits[0] = q;
        scale = 28;
      }
    }
  }

  s21_set_scale(&out, scale);
  s21_set_sign(&out, sign);

  if (s21_zero_value(out)) {
    s21_set_sign(&out, 0);
  }

  *dst = out;
  return S21_CONV_OK;
}

int s21_from_decimal_to_float(s21_decimal src, float *dst) {
  if (!dst)
    return S21_CONV_ERROR;
  if (!s21_is_valid_decimal(src))
    return S21_CONV_ERROR;

  if (s21_zero_value(src)) {
    *dst = 0.0f;
    return S21_CONV_OK;
  }

  long double v = 0.0L;
  v += (long double)src.bits[0];
  v += (long double)src.bits[1] * 4294967296.0L;
  v += (long double)src.bits[2] * 18446744073709551616.0L;

  int scale = s21_get_scale(&src);
  if (scale > 0) {
    v /= powl(10.0L, (long double)scale);
  }

  if (s21_get_sign(&src)) {
    v = -v;
  }

  *dst = (float)v;
  return S21_CONV_OK;
}