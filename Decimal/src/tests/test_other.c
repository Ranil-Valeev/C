#include "test.h"

/* Вспомогательные функции для создания decimal значений */
s21_decimal make_dec(uint32_t b0, uint32_t b1, uint32_t b2, int scale,
                     int sign) {
  s21_decimal result;
  result.bits[0] = b0;
  result.bits[1] = b1;
  result.bits[2] = b2;

  /* Устанавливаем scale и sign в bits[3] */
  result.bits[3] = (scale << 16) | (sign ? 0x80000000 : 0);

  return result;
}

/* Создание "невалидного" decimal для тестов */
s21_decimal make_invalid_decimal(void) {
  s21_decimal result;
  result.bits[0] = 0xFFFFFFFF;
  result.bits[1] = 0xFFFFFFFF;
  result.bits[2] = 0xFFFFFFFF;
  result.bits[3] = 0xFFFFFFFF; /* Неверный scale > 28 */
  return result;
}

/* ========== Тесты из первого файла ========== */

START_TEST(negate_positive) {
  s21_decimal a, res, expected;
  s21_from_int_to_decimal(5, &a);
  s21_from_int_to_decimal(-5, &expected);
  ck_assert_int_eq(s21_negate(a, &res), 0);
  ck_assert_int_eq(s21_is_equal(res, expected), 1);
}
END_TEST

START_TEST(negate_negative) {
  s21_decimal a, res, expected;
  s21_from_int_to_decimal(-10, &a);
  s21_from_int_to_decimal(10, &expected);
  s21_negate(a, &res);
  ck_assert_int_eq(s21_is_equal(res, expected), 1);
}
END_TEST

START_TEST(negate_zero) {
  s21_decimal a, res, expected;
  s21_from_int_to_decimal(0, &a);
  s21_from_int_to_decimal(0, &expected);
  s21_negate(a, &res);
  ck_assert_int_eq(s21_is_equal(res, expected), 1);
}
END_TEST

START_TEST(negate_int_min) {
  s21_decimal a, res;
  s21_from_int_to_decimal(-2147483648, &a);
  int out;
  s21_negate(a, &res);
  ck_assert_int_ne(s21_from_decimal_to_int(res, &out), 0);
}
END_TEST

START_TEST(truncate_positive) {
  s21_decimal a, res, expected;
  s21_from_float_to_decimal(5.7f, &a);
  s21_from_int_to_decimal(5, &expected);
  s21_truncate(a, &res);
  ck_assert_int_eq(s21_is_equal(res, expected), 1);
}
END_TEST

START_TEST(truncate_negative) {
  s21_decimal a, res, expected;
  s21_from_float_to_decimal(-5.7f, &a);
  s21_from_int_to_decimal(-5, &expected);
  s21_truncate(a, &res);
  ck_assert_int_eq(s21_is_equal(res, expected), 1);
}
END_TEST

START_TEST(truncate_integer) {
  s21_decimal a, res, expected;
  s21_from_int_to_decimal(10, &a);
  s21_from_int_to_decimal(10, &expected);
  s21_truncate(a, &res);
  ck_assert_int_eq(s21_is_equal(res, expected), 1);
}
END_TEST

START_TEST(truncate_fractional_scale) {
  s21_decimal a, res, expected;
  s21_from_float_to_decimal(12.3456f, &a);
  s21_from_int_to_decimal(12, &expected);
  s21_truncate(a, &res);
  ck_assert_int_eq(s21_is_equal(res, expected), 1);
}
END_TEST

START_TEST(floor_positive) {
  s21_decimal a, res, expected;
  s21_from_float_to_decimal(5.9f, &a);
  s21_from_int_to_decimal(5, &expected);
  s21_floor(a, &res);
  ck_assert_int_eq(s21_is_equal(res, expected), 1);
}
END_TEST

START_TEST(floor_negative) {
  s21_decimal a, res, expected;
  s21_from_float_to_decimal(-5.1f, &a);
  s21_from_int_to_decimal(-6, &expected);
  s21_floor(a, &res);
  ck_assert_int_eq(s21_is_equal(res, expected), 1);
}
END_TEST

START_TEST(floor_integer) {
  s21_decimal a, res, expected;
  s21_from_int_to_decimal(-10, &a);
  s21_from_int_to_decimal(-10, &expected);
  s21_floor(a, &res);
  ck_assert_int_eq(s21_is_equal(res, expected), 1);
}
END_TEST

START_TEST(floor_fractional_scale) {
  s21_decimal a, res, expected;
  s21_from_float_to_decimal(-7.891f, &a);
  s21_from_int_to_decimal(-8, &expected);
  s21_floor(a, &res);
  ck_assert_int_eq(s21_is_equal(res, expected), 1);
}
END_TEST

START_TEST(round_down) {
  s21_decimal a, res, expected;
  s21_from_float_to_decimal(2.4f, &a);
  s21_from_int_to_decimal(2, &expected);
  s21_round(a, &res);
  ck_assert_int_eq(s21_is_equal(res, expected), 1);
}
END_TEST

START_TEST(round_half_up) {
  s21_decimal a, res, expected;
  s21_from_float_to_decimal(2.5f, &a);
  s21_from_int_to_decimal(3, &expected);
  s21_round(a, &res);
  ck_assert_int_eq(s21_is_equal(res, expected), 1);
}
END_TEST

START_TEST(round_negative_half) {
  s21_decimal a, res, expected;
  s21_from_float_to_decimal(-2.5f, &a);
  s21_from_int_to_decimal(-3, &expected);
  s21_round(a, &res);
  ck_assert_int_eq(s21_is_equal(res, expected), 1);
}
END_TEST

START_TEST(round_fractional_half) {
  s21_decimal a, res, expected;
  s21_from_float_to_decimal(3.555f, &a);
  s21_from_int_to_decimal(4, &expected);
  s21_round(a, &res);
  ck_assert_int_eq(s21_is_equal(res, expected), 1);
}
END_TEST

/* ========== Тесты из второго файла ========== */

START_TEST(other_null_and_invalid) {
  s21_decimal a = make_dec(1, 0, 0, 0, 0);
  // s21_decimal r;

  ck_assert_int_eq(s21_floor(a, NULL), 1);
  ck_assert_int_eq(s21_round(a, NULL), 1);
  ck_assert_int_eq(s21_truncate(a, NULL), 1);
  ck_assert_int_eq(s21_negate(a, NULL), 1);

#ifdef S21_IS_VALID_DECIMAL
  s21_decimal bad = make_invalid_decimal();
  ck_assert_int_eq(s21_floor(bad, &r), 1);
  ck_assert_int_eq(s21_round(bad, &r), 1);
  ck_assert_int_eq(s21_truncate(bad, &r), 1);
#endif
}
END_TEST

START_TEST(negate_zero_and_nonzero) {
  s21_decimal z = make_dec(0, 0, 0, 0, 0);
  s21_decimal r;
  ck_assert_int_eq(s21_negate(z, &r), 0);

  int sign = (r.bits[3] & 0x80000000) ? 1 : 0;
  ck_assert_int_eq(sign, 0);

  s21_decimal a = make_dec(5, 0, 0, 0, 0);
  ck_assert_int_eq(s21_negate(a, &r), 0);
  sign = (r.bits[3] & 0x80000000) ? 1 : 0;
  ck_assert_int_eq(sign, 1);
}
END_TEST

START_TEST(truncate_basic) {
  s21_decimal a = make_dec(12345u, 0u, 0u, 2, 0);
  s21_decimal r;
  ck_assert_int_eq(s21_truncate(a, &r), 0);

  int scale = (r.bits[3] >> 16) & 0xFF;
  ck_assert_int_eq(scale, 0);

  int out = 0;
  int conv_result = s21_from_decimal_to_int(r, &out);
  if (conv_result == 0) {
    ck_assert_int_eq(out, 123);
  }
}
END_TEST

START_TEST(floor_scale0_returns_same) {
  s21_decimal a = make_dec(10u, 0u, 0u, 0, 0);
  s21_decimal r;
  ck_assert_int_eq(s21_floor(a, &r), 0);
  ck_assert_int_eq(s21_is_equal(a, r), 1);

  s21_decimal z = make_dec(0u, 0u, 0u, 0, 1);
  ck_assert_int_eq(s21_floor(z, &r), 0);
  int sign = (r.bits[3] & 0x80000000) ? 1 : 0;
  ck_assert_int_eq(sign, 0);
}
END_TEST

START_TEST(floor_negative_with_fraction) {
  s21_decimal a = make_dec(12u, 0u, 0u, 1, 1);
  s21_decimal r;
  ck_assert_int_eq(s21_floor(a, &r), 0);

  int out = 0;
  int conv_result = s21_from_decimal_to_int(r, &out);
  if (conv_result == 0) {
    ck_assert_int_eq(out, -2);
  }

  s21_decimal b = make_dec(10u, 0u, 0u, 1, 1);
  ck_assert_int_eq(s21_floor(b, &r), 0);

  conv_result = s21_from_decimal_to_int(r, &out);
  if (conv_result == 0) {
    ck_assert_int_eq(out, -1);
  }
}
END_TEST

START_TEST(round_scale0_returns_same) {
  s21_decimal a = make_dec(10u, 0u, 0u, 0, 0);
  s21_decimal r;
  ck_assert_int_eq(s21_round(a, &r), 0);
  ck_assert_int_eq(s21_is_equal(a, r), 1);
}
END_TEST

/* ========== Тесты из третьего файла ========== */

START_TEST(s21_floor_1) {
  s21_decimal val = {{2, 0, 0, 0}};
  s21_decimal res;
  ck_assert_int_eq(0, s21_floor(val, &res));
}
END_TEST

START_TEST(s21_floor_2) {
  s21_decimal value_1 = {{7444923, 0, 0, 0}};
  s21_set_scale(&value_1, 5);
  s21_decimal check = {{74, 0, 0, 0}};
  s21_decimal result = {0};
  int return_value = s21_floor(value_1, &result);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(s21_floor_3) {
  s21_decimal value_1 = {{7444923, 0, 0, 0}};
  s21_set_scale(&value_1, 5); // Устанавливаем scale=5 (74.44923)
  s21_set_sign(&value_1, 1); // Устанавливаем знак=1 (-74.44923)

  // floor(-74.44923) = -75 (для отрицательных чисел округляем вниз)
  s21_decimal check = {{75, 0, 0, 0}};
  s21_set_scale(&check, 0); // После floor scale=0
  s21_set_sign(&check, 1); // Знак остается отрицательным

  s21_decimal result = {0};
  int return_value = s21_floor(value_1, &result);

  ck_assert_int_eq(s21_is_equal(result, check), 1);
  ck_assert_int_eq(return_value, 0);
}
END_TEST
START_TEST(s21_round_1) {
  s21_decimal val = {{3, 3, 3, ~(UINT_MAX / 2)}};
  s21_decimal res = {{0}};
  ck_assert_int_eq(0, s21_round(val, &res));
}
END_TEST

START_TEST(s21_round_2) {
  s21_decimal val = {{3, 3, 3, 0}};
  s21_decimal res = {{0}};
  s21_set_sign(&val, 5);
  ck_assert_int_eq(0, s21_round(val, &res));
}
END_TEST

START_TEST(s21_round_3) {
  s21_decimal val = {{7, 7, 7, ~(UINT_MAX / 2)}};
  s21_decimal res = {{0}};
  s21_set_sign(&val, 5);
  ck_assert_int_eq(0, s21_round(val, &res));
}
END_TEST

START_TEST(s21_round_4) {
  s21_decimal val = {{25, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal res = {{0}};
  s21_set_sign(&val, 1);
  ck_assert_int_eq(0, s21_round(val, &res));
}
END_TEST

START_TEST(s21_round_5) {
  s21_decimal val = {{26, 0, 0, 0}};
  s21_decimal res = {{0}};
  s21_set_sign(&val, 1);
  ck_assert_int_eq(0, s21_round(val, &res));
}
END_TEST

START_TEST(s21_round_6) {
  s21_decimal val = {{115, 0, 0, 0}};
  s21_decimal res = {{0}};
  s21_set_sign(&val, 1);
  ck_assert_int_eq(0, s21_round(val, &res));
}
END_TEST

START_TEST(s21_round_7) {
  s21_decimal val = {{118, 0, 0, 0}};
  s21_decimal res = {{0}};
  s21_set_sign(&val, 1);
  ck_assert_int_eq(0, s21_round(val, &res));
}
END_TEST

START_TEST(s21_round_8) {
  s21_decimal val = {{125, 0, 0, 0}};
  s21_decimal res = {{0}};
  s21_set_sign(&val, 1);
  ck_assert_int_eq(0, s21_round(val, &res));
}
END_TEST

START_TEST(s21_round_9) {
  s21_decimal value_1 = {{7464923, 0, 0, 0}};
  s21_set_scale(&value_1, 5); // Устанавливаем scale=5 (74.64923)
  s21_set_sign(&value_1, 0); // Устанавливаем знак=0 (положительное)

  s21_decimal check = {{75, 0, 0, 0}};
  s21_set_scale(&check, 0); // После округления scale=0
  s21_set_sign(&check, 0); // Знак остается положительным

  s21_decimal result = {0};
  int return_value = s21_round(value_1, &result);

  ck_assert_int_eq(s21_is_equal(result, check), 1);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(s21_round_10) {
  s21_decimal value_1 = {{7444923, 0, 0, 0}};
  s21_set_scale(&value_1, 5); // Устанавливаем scale=5 (74.44923)
  s21_set_sign(&value_1, 0);  // Устанавливаем знак=0

  s21_decimal check = {{74, 0, 0, 0}};
  s21_set_scale(&check, 0); // После округления scale=0
  s21_set_sign(&check, 0); // Знак остается положительным

  s21_decimal result = {0};
  int return_value = s21_round(value_1, &result);

  ck_assert_int_eq(s21_is_equal(result, check), 1);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(s21_truncate_1) {
  s21_decimal decimal = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}};
  s21_set_scale(&decimal, 28); // Устанавливаем scale=28
  s21_set_sign(&decimal, 0);   // Устанавливаем знак=0

  s21_decimal result;
  s21_decimal expected_result = {{7, 0, 0, 0}}; // Уточните ожидаемый результат
  s21_set_scale(&expected_result, 0); // Устанавливаем scale=0
  s21_set_sign(&expected_result, 0);  // Устанавливаем знак=0

  ck_assert_int_eq(s21_truncate(decimal, &result), 0);
  ck_assert_int_eq(s21_is_equal(result, expected_result), 1);
}
END_TEST

START_TEST(s21_truncate_2) {
  s21_decimal decimal = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}};
  s21_set_scale(&decimal, 28); // Устанавливаем scale=28
  s21_set_sign(&decimal, 1); // Устанавливаем знак=1 (отрицательное)

  s21_decimal result;
  s21_decimal expected_result = {{7, 0, 0, 0}}; // Уточните ожидаемый результат
  s21_set_scale(&expected_result, 0); // Устанавливаем scale=0
  s21_set_sign(&expected_result, 1);  // Устанавливаем знак=1

  ck_assert_int_eq(s21_truncate(decimal, &result), 0);
  ck_assert_int_eq(s21_is_equal(result, expected_result), 1);
}
END_TEST

START_TEST(s21_truncate_3) {
  s21_decimal decimal = {{7, 0, 0, 0}};
  s21_set_scale(&decimal, 1); // Устанавливаем scale=1 (0.7)
  s21_set_sign(&decimal, 1);  // Устанавливаем знак=1

  s21_decimal result;
  s21_decimal expected_result = {{0, 0, 0, 0}}; // truncate(-0.7) = 0
  s21_set_scale(&expected_result, 0); // Устанавливаем scale=0
  s21_set_sign(&expected_result, 0); // Устанавливаем знак=0 (0 без знака)

  ck_assert_int_eq(s21_truncate(decimal, &result), 0);
  ck_assert_int_eq(s21_is_equal(result, expected_result), 1);
}
END_TEST

START_TEST(s21_truncate_4) {
  s21_decimal decimal = {{7234, 0, 0, 0}};
  s21_set_scale(&decimal, 3); // Устанавливаем scale=3 (7.234)
  s21_set_sign(&decimal, 1);  // Устанавливаем знак=1 (-7.234)

  s21_decimal result;
  s21_decimal expected_result = {{7, 0, 0, 0}}; // truncate(-7.234) = -7
  s21_set_scale(&expected_result, 0); // Устанавливаем scale=0
  s21_set_sign(&expected_result, 1);  // Устанавливаем знак=1

  ck_assert_int_eq(s21_truncate(decimal, &result), 0);
  ck_assert_int_eq(s21_is_equal(result, expected_result), 1);
}
END_TEST

START_TEST(s21_truncate_5) {
  s21_decimal decimal = {{1, 0, 0, 0}};
  s21_set_scale(&decimal, 2); // Устанавливаем scale=2 (0.01)
  s21_set_sign(&decimal, 0);  // Устанавливаем знак=0

  s21_decimal result;
  s21_decimal expected_result = {{0, 0, 0, 0}}; // truncate(0.01) = 0
  s21_set_scale(&expected_result, 0); // Устанавливаем scale=0
  s21_set_sign(&expected_result, 0);  // Устанавливаем знак=0

  ck_assert_int_eq(s21_truncate(decimal, &result), 0);
  ck_assert_int_eq(s21_is_equal(result, expected_result), 1);
}
END_TEST

START_TEST(s21_negate_1) {
  s21_decimal decimal = {{1, 1, 1, 0}};
  s21_set_scale(&decimal, 28); // Правильно: устанавливаем scale=28
  s21_set_sign(&decimal, 0); // Устанавливаем знак=0 (положительное)

  s21_decimal result;
  s21_decimal expected_result = {{1, 1, 1, 0}};
  s21_set_scale(&expected_result, 28); // Устанавливаем scale=28
  s21_set_sign(&expected_result, 1); // Устанавливаем знак=1 (отрицательное)

  ck_assert_int_eq(s21_negate(decimal, &result), 0);
  ck_assert_int_eq(s21_is_equal(result, expected_result), 1);
}
END_TEST

START_TEST(s21_negate_2) {
  s21_decimal decimal = {{5, 5, 5, 0}};
  s21_set_sign(&decimal, 1);  // Устанавливаем знак=1
  s21_set_scale(&decimal, 0); // Явно устанавливаем scale=0

  s21_decimal result;
  s21_decimal expected_result = {{5, 5, 5, 0}};
  s21_set_sign(&expected_result, 0); // Устанавливаем знак=0
  s21_set_scale(&expected_result, 0); // Явно устанавливаем scale=0

  ck_assert_int_eq(s21_negate(decimal, &result), 0);
  ck_assert_int_eq(s21_is_equal(result, expected_result), 1);
}
END_TEST

START_TEST(s21_negate_3) {
  s21_decimal decimal = {{7, 0, 0, 0}};
  s21_set_scale(&decimal, 5); // Устанавливаем scale=5
  s21_set_sign(&decimal, 0);  // Устанавливаем знак=0

  s21_decimal result;
  s21_decimal expected_result = {{7, 0, 0, 0}};
  s21_set_scale(&expected_result, 5); // Устанавливаем scale=5
  s21_set_sign(&expected_result, 1);  // Устанавливаем знак=1

  ck_assert_int_eq(s21_negate(decimal, &result), 0);
  ck_assert_int_eq(s21_is_equal(result, expected_result), 1);
}
END_TEST

START_TEST(s21_negate_4) {
  s21_decimal decimal = {{0, 0, 0, 0}};
  s21_set_sign(&decimal, 0);  // Устанавливаем знак=0
  s21_set_scale(&decimal, 0); // Устанавливаем scale=0

  s21_decimal result;
  s21_decimal expected_result = {{0, 0, 0, 0}};
  s21_set_sign(&expected_result, 1);  // Устанавливаем знак=1
  s21_set_scale(&expected_result, 0); // Устанавливаем scale=0

  ck_assert_int_eq(s21_negate(decimal, &result), 0);
  ck_assert_int_eq(s21_is_equal(result, expected_result), 1);
}
END_TEST

START_TEST(s21_negate_5) {
  s21_decimal decimal = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}};
  s21_set_scale(&decimal, 28); // Устанавливаем scale=28
  s21_set_sign(&decimal, 0);   // Устанавливаем знак=0

  s21_decimal result;
  s21_decimal expected_result = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}};
  s21_set_scale(&expected_result, 28); // Устанавливаем scale=28
  s21_set_sign(&expected_result, 1);   // Устанавливаем знак=1

  ck_assert_int_eq(s21_negate(decimal, &result), 0);
  ck_assert_int_eq(s21_is_equal(result, expected_result), 1);
}
END_TEST

Suite *other_suite(void) {
  Suite *s = suite_create("other");
  TCase *tc = tcase_create("core");

  /* Тесты из первого файла */
  tcase_add_test(tc, negate_positive);
  tcase_add_test(tc, negate_negative);
  tcase_add_test(tc, negate_zero);
  tcase_add_test(tc, negate_int_min);
  tcase_add_test(tc, truncate_positive);
  tcase_add_test(tc, truncate_negative);
  tcase_add_test(tc, truncate_integer);
  tcase_add_test(tc, truncate_fractional_scale);
  tcase_add_test(tc, floor_positive);
  tcase_add_test(tc, floor_negative);
  tcase_add_test(tc, floor_integer);
  tcase_add_test(tc, floor_fractional_scale);
  tcase_add_test(tc, round_down);
  tcase_add_test(tc, round_half_up);
  tcase_add_test(tc, round_negative_half);
  tcase_add_test(tc, round_fractional_half);

  /* Тесты из второго файла */
  tcase_add_test(tc, other_null_and_invalid);
  tcase_add_test(tc, negate_zero_and_nonzero);
  tcase_add_test(tc, truncate_basic);
  tcase_add_test(tc, floor_scale0_returns_same);
  tcase_add_test(tc, floor_negative_with_fraction);
  tcase_add_test(tc, round_scale0_returns_same);

  /* Тесты из третьего файла */
  tcase_add_test(tc, s21_floor_1);
  tcase_add_test(tc, s21_floor_2);
  tcase_add_test(tc, s21_floor_3);
  tcase_add_test(tc, s21_round_1);
  tcase_add_test(tc, s21_round_2);
  tcase_add_test(tc, s21_round_3);
  tcase_add_test(tc, s21_round_4);
  tcase_add_test(tc, s21_round_5);
  tcase_add_test(tc, s21_round_6);
  tcase_add_test(tc, s21_round_7);
  tcase_add_test(tc, s21_round_8);
  tcase_add_test(tc, s21_round_9);
  tcase_add_test(tc, s21_round_10);
  tcase_add_test(tc, s21_truncate_1);
  tcase_add_test(tc, s21_truncate_2);
  tcase_add_test(tc, s21_truncate_3);
  tcase_add_test(tc, s21_truncate_4);
  tcase_add_test(tc, s21_truncate_5);
  tcase_add_test(tc, s21_negate_1);
  tcase_add_test(tc, s21_negate_2);
  tcase_add_test(tc, s21_negate_3);
  tcase_add_test(tc, s21_negate_4);
  tcase_add_test(tc, s21_negate_5);

  suite_add_tcase(s, tc);
  return s;
}