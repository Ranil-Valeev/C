#include "s21_decimal.h"

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  if (!result)
    return S21_ARITH_TOO_LARGE;
  s21_reset_to_zero(result);

  if (!s21_is_valid_decimal(value_1) || !s21_is_valid_decimal(value_2)) {
    return S21_ARITH_TOO_LARGE;
  }

  if (s21_get_scale(&value_1) > 28 || s21_get_scale(&value_2) > 28) {
    return S21_ARITH_TOO_LARGE;
  }

  s21_decimal a = value_1;
  s21_decimal b = value_2;

  int sign_a = s21_get_sign(&a);
  int sign_b = s21_get_sign(&b);

  s21_set_sign(&a, 0);
  s21_set_sign(&b, 0);

  if (!s21_normalize_pair_scales_96(&a, &b)) {
    return S21_ARITH_TOO_LARGE;
  }
  int scale = s21_get_scale(&a);

  s21_decimal r = {{0u, 0u, 0u, 0u}};
  int sign_r = 0;

  if (sign_a == sign_b) {
    int carry = s21_add_mantissa_96(&a, &b, &r);
    sign_r = sign_a;

    if (!carry) {
      s21_set_scale(&r, scale);
      return s21_pack_result(r, sign_r, scale, result)
                 ? S21_ARITH_OK
                 : (sign_r ? S21_ARITH_TOO_SMALL : S21_ARITH_TOO_LARGE);
    }

    s21_big ba, bb, br;
    s21_big_from_mantissa_96(&ba, &a);
    s21_big_from_mantissa_96(&bb, &b);
    s21_big_add(&ba, &bb, &br);

    while (!s21_big_fits_96(&br) && scale > 0) {
      uint32_t digit = s21_big_div_small(&br, 10u);
      scale--;
      int lsd_even = ((br.w[0] % 2u) == 0u);
      int up = s21_need_bankers_round_up((int)digit, 0, lsd_even);
      if (up)
        (void)s21_big_add_small(&br, 1u);
    }

    if (!s21_big_fits_96(&br)) {
      return sign_r ? S21_ARITH_TOO_SMALL : S21_ARITH_TOO_LARGE;
    }

    s21_decimal rr = {{0u, 0u, 0u, 0u}};
    s21_big_to_mantissa_96(&br, &rr);
    s21_set_scale(&rr, scale);
    return s21_pack_result(rr, sign_r, scale, result)
               ? S21_ARITH_OK
               : (sign_r ? S21_ARITH_TOO_SMALL : S21_ARITH_TOO_LARGE);
  }

  /* разные знаки => вычитание модулей */
  int cmp = s21_cmp_mantissa_96(&a, &b);
  if (cmp == 0) {
    s21_reset_to_zero(result);
    return S21_ARITH_OK;
  } else if (cmp > 0) {
    (void)s21_sub_mantissa_96(&a, &b, &r);
    sign_r = sign_a;
  } else {
    (void)s21_sub_mantissa_96(&b, &a, &r);
    sign_r = sign_b;
  }

  s21_set_scale(&r, scale);
  return s21_pack_result(r, sign_r, scale, result) ? S21_ARITH_OK
                                                   : S21_ARITH_TOO_LARGE;
}

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  if (!result)
    return S21_ARITH_TOO_LARGE;
  s21_reset_to_zero(result);

  if (!s21_is_valid_decimal(value_1) || !s21_is_valid_decimal(value_2)) {
    return S21_ARITH_TOO_LARGE;
  }

  int sign = s21_get_sign(&value_1) ^ s21_get_sign(&value_2);
  int scale = s21_get_scale(&value_1) + s21_get_scale(&value_2);

  if (s21_get_scale(&value_1) > 28 || s21_get_scale(&value_2) > 28) {
    return S21_ARITH_TOO_LARGE;
  }

  s21_decimal a = value_1;
  s21_decimal b = value_2;
  s21_set_sign(&a, 0);
  s21_set_sign(&b, 0);

  s21_big prod;
  s21_big_mul_96x96(&a, &b, &prod);

  /* scale не должен превышать 28 */
  while (scale > 28) {
    uint32_t digit = s21_big_div_small(&prod, 10u);
    scale--;
    int lsd_even = ((prod.w[0] % 2u) == 0u);
    int up = s21_need_bankers_round_up((int)digit, 0, lsd_even);
    if (up)
      (void)s21_big_add_small(&prod, 1u);
  }

  /* Влезаем в 96 бит, уменьшая scale с банковским округлением */
  while (!s21_big_fits_96(&prod) && scale > 0) {
    uint32_t digit = s21_big_div_small(&prod, 10u);
    scale--;
    int lsd_even = ((prod.w[0] % 2u) == 0u);
    int up = s21_need_bankers_round_up((int)digit, 0, lsd_even);
    if (up)
      (void)s21_big_add_small(&prod, 1u);
  }

  if (!s21_big_fits_96(&prod)) {
    return sign ? S21_ARITH_TOO_SMALL : S21_ARITH_TOO_LARGE;
  }

  s21_decimal r = {{0u, 0u, 0u, 0u}};
  s21_big_to_mantissa_96(&prod, &r);
  s21_set_scale(&r, scale);
  s21_set_sign(&r, sign);

  *result = r;
  if (s21_zero_value(*result))
    s21_set_sign(result, 0);
  return S21_ARITH_OK;
}

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  if (!result)
    return S21_ARITH_TOO_LARGE;
  s21_reset_to_zero(result);

  if (!s21_is_valid_decimal(value_1) || !s21_is_valid_decimal(value_2)) {
    return S21_ARITH_TOO_LARGE;
  }
  if (s21_zero_value(value_2))
    return S21_ARITH_DIV_BY_ZERO;

  if (s21_get_scale(&value_1) > 28 || s21_get_scale(&value_2) > 28) {
    return S21_ARITH_TOO_LARGE;
  }

  int sign = s21_get_sign(&value_1) ^ s21_get_sign(&value_2);
  int scale1 = s21_get_scale(&value_1);
  int scale2 = s21_get_scale(&value_2);

  s21_decimal a = value_1;
  s21_decimal b = value_2;
  s21_set_sign(&a, 0);
  s21_set_sign(&b, 0);
  s21_set_scale(&a, 0);
  s21_set_scale(&b, 0);

  s21_big n, d;
  s21_big_from_mantissa_96(&n, &a);
  s21_big_from_mantissa_96(&d, &b);

  int scale = scale1 - scale2;

  while (scale < 0) {
    if (!s21_big_mul_small(&n, 10u))
      break;
    scale++;
  }

  s21_big q, r;
  s21_big_divmod(&n, &d, &q, &r);

  while (!s21_big_is_zero(&r) && scale < 28) {
    s21_big q10 = q;
    if (!s21_big_mul_small(&q10, 10u))
      break;

    (void)s21_big_mul_small(&r, 10u);

    s21_big digit_q, digit_r;
    s21_big_divmod(&r, &d, &digit_q, &digit_r);

    uint32_t digit = digit_q.w[0];
    q = q10;
    (void)s21_big_add_small(&q, digit);

    r = digit_r;
    scale++;
  }

  if (!s21_big_is_zero(&r)) {
    s21_big r10 = r;
    (void)s21_big_mul_small(&r10, 10u);

    s21_big digit_q, digit_r;
    s21_big_divmod(&r10, &d, &digit_q, &digit_r);

    int next_digit = (int)digit_q.w[0];
    int tail = !s21_big_is_zero(&digit_r);

    int lsd_even = ((q.w[0] % 2u) == 0u);
    int up = s21_need_bankers_round_up(next_digit, tail, lsd_even);
    if (up) {
      if (!s21_big_add_small(&q, 1u)) {
        return sign ? S21_ARITH_TOO_SMALL : S21_ARITH_TOO_LARGE;
      }
    }
  }

  while (!s21_big_fits_96(&q) && scale > 0) {
    uint32_t digit = s21_big_div_small(&q, 10u);
    scale--;
    int lsd_even = ((q.w[0] % 2u) == 0u);
    int up = s21_need_bankers_round_up((int)digit, 0, lsd_even);
    if (up)
      (void)s21_big_add_small(&q, 1u);
  }

  if (!s21_big_fits_96(&q)) {
    return sign ? S21_ARITH_TOO_SMALL : S21_ARITH_TOO_LARGE;
  }

  while (scale > 28) {
    uint32_t digit = s21_big_div_small(&q, 10u);
    scale--;
    int lsd_even = ((q.w[0] % 2u) == 0u);
    int up = s21_need_bankers_round_up((int)digit, 0, lsd_even);
    if (up)
      (void)s21_big_add_small(&q, 1u);
  }

  s21_decimal out = {{0u, 0u, 0u, 0u}};
  s21_big_to_mantissa_96(&q, &out);
  s21_set_scale(&out, scale);
  s21_set_sign(&out, sign);
  if (s21_zero_value(out))
    s21_set_sign(&out, 0);

  *result = out;
  return S21_ARITH_OK;
}

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  if (!result)
    return S21_ARITH_TOO_LARGE;
  s21_decimal b = value_2;
  s21_set_sign(&b, !s21_get_sign(&b));
  return s21_add(value_1, b, result);
}