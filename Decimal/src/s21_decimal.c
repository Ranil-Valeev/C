#include "s21_decimal.h"

// сбрасывает структуру в ноль
void s21_reset_to_zero(s21_decimal *d) {
  if (d)
    memset(d, 0, sizeof(*d));
}

// получить знак
int s21_get_sign(const s21_decimal *d) {
  if (!d)
    return 0;
  return (d->bits[3] & S21_DECIMAL_SIGN_PLUS) ? 1 : 0;
}

// получить знак
void s21_set_sign(s21_decimal *d, int sign) {
  if (!d)
    return;

  if (sign) {
    d->bits[3] |= S21_DECIMAL_SIGN_PLUS;
  } else {
    d->bits[3] &= S21_DECIMAL_SIGN_MINUS;
  }
}

// получить масштаб
int s21_get_scale(const s21_decimal *d) {
  if (!d)
    return 0;
  return (d->bits[3] & S21_DECIMAL_SCALE_MASK) >> S21_DECIMAL_SCALE_SHIFT;
}

void s21_set_scale(s21_decimal *d, int scale) {
  if (!d)
    return;

  int sign = s21_get_sign(d);

  d->bits[3] = 0;

  if (scale < 0)
    scale = 0;
  if (scale > S21_DECIMAL_MAX_SCALE)
    scale = S21_DECIMAL_MAX_SCALE;

  d->bits[3] |= (scale << 16);

  if (sign) {
    d->bits[3] |= S21_DECIMAL_SIGN_PLUS;
  }
}

int s21_is_valid_decimal(s21_decimal d) {
  int scale = s21_get_scale(&d);
  if (scale < 0 || scale > 28)
    return 0;

  uint32_t bits3 = (uint32_t)d.bits[3];
  uint32_t reserved_bits = bits3 & 0x7F000000;
  if (reserved_bits != 0)
    return 0;

  return 1;
}

// отбрасывание знака для int
int s21_trim_fractional_part(s21_decimal src, s21_decimal *dst) {
  if (!dst)
    return S21_CONV_ERROR;

  int sign = s21_get_sign(&src);

  *dst = src;
  s21_set_sign(dst, 0);

  int scale = s21_get_scale(dst);

  if (scale == 0) {
    if (sign) {
      s21_set_sign(dst, 1);
    }
    s21_set_sign(dst, 0);
    return S21_CONV_OK;
  }

  while (scale > 0) {
    unsigned long long remainder = 0;

    for (int i = 2; i >= 0; i--) {
      unsigned long long current =
          ((unsigned long long)dst->bits[i]) | (remainder << 32);

      dst->bits[i] = (unsigned int)(current / 10);
      remainder = current % 10;
    }
    scale--;
  }

  s21_set_scale(dst, 0);

  if (sign) {
    s21_set_sign(dst, 1);
  }
  return S21_CONV_OK;
}

// проверка на нулевое значение мантиссы
int s21_zero_value(s21_decimal d) {
  return (d.bits[0] == 0 && d.bits[1] == 0 && d.bits[2] == 0);
}

// нормализация шкалы двух мантисс
int s21_normal_scale_decimal(s21_decimal *value_1, s21_decimal *value_2,
                             s21_decimal *normal_value_1,
                             s21_decimal *normal_value_2, int *normal_scale) {
  *normal_value_1 = *value_1;
  *normal_value_2 = *value_2;

  int scale_value_1 = s21_get_scale(value_1);
  int scale_value_2 = s21_get_scale(value_2);

  if (scale_value_1 == scale_value_2) {
    *normal_scale = scale_value_1;
    return TRUE;
  }

  if (scale_value_1 < scale_value_2) {
    *normal_scale = scale_value_2;
    int difference = scale_value_2 - scale_value_1;

    for (int i = 0; i < difference; i++) {
      if (!s21_multiplication_by_10(normal_value_1)) {
        return FALSE;
      }
    }

    s21_set_scale(normal_value_1, scale_value_2);

  } else {
    *normal_scale = scale_value_1;
    int difference = scale_value_1 - scale_value_2;

    for (int i = 0; i < difference; i++) {
      if (!s21_multiplication_by_10(normal_value_2)) {
        return FALSE;
      }
    }

    s21_set_scale(normal_value_2, scale_value_1);
  }
  return TRUE;
}

// умножение мантиссы на 10
int s21_multiplication_by_10(s21_decimal *value) {
  if (!value)
    return 0;

  unsigned int low = value->bits[0];
  unsigned int middle = value->bits[1];
  unsigned int high = value->bits[2];

  unsigned long long temp = 0;
  unsigned long long carry = 0;

  temp = (unsigned long long)low * 10 + carry;
  low = (unsigned int)(temp & S21_DECIMAL_ALL_BITS);
  carry = temp >> S21_DECIMAL_NEXT_INT_SHIFT;

  temp = (unsigned long long)middle * 10 + carry;
  middle = (unsigned int)(temp & S21_DECIMAL_ALL_BITS);
  carry = temp >> S21_DECIMAL_NEXT_INT_SHIFT;

  temp = (unsigned long long)high * 10 + carry;
  high = (unsigned int)(temp & S21_DECIMAL_ALL_BITS);
  carry = temp >> S21_DECIMAL_NEXT_INT_SHIFT;

  if (carry != 0) {
    return 0;
  }

  value->bits[0] = low;
  value->bits[1] = middle;
  value->bits[2] = high;

  return 1;
}

int s21_mantissa_equal(s21_decimal value_1, s21_decimal value_2) {
  return (value_1.bits[0] == value_2.bits[0] &&
          value_1.bits[1] == value_2.bits[1] &&
          value_1.bits[2] == value_2.bits[2]);
}

int s21_is_greater_abs(s21_decimal a, s21_decimal b) {
  int scale_a = s21_get_scale(&a);
  int scale_b = s21_get_scale(&b);

  s21_set_sign(&a, 0);
  s21_set_sign(&b, 0);

  if (scale_a != scale_b) {
    while (scale_a < scale_b) {
      if (!s21_multiplication_by_10(&a)) {
        return 1;
      }
      scale_a++;
    }
    while (scale_b < scale_a) {
      if (!s21_multiplication_by_10(&b)) {
        return 1;
      }
      scale_b++;
    }
  }

  for (int i = 2; i >= 0; i--) {
    if (a.bits[i] > b.bits[i]) {
      return 1;
    } else if (a.bits[i] < b.bits[i]) {
      return 0;
    }
  }
  return 0;
}

int my_isfinite(float x) {
  uint32_t bits;
  memcpy(&bits, &x, sizeof(float));
  return (bits & 0x7F800000) != 0x7F800000;
}

int s21_bank_round(s21_decimal value, s21_decimal *result) {
  if (!result)
    return S21_OTHER_ERROR;

  if (s21_get_scale(&value) == 0) {
    *result = value;
    return S21_OTHER_OK;
  }

  int sign = s21_get_sign(&value);

  s21_decimal abs_value = value;
  s21_set_sign(&abs_value, 0);

  s21_decimal int_part;
  s21_truncate(abs_value, &int_part);

  s21_decimal fractional;
  s21_sub(abs_value, int_part, &fractional);

  s21_decimal half = {{5, 0, 0, 0}};
  s21_set_scale(&half, 1);

  if (s21_is_equal(fractional, half)) {
    if (s21_is_odd(&int_part)) {
      s21_decimal one = {{1, 0, 0, 0}};
      s21_add(int_part, one, &int_part);
    }
  } else {
    if (s21_is_greater(fractional, half)) {
      s21_decimal one = {{1, 0, 0, 0}};
      s21_add(int_part, one, &int_part);
    }
  }
  if (sign) {
    s21_set_sign(&int_part, 1);
  }

  *result = int_part;
  return S21_OTHER_OK;
}

int s21_cmp_mantissa_96(const s21_decimal *a, const s21_decimal *b) {
  uint32_t a2 = (uint32_t)a->bits[2], b2 = (uint32_t)b->bits[2];
  if (a2 != b2)
    return (a2 < b2) ? -1 : 1;
  uint32_t a1 = (uint32_t)a->bits[1], b1 = (uint32_t)b->bits[1];
  if (a1 != b1)
    return (a1 < b1) ? -1 : 1;
  uint32_t a0 = (uint32_t)a->bits[0], b0 = (uint32_t)b->bits[0];
  if (a0 != b0)
    return (a0 < b0) ? -1 : 1;
  return 0;
}

int s21_add_mantissa_96(const s21_decimal *a, const s21_decimal *b,
                        s21_decimal *res) {
  uint32_t carry = 0;
  for (int i = 0; i < 3; i++) {
    uint64_t sum = (uint64_t)a->bits[i] + (uint64_t)b->bits[i] + carry;
    res->bits[i] = (uint32_t)sum;
    carry = (uint32_t)(sum >> 32);
  }
  return (int)carry;
}

int s21_sub_mantissa_96(const s21_decimal *a, const s21_decimal *b,
                        s21_decimal *res) {
  uint32_t borrow = 0;
  for (int i = 0; i < 3; i++) {
    uint64_t av = (uint64_t)a->bits[i];
    uint64_t bv = (uint64_t)b->bits[i] + borrow;
    if (av >= bv) {
      res->bits[i] = (uint32_t)(av - bv);
      borrow = 0;
    } else {
      res->bits[i] = (uint32_t)((av + ((uint64_t)1 << 32)) - bv);
      borrow = 1;
    }
  }
  return (int)borrow;
}

int s21_inc_mantissa_96(s21_decimal *v) {
  uint64_t cur = (uint64_t)(uint32_t)v->bits[0] + 1u;
  v->bits[0] = (int)(uint32_t)cur;
  uint32_t carry = (uint32_t)(cur >> 32);

  for (int i = 1; i < 3 && carry; i++) {
    cur = (uint64_t)(uint32_t)v->bits[i] + carry;
    v->bits[i] = (int)(uint32_t)cur;
    carry = (uint32_t)(cur >> 32);
  }
  return carry ? 0 : 1;
}

int s21_mul_mantissa_by_10_96(s21_decimal *v) {
  s21_decimal a = *v;
  s21_decimal b = *v;

  uint32_t carry = 0;
  for (int i = 0; i < 3; i++) {
    uint64_t cur = ((uint64_t)(uint32_t)a.bits[i] << 1) + carry;
    a.bits[i] = (int)(uint32_t)cur;
    carry = (uint32_t)(cur >> 32);
  }
  if (carry)
    return 0;

  carry = 0;
  for (int i = 0; i < 3; i++) {
    uint64_t cur = ((uint64_t)(uint32_t)b.bits[i] << 3) + carry;
    b.bits[i] = (int)(uint32_t)cur;
    carry = (uint32_t)(cur >> 32);
  }
  if (carry)
    return 0;

  s21_decimal r = {{0, 0, 0, v->bits[3]}};
  if (s21_add_mantissa_96(&a, &b, &r))
    return 0;
  v->bits[0] = r.bits[0];
  v->bits[1] = r.bits[1];
  v->bits[2] = r.bits[2];
  return 1;
}

uint32_t s21_div_mantissa_by_10_96(s21_decimal *v) {
  uint64_t rem = 0;
  for (int i = 2; i >= 0; i--) {
    uint64_t cur = (rem << 32) | (uint32_t)v->bits[i];
    uint64_t q = cur / 10u;
    rem = cur % 10u;
    v->bits[i] = (int)(uint32_t)q;
  }
  return (uint32_t)rem;
}

int s21_need_bankers_round_up(int last_digit, int tail_nonzero, int lsd_even) {
  if (last_digit > 5)
    return 1;
  if (last_digit < 5)
    return 0;
  if (tail_nonzero)
    return 1;
  return (lsd_even) ? 0 : 1;
}

int s21_reduce_scale_bankers_96(s21_decimal *v, int new_scale) {
  int scale = s21_get_scale(v);
  if (new_scale < 0)
    new_scale = 0;
  if (new_scale > scale)
    return 1;

  while (scale > new_scale) {
    uint32_t last = s21_div_mantissa_by_10_96(v);
    scale--;
    s21_set_scale(v, scale);

    int tail = 0;
    int saved_last = (int)last;
    while (scale > new_scale) {
      if (saved_last != 0)
        tail = 1;
      saved_last = (int)s21_div_mantissa_by_10_96(v);
      scale--;
      s21_set_scale(v, scale);
    }

    int lsd = (int)((uint32_t)v->bits[0] % 10u);
    int up = s21_need_bankers_round_up(saved_last, tail, (lsd % 2 == 0));
    if (up) {
      if (!s21_inc_mantissa_96(v)) {
        if (scale == 0)
          return 0;
        (void)s21_div_mantissa_by_10_96(v);
        scale--;
        s21_set_scale(v, scale);
      }
    }
    return 1;
  }
  return 1;
}

int s21_normalize_pair_scales_96(s21_decimal *a, s21_decimal *b) {
  if (!a || !b)
    return 0;

  int sa = s21_get_scale(a);
  int sb = s21_get_scale(b);

  if (sa < 0 || sa > 28 || sb < 0 || sb > 28) {
    return 0;
  }

  if (sa == sb)
    return 1;

  s21_decimal *smaller_scale_dec;
  s21_decimal *larger_scale_dec;
  int smaller_scale, larger_scale;

  if (sa < sb) {
    smaller_scale_dec = a;
    larger_scale_dec = b;
    smaller_scale = sa;
    larger_scale = sb;
  } else {
    smaller_scale_dec = b;
    larger_scale_dec = a;
    smaller_scale = sb;
    larger_scale = sa;
  }

  while (smaller_scale < larger_scale) {
    if (smaller_scale < 28 && s21_mul_mantissa_by_10_96(smaller_scale_dec)) {
      smaller_scale++;
      s21_set_scale(smaller_scale_dec, smaller_scale);
    } else {
      break;
    }
  }

  if (smaller_scale == larger_scale) {
    return 1;
  }

  while (smaller_scale < larger_scale) {
    if (larger_scale > 0 &&
        s21_reduce_scale_bankers_96(larger_scale_dec, larger_scale - 1)) {
      larger_scale--;
      s21_set_scale(larger_scale_dec, larger_scale);
    } else {
      return 0;
    }
  }

  return 1;
}

void s21_big_zero(s21_big *x) { memset(x, 0, sizeof(*x)); }

void s21_big_from_mantissa_96(s21_big *x, const s21_decimal *d) {
  s21_big_zero(x);
  x->w[0] = (uint32_t)d->bits[0];
  x->w[1] = (uint32_t)d->bits[1];
  x->w[2] = (uint32_t)d->bits[2];
}

int s21_big_fits_96(const s21_big *x) {
  for (int i = 3; i < S21_BIG_WORDS; i++) {
    if (x->w[i] != 0u)
      return 0;
  }
  return 1;
}

int s21_big_is_zero(const s21_big *x) {
  for (int i = 0; i < S21_BIG_WORDS; i++) {
    if (x->w[i] != 0u)
      return 0;
  }
  return 1;
}

int s21_big_cmp(const s21_big *a, const s21_big *b) {
  for (int i = S21_BIG_WORDS - 1; i >= 0; i--) {
    if (a->w[i] != b->w[i])
      return (a->w[i] < b->w[i]) ? -1 : 1;
  }
  return 0;
}

void s21_big_add(const s21_big *a, const s21_big *b, s21_big *r) {
  uint64_t carry = 0;
  for (int i = 0; i < S21_BIG_WORDS; i++) {
    uint64_t sum = (uint64_t)a->w[i] + b->w[i] + carry;
    r->w[i] = (uint32_t)sum;
    carry = sum >> 32;
  }
}

void s21_big_sub(const s21_big *a, const s21_big *b, s21_big *r) {
  uint64_t borrow = 0;
  for (int i = 0; i < S21_BIG_WORDS; i++) {
    uint64_t av = (uint64_t)a->w[i];
    uint64_t bv = (uint64_t)b->w[i] + borrow;
    if (av >= bv) {
      r->w[i] = (uint32_t)(av - bv);
      borrow = 0;
    } else {
      r->w[i] = (uint32_t)((av + ((uint64_t)1 << 32)) - bv);
      borrow = 1;
    }
  }
}

int s21_big_mul_small(s21_big *a, uint32_t mul) {
  uint64_t carry = 0;
  for (int i = 0; i < S21_BIG_WORDS; i++) {
    uint64_t cur = (uint64_t)a->w[i] * mul + carry;
    a->w[i] = (uint32_t)cur;
    carry = cur >> 32;
  }
  return carry ? 0 : 1;
}

int s21_big_add_small(s21_big *a, uint32_t add) {
  uint64_t cur = (uint64_t)a->w[0] + add;
  a->w[0] = (uint32_t)cur;
  uint64_t carry = cur >> 32;
  for (int i = 1; i < S21_BIG_WORDS && carry; i++) {
    cur = (uint64_t)a->w[i] + carry;
    a->w[i] = (uint32_t)cur;
    carry = cur >> 32;
  }
  return carry ? 0 : 1;
}

uint32_t s21_big_div_small(s21_big *a, uint32_t div) {
  uint64_t rem = 0;
  for (int i = S21_BIG_WORDS - 1; i >= 0; i--) {
    uint64_t cur = (rem << 32) | a->w[i];
    uint64_t q = cur / div;
    rem = cur % div;
    a->w[i] = (uint32_t)q;
  }
  return (uint32_t)rem;
}

void s21_big_to_mantissa_96(const s21_big *x, s21_decimal *d) {
  d->bits[0] = (int)x->w[0];
  d->bits[1] = (int)x->w[1];
  d->bits[2] = (int)x->w[2];
}

void s21_big_mul_96x96(const s21_decimal *a, const s21_decimal *b, s21_big *r) {
  s21_big_zero(r);
  const uint32_t aw[3] = {(uint32_t)a->bits[0], (uint32_t)a->bits[1],
                          (uint32_t)a->bits[2]};
  const uint32_t bw[3] = {(uint32_t)b->bits[0], (uint32_t)b->bits[1],
                          (uint32_t)b->bits[2]};

  for (int i = 0; i < 3; i++) {
    uint64_t carry = 0;
    for (int j = 0; j < 3; j++) {
      int k = i + j;
      uint64_t cur = (uint64_t)aw[i] * bw[j] + r->w[k] + carry;
      r->w[k] = (uint32_t)cur;
      carry = cur >> 32;
    }
    r->w[i + 3] = (uint32_t)carry;
  }
}

/* Деление bigints через битовый long division */
static int s21_big_get_bit(const s21_big *x, int bit) {
  int w = bit / 32;
  int b = bit % 32;
  if (w < 0 || w >= S21_BIG_WORDS)
    return 0;
  return (x->w[w] >> b) & 1u;
}

static void s21_big_set_bit(s21_big *x, int bit, int val) {
  int w = bit / 32;
  int b = bit % 32;
  if (w < 0 || w >= S21_BIG_WORDS)
    return;
  if (val)
    x->w[w] |= (1u << b);
  else
    x->w[w] &= ~(1u << b);
}

static void s21_big_shl1(s21_big *x) {
  uint32_t carry = 0;
  for (int i = 0; i < S21_BIG_WORDS; i++) {
    uint32_t new_carry = (x->w[i] >> 31) & 1u;
    x->w[i] = (x->w[i] << 1) | carry;
    carry = new_carry;
  }
}

void s21_big_divmod(const s21_big *n, const s21_big *d, s21_big *q,
                    s21_big *r) {
  s21_big_zero(q);
  s21_big_zero(r);

  for (int bit = S21_BIG_WORDS * 32 - 1; bit >= 0; bit--) {
    s21_big_shl1(r);
    s21_big_set_bit(r, 0, s21_big_get_bit(n, bit));

    if (s21_big_cmp(r, d) >= 0) {
      s21_big tmp;
      s21_big_sub(r, d, &tmp);
      *r = tmp;
      s21_big_set_bit(q, bit, 1);
    }
  }
}

int s21_big_mul_pow10(s21_big *x, int pow) {
  for (int i = 0; i < pow; i++) {
    if (!s21_big_mul_small(x, 10u))
      return 0;
  }
  return 1;
}

int s21_big_fit_96_by_trailing_zeros(s21_big *m, int *scale) {
  if (!m || !scale)
    return 0;
  while (!s21_big_fits_96(m) && *scale > 0) {
    s21_big tmp = *m;
    uint32_t rem = s21_big_div_small(&tmp, 10u);
    if (rem != 0u)
      return 0;
    *m = tmp;
    (*scale)--;
  }
  return s21_big_fits_96(m) ? 1 : 0;
}

uint32_t s21_pow10_u32(int p) {
  uint32_t r = 1u;
  for (int i = 0; i < p; ++i)
    r *= 10u;
  return r;
}

uint32_t s21_round_bankers_u32(long double x) {
  long double ip = 0.0L;
  long double frac = modfl(x, &ip);
  uint32_t base = (uint32_t)ip;

  const long double eps = 1e-12L;

  if (frac > 0.5L + eps)
    return base + 1u;
  if (frac < 0.5L - eps)
    return base;
  return (base % 2u == 0u) ? base : (base + 1u);
}

int s21_pack_result(s21_decimal mantissa_only, int sign, int scale,
                    s21_decimal *result) {
  if (!result)
    return 0;
  *result = mantissa_only;
  s21_set_sign(result, sign);
  s21_set_scale(result, scale);
  if (s21_zero_value(*result))
    s21_set_sign(result, 0);
  return 1;
}

int s21_mod(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
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

  int sign_res = s21_get_sign(&value_1);

  int scale_a = s21_get_scale(&value_1);
  int scale_b = s21_get_scale(&value_2);
  int common_scale = (scale_a > scale_b) ? scale_a : scale_b;

  s21_decimal a = value_1;
  s21_decimal b = value_2;
  s21_set_sign(&a, 0);
  s21_set_sign(&b, 0);
  s21_set_scale(&a, 0);
  s21_set_scale(&b, 0);

  s21_big A, B;
  s21_big_from_mantissa_96(&A, &a);
  s21_big_from_mantissa_96(&B, &b);

  if (scale_a < common_scale) {
    if (!s21_big_mul_pow10(&A, common_scale - scale_a))
      return S21_ARITH_TOO_LARGE;
  }
  if (scale_b < common_scale) {
    if (!s21_big_mul_pow10(&B, common_scale - scale_b))
      return S21_ARITH_TOO_LARGE;
  }

  s21_big Q, R;
  s21_big_divmod(&A, &B, &Q, &R);

  if (s21_big_is_zero(&R)) {
    s21_reset_to_zero(result);
    return S21_ARITH_OK;
  }

  int out_scale = common_scale;
  if (!s21_big_fits_96(&R)) {
    if (!s21_big_fit_96_by_trailing_zeros(&R, &out_scale)) {
      return sign_res ? S21_ARITH_TOO_SMALL : S21_ARITH_TOO_LARGE;
    }
  }

  s21_decimal out = {{0u, 0u, 0u, 0u}};
  s21_big_to_mantissa_96(&R, &out);
  s21_set_scale(&out, out_scale);
  s21_set_sign(&out, sign_res);
  if (s21_zero_value(out))
    s21_set_sign(&out, 0);

  *result = out;
  return S21_ARITH_OK;
}

// Возвращает 1 - нечетное, 0 - четное
int s21_is_odd(const s21_decimal *dec) {
  if (!dec)
    return 0;
  return (dec->bits[0] & 1);
}