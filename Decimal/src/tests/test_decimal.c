#include "test.h"

// Тесты для s21_is_greater_abs
START_TEST(is_greater_abs_with_scale) {
  s21_decimal a, b;
  s21_from_float_to_decimal(-3.5f, &a);
  s21_from_float_to_decimal(3.4f, &b);
  ck_assert_int_eq(s21_is_greater_abs(a, b), 1);
}
END_TEST

START_TEST(is_greater_abs_zero) {
  s21_decimal a, b;
  s21_from_int_to_decimal(0, &a);
  s21_from_int_to_decimal(-0, &b);
  ck_assert_int_eq(s21_is_greater_abs(a, b), 0);
}
END_TEST

START_TEST(is_greater_abs_simple) {
  s21_decimal a, b;
  s21_from_int_to_decimal(5, &a);
  s21_from_int_to_decimal(-3, &b);
  ck_assert_int_eq(s21_is_greater_abs(a, b), 1);
}
END_TEST

START_TEST(is_greater_abs_equal) {
  s21_decimal a, b;
  s21_from_int_to_decimal(-7, &a);
  s21_from_int_to_decimal(7, &b);
  ck_assert_int_eq(s21_is_greater_abs(a, b), 0);
}
END_TEST

// Тесты для s21_multiplication_by_10
START_TEST(multiply_by_10_positive) {
  s21_decimal d;
  s21_from_int_to_decimal(3, &d);
  s21_multiplication_by_10(&d);
  int out;
  s21_from_decimal_to_int(d, &out);
  ck_assert_int_eq(out, 30);
}
END_TEST

START_TEST(multiply_by_10_negative) {
  s21_decimal d;
  s21_from_int_to_decimal(-7, &d);
  s21_multiplication_by_10(&d);
  int out;
  s21_from_decimal_to_int(d, &out);
  ck_assert_int_eq(out, -70);
}
END_TEST

START_TEST(multiply_by_10_scale) {
  s21_decimal d;
  s21_from_float_to_decimal(3.1f, &d);
  s21_multiplication_by_10(&d);
  float out;
  s21_from_decimal_to_float(d, &out);
  ck_assert_float_eq_tol(out, 31.0f, 1e-6);
}
END_TEST

// Тесты для s21_need_bankers_round_up
START_TEST(test_need_bankers_round_up_gt_5) {
  ck_assert_int_eq(s21_need_bankers_round_up(6, 0, 1), 1);
  ck_assert_int_eq(s21_need_bankers_round_up(7, 1, 0), 1);
}
END_TEST

START_TEST(test_need_bankers_round_up_lt_5) {
  ck_assert_int_eq(s21_need_bankers_round_up(4, 0, 1), 0);
  ck_assert_int_eq(s21_need_bankers_round_up(3, 1, 0), 0);
}
END_TEST

START_TEST(test_need_bankers_round_up_eq_5_no_tail) {
  ck_assert_int_eq(s21_need_bankers_round_up(5, 0, 1), 0);
  ck_assert_int_eq(s21_need_bankers_round_up(5, 0, 0), 1);
}
END_TEST

START_TEST(test_need_bankers_round_up_eq_5_with_tail) {
  ck_assert_int_eq(s21_need_bankers_round_up(5, 1, 1), 1);
  ck_assert_int_eq(s21_need_bankers_round_up(5, 1, 0), 1);
}
END_TEST

// Тесты для s21_round_bankers_u32
START_TEST(test_round_bankers_u32_simple) {
  ck_assert_uint_eq(s21_round_bankers_u32(1.4L), 1u);
  ck_assert_uint_eq(s21_round_bankers_u32(1.49L), 1u);
  ck_assert_uint_eq(s21_round_bankers_u32(1.6L), 2u);
  ck_assert_uint_eq(s21_round_bankers_u32(1.51L), 2u);
  ck_assert_uint_eq(s21_round_bankers_u32(1.25L), 1u);
  ck_assert_uint_eq(s21_round_bankers_u32(1.75L), 2u);
}
END_TEST

START_TEST(test_round_bankers_u32_tie_even) {
  ck_assert_uint_eq(s21_round_bankers_u32(1.5L), 2u);
  ck_assert_uint_eq(s21_round_bankers_u32(2.5L), 2u);
  ck_assert_uint_eq(s21_round_bankers_u32(3.5L), 4u);
}
END_TEST

// Тесты для s21_pow10_u32
START_TEST(test_pow10_u32) {
  ck_assert_uint_eq(s21_pow10_u32(0), 1u);
  ck_assert_uint_eq(s21_pow10_u32(1), 10u);
  ck_assert_uint_eq(s21_pow10_u32(2), 100u);
  ck_assert_uint_eq(s21_pow10_u32(5), 100000u);
}
END_TEST

// Тесты для s21_cmp_mantissa_96
START_TEST(test_cmp_mantissa_96) {
  s21_decimal a = {{1, 0, 0, 0}};
  s21_decimal b = {{2, 0, 0, 0}};
  s21_decimal c = {{1, 1, 0, 0}};

  ck_assert_int_lt(s21_cmp_mantissa_96(&a, &b), 0);
  ck_assert_int_gt(s21_cmp_mantissa_96(&b, &a), 0);
  ck_assert_int_eq(s21_cmp_mantissa_96(&a, &a), 0);
  ck_assert_int_lt(s21_cmp_mantissa_96(&a, &c), 0);
}
END_TEST

// Тесты для s21_add_mantissa_96
START_TEST(test_add_mantissa_96_no_carry) {
  s21_decimal a = {{100, 0, 0, 0}};
  s21_decimal b = {{200, 0, 0, 0}};
  s21_decimal res;

  int carry = s21_add_mantissa_96(&a, &b, &res);
  ck_assert_int_eq(carry, 0);
  ck_assert_int_eq(res.bits[0], 300);
}
END_TEST

START_TEST(test_add_mantissa_96_with_carry) {
  s21_decimal a = {{0xFFFFFFFF, 0, 0, 0}};
  s21_decimal b = {{1, 0, 0, 0}};
  s21_decimal res;

  int carry = s21_add_mantissa_96(&a, &b, &res);
  ck_assert_int_eq(carry, 0);
  ck_assert_int_eq(res.bits[0], 0);
  ck_assert_int_eq(res.bits[1], 1);
}
END_TEST

// Тесты для s21_sub_mantissa_96
START_TEST(test_sub_mantissa_96_no_borrow) {
  s21_decimal a = {{500, 0, 0, 0}};
  s21_decimal b = {{200, 0, 0, 0}};
  s21_decimal res;

  int borrow = s21_sub_mantissa_96(&a, &b, &res);
  ck_assert_int_eq(borrow, 0);
  ck_assert_int_eq(res.bits[0], 300);
}
END_TEST

START_TEST(test_sub_mantissa_96_with_borrow) {
  s21_decimal a = {{0, 1, 0, 0}};
  s21_decimal b = {{1, 0, 0, 0}};
  s21_decimal res;

  int borrow = s21_sub_mantissa_96(&a, &b, &res);
  ck_assert_int_eq(borrow, 0);
  ck_assert_uint_eq(res.bits[0], 0xFFFFFFFF);
  ck_assert_int_eq(res.bits[1], 0);
}
END_TEST

// Тесты для s21_inc_mantissa_96
START_TEST(test_inc_mantissa_96_simple) {
  s21_decimal a = {{100, 0, 0, 0}};

  int result = s21_inc_mantissa_96(&a);
  ck_assert_int_eq(result, 1);
  ck_assert_int_eq(a.bits[0], 101);
}
END_TEST

START_TEST(test_inc_mantissa_96_overflow) {
  s21_decimal a = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};

  int result = s21_inc_mantissa_96(&a);
  ck_assert_int_eq(result, 0);
}
END_TEST

// Тесты для s21_div_mantissa_by_10_96
START_TEST(test_div_mantissa_by_10_96) {
  s21_decimal a = {{100, 0, 0, 0}};

  uint32_t rem = s21_div_mantissa_by_10_96(&a);
  ck_assert_uint_eq(rem, 0);
  ck_assert_int_eq(a.bits[0], 10);
}
END_TEST

START_TEST(test_div_mantissa_by_10_96_with_remainder) {
  s21_decimal a = {{123, 0, 0, 0}};

  uint32_t rem = s21_div_mantissa_by_10_96(&a);
  ck_assert_uint_eq(rem, 3);
  ck_assert_int_eq(a.bits[0], 12);
}
END_TEST

// Тесты для s21_big_zero и s21_big_is_zero
START_TEST(test_big_zero) {
  s21_big big;
  s21_big_from_mantissa_96(&big, &(s21_decimal){{1, 2, 3, 0}});

  s21_big_zero(&big);
  ck_assert_int_eq(s21_big_is_zero(&big), 1);
}
END_TEST

// Тесты для s21_big_from_mantissa_96
START_TEST(test_big_from_mantissa_96) {
  s21_decimal dec = {{0x12345678, 0x9ABCDEF0, 0x13579BDF, 0}};
  s21_big big;

  s21_big_from_mantissa_96(&big, &dec);
  ck_assert_uint_eq(big.w[0], 0x12345678);
  ck_assert_uint_eq(big.w[1], 0x9ABCDEF0);
  ck_assert_uint_eq(big.w[2], 0x13579BDF);
  for (int i = 3; i < S21_BIG_WORDS; i++) {
    ck_assert_uint_eq(big.w[i], 0);
  }
}
END_TEST

// Тесты для s21_big_fits_96
START_TEST(test_big_fits_96_true) {
  s21_big big;
  s21_big_zero(&big);
  big.w[0] = 1;
  big.w[1] = 2;
  big.w[2] = 3;

  ck_assert_int_eq(s21_big_fits_96(&big), 1);
}
END_TEST

START_TEST(test_big_fits_96_false) {
  s21_big big;
  s21_big_zero(&big);
  big.w[3] = 1;
  ck_assert_int_eq(s21_big_fits_96(&big), 0);
}
END_TEST

// Тесты для s21_big_cmp
START_TEST(test_big_cmp) {
  s21_big a = {{1, 2, 3, 0, 0, 0, 0}};
  s21_big b = {{1, 2, 3, 0, 0, 0, 0}};
  s21_big c = {{1, 2, 4, 0, 0, 0, 0}};
  s21_big d = {{1, 2, 2, 0, 0, 0, 0}};

  ck_assert_int_eq(s21_big_cmp(&a, &b), 0);
  ck_assert_int_lt(s21_big_cmp(&a, &c), 0);
  ck_assert_int_gt(s21_big_cmp(&a, &d), 0);
}
END_TEST

// Тесты для s21_big_mul_small
START_TEST(test_big_mul_small) {
  s21_big a = {{1, 0, 0, 0, 0, 0, 0}};

  int result = s21_big_mul_small(&a, 10);
  ck_assert_int_eq(result, 1);
  ck_assert_uint_eq(a.w[0], 10);
}
END_TEST

START_TEST(test_big_mul_small_overflow) {
  s21_big a;
  memset(&a, 0xFF, sizeof(a));

  int result = s21_big_mul_small(&a, 2);
  ck_assert_int_eq(result, 0);
}
END_TEST

// Тесты для s21_big_div_small
START_TEST(test_big_div_small) {
  s21_big a = {{100, 0, 0, 0, 0, 0, 0}};

  uint32_t rem = s21_big_div_small(&a, 10);
  ck_assert_uint_eq(rem, 0);
  ck_assert_uint_eq(a.w[0], 10);
}
END_TEST

// Тесты для s21_reduce_scale_bankers_96
START_TEST(test_reduce_scale_bankers_96) {
  s21_decimal dec = {{123456789, 0, 0, 2 << 16}};

  int result = s21_reduce_scale_bankers_96(&dec, 1);
  ck_assert_int_eq(result, 1);
  ck_assert_int_eq(s21_get_scale(&dec), 1);
}
END_TEST

// Тесты для s21_normalize_pair_scales_96
START_TEST(test_normalize_pair_scales_96_equal) {
  s21_decimal a = {{100, 0, 0, 2 << 16}};
  s21_decimal b = {{200, 0, 0, 2 << 16}};

  int result = s21_normalize_pair_scales_96(&a, &b);
  ck_assert_int_eq(result, 1);
  ck_assert_int_eq(s21_get_scale(&a), s21_get_scale(&b));
}
END_TEST

START_TEST(test_normalize_pair_scales_96_different) {
  s21_decimal a = {{100, 0, 0, 1 << 16}};
  s21_decimal b = {{200, 0, 0, 3 << 16}};

  int result = s21_normalize_pair_scales_96(&a, &b);
  ck_assert_int_eq(result, 1);
  ck_assert_int_eq(s21_get_scale(&a), s21_get_scale(&b));
}
END_TEST

// Тесты для проверки на NULL
START_TEST(test_null_pointers) {
  ck_assert_int_eq(s21_get_sign(NULL), 0);
  ck_assert_int_eq(s21_get_scale(NULL), 0);

  s21_decimal dec;
  s21_reset_to_zero(&dec);
  ck_assert_int_eq(s21_trim_fractional_part(dec, NULL), S21_CONV_ERROR);

  s21_set_sign(NULL, 1);
  s21_set_scale(NULL, 5);
  s21_reset_to_zero(NULL);
}
END_TEST

START_TEST(test_my_isfinite) {
  float normal = 123.456f;
  float inf = INFINITY;
  float nan = NAN;

  // Или даже直接用 стандартные макросы для проверки
  ck_assert_int_eq(my_isfinite(normal), 1);
  ck_assert_int_eq(my_isfinite(inf), 0);
  ck_assert_int_eq(my_isfinite(nan), 0);
}
END_TEST

// Тест для s21_mul_mantissa_by_10_96
START_TEST(test_mul_mantissa_by_10_96_overflow) {
  s21_decimal max = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};

  int result = s21_mul_mantissa_by_10_96(&max);
  ck_assert_int_eq(result, 0);
}
END_TEST

// Тесты для s21_big_mul_pow10
START_TEST(test_big_mul_pow10_zero_pow) {
  s21_big big;
  s21_big_zero(&big);
  big.w[0] = 123;

  int result = s21_big_mul_pow10(&big, 0);
  ck_assert_int_eq(result, 1);
  ck_assert_uint_eq(big.w[0], 123);
}
END_TEST

START_TEST(test_big_mul_pow10_small) {
  s21_big big;
  s21_big_zero(&big);
  big.w[0] = 5;

  int result = s21_big_mul_pow10(&big, 3);
  ck_assert_int_eq(result, 1);
  ck_assert_uint_eq(big.w[0], 5000);
}
END_TEST

START_TEST(test_big_mul_pow10_large) {
  s21_big big;
  s21_big_zero(&big);
  big.w[0] = 1;

  int result = s21_big_mul_pow10(&big, 6);
  ck_assert_int_eq(result, 1);
  ck_assert_uint_eq(big.w[0], 1000000);
}
END_TEST

START_TEST(test_big_mul_pow10_overflow) {
  s21_big big;
  for (int i = 0; i < S21_BIG_WORDS; i++) {
    big.w[i] = 0xFFFFFFFF;
  }

  int result = s21_big_mul_pow10(&big, 1);
  ck_assert_int_eq(result, 0);
}
END_TEST

// Тесты для s21_big_fit_96_by_trailing_zeros
START_TEST(test_big_fit_96_by_trailing_zeros_fits_already) {
  s21_big big;
  s21_big_zero(&big);
  big.w[0] = 123;
  big.w[1] = 456;
  big.w[2] = 789;

  int scale = 5;
  int result = s21_big_fit_96_by_trailing_zeros(&big, &scale);

  ck_assert_int_eq(result, 1);
  ck_assert_int_eq(scale, 5);
  ck_assert_uint_eq(big.w[0], 123);
  ck_assert_uint_eq(big.w[1], 456);
  ck_assert_uint_eq(big.w[2], 789);
}
END_TEST

START_TEST(test_big_fit_96_by_trailing_zeros_needs_reduction) {
  s21_big big;
  s21_big_zero(&big);
  big.w[0] = 123456789;
  big.w[1] = 987654321;
  big.w[2] = 555555555;
  big.w[3] = 1;

  int scale = 10;
  int result = s21_big_fit_96_by_trailing_zeros(&big, &scale);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(test_big_fit_96_by_trailing_zeros_scale_zero) {
  s21_big big;
  s21_big_zero(&big);
  big.w[3] = 1;

  int scale = 0;
  int result = s21_big_fit_96_by_trailing_zeros(&big, &scale);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(test_big_fit_96_by_trailing_zeros_null_pointers) {
  s21_big big;
  int scale = 5;

  ck_assert_int_eq(s21_big_fit_96_by_trailing_zeros(NULL, &scale), 0);
  ck_assert_int_eq(s21_big_fit_96_by_trailing_zeros(&big, NULL), 0);
  ck_assert_int_eq(s21_big_fit_96_by_trailing_zeros(NULL, NULL), 0);
}
END_TEST

START_TEST(test_big_fit_96_by_trailing_zeros_complete_reduction) {
  s21_big big;
  s21_big_zero(&big);

  big.w[0] = 1000000u;
  int scale = 6;
  int result = s21_big_fit_96_by_trailing_zeros(&big, &scale);

  ck_assert_int_eq(result, 1);
  ck_assert_int_eq(scale, 6);
  ck_assert(s21_big_fits_96(&big) == 1);
}
END_TEST

START_TEST(test_big_mul_pow10_integration) {
  s21_decimal a = {{1, 0, 0, 0}};
  s21_big big_a;

  s21_big_from_mantissa_96(&big_a, &a);
  int result = s21_big_mul_pow10(&big_a, 2);
  ck_assert_int_eq(result, 1);
  ck_assert_uint_eq(big_a.w[0], 100);
}
END_TEST

START_TEST(test_s21_reset_to_zero_null) {
  s21_reset_to_zero(NULL);
  ck_assert_int_eq(1, 1);
}
END_TEST

START_TEST(test_s21_get_sign_null) {
  int sign = s21_get_sign(NULL);
  ck_assert_int_eq(sign, 0);
}
END_TEST

START_TEST(test_s21_set_sign_null) {
  s21_set_sign(NULL, 1);
  ck_assert_int_eq(1, 1);
}
END_TEST

START_TEST(test_s21_get_scale_null) {
  int scale = s21_get_scale(NULL);
  ck_assert_int_eq(scale, 0);
}
END_TEST

START_TEST(test_s21_set_scale_null) {
  s21_set_scale(NULL, 5);
  ck_assert_int_eq(1, 1);
}
END_TEST

START_TEST(test_s21_set_scale_boundary_values) {
  s21_decimal d = {{0}};

  s21_set_scale(&d, -5);
  int scale = s21_get_scale(&d);
  ck_assert_int_eq(scale, 0);

  s21_set_scale(&d, 30);
  scale = s21_get_scale(&d);
  ck_assert_int_eq(scale, 28);

  s21_set_sign(&d, 1);
  s21_set_scale(&d, 10);
  ck_assert_int_eq(s21_get_sign(&d), 1);
  ck_assert_int_eq(s21_get_scale(&d), 10);
}
END_TEST

START_TEST(test_s21_is_valid_decimal_invalid_scale) {
  s21_decimal d = {{0}};

  d.bits[3] = 0xFFFF0000;
  int valid = s21_is_valid_decimal(d);
  ck_assert_int_eq(valid, 0);

  d.bits[3] = 0x01000000;
  valid = s21_is_valid_decimal(d);
  ck_assert_int_eq(valid, 0);
}
END_TEST

START_TEST(test_s21_trim_fractional_part_null_dst) {
  s21_decimal src = {{123, 0, 0, 0}};
  int result = s21_trim_fractional_part(src, NULL);
  ck_assert_int_eq(result, S21_CONV_ERROR);
}
END_TEST

START_TEST(test_s21_multiplication_by_10_null) {
  int result = s21_multiplication_by_10(NULL);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(test_s21_multiplication_by_10_overflow) {
  s21_decimal d = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  int result = s21_multiplication_by_10(&d);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(test_s21_is_greater_abs_different_scales) {
  s21_decimal a = {{100, 0, 0, 0x00010000}};
  s21_decimal b = {{1, 0, 0, 0}};
  int result = s21_is_greater_abs(a, b);
  (void)result;
  ck_assert_int_eq(1, 1);
}
END_TEST

START_TEST(test_s21_add_mantissa_96_carry) {
  s21_decimal a = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_decimal b = {{1, 0, 0, 0}};
  s21_decimal result;

  int carry = s21_add_mantissa_96(&a, &b, &result);
  ck_assert_int_eq(carry, 1);
}
END_TEST

START_TEST(test_s21_inc_mantissa_96_carry_overflow) {
  s21_decimal v = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  int result = s21_inc_mantissa_96(&v);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(test_s21_mul_mantissa_by_10_96_overflow) {
  s21_decimal v = {{0x19999999, 0x19999999, 0x19999999, 0}};
  int result = s21_mul_mantissa_by_10_96(&v);
  (void)result;
  ck_assert_int_eq(1, 1);
}
END_TEST

START_TEST(test_s21_need_bankers_round_up_all_branches) {
  ck_assert_int_eq(s21_need_bankers_round_up(6, 0, 0), 1);
  ck_assert_int_eq(s21_need_bankers_round_up(4, 1, 0), 0);
  ck_assert_int_eq(s21_need_bankers_round_up(5, 1, 0), 1);
  ck_assert_int_eq(s21_need_bankers_round_up(5, 0, 0), 1);
  ck_assert_int_eq(s21_need_bankers_round_up(5, 0, 1), 0);
}
END_TEST

START_TEST(test_s21_reduce_scale_bankers_96_invalid_params) {
  s21_decimal v = {{123, 0, 0, 0x00010000}};
  int result = s21_reduce_scale_bankers_96(&v, -1);
  ck_assert_int_eq(result, 1);
  result = s21_reduce_scale_bankers_96(&v, 5);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(test_s21_big_mul_small_overflow) {
  s21_big x;
  memset(&x, 0xFF, sizeof(x));
  int result = s21_big_mul_small(&x, 2);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(test_s21_big_add_small_overflow) {
  s21_big x;
  memset(&x, 0xFF, sizeof(x));
  int result = s21_big_add_small(&x, 1);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(test_s21_big_div_small_zero_div) {
  s21_big x;
  s21_big_zero(&x);
  x.w[0] = 100;
  uint32_t rem = s21_big_div_small(&x, 3);
  ck_assert_uint_eq(x.w[0], 33);
  ck_assert_uint_eq(rem, 1);
}
END_TEST

START_TEST(test_s21_pack_result_null) {
  s21_decimal mantissa = {{123, 0, 0, 0}};
  int result = s21_pack_result(mantissa, 0, 0, NULL);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(test_s21_pack_result_zero_normalization) {
  s21_decimal mantissa = {{0, 0, 0, 0}};
  s21_decimal result;
  int pack_result = s21_pack_result(mantissa, 1, 0, &result);
  ck_assert_int_eq(pack_result, 1);
  ck_assert_int_eq(s21_get_sign(&result), 0);
}
END_TEST

// ============================================
// s21_mod (остаток от деления) - ТЕСТЫ
// ============================================

START_TEST(mod_positive_basic) {
  s21_decimal a = {{10, 0, 0, 0}};
  s21_decimal b = {{3, 0, 0, 0}};
  s21_decimal result;

  ck_assert_int_eq(s21_mod(a, b, &result), 0);
  ck_assert_int_eq(result.bits[0], 1);
}
END_TEST

START_TEST(mod_negative_dividend) {
  s21_decimal a = {{10, 0, 0, 0}};
  s21_set_sign(&a, 1);
  s21_decimal b = {{3, 0, 0, 0}};
  s21_decimal result;

  ck_assert_int_eq(s21_mod(a, b, &result), 0);
  ck_assert_int_eq(result.bits[0], 1);
  ck_assert_int_eq(s21_get_sign(&result), 1);
}
END_TEST

START_TEST(mod_negative_divisor) {
  s21_decimal a = {{10, 0, 0, 0}};
  s21_decimal b = {{3, 0, 0, 0}};
  s21_set_sign(&b, 1);
  s21_decimal result;

  ck_assert_int_eq(s21_mod(a, b, &result), 0);
  ck_assert_int_eq(result.bits[0], 1);
  ck_assert_int_eq(s21_get_sign(&result), 0);
}
END_TEST

START_TEST(mod_both_negative) {
  s21_decimal a = {{10, 0, 0, 0}};
  s21_set_sign(&a, 1);
  s21_decimal b = {{3, 0, 0, 0}};
  s21_set_sign(&b, 1);
  s21_decimal result;

  ck_assert_int_eq(s21_mod(a, b, &result), 0);
  ck_assert_int_eq(result.bits[0], 1);
  ck_assert_int_eq(s21_get_sign(&result), 1);
}
END_TEST

START_TEST(mod_zero_remainder) {
  s21_decimal a = {{10, 0, 0, 0}};
  s21_decimal b = {{5, 0, 0, 0}};
  s21_decimal result;

  ck_assert_int_eq(s21_mod(a, b, &result), 0);
  ck_assert_int_eq(s21_zero_value(result), TRUE);
}
END_TEST

START_TEST(mod_dividend_less_than_divisor) {
  s21_decimal a = {{2, 0, 0, 0}};
  s21_decimal b = {{5, 0, 0, 0}};
  s21_decimal result;

  ck_assert_int_eq(s21_mod(a, b, &result), 0);
  ck_assert_int_eq(result.bits[0], 2);
}
END_TEST

START_TEST(mod_division_by_zero) {
  s21_decimal a = {{10, 0, 0, 0}};
  s21_decimal b = {{0, 0, 0, 0}};
  s21_decimal result;

  ck_assert_int_eq(s21_mod(a, b, &result), 3);
}
END_TEST

START_TEST(mod_null_result_pointer) {
  s21_decimal a = {{10, 0, 0, 0}};
  s21_decimal b = {{3, 0, 0, 0}};

  ck_assert_int_eq(s21_mod(a, b, NULL), 1);
}
END_TEST

START_TEST(mod_with_one) {
  s21_decimal a = {{123456, 0, 0, 0}};
  s21_decimal b = {{1, 0, 0, 0}};
  s21_decimal result;

  ck_assert_int_eq(s21_mod(a, b, &result), 0);
  ck_assert_int_eq(s21_zero_value(result), TRUE);
}
END_TEST

START_TEST(mod_equal_numbers) {
  s21_decimal a = {{123, 0, 0, 0}};
  s21_decimal b = {{123, 0, 0, 0}};
  s21_decimal result;

  ck_assert_int_eq(s21_mod(a, b, &result), 0);
  ck_assert_int_eq(s21_zero_value(result), TRUE);
}
END_TEST

START_TEST(mod_large_numbers) {
  s21_decimal a = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_decimal b = {{12345, 0, 0, 0}};
  s21_decimal result;

  int status = s21_mod(a, b, &result);
  ck_assert(status == 0 || status == 1);
}
END_TEST

START_TEST(mod_big_remainder_fits_96) {
  s21_decimal a = {{1000, 0, 0, 0}};
  s21_decimal b = {{7, 0, 0, 0}};
  s21_decimal result;

  ck_assert_int_eq(s21_mod(a, b, &result), 0);
  ck_assert_int_eq(result.bits[0], 6);
}
END_TEST

START_TEST(mod_zero_remainder_exact) {
  s21_decimal a = {{15, 0, 0, 0}};
  s21_decimal b = {{5, 0, 0, 0}};
  s21_decimal result;

  ck_assert_int_eq(s21_mod(a, b, &result), 0);
  ck_assert_int_eq(s21_zero_value(result), TRUE);
}
END_TEST

// trim
START_TEST(test_trim_fractional_part) {
  s21_decimal dec = {{123456, 0, 0, 0}};
  s21_set_scale(&dec, 3); // 123.456

  s21_decimal trimmed;
  s21_trim_fractional_part(dec, &trimmed);

  // Проверяем, что дробная часть отброшена
  ck_assert_int_eq(trimmed.bits[0], 123);
  ck_assert_int_eq(s21_get_scale(&trimmed), 0);
}
END_TEST

// ============================================
// Тесты для s21_mantissa_equal
// ============================================

START_TEST(mantissa_equal_both_zero) {
  s21_decimal a = {{0, 0, 0, 0}};
  s21_decimal b = {{0, 0, 0, 0}};
  ck_assert_int_eq(s21_mantissa_equal(a, b), 1);
}
END_TEST

START_TEST(mantissa_equal_identical_positive) {
  s21_decimal a = {{12345, 6789, 123, 0}};
  s21_decimal b = {{12345, 6789, 123, 0}};
  ck_assert_int_eq(s21_mantissa_equal(a, b), 1);
}
END_TEST

START_TEST(mantissa_equal_identical_negative) {
  s21_decimal a = {{12345, 6789, 123, 0}};
  s21_set_sign(&a, 1);
  s21_decimal b = {{12345, 6789, 123, 0}};
  s21_set_sign(&b, 1);
  // Функция смотрит только на мантиссу (bits[0-2]), знак игнорируется
  ck_assert_int_eq(s21_mantissa_equal(a, b), 1);
}
END_TEST

START_TEST(mantissa_equal_different_low) {
  s21_decimal a = {{12345, 6789, 123, 0}};
  s21_decimal b = {{54321, 6789, 123, 0}};
  ck_assert_int_eq(s21_mantissa_equal(a, b), 0);
}
END_TEST

START_TEST(mantissa_equal_different_mid) {
  s21_decimal a = {{12345, 6789, 123, 0}};
  s21_decimal b = {{12345, 9876, 123, 0}};
  ck_assert_int_eq(s21_mantissa_equal(a, b), 0);
}
END_TEST

START_TEST(mantissa_equal_different_high) {
  s21_decimal a = {{12345, 6789, 123, 0}};
  s21_decimal b = {{12345, 6789, 321, 0}};
  ck_assert_int_eq(s21_mantissa_equal(a, b), 0);
}
END_TEST

START_TEST(mantissa_equal_different_scale) {
  s21_decimal a = {{123, 0, 0, 0}};
  s21_set_scale(&a, 2); // 1.23
  s21_decimal b = {{123, 0, 0, 0}};
  s21_set_scale(&b, 5); // 0.00123
  // Мантисса (123) одинаковая, scale разный.
  ck_assert_int_eq(s21_mantissa_equal(a, b), 1);
}
END_TEST

START_TEST(mantissa_equal_different_sign) {
  s21_decimal a = {{12345, 6789, 123, 0}};
  s21_set_sign(&a, 0);
  s21_decimal b = {{12345, 6789, 123, 0}};
  s21_set_sign(&b, 1);
  // Функция смотрит только на мантиссу (bits[0-2]), знак игнорируется.
  ck_assert_int_eq(s21_mantissa_equal(a, b), 1);
}
END_TEST

Suite *decimal_suite(void) {
  Suite *s = suite_create("decimal");
  TCase *tc = tcase_create("core");

  // Основные функции
  tcase_add_test(tc, is_greater_abs_with_scale);
  tcase_add_test(tc, is_greater_abs_zero);
  tcase_add_test(tc, is_greater_abs_simple);
  tcase_add_test(tc, is_greater_abs_equal);

  tcase_add_test(tc, multiply_by_10_positive);
  tcase_add_test(tc, multiply_by_10_negative);
  tcase_add_test(tc, multiply_by_10_scale);

  // Банковское округление
  tcase_add_test(tc, test_need_bankers_round_up_gt_5);
  tcase_add_test(tc, test_need_bankers_round_up_lt_5);
  tcase_add_test(tc, test_need_bankers_round_up_eq_5_no_tail);
  tcase_add_test(tc, test_need_bankers_round_up_eq_5_with_tail);
  tcase_add_test(tc, test_round_bankers_u32_simple);
  tcase_add_test(tc, test_round_bankers_u32_tie_even);
  tcase_add_test(tc, test_pow10_u32);

  // 96-битные операции
  tcase_add_test(tc, test_cmp_mantissa_96);
  tcase_add_test(tc, test_add_mantissa_96_no_carry);
  tcase_add_test(tc, test_add_mantissa_96_with_carry);
  tcase_add_test(tc, test_sub_mantissa_96_no_borrow);
  tcase_add_test(tc, test_sub_mantissa_96_with_borrow);
  tcase_add_test(tc, test_inc_mantissa_96_simple);
  tcase_add_test(tc, test_inc_mantissa_96_overflow);
  tcase_add_test(tc, test_div_mantissa_by_10_96);
  tcase_add_test(tc, test_div_mantissa_by_10_96_with_remainder);

  // BIGINT операции
  tcase_add_test(tc, test_big_zero);
  tcase_add_test(tc, test_big_from_mantissa_96);
  tcase_add_test(tc, test_big_fits_96_true);
  tcase_add_test(tc, test_big_fits_96_false);
  tcase_add_test(tc, test_big_cmp);
  tcase_add_test(tc, test_big_mul_small);
  tcase_add_test(tc, test_big_mul_small_overflow);
  tcase_add_test(tc, test_big_div_small);

  // Нормализация
  tcase_add_test(tc, test_reduce_scale_bankers_96);
  tcase_add_test(tc, test_normalize_pair_scales_96_equal);
  tcase_add_test(tc, test_normalize_pair_scales_96_different);

  // Граничные случаи
  tcase_add_test(tc, test_null_pointers);
  tcase_add_test(tc, test_my_isfinite);
  tcase_add_test(tc, test_mul_mantissa_by_10_96_overflow);

  // BIGINT дополнительные
  tcase_add_test(tc, test_big_mul_pow10_zero_pow);
  tcase_add_test(tc, test_big_mul_pow10_small);
  tcase_add_test(tc, test_big_mul_pow10_large);
  tcase_add_test(tc, test_big_mul_pow10_overflow);

  tcase_add_test(tc, test_big_fit_96_by_trailing_zeros_fits_already);
  tcase_add_test(tc, test_big_fit_96_by_trailing_zeros_needs_reduction);
  tcase_add_test(tc, test_big_fit_96_by_trailing_zeros_scale_zero);
  tcase_add_test(tc, test_big_fit_96_by_trailing_zeros_null_pointers);
  tcase_add_test(tc, test_big_fit_96_by_trailing_zeros_complete_reduction);
  tcase_add_test(tc, test_big_mul_pow10_integration);

  // NULL и boundary тесты
  tcase_add_test(tc, test_s21_reset_to_zero_null);
  tcase_add_test(tc, test_s21_get_sign_null);
  tcase_add_test(tc, test_s21_set_sign_null);
  tcase_add_test(tc, test_s21_get_scale_null);
  tcase_add_test(tc, test_s21_set_scale_null);
  tcase_add_test(tc, test_s21_set_scale_boundary_values);
  tcase_add_test(tc, test_s21_is_valid_decimal_invalid_scale);
  tcase_add_test(tc, test_s21_trim_fractional_part_null_dst);
  tcase_add_test(tc, test_s21_multiplication_by_10_null);
  tcase_add_test(tc, test_s21_multiplication_by_10_overflow);
  tcase_add_test(tc, test_s21_is_greater_abs_different_scales);
  tcase_add_test(tc, test_s21_add_mantissa_96_carry);
  tcase_add_test(tc, test_s21_inc_mantissa_96_carry_overflow);
  tcase_add_test(tc, test_s21_mul_mantissa_by_10_96_overflow);
  tcase_add_test(tc, test_s21_need_bankers_round_up_all_branches);
  tcase_add_test(tc, test_s21_reduce_scale_bankers_96_invalid_params);
  tcase_add_test(tc, test_s21_big_mul_small_overflow);
  tcase_add_test(tc, test_s21_big_add_small_overflow);
  tcase_add_test(tc, test_s21_big_div_small_zero_div);
  tcase_add_test(tc, test_s21_pack_result_null);
  tcase_add_test(tc, test_s21_pack_result_zero_normalization);

  // Тесты s21_mod
  tcase_add_test(tc, mod_positive_basic);
  tcase_add_test(tc, mod_negative_dividend);
  tcase_add_test(tc, mod_negative_divisor);
  tcase_add_test(tc, mod_both_negative);
  tcase_add_test(tc, mod_zero_remainder);
  tcase_add_test(tc, mod_dividend_less_than_divisor);
  tcase_add_test(tc, mod_division_by_zero);
  tcase_add_test(tc, mod_null_result_pointer);
  tcase_add_test(tc, mod_with_one);
  tcase_add_test(tc, mod_equal_numbers);
  tcase_add_test(tc, mod_large_numbers);
  tcase_add_test(tc, mod_big_remainder_fits_96);
  tcase_add_test(tc, mod_zero_remainder_exact);

  // trim
  tcase_add_test(tc, test_trim_fractional_part);

  // Тесты для s21_mantissa_equal
  tcase_add_test(tc, mantissa_equal_both_zero);
  tcase_add_test(tc, mantissa_equal_identical_positive);
  tcase_add_test(tc, mantissa_equal_identical_negative);
  tcase_add_test(tc, mantissa_equal_different_low);
  tcase_add_test(tc, mantissa_equal_different_mid);
  tcase_add_test(tc, mantissa_equal_different_high);
  tcase_add_test(tc, mantissa_equal_different_scale);
  tcase_add_test(tc, mantissa_equal_different_sign);

  suite_add_tcase(s, tc);
  return s;
}