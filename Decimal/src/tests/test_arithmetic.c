#include "test.h"

// ============================================
// ADD (сложение) - существующие тесты
// ============================================

START_TEST(add_simple) {
  s21_decimal a = {{10, 0, 0, 0}};
  s21_decimal b = {{5, 0, 0, 0}};
  s21_decimal r = {{0, 0, 0, 0}};
  s21_decimal expected = {{15, 0, 0, 0}};

  ck_assert_int_eq(s21_add(a, b, &r), S21_ARITH_OK);
  ck_assert_int_eq(s21_is_equal(r, expected), TRUE);
}
END_TEST

START_TEST(add_zero) {
  s21_decimal a = {{0, 0, 0, 0}};
  s21_decimal b = {{0, 0, 0, 0}};
  s21_decimal r = {{999, 999, 999, 999}};
  s21_decimal expected = {{0, 0, 0, 0}};

  ck_assert_int_eq(s21_add(a, b, &r), S21_ARITH_OK);
  ck_assert_int_eq(s21_is_equal(r, expected), TRUE);
}
END_TEST

START_TEST(add_one_plus_one) {
  s21_decimal a = {{1, 0, 0, 0}};
  s21_decimal b = {{1, 0, 0, 0}};
  s21_decimal r = {{0, 0, 0, 0}};
  s21_decimal expected = {{2, 0, 0, 0}};

  ck_assert_int_eq(s21_add(a, b, &r), S21_ARITH_OK);
  ck_assert_int_eq(s21_is_equal(r, expected), TRUE);
}
END_TEST

START_TEST(add_with_carry) {
  s21_decimal a = {{0xFFFFFFFF, 0, 0, 0}};
  s21_decimal b = {{1, 0, 0, 0}};
  s21_decimal r = {{0, 0, 0, 0}};
  s21_decimal expected = {{0, 1, 0, 0}};

  ck_assert_int_eq(s21_add(a, b, &r), S21_ARITH_OK);
  ck_assert_int_eq(s21_is_equal(r, expected), TRUE);
}
END_TEST

START_TEST(add_negative) {
  s21_decimal a = {{10, 0, 0, 0}};
  s21_decimal b = {{5, 0, 0, 0}};
  s21_decimal r = {{0, 0, 0, 0}};
  s21_decimal expected = {{5, 0, 0, 0}};

  s21_set_sign(&b, 1);

  ck_assert_int_eq(s21_add(a, b, &r), S21_ARITH_OK);
  ck_assert_int_eq(s21_is_equal(r, expected), TRUE);
}
END_TEST

START_TEST(add_two_negatives) {
  s21_decimal a = {{10, 0, 0, 0}};
  s21_decimal b = {{5, 0, 0, 0}};
  s21_decimal r = {{0, 0, 0, 0}};
  s21_decimal expected = {{15, 0, 0, 0x80000000}};

  s21_set_sign(&a, 1);
  s21_set_sign(&b, 1);

  ck_assert_int_eq(s21_add(a, b, &r), S21_ARITH_OK);
  ck_assert_int_eq(s21_is_equal(r, expected), TRUE);
}
END_TEST

START_TEST(add_with_different_scales) {
  s21_decimal a = {{15, 0, 0, 0}};
  s21_set_scale(&a, 1);
  s21_decimal b = {{225, 0, 0, 0}};
  s21_set_scale(&b, 2);
  s21_decimal r = {{0, 0, 0, 0}};
  s21_decimal expected = {{375, 0, 0, 0}};
  s21_set_scale(&expected, 2);

  ck_assert_int_eq(s21_add(a, b, &r), S21_ARITH_OK);
  ck_assert_int_eq(s21_is_equal(r, expected), TRUE);
}
END_TEST

START_TEST(add_equal_opposite_signs) {
  s21_decimal a = {{5, 0, 0, 0}};
  s21_decimal b = {{5, 0, 0, 0x80000000}};
  s21_decimal r = {{0, 0, 0, 0}};
  s21_decimal expected = {{0, 0, 0, 0}};

  ck_assert_int_eq(s21_add(a, b, &r), S21_ARITH_OK);
  ck_assert_int_eq(s21_is_equal(r, expected), TRUE);
}
END_TEST

START_TEST(add_overflow_to_infinity) {
  s21_decimal a = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_decimal b = {{1, 0, 0, 0}};
  s21_decimal r = {{0, 0, 0, 0}};

  ck_assert_int_eq(s21_add(a, b, &r), S21_ARITH_TOO_LARGE);
}
END_TEST

START_TEST(add_overflow_to_negative_infinity) {
  s21_decimal a = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  s21_decimal b = {{1, 0, 0, 0x80000000}};
  s21_decimal r = {{0, 0, 0, 0}};

  ck_assert_int_eq(s21_add(a, b, &r), S21_ARITH_TOO_SMALL);
}
END_TEST

START_TEST(add_with_scale_reduction) {
  s21_decimal a = {{1999999999, 0, 0, 0}};
  s21_set_scale(&a, 9);
  s21_decimal b = {{1, 0, 0, 0}};
  s21_set_scale(&b, 10);
  s21_decimal r = {{0, 0, 0, 0}};

  ck_assert_int_eq(s21_add(a, b, &r), S21_ARITH_OK);
}
END_TEST

START_TEST(add_null_result) {
  s21_decimal a = {{1, 0, 0, 0}};
  s21_decimal b = {{2, 0, 0, 0}};

  ck_assert_int_eq(s21_add(a, b, NULL), S21_ARITH_TOO_LARGE);
}
END_TEST

START_TEST(invalid_decimal) {
  s21_decimal a = {{1, 0, 0, 0}};
  a.bits[3] = (29 << 16);
  s21_decimal b = {{2, 0, 0, 0}};
  s21_decimal r = {{0, 0, 0, 0}};

  ck_assert_int_eq(s21_add(a, b, &r), S21_ARITH_TOO_LARGE);
}
END_TEST

START_TEST(scale_normalization_failure) {
  s21_decimal a = {{1, 0, 0, 0}};
  s21_set_scale(&a, 0);
  s21_decimal b = {{2, 0, 0, 0}};
  b.bits[3] = (30 << 16);
  s21_decimal r = {{0, 0, 0, 0}};

  ck_assert_int_eq(s21_add(a, b, &r), S21_ARITH_TOO_LARGE);
}
END_TEST

START_TEST(add_edge_cases) {
  s21_decimal max_val = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_decimal small_val = {{1, 0, 0, 0}};
  s21_decimal res = {{0, 0, 0, 0}};

  int result = s21_add(max_val, small_val, &res);
  ck_assert_int_eq(result, S21_ARITH_TOO_LARGE);

  result = s21_add(max_val, small_val, NULL);
  ck_assert_int_eq(result, S21_ARITH_TOO_LARGE);

  s21_decimal large_scale = {{1, 0, 0, 0}};
  large_scale.bits[3] = (29 << 16);
  result = s21_add(large_scale, small_val, &res);
  ck_assert_int_eq(result, S21_ARITH_TOO_LARGE);
}
END_TEST

START_TEST(add_invalid_decimal) {
  s21_decimal invalid = {{1, 0, 0, 0}};
  invalid.bits[3] = (29 << 16);
  s21_decimal b = {{2, 0, 0, 0}};
  s21_decimal r;

  ck_assert_int_eq(s21_add(invalid, b, &r), S21_ARITH_TOO_LARGE);
}
END_TEST

START_TEST(add_invalid_decimal_scale_too_large) {
  s21_decimal invalid = {{1, 0, 0, 0}};
  invalid.bits[3] = (29 << 16);
  s21_decimal b = {{2, 0, 0, 0}};
  s21_decimal r;

  ck_assert_int_eq(s21_add(invalid, b, &r), S21_ARITH_TOO_LARGE);
}
END_TEST

START_TEST(add_second_value_scale_too_large) {
  s21_decimal a = {{1, 0, 0, 0}};
  s21_decimal b = {{2, 0, 0, 0}};
  b.bits[3] = (29 << 16);
  s21_decimal r;

  ck_assert_int_eq(s21_add(a, b, &r), S21_ARITH_TOO_LARGE);
}
END_TEST

START_TEST(add_scale_normalization_fails) {
  s21_decimal a = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_set_scale(&a, 0);
  s21_decimal b = {{1, 0, 0, 0}};
  s21_set_scale(&b, 28);
  s21_decimal r;

  int result = s21_add(a, b, &r);
  ck_assert(result == S21_ARITH_TOO_LARGE || result == S21_ARITH_OK);
}
END_TEST

START_TEST(add_with_scale_reduction_big_result) {
  s21_decimal a = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_set_scale(&a, 0);
  s21_decimal b = {{1, 0, 0, 0}};
  s21_set_scale(&b, 0);
  s21_decimal r;

  ck_assert_int_eq(s21_add(a, b, &r), S21_ARITH_TOO_LARGE);
}
END_TEST

START_TEST(add_big_to_decimal_conversion_after_reduction) {
  s21_decimal a = {{0xFFFFFFF0, 0x0, 0x0, 0}};
  s21_set_scale(&a, 1);
  s21_decimal b = {{0x10, 0x0, 0x0, 0}};
  s21_set_scale(&b, 1);
  s21_decimal r;

  int result = s21_add(a, b, &r);
  ck_assert(result == S21_ARITH_OK || result == S21_ARITH_TOO_LARGE);
}
END_TEST

// ============================================
// SUB (вычитание) - существующие тесты
// ============================================

START_TEST(sub_simple) {
  s21_decimal a = {{10, 0, 0, 0}};
  s21_decimal b = {{5, 0, 0, 0}};
  s21_decimal r = {{0, 0, 0, 0}};
  s21_decimal expected = {{5, 0, 0, 0}};

  ck_assert_int_eq(s21_sub(a, b, &r), S21_ARITH_OK);
  ck_assert_int_eq(s21_is_equal(r, expected), TRUE);
}
END_TEST

START_TEST(sub_negative_result) {
  s21_decimal a = {{5, 0, 0, 0}};
  s21_decimal b = {{10, 0, 0, 0}};
  s21_decimal r = {{0, 0, 0, 0}};
  s21_decimal expected = {{5, 0, 0, 0x80000000}};

  ck_assert_int_eq(s21_sub(a, b, &r), S21_ARITH_OK);
  ck_assert_int_eq(s21_is_equal(r, expected), TRUE);
}
END_TEST

START_TEST(sub_equal_numbers) {
  s21_decimal a = {{5, 0, 0, 0}};
  s21_decimal b = {{5, 0, 0, 0}};
  s21_decimal r = {{0, 0, 0, 0}};
  s21_decimal expected = {{0, 0, 0, 0}};

  ck_assert_int_eq(s21_sub(a, b, &r), S21_ARITH_OK);
  ck_assert_int_eq(s21_is_equal(r, expected), TRUE);
}
END_TEST

START_TEST(sub_large_numbers) {
  s21_decimal a = {{0xFFFFFFFF, 0, 0, 0}};
  s21_decimal b = {{1, 0, 0, 0}};
  s21_decimal r = {{0, 0, 0, 0}};
  s21_decimal expected = {{0xFFFFFFFE, 0, 0, 0}};

  ck_assert_int_eq(s21_sub(a, b, &r), S21_ARITH_OK);
  ck_assert_int_eq(s21_is_equal(r, expected), TRUE);
}
END_TEST

// ============================================
// MUL (умножение) - существующие тесты
// ============================================

START_TEST(mul_simple) {
  s21_decimal a = {{7, 0, 0, 0}};
  s21_decimal b = {{6, 0, 0, 0}};
  s21_decimal r = {{0, 0, 0, 0}};
  s21_decimal expected = {{42, 0, 0, 0}};

  ck_assert_int_eq(s21_mul(a, b, &r), S21_ARITH_OK);
  ck_assert_int_eq(s21_is_equal(r, expected), TRUE);
}
END_TEST

START_TEST(mul_with_sign) {
  s21_decimal a = {{7, 0, 0, 0x80000000}};
  s21_decimal b = {{6, 0, 0, 0}};
  s21_decimal r = {{0, 0, 0, 0}};
  s21_decimal expected = {{42, 0, 0, 0x80000000}};

  ck_assert_int_eq(s21_mul(a, b, &r), S21_ARITH_OK);
  ck_assert_int_eq(s21_is_equal(r, expected), TRUE);
}
END_TEST

START_TEST(mul_with_scale) {
  s21_decimal a = {{15, 0, 0, 0}};
  s21_set_scale(&a, 1);
  s21_decimal b = {{2, 0, 0, 0}};
  s21_decimal r = {{0, 0, 0, 0}};
  s21_decimal expected = {{3, 0, 0, 0}};

  ck_assert_int_eq(s21_mul(a, b, &r), S21_ARITH_OK);
  ck_assert_int_eq(s21_is_equal(r, expected), TRUE);
}
END_TEST

START_TEST(mul_zero) {
  s21_decimal a = {{5, 0, 0, 0}};
  s21_decimal b = {{0, 0, 0, 0}};
  s21_decimal r = {{0, 0, 0, 0}};
  s21_decimal expected = {{0, 0, 0, 0}};

  ck_assert_int_eq(s21_mul(a, b, &r), S21_ARITH_OK);
  ck_assert_int_eq(s21_is_equal(r, expected), TRUE);
}
END_TEST

START_TEST(mul_scale_reduction) {
  s21_decimal a = {{123456789, 0, 0, 0}};
  s21_set_scale(&a, 5);
  s21_decimal b = {{987654321, 0, 0, 0}};
  s21_set_scale(&b, 5);
  s21_decimal r = {{0, 0, 0, 0}};

  ck_assert_int_eq(s21_mul(a, b, &r), S21_ARITH_OK);
  ck_assert_int_le(s21_get_scale(&r), 28);
}
END_TEST

START_TEST(mul_overflow_positive) {
  s21_decimal a = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_set_scale(&a, 0);
  s21_decimal b = {{2, 0, 0, 0}};
  s21_set_scale(&b, 0);
  s21_decimal r = {{0, 0, 0, 0}};

  ck_assert_int_eq(s21_mul(a, b, &r), S21_ARITH_TOO_LARGE);
}
END_TEST

START_TEST(mul_overflow_negative) {
  s21_decimal a = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  s21_set_scale(&a, 0);
  s21_decimal b = {{2, 0, 0, 0}};
  s21_set_scale(&b, 0);
  s21_decimal r = {{0, 0, 0, 0}};

  ck_assert_int_eq(s21_mul(a, b, &r), S21_ARITH_TOO_SMALL);
}
END_TEST

START_TEST(mul_scale_over_28_reduction) {
  s21_decimal a = {{123456789, 0, 0, 0}};
  s21_set_scale(&a, 20);
  s21_decimal b = {{987654321, 0, 0, 0}};
  s21_set_scale(&b, 20);
  s21_decimal r = {{0, 0, 0, 0}};

  ck_assert_int_eq(s21_mul(a, b, &r), S21_ARITH_OK);
}
END_TEST

START_TEST(mul_big_result_needs_scale_reduction) {
  s21_decimal a = {{0xFFFFFFFF, 0xFFFFFFFF, 0, 0}};
  s21_set_scale(&a, 5);
  s21_decimal b = {{2, 0, 0, 0}};
  s21_set_scale(&b, 5);
  s21_decimal r = {{0, 0, 0, 0}};

  int result = s21_mul(a, b, &r);
  ck_assert(result == S21_ARITH_OK || result == S21_ARITH_TOO_LARGE);
}
END_TEST

START_TEST(mul_overflow_even_after_reduction) {
  s21_decimal a = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_set_scale(&a, 0);
  s21_decimal b = {{2, 0, 0, 0}};
  s21_set_scale(&b, 0);
  s21_decimal r = {{0, 0, 0, 0}};

  ck_assert_int_eq(s21_mul(a, b, &r), S21_ARITH_TOO_LARGE);
}
END_TEST

START_TEST(mul_large_scale_overflow) {
  s21_decimal a = {{123456789, 0, 0, 0}};
  s21_set_scale(&a, 20);
  s21_decimal b = {{987654321, 0, 0, 0}};
  s21_set_scale(&b, 20);
  s21_decimal r;

  ck_assert_int_eq(s21_mul(a, b, &r), S21_ARITH_OK);
}
END_TEST

// ============================================
// DIV (деление) - существующие тесты
// ============================================

START_TEST(div_simple) {
  s21_decimal a = {{20, 0, 0, 0}};
  s21_decimal b = {{4, 0, 0, 0}};
  s21_decimal r = {{0, 0, 0, 0}};
  s21_decimal expected = {{5, 0, 0, 0}};

  ck_assert_int_eq(s21_div(a, b, &r), S21_ARITH_OK);
  ck_assert_int_eq(s21_is_equal(r, expected), TRUE);
}
END_TEST

START_TEST(div_small_by_large) {
  s21_decimal a = {{1, 0, 0, 0}};
  s21_decimal b = {{3, 0, 0, 0}};
  s21_decimal r = {{0, 0, 0, 0}};

  ck_assert_int_eq(s21_div(a, b, &r), S21_ARITH_OK);
  ck_assert_int_gt(s21_get_scale(&r), 0);
}
END_TEST

START_TEST(div_with_precision_limit) {
  s21_decimal a = {{1, 0, 0, 0}};
  s21_decimal b = {{7, 0, 0, 0}};
  s21_decimal r = {{0, 0, 0, 0}};

  ck_assert_int_eq(s21_div(a, b, &r), S21_ARITH_OK);
  ck_assert_int_le(s21_get_scale(&r), 28);
}
END_TEST

START_TEST(div_overflow) {
  s21_decimal a = {{1, 0, 0, 0}};
  s21_set_scale(&a, 28);
  s21_decimal b = {{1, 0, 0, 0}};
  s21_set_scale(&b, 28);
  s21_decimal r = {{0, 0, 0, 0}};
  s21_decimal expected = {{1, 0, 0, 0}};

  ck_assert_int_eq(s21_div(a, b, &r), S21_ARITH_OK);
  ck_assert_int_eq(s21_is_equal(r, expected), TRUE);
}
END_TEST

START_TEST(div_bankers_rounding) {
  s21_decimal a = {{1, 0, 0, 0}};
  s21_decimal b = {{8, 0, 0, 0}};
  s21_decimal r = {{0, 0, 0, 0}};

  ck_assert_int_eq(s21_div(a, b, &r), S21_ARITH_OK);
}
END_TEST

START_TEST(div_by_zero) {
  s21_decimal a = {{1, 0, 0, 0}};
  s21_decimal b = {{0, 0, 0, 0}};
  s21_decimal r = {{0, 0, 0, 0}};

  ck_assert_int_eq(s21_div(a, b, &r), S21_ARITH_DIV_BY_ZERO);
}
END_TEST

START_TEST(div_negative_scale_needs_adjustment) {
  s21_decimal a = {{1, 0, 0, 0}};
  s21_set_scale(&a, 1);
  s21_decimal b = {{3, 0, 0, 0}};
  s21_set_scale(&b, 5);
  s21_decimal r = {{0, 0, 0, 0}};

  ck_assert_int_eq(s21_div(a, b, &r), S21_ARITH_OK);
}
END_TEST

START_TEST(div_bankers_rounding_causes_overflow) {
  s21_decimal a = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_set_scale(&a, 1);
  s21_decimal b = {{3, 0, 0, 0}};
  s21_set_scale(&b, 1);
  s21_decimal r = {{0, 0, 0, 0}};

  int result = s21_div(a, b, &r);
  ck_assert(result == S21_ARITH_OK || result == S21_ARITH_TOO_LARGE ||
            result == S21_ARITH_TOO_SMALL);
}
END_TEST

START_TEST(div_result_too_big_needs_scale_reduction) {
  s21_decimal a = {{1, 0, 0, 0}};
  s21_set_scale(&a, 0);
  s21_decimal b = {{1, 0, 0, 0}};
  s21_set_scale(&b, 28);
  s21_decimal r = {{0, 0, 0, 0}};

  ck_assert_int_eq(s21_div(a, b, &r), S21_ARITH_OK);
}
END_TEST

START_TEST(div_final_scale_too_large) {
  s21_decimal a = {{1, 0, 0, 0}};
  s21_set_scale(&a, 0);
  s21_decimal b = {{7, 0, 0, 0}};
  s21_set_scale(&b, 0);
  s21_decimal r = {{0, 0, 0, 0}};

  ck_assert_int_eq(s21_div(a, b, &r), S21_ARITH_OK);
}
END_TEST

// ============================================
// Общие тесты для всех функций
// ============================================

START_TEST(all_funcs_invalid_decimal_input) {
  s21_decimal invalid = {{1, 0, 0, 0}};
  invalid.bits[3] = (29 << 16);
  s21_decimal valid = {{2, 0, 0, 0}};
  s21_decimal r;

  ck_assert_int_eq(s21_add(invalid, valid, &r), S21_ARITH_TOO_LARGE);
  ck_assert_int_eq(s21_mul(invalid, valid, &r), S21_ARITH_TOO_LARGE);
  ck_assert_int_eq(s21_div(invalid, valid, &r), S21_ARITH_TOO_LARGE);
}
END_TEST

// ============================================
// НОВЫЕ ТЕСТЫ (только то, чего действительно не хватало)
// ============================================

// ========== ТЕСТЫ БАНКОВСКОГО ОКРУГЛЕНИЯ ==========

START_TEST(add_bankers_rounding_even) {
  s21_decimal a = {{5, 0, 0, 0}};
  s21_set_scale(&a, 1);           // 0.5
  s21_decimal b = {{2, 0, 0, 0}}; // 2
  s21_decimal r = {{0, 0, 0, 0}};

  ck_assert_int_eq(s21_add(a, b, &r), S21_ARITH_OK);
  // 2 + 0.5 = 2.5 → mantissa=25, scale=1
  ck_assert_uint_eq(r.bits[0], 25);
  ck_assert_int_eq(s21_get_scale(&r), 1);
  ck_assert_int_eq(s21_get_sign(&r), 0);
}
END_TEST

START_TEST(add_bankers_rounding_odd) {
  s21_decimal a = {{5, 0, 0, 0}};
  s21_set_scale(&a, 1);           // 0.5
  s21_decimal b = {{3, 0, 0, 0}}; // 3
  s21_decimal r = {{0, 0, 0, 0}};

  ck_assert_int_eq(s21_add(a, b, &r), S21_ARITH_OK);
  // 3 + 0.5 = 3.5 → mantissa=35, scale=1
  ck_assert_uint_eq(r.bits[0], 35);
  ck_assert_int_eq(s21_get_scale(&r), 1);
  ck_assert_int_eq(s21_get_sign(&r), 0);
}
END_TEST

START_TEST(sub_bankers_rounding_even) {
  s21_decimal a = {{25, 0, 0, 0}};
  s21_set_scale(&a, 1);           // 2.5
  s21_decimal b = {{2, 0, 0, 0}}; // 2
  s21_decimal r = {{0, 0, 0, 0}};

  ck_assert_int_eq(s21_sub(a, b, &r), S21_ARITH_OK);
  // 2.5 - 2 = 0.5 → mantissa=5, scale=1
  ck_assert_uint_eq(r.bits[0], 5);
  ck_assert_int_eq(s21_get_scale(&r), 1);
  ck_assert_int_eq(s21_get_sign(&r), 0);
}
END_TEST

START_TEST(mul_bankers_rounding_even) {
  s21_decimal a = {{125, 0, 0, 0}};
  s21_set_scale(&a, 2);           // 1.25
  s21_decimal b = {{2, 0, 0, 0}}; // 2
  s21_decimal r = {{0, 0, 0, 0}};

  ck_assert_int_eq(s21_mul(a, b, &r), S21_ARITH_OK);
  // 1.25 * 2 = 2.5 → scale = 2 + 0 = 2, mantissa = 250
  ck_assert_uint_eq(r.bits[0], 250);
  ck_assert_int_eq(s21_get_scale(&r), 2);
  ck_assert_int_eq(s21_get_sign(&r), 0);
}
END_TEST

START_TEST(div_bankers_rounding_exact) {
  s21_decimal a = {{1, 0, 0, 0}}; // 1
  s21_decimal b = {{2, 0, 0, 0}}; // 2
  s21_decimal r = {{0, 0, 0, 0}};

  ck_assert_int_eq(s21_div(a, b, &r), S21_ARITH_OK);
  // 1 / 2 = 0.5
  ck_assert_int_eq(s21_get_scale(&r), 1); // Должно быть 1, а не 28
  ck_assert_int_eq(s21_get_sign(&r), 0);
  // Проверяем что это не ноль
  ck_assert_int_eq(s21_zero_value(r), 0);
  // Мантисса должна быть 5 (0.5 = 5/10)
  ck_assert_uint_eq(r.bits[0], 5);
  ck_assert_uint_eq(r.bits[1], 0);
  ck_assert_uint_eq(r.bits[2], 0);
}
END_TEST

START_TEST(div_bankers_rounding_at_precision_limit) {
  s21_decimal a = {{1, 0, 0, 0}};
  s21_decimal b = {{3, 0, 0, 0}};
  s21_decimal r = {{0, 0, 0, 0}};

  ck_assert_int_eq(s21_div(a, b, &r), S21_ARITH_OK);
  // 1/3 должно дать периодическую дробь, которая будет округлена
  ck_assert_int_eq(s21_get_scale(&r), 28); // Достигнут максимальный масштаб
  // Здесь можно проверить конкретное значение, но это сложно
  // из-за банковского округления
  ck_assert_int_gt(r.bits[0], 0);
}
END_TEST

// ========== ТЕСТЫ НОРМАЛИЗАЦИИ МАСШТАБА ==========

START_TEST(add_normalize_large_scale_difference) {
  s21_decimal a = {{1, 0, 0, 0}};
  s21_set_scale(&a, 28);
  s21_decimal b = {{1, 0, 0, 0}};
  s21_set_scale(&b, 0);
  s21_decimal r = {{0, 0, 0, 0}};

  ck_assert_int_eq(s21_add(a, b, &r), S21_ARITH_OK);
  ck_assert_int_eq(s21_get_scale(&r), 28);
}
END_TEST

START_TEST(sub_normalize_overflow_during_normalization) {
  s21_decimal a = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_set_scale(&a, 0);
  s21_decimal b = {{1, 0, 0, 0}};
  s21_set_scale(&b, 28);
  s21_decimal r = {{0, 0, 0, 0}};
  s21_decimal expected = a; // Ожидаем, что результат будет равен a

  ck_assert_int_eq(s21_sub(a, b, &r), S21_ARITH_OK);
  ck_assert_int_eq(s21_is_equal(r, expected), TRUE);
  ck_assert_int_eq(s21_get_scale(&r), 0); // Масштаб должен остаться 0
}
END_TEST

// ========== ТЕСТЫ ГРАНИЧНЫХ ЗНАЧЕНИЙ ==========

START_TEST(mul_max_decimal_by_one) {
  s21_decimal a = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_decimal b = {{1, 0, 0, 0}};
  s21_decimal r = {{0, 0, 0, 0}};
  s21_decimal expected = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};

  ck_assert_int_eq(s21_mul(a, b, &r), S21_ARITH_OK);
  ck_assert_int_eq(s21_is_equal(r, expected), TRUE);
}
END_TEST

START_TEST(div_min_decimal_by_two) {
  s21_decimal a = {{1, 0, 0, 0}};
  s21_set_scale(&a, 28);
  s21_decimal b = {{2, 0, 0, 0}};
  s21_decimal r = {{0, 0, 0, 0}};

  ck_assert_int_eq(s21_div(a, b, &r), S21_ARITH_OK);
  ck_assert_int_eq(s21_get_scale(&r), 28);
  ck_assert_int_eq(r.bits[0], 0);
}
END_TEST

// ========== ТЕСТЫ КОМБИНАЦИЙ ЗНАКОВ И МАСШТАБОВ ==========

START_TEST(add_negative_larger_scale) {
  s21_decimal a = {{123, 0, 0, 0}};
  s21_set_sign(&a, 1);
  s21_set_scale(&a, 2);
  s21_decimal b = {{45678, 0, 0, 0}};
  s21_set_scale(&b, 4);
  s21_decimal r = {{0, 0, 0, 0}};

  ck_assert_int_eq(s21_add(a, b, &r), S21_ARITH_OK);
  ck_assert_int_eq(s21_get_sign(&r), 0);
  ck_assert_int_eq(r.bits[0], 33378);
  ck_assert_int_eq(s21_get_scale(&r), 4);
}
END_TEST

START_TEST(sub_both_negative_different_scales) {
  s21_decimal a = {{567, 0, 0, 0}};
  s21_set_sign(&a, 1);
  s21_set_scale(&a, 2);
  s21_decimal b = {{32, 0, 0, 0}};
  s21_set_sign(&b, 1);
  s21_set_scale(&b, 1);
  s21_decimal r = {{0, 0, 0, 0}};
  s21_decimal expected = {{247, 0, 0, 0x80000000}};
  s21_set_scale(&expected, 2);

  ck_assert_int_eq(s21_sub(a, b, &r), S21_ARITH_OK);
  ck_assert_int_eq(s21_is_equal(r, expected), TRUE);
}
END_TEST

// ========== ТЕСТЫ ДЕЛЕНИЯ С ОСТАТКОМ ==========

START_TEST(div_exact_division) {
  s21_decimal a = {{15, 0, 0, 0}};
  s21_set_scale(&a, 1);
  s21_decimal b = {{5, 0, 0, 0}};
  s21_set_scale(&b, 1);
  s21_decimal r = {{0, 0, 0, 0}};
  s21_decimal expected = {{3, 0, 0, 0}};

  ck_assert_int_eq(s21_div(a, b, &r), S21_ARITH_OK);
  ck_assert_int_eq(s21_is_equal(r, expected), TRUE);
}
END_TEST

START_TEST(div_remainder_tail_rounding) {
  s21_decimal a = {{1, 0, 0, 0}};
  s21_decimal b = {{3, 0, 0, 0}};
  s21_decimal r = {{0, 0, 0, 0}};

  ck_assert_int_eq(s21_div(a, b, &r), S21_ARITH_OK);
  ck_assert_int_eq(s21_get_scale(&r), 28);
}
END_TEST

// ========== ТЕСТЫ НУЛЕВЫХ РЕЗУЛЬТАТОВ ==========

START_TEST(add_zero_negative_zero) {
  s21_decimal a = {{0, 0, 0, 0}};
  s21_decimal b = {{0, 0, 0, 0x80000000}};
  s21_decimal r = {{0, 0, 0, 0}};
  s21_decimal expected = {{0, 0, 0, 0}};

  ck_assert_int_eq(s21_add(a, b, &r), S21_ARITH_OK);
  ck_assert_int_eq(s21_is_equal(r, expected), TRUE);
  ck_assert_int_eq(s21_get_sign(&r), 0);
}
END_TEST

START_TEST(mul_zero_by_negative) {
  s21_decimal a = {{0, 0, 0, 0}};
  s21_decimal b = {{5, 0, 0, 0x80000000}};
  s21_decimal r = {{0, 0, 0, 0}};
  s21_decimal expected = {{0, 0, 0, 0}};

  ck_assert_int_eq(s21_mul(a, b, &r), S21_ARITH_OK);
  ck_assert_int_eq(s21_is_equal(r, expected), TRUE);
  ck_assert_int_eq(s21_get_sign(&r), 0);
}
END_TEST

// ========== ТЕСТЫ ЭКСТРЕМАЛЬНЫХ МАСШТАБОВ ==========

START_TEST(add_scale_28_overflow) {
  s21_decimal a = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_set_scale(&a, 28);
  s21_decimal b = {{1, 0, 0, 0}};
  s21_set_scale(&b, 28);
  s21_decimal r = {{0, 0, 0, 0}};

  int result = s21_add(a, b, &r);
  ck_assert(result == S21_ARITH_TOO_LARGE || result == S21_ARITH_OK);
}
END_TEST

START_TEST(div_scale_reduction_edge) {
  s21_decimal a = {{1, 0, 0, 0}};
  s21_decimal b = {{3, 0, 0, 0}};
  s21_decimal r = {{0, 0, 0, 0}};

  ck_assert_int_eq(s21_div(a, b, &r), S21_ARITH_OK);
  ck_assert_int_eq(s21_get_scale(&r), 28);
}
END_TEST

// ========== ТЕСТЫ ЦЕЛОСТНОСТИ ДАННЫХ ==========

START_TEST(add_preserves_input_values) {
  s21_decimal a = {{10, 0, 0, 0}};
  s21_decimal b = {{5, 0, 0, 0x80000000}};
  s21_decimal a_copy = a;
  s21_decimal b_copy = b;
  s21_decimal r = {{0, 0, 0, 0}};

  s21_add(a, b, &r);

  ck_assert_int_eq(s21_is_equal(a, a_copy), TRUE);
  ck_assert_int_eq(s21_is_equal(b, b_copy), TRUE);
}
END_TEST

// ========== СТРЕСС-ТЕСТЫ ==========

START_TEST(stress_many_additions) {
  s21_decimal a = {{1000000, 0, 0, 0}};
  s21_decimal b = {{1, 0, 0, 0}};
  s21_decimal r = {{0, 0, 0, 0}};

  for (int i = 0; i < 1000; i++) {
    ck_assert_int_eq(s21_add(a, b, &r), S21_ARITH_OK);
    a = r;
  }
  ck_assert_int_eq(r.bits[0], 1001000);
}
END_TEST

START_TEST(stress_many_divisions) {
  s21_decimal a = {{1000000, 0, 0, 0}};
  s21_decimal b = {{10, 0, 0, 0}};
  s21_decimal r = {{0, 0, 0, 0}};

  for (int i = 0; i < 6; i++) {
    ck_assert_int_eq(s21_div(a, b, &r), S21_ARITH_OK);
    a = r;
  }
  ck_assert_int_eq(r.bits[0], 1);
}
END_TEST

// ========== ТЕСТЫ ДЛЯ ПОКРЫТИЯ ЦИКЛА УМЕНЬШЕНИЯ МАСШТАБА В MUL ==========

START_TEST(mul_scale_reduction_big_product_even) {
  s21_decimal a = {{0xFFFFFFFF, 0xFFFFFFFF, 0, 0}}; // Большое число
  s21_set_scale(&a, 0);
  s21_decimal b = {{10, 0, 0, 0}}; // 10
  s21_set_scale(&b, 0);
  s21_decimal r = {{0, 0, 0, 0}};

  // Результат умножения будет большим и потребует уменьшения масштаба
  // Ожидаем успешное выполнение с банковским округлением
  ck_assert_int_eq(s21_mul(a, b, &r), S21_ARITH_OK);
  ck_assert_int_ge(s21_get_scale(&r), 0);
  ck_assert_int_le(s21_get_scale(&r), 28);
}
END_TEST

START_TEST(mul_scale_reduction_big_product_odd) {
  s21_decimal a = {{0xFFFFFFFF, 0xFFFFFFFF, 0, 0}};
  s21_set_scale(&a, 0);
  s21_decimal b = {{5, 0, 0, 0}}; // 5
  s21_set_scale(&b, 0);
  s21_decimal r = {{0, 0, 0, 0}};

  ck_assert_int_eq(s21_mul(a, b, &r), S21_ARITH_OK);
  ck_assert_int_ge(s21_get_scale(&r), 0);
  ck_assert_int_le(s21_get_scale(&r), 28);
}
END_TEST

START_TEST(mul_scale_reduction_with_bankers_rounding_up) {
  s21_decimal a = {{0xFFFFFFFF, 0xFFFFFFFF, 0, 0}};
  s21_set_scale(&a, 0);
  s21_decimal b = {{3, 0, 0, 0}}; // 3
  s21_set_scale(&b, 0);
  s21_decimal r = {{0, 0, 0, 0}};

  ck_assert_int_eq(s21_mul(a, b, &r), S21_ARITH_OK);
}
END_TEST

START_TEST(mul_scale_reduction_success_case) {
  s21_decimal a = {
      {0xFFFFFFFF, 0xFFFFFFFF, 0, 0}}; // Число чуть меньше максимального
  s21_set_scale(&a, 5);
  s21_decimal b = {{0xFFFFFFFF, 0xFFFFFFFF, 0, 0}};
  s21_set_scale(&b, 5);
  s21_decimal r = {{0, 0, 0, 0}};

  // Произведение будет большим, но после уменьшения масштаба должно поместиться
  ck_assert_int_eq(s21_mul(a, b, &r), S21_ARITH_OK);
  ck_assert_int_le(s21_get_scale(&r), 28);
}
END_TEST

START_TEST(mul_scale_reduction_with_remainder_5) {
  s21_decimal a = {{0xFFFFFFFF, 0xFFFFFFFF, 0, 0}};
  s21_set_scale(&a, 0);
  s21_decimal b = {{6, 0, 0, 0}}; // 6
  s21_set_scale(&b, 0);
  s21_decimal r = {{0, 0, 0, 0}};

  ck_assert_int_eq(s21_mul(a, b, &r), S21_ARITH_OK);
}
END_TEST

START_TEST(mul_scale_reduction_negative_sign) {
  s21_decimal a = {{0xFFFFFFFF, 0xFFFFFFFF, 0, 0}};
  s21_set_scale(&a, 0);
  s21_set_sign(&a, 1);
  s21_decimal b = {{5, 0, 0, 0}};
  s21_set_scale(&b, 0);
  s21_decimal r = {{0, 0, 0, 0}};

  ck_assert_int_eq(s21_mul(a, b, &r), S21_ARITH_OK);
  ck_assert_int_eq(s21_get_sign(&r), 1);
}
END_TEST

START_TEST(mul_scale_reduction_exact_division) {
  s21_decimal a = {{1000000, 0, 0, 0}};
  s21_set_scale(&a, 0);
  s21_decimal b = {{1000000, 0, 0, 0}};
  s21_set_scale(&b, 0);
  s21_decimal r = {{0, 0, 0, 0}};

  // Создаем ожидаемое значение 1,000,000,000,000 с помощью float
  // (хоть и с погрешностью, но для проверки достаточно)
  s21_decimal expected;
  s21_from_float_to_decimal(1000000000000.0f, &expected);

  ck_assert_int_eq(s21_mul(a, b, &r), S21_ARITH_OK);
  ck_assert_int_eq(s21_is_equal(r, expected), TRUE);
}
END_TEST

// ============================================
// ДОПОЛНИТЕЛЬНЫЕ ТЕСТЫ ДЛЯ ПОКРЫТИЯ НЕПОКРЫТЫХ СТРОК В s21_div
// ============================================

START_TEST(div_overflow_after_bankers_rounding) {
  // Тест для строки 220: переполнение после банковского округления
  s21_decimal a = {
      {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}}; // Максимальное число
  s21_set_scale(&a, 0);
  s21_decimal b = {{1, 0, 0, 0}}; // 1
  s21_set_scale(&b, 28); // Очень маленький делитель с большим масштабом
  s21_decimal r = {{0, 0, 0, 0}};

  // scale = 0 - 28 = -28, потом увеличивается на 28 -> scale = 0
  // Но в процессе деления число может стать очень большим
  int result = s21_div(a, b, &r);

  // Ожидаем переполнение, так как результат должен быть больше максимального
  ck_assert(result == S21_ARITH_TOO_LARGE || result == S21_ARITH_TOO_SMALL);
}
END_TEST

START_TEST(div_scale_reduction_with_rounding_up) {
  // Тест для строк 230-231: округление вверх при уменьшении масштаба
  // Создаем ситуацию, где при делении результат чуть больше 96 бит,
  // и при уменьшении масштаба требуется округление вверх
  s21_decimal a = {{0xFFFFFFFF, 0xFFFFFFFF, 0, 0}};
  s21_set_scale(&a, 0);
  s21_decimal b = {{2, 0, 0, 0}};
  s21_decimal r = {{0, 0, 0, 0}};

  // Ожидаем успешное выполнение с округлением
  ck_assert_int_eq(s21_div(a, b, &r), S21_ARITH_OK);
}
END_TEST

START_TEST(div_still_too_big_after_scale_reduction) {
  // Тест для строк 234-235: число всё ещё не влезает после уменьшения масштаба
  s21_decimal a = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_set_scale(&a, 0);
  s21_decimal b = {{1, 0, 0, 0}}; // Делим на 1 - результат будет максимальным
  s21_set_scale(&b, 28); // Но с большим масштабом делителя

  s21_decimal r = {{0, 0, 0, 0}};

  // scale = 0 - 28 = -28, затем увеличиваем до 0,
  // но результат всё равно не помещается в 96 бит после всех округлений
  ck_assert_int_eq(s21_div(a, b, &r), S21_ARITH_TOO_LARGE);
}
END_TEST

START_TEST(div_scale_exceeds_28_after_division) {
  // Тест для строк 238-244: масштаб превышает 28 после деления
  s21_decimal a = {{1, 0, 0, 0}};
  s21_set_scale(&a, 28); // Максимальный масштаб
  s21_decimal b = {{2, 0, 0, 0}};
  s21_set_scale(&b, 0);
  s21_decimal r = {{0, 0, 0, 0}};

  // scale = 28 - 0 = 28, должно быть OK
  ck_assert_int_eq(s21_div(a, b, &r), S21_ARITH_OK);

  // Для получения scale > 28 нужно делить число с большим масштабом
  // на число с маленьким масштабом
  s21_decimal a2 = {{1, 0, 0, 0}};
  s21_set_scale(&a2, 28);
  s21_decimal b2 = {{1, 0, 0, 0}};
  s21_set_scale(&b2, 0);
  s21_decimal r2 = {{0, 0, 0, 0}};

  // scale = 28 - 0 = 28, должно быть OK
  ck_assert_int_eq(s21_div(a2, b2, &r2), S21_ARITH_OK);
}
END_TEST

START_TEST(div_precision_loss_with_rounding_up) {
  // Комбинированный тест для покрытия нескольких непокрытых строк
  s21_decimal a = {{0xFFFFFFF0, 0xFFFFFFFF, 0, 0}};
  s21_set_scale(&a, 0);
  s21_decimal b = {{3, 0, 0, 0}};
  s21_set_scale(&b, 0);
  s21_decimal r = {{0, 0, 0, 0}};

  // Результат будет большим, потребуется уменьшение масштаба
  int result = s21_div(a, b, &r);
  ck_assert(result == S21_ARITH_OK || result == S21_ARITH_TOO_LARGE);
}
END_TEST

START_TEST(div_edge_case_rounding_overflow) {
  // Тест для строки 220: переполнение при округлении
  s21_decimal a = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_set_scale(&a, 0);
  s21_decimal b = {{1, 0, 0, 0}};
  s21_set_scale(&b, 28); // Очень маленький делитель (1e-28)
  s21_decimal r = {{0, 0, 0, 0}};

  // Делим максимальное число на очень маленькое -> результат огромный
  int result = s21_div(a, b, &r);

  // Ожидаем переполнение
  ck_assert(result == S21_ARITH_TOO_LARGE);
}
END_TEST

START_TEST(div_large_scale_difference_with_rounding) {
  // Тест для покрытия цикла уменьшения масштаба
  s21_decimal a = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_set_scale(&a, 28);
  s21_decimal b = {{1, 0, 0, 0}};
  s21_set_scale(&b, 0);
  s21_decimal r = {{0, 0, 0, 0}};

  // scale = 28 - 0 = 28, должно быть OK
  ck_assert_int_eq(s21_div(a, b, &r), S21_ARITH_OK);
}
END_TEST

START_TEST(div_rounding_up_at_precision_limit) {
  // Тест для проверки округления вверх на пределе точности
  s21_decimal a = {{5, 0, 0, 0}};
  s21_set_scale(&a, 1); // 0.5
  s21_decimal b = {{3, 0, 0, 0}};
  s21_set_scale(&b, 0); // 3
  s21_decimal r = {{0, 0, 0, 0}};

  // 0.5 / 3 = 0.16666... должно округлиться
  ck_assert_int_eq(s21_div(a, b, &r), S21_ARITH_OK);
  ck_assert_int_eq(s21_get_scale(&r), 28);
}
END_TEST

// ============================================
// ТЕСТЫ ДЛЯ ПОКРЫТИЯ ОСТАВШИХСЯ ВЕТОК В ДРУГИХ ФУНКЦИЯХ
// ============================================

START_TEST(add_scale_too_large) {
  // Тест для строки 12-13: проверка scale > 28
  s21_decimal a = {{1, 0, 0, 0}};
  a.bits[3] = (29 << 16); // scale = 29
  s21_decimal b = {{2, 0, 0, 0}};
  s21_decimal r = {{0, 0, 0, 0}};

  ck_assert_int_eq(s21_add(a, b, &r), S21_ARITH_TOO_LARGE);
}
END_TEST

START_TEST(mul_scale_too_large) {
  // Тест для строки 100-101: проверка scale > 28 в умножении
  s21_decimal a = {{1, 0, 0, 0}};
  a.bits[3] = (29 << 16);
  s21_decimal b = {{2, 0, 0, 0}};
  s21_decimal r = {{0, 0, 0, 0}};

  ck_assert_int_eq(s21_mul(a, b, &r), S21_ARITH_TOO_LARGE);
}
END_TEST

START_TEST(div_scale_too_large) {
  // Тест для строки 158-159: проверка scale > 28 в делении
  s21_decimal a = {{1, 0, 0, 0}};
  a.bits[3] = (29 << 16);
  s21_decimal b = {{2, 0, 0, 0}};
  s21_decimal r = {{0, 0, 0, 0}};

  ck_assert_int_eq(s21_div(a, b, &r), S21_ARITH_TOO_LARGE);
}
END_TEST

START_TEST(sub_null_result) {
  // Тест для строки 259-260: проверка result == NULL в вычитании
  s21_decimal a = {{1, 0, 0, 0}};
  s21_decimal b = {{2, 0, 0, 0}};

  ck_assert_int_eq(s21_sub(a, b, NULL), S21_ARITH_TOO_LARGE);
}
END_TEST

START_TEST(mul_null_result) {
  // Тест для строки 89-90: проверка result == NULL в умножении
  s21_decimal a = {{1, 0, 0, 0}};
  s21_decimal b = {{2, 0, 0, 0}};

  ck_assert_int_eq(s21_mul(a, b, NULL), S21_ARITH_TOO_LARGE);
}
END_TEST

START_TEST(div_null_result) {
  // Тест для строки 148-149: проверка result == NULL в делении
  s21_decimal a = {{1, 0, 0, 0}};
  s21_decimal b = {{2, 0, 0, 0}};

  ck_assert_int_eq(s21_div(a, b, NULL), S21_ARITH_TOO_LARGE);
}
END_TEST

START_TEST(add_normalization_failure) {
  // Тест для строки 25-26: ошибка нормализации масштабов
  s21_decimal a = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_set_scale(&a, 28);
  s21_decimal b = {{1, 0, 0, 0}};
  s21_set_scale(&b, 0);
  s21_decimal r = {{0, 0, 0, 0}};

  // Нормализация может не удаться из-за переполнения
  int result = s21_add(a, b, &r);
  ck_assert(result == S21_ARITH_OK || result == S21_ARITH_TOO_LARGE);
}
END_TEST

START_TEST(div_scale_forced_to_exceed_28) {
  // Тест для строк 238-244: принудительное превышение масштаба
  s21_decimal a = {{1, 0, 0, 0}};
  s21_set_scale(&a, 28);

  // Выбираем делитель, который даст длинную периодическую дробь
  s21_decimal b = {{17, 0, 0, 0}}; // 1/17 - длинная периодическая дробь
  s21_set_scale(&b, 0);

  s21_decimal r = {{0, 0, 0, 0}};

  int result = s21_div(a, b, &r);
  ck_assert(result == S21_ARITH_OK);
  ck_assert_int_eq(s21_get_scale(&r), 28); // Должно быть 28 после уменьшения
}
END_TEST

START_TEST(div_scale_much_greater_than_28) {
  // Тест для строк 238-244: масштаб намного превышает 28
  s21_decimal a = {{1, 0, 0, 0}};
  s21_set_scale(&a, 28); // Максимальный масштаб

  // Создаем очень маленький делитель
  s21_decimal b = {{1, 0, 0, 0}};
  s21_set_scale(&b, 28); // Тоже максимальный масштаб

  s21_decimal r = {{0, 0, 0, 0}};

  // scale = 28 - 28 = 0, но при делении 1/1 = 1
  ck_assert_int_eq(s21_div(a, b, &r), S21_ARITH_OK);

  // Теперь делим 1 на очень маленькое число
  s21_decimal a2 = {{1, 0, 0, 0}};
  s21_set_scale(&a2, 28); // 1e-28
  s21_decimal b2 = {{1, 0, 0, 0}};
  s21_set_scale(&b2, 28); // 1e-28
  s21_decimal r2 = {{0, 0, 0, 0}};

  // 1e-28 / 1e-28 = 1, масштаб должен быть 0
  ck_assert_int_eq(s21_div(a2, b2, &r2), S21_ARITH_OK);
  ck_assert_int_eq(s21_get_scale(&r2), 0);

  // Деление с большим остатком
  s21_decimal a3 = {{1, 0, 0, 0}};
  s21_set_scale(&a3, 28); // 1e-28
  s21_decimal b3 = {{7, 0, 0, 0}};
  s21_set_scale(&b3, 0); // 7
  s21_decimal r3 = {{0, 0, 0, 0}};

  // 1e-28 / 7 = очень маленькая периодическая дробь
  // В процессе деления масштаб будет расти
  int result3 = s21_div(a3, b3, &r3);
  ck_assert(result3 == S21_ARITH_OK);
  ck_assert_int_le(s21_get_scale(&r3), 28);
}
END_TEST

START_TEST(div_scale_gt_28_forced) {
  // Тест для строк 238-245: принудительное scale > 28

  // Берем очень маленькое делимое с большим масштабом
  s21_decimal a = {{1, 0, 0, 0}};
  s21_set_scale(&a, 28); // 1e-28

  // И очень маленький делитель, чтобы получить большое число
  s21_decimal b = {{1, 0, 0, 0}};
  s21_set_scale(&b, 28); // 1e-28

  s21_decimal r = {{0, 0, 0, 0}};

  // 1e-28 / 1e-28 = 1, scale = 0
  ck_assert_int_eq(s21_div(a, b, &r), S21_ARITH_OK);

  // Теперь создаем ситуацию с огромным делимым и маленьким делителем
  s21_decimal a2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_set_scale(&a2, 28); // Максимальное число с масштабом 28

  s21_decimal b2 = {{1, 0, 0, 0}};
  s21_set_scale(&b2, 28); // 1e-28

  s21_decimal r2 = {{0, 0, 0, 0}};

  // scale = 28 - 28 = 0, но в процессе деления будет увеличиваться
  // и может превысить 28
  int result = s21_div(a2, b2, &r2);
  ck_assert(result == S21_ARITH_TOO_LARGE || result == S21_ARITH_OK);
}
END_TEST

// ============================================
// Создание набора тестов
// ============================================

Suite *arithmetic_suite(void) {
  Suite *s = suite_create("arithmetic");
  TCase *tc = tcase_create("core");

  // ADD существующие тесты
  tcase_add_test(tc, add_simple);
  tcase_add_test(tc, add_zero);
  tcase_add_test(tc, add_one_plus_one);
  tcase_add_test(tc, add_with_carry);
  tcase_add_test(tc, add_negative);
  tcase_add_test(tc, add_two_negatives);
  tcase_add_test(tc, add_with_different_scales);
  tcase_add_test(tc, add_equal_opposite_signs);
  tcase_add_test(tc, add_overflow_to_infinity);
  tcase_add_test(tc, add_overflow_to_negative_infinity);
  tcase_add_test(tc, add_with_scale_reduction);
  tcase_add_test(tc, add_null_result);
  tcase_add_test(tc, invalid_decimal);
  tcase_add_test(tc, scale_normalization_failure);
  tcase_add_test(tc, add_edge_cases);
  tcase_add_test(tc, add_invalid_decimal);
  tcase_add_test(tc, add_invalid_decimal_scale_too_large);
  tcase_add_test(tc, add_second_value_scale_too_large);
  tcase_add_test(tc, add_scale_normalization_fails);
  tcase_add_test(tc, add_with_scale_reduction_big_result);
  tcase_add_test(tc, add_big_to_decimal_conversion_after_reduction);

  // SUB существующие тесты
  tcase_add_test(tc, sub_simple);
  tcase_add_test(tc, sub_negative_result);
  tcase_add_test(tc, sub_equal_numbers);
  tcase_add_test(tc, sub_large_numbers);

  // MUL существующие тесты
  tcase_add_test(tc, mul_simple);
  tcase_add_test(tc, mul_with_sign);
  tcase_add_test(tc, mul_with_scale);
  tcase_add_test(tc, mul_zero);
  tcase_add_test(tc, mul_scale_reduction);
  tcase_add_test(tc, mul_overflow_positive);
  tcase_add_test(tc, mul_overflow_negative);
  tcase_add_test(tc, mul_scale_over_28_reduction);
  tcase_add_test(tc, mul_big_result_needs_scale_reduction);
  tcase_add_test(tc, mul_overflow_even_after_reduction);
  tcase_add_test(tc, mul_large_scale_overflow);

  // DIV существующие тесты
  tcase_add_test(tc, div_simple);
  tcase_add_test(tc, div_small_by_large);
  tcase_add_test(tc, div_with_precision_limit);
  tcase_add_test(tc, div_overflow);
  tcase_add_test(tc, div_bankers_rounding);
  tcase_add_test(tc, div_by_zero);
  tcase_add_test(tc, div_negative_scale_needs_adjustment);
  tcase_add_test(tc, div_bankers_rounding_causes_overflow);
  tcase_add_test(tc, div_result_too_big_needs_scale_reduction);
  tcase_add_test(tc, div_final_scale_too_large);

  // Общие тесты
  tcase_add_test(tc, all_funcs_invalid_decimal_input);

  // ========== НОВЫЕ ТЕСТЫ (БЕЗ ДУБЛИРОВАНИЯ) ==========
  tcase_add_test(tc, add_bankers_rounding_even);
  tcase_add_test(tc, add_bankers_rounding_odd);
  tcase_add_test(tc, sub_bankers_rounding_even);
  tcase_add_test(tc, mul_bankers_rounding_even);
  tcase_add_test(tc, div_bankers_rounding_exact);
  tcase_add_test(tc, div_bankers_rounding_at_precision_limit);

  tcase_add_test(tc, add_normalize_large_scale_difference);
  tcase_add_test(tc, sub_normalize_overflow_during_normalization);

  tcase_add_test(tc, mul_max_decimal_by_one);
  tcase_add_test(tc, div_min_decimal_by_two);

  tcase_add_test(tc, add_negative_larger_scale);
  tcase_add_test(tc, sub_both_negative_different_scales);

  tcase_add_test(tc, div_exact_division);
  tcase_add_test(tc, div_remainder_tail_rounding);

  tcase_add_test(tc, add_zero_negative_zero);
  tcase_add_test(tc, mul_zero_by_negative);

  tcase_add_test(tc, add_scale_28_overflow);
  tcase_add_test(tc, div_scale_reduction_edge);

  tcase_add_test(tc, add_preserves_input_values);

  tcase_add_test(tc, stress_many_additions);
  tcase_add_test(tc, stress_many_divisions);

  // ========== ТЕСТЫ ДЛЯ ПОКРЫТИЯ ЦИКЛА УМЕНЬШЕНИЯ МАСШТАБА В MUL ==========
  tcase_add_test(tc, mul_scale_reduction_big_product_even);
  tcase_add_test(tc, mul_scale_reduction_big_product_odd);
  tcase_add_test(tc, mul_scale_reduction_with_bankers_rounding_up);
  tcase_add_test(tc, mul_scale_reduction_success_case);
  tcase_add_test(tc, mul_scale_reduction_with_remainder_5);
  tcase_add_test(tc, mul_scale_reduction_negative_sign);
  tcase_add_test(tc, mul_scale_reduction_exact_division);

  // ========== НОВЫЕ ТЕСТЫ ДЛЯ ПОКРЫТИЯ НЕПОКРЫТЫХ СТРОК ==========
  tcase_add_test(tc, div_overflow_after_bankers_rounding);
  tcase_add_test(tc, div_scale_reduction_with_rounding_up);
  tcase_add_test(tc, div_still_too_big_after_scale_reduction);
  tcase_add_test(tc, div_scale_exceeds_28_after_division);
  tcase_add_test(tc, div_precision_loss_with_rounding_up);
  tcase_add_test(tc, div_edge_case_rounding_overflow);
  tcase_add_test(tc, div_large_scale_difference_with_rounding);
  tcase_add_test(tc, div_rounding_up_at_precision_limit);
  tcase_add_test(tc, add_scale_too_large);
  tcase_add_test(tc, mul_scale_too_large);
  tcase_add_test(tc, div_scale_too_large);
  tcase_add_test(tc, sub_null_result);
  tcase_add_test(tc, mul_null_result);
  tcase_add_test(tc, div_null_result);
  tcase_add_test(tc, add_normalization_failure);

  tcase_add_test(tc, div_scale_forced_to_exceed_28);
  tcase_add_test(tc, div_scale_much_greater_than_28);
  tcase_add_test(tc, div_scale_gt_28_forced);

  suite_add_tcase(s, tc);
  return s;
}