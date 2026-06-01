#include "test.h"

START_TEST(is_less_equal_positive) {
  s21_decimal a, b;
  s21_from_int_to_decimal(5, &a);
  s21_from_int_to_decimal(5, &b);
  ck_assert_int_eq(s21_is_less(a, b), 0);
}
END_TEST

START_TEST(is_less_positive) {
  s21_decimal a, b;
  s21_from_int_to_decimal(3, &a);
  s21_from_int_to_decimal(7, &b);
  ck_assert_int_eq(s21_is_less(a, b), 1);
}
END_TEST

START_TEST(is_less_positive_false) {
  s21_decimal a, b;
  s21_from_int_to_decimal(10, &a);
  s21_from_int_to_decimal(2, &b);
  ck_assert_int_eq(s21_is_less(a, b), 0);
}
END_TEST

START_TEST(is_less_negative) {
  s21_decimal a, b;
  s21_from_int_to_decimal(-5, &a);
  s21_from_int_to_decimal(-2, &b);
  ck_assert_int_eq(s21_is_less(a, b), 1);
}
END_TEST

START_TEST(is_less_negative_positive) {
  s21_decimal a, b;
  s21_from_int_to_decimal(-1, &a);
  s21_from_int_to_decimal(1, &b);
  ck_assert_int_eq(s21_is_less(a, b), 1);
}
END_TEST

START_TEST(is_less_zero_positive) {
  s21_decimal a, b;
  s21_from_int_to_decimal(0, &a);
  s21_from_int_to_decimal(1, &b);
  ck_assert_int_eq(s21_is_less(a, b), 1);
}
END_TEST

START_TEST(is_less_positive_zero) {
  s21_decimal a, b;
  s21_from_int_to_decimal(1, &a);
  s21_from_int_to_decimal(0, &b);
  ck_assert_int_eq(s21_is_less(a, b), 0);
}
END_TEST

START_TEST(is_less_zero_negative) {
  s21_decimal a, b;
  s21_from_int_to_decimal(0, &a);
  s21_from_int_to_decimal(-1, &b);
  ck_assert_int_eq(s21_is_less(a, b), 0);
}
END_TEST

START_TEST(is_less_negative_zero) {
  s21_decimal a, b;
  s21_from_int_to_decimal(-1, &a);
  s21_from_int_to_decimal(0, &b);
  ck_assert_int_eq(s21_is_less(a, b), 1);
}
END_TEST

START_TEST(is_equal_positive) {
  s21_decimal a, b;
  s21_from_int_to_decimal(5, &a);
  s21_from_int_to_decimal(5, &b);
  ck_assert_int_eq(s21_is_equal(a, b), 1);
}
END_TEST

START_TEST(is_equal_diff_positive) {
  s21_decimal a, b;
  s21_from_int_to_decimal(3, &a);
  s21_from_int_to_decimal(7, &b);
  ck_assert_int_eq(s21_is_equal(a, b), 0);
}
END_TEST

START_TEST(is_equal_positive_negative) {
  s21_decimal a, b;
  s21_from_int_to_decimal(5, &a);
  s21_from_int_to_decimal(-5, &b);
  ck_assert_int_eq(s21_is_equal(a, b), 0);
}
END_TEST

START_TEST(is_equal_negatives) {
  s21_decimal a, b;
  s21_from_int_to_decimal(-10, &a);
  s21_from_int_to_decimal(-10, &b);
  ck_assert_int_eq(s21_is_equal(a, b), 1);
}
END_TEST

START_TEST(is_equal_diff_negatives) {
  s21_decimal a, b;
  s21_from_int_to_decimal(-5, &a);
  s21_from_int_to_decimal(-1, &b);
  ck_assert_int_eq(s21_is_equal(a, b), 0);
}
END_TEST

START_TEST(is_equal_zeros) {
  s21_decimal a, b;
  s21_from_int_to_decimal(0, &a);
  s21_from_int_to_decimal(0, &b);
  ck_assert_int_eq(s21_is_equal(a, b), 1);
}
END_TEST

START_TEST(is_equal_minus_zeros) {
  s21_decimal a, b;
  s21_from_int_to_decimal(0, &a);
  s21_from_int_to_decimal(-0, &b);
  ck_assert_int_eq(s21_is_equal(a, b), 1);
}
END_TEST

START_TEST(is_greater_equal_positive) {
  s21_decimal a, b;
  s21_from_int_to_decimal(5, &a);
  s21_from_int_to_decimal(5, &b);
  ck_assert_int_eq(s21_is_greater(a, b), 0);
}
END_TEST

START_TEST(is_greater_positive) {
  s21_decimal a, b;
  s21_from_int_to_decimal(10, &a);
  s21_from_int_to_decimal(5, &b);
  ck_assert_int_eq(s21_is_greater(a, b), 1);
}
END_TEST

START_TEST(is_greater_positive_false) {
  s21_decimal a, b;
  s21_from_int_to_decimal(5, &a);
  s21_from_int_to_decimal(10, &b);
  ck_assert_int_eq(s21_is_greater(a, b), 0);
}
END_TEST

START_TEST(is_greater_negative) {
  s21_decimal a, b;
  s21_from_int_to_decimal(-5, &a);
  s21_from_int_to_decimal(-10, &b);
  ck_assert_int_eq(s21_is_greater(a, b), 1);
}
END_TEST

START_TEST(is_greater_negative_false) {
  s21_decimal a, b;
  s21_from_int_to_decimal(-10, &a);
  s21_from_int_to_decimal(-5, &b);
  ck_assert_int_eq(s21_is_greater(a, b), 0);
}
END_TEST

START_TEST(is_greater_positive_negative) {
  s21_decimal a, b;
  s21_from_int_to_decimal(5, &a);
  s21_from_int_to_decimal(-5, &b);
  ck_assert_int_eq(s21_is_greater(a, b), 1);
}
END_TEST

START_TEST(is_greater_zero_negative) {
  s21_decimal a, b;
  s21_from_int_to_decimal(0, &a);
  s21_from_int_to_decimal(-5, &b);
  ck_assert_int_eq(s21_is_greater(a, b), 1);
}
END_TEST

START_TEST(is_greater_positive_zero) {
  s21_decimal a, b;
  s21_from_int_to_decimal(5, &a);
  s21_from_int_to_decimal(0, &b);
  ck_assert_int_eq(s21_is_greater(a, b), 1);
}
END_TEST

START_TEST(is_greater_zeros) {
  s21_decimal a, b;
  s21_from_int_to_decimal(0, &a);
  s21_from_int_to_decimal(0, &b);
  ck_assert_int_eq(s21_is_greater(a, b), 0);
}
END_TEST

START_TEST(is_not_equal_equal) {
  s21_decimal a, b;
  s21_from_int_to_decimal(5, &a);
  s21_from_int_to_decimal(5, &b);
  ck_assert_int_eq(s21_is_not_equal(a, b), 0);
}
END_TEST

START_TEST(is_not_equal_diff) {
  s21_decimal a, b;
  s21_from_int_to_decimal(5, &a);
  s21_from_int_to_decimal(7, &b);
  ck_assert_int_eq(s21_is_not_equal(a, b), 1);
}
END_TEST

START_TEST(is_not_equal_negative) {
  s21_decimal a, b;
  s21_from_int_to_decimal(-5, &a);
  s21_from_int_to_decimal(5, &b);
  ck_assert_int_eq(s21_is_not_equal(a, b), 1);
}
END_TEST

START_TEST(is_less_or_equal_equal) {
  s21_decimal a, b;
  s21_from_int_to_decimal(5, &a);
  s21_from_int_to_decimal(5, &b);
  ck_assert_int_eq(s21_is_less_or_equal(a, b), 1);
}
END_TEST

START_TEST(is_less_or_equal_less) {
  s21_decimal a, b;
  s21_from_int_to_decimal(3, &a);
  s21_from_int_to_decimal(7, &b);
  ck_assert_int_eq(s21_is_less_or_equal(a, b), 1);
}
END_TEST

START_TEST(is_less_or_equal_false) {
  s21_decimal a, b;
  s21_from_int_to_decimal(10, &a);
  s21_from_int_to_decimal(2, &b);
  ck_assert_int_eq(s21_is_less_or_equal(a, b), 0);
}
END_TEST

START_TEST(is_greater_or_equal_equal) {
  s21_decimal a, b;
  s21_from_int_to_decimal(5, &a);
  s21_from_int_to_decimal(5, &b);
  ck_assert_int_eq(s21_is_greater_or_equal(a, b), 1);
}
END_TEST

START_TEST(is_greater_or_equal_greater) {
  s21_decimal a, b;
  s21_from_int_to_decimal(10, &a);
  s21_from_int_to_decimal(5, &b);
  ck_assert_int_eq(s21_is_greater_or_equal(a, b), 1);
}
END_TEST

START_TEST(is_greater_or_equal_false) {
  s21_decimal a, b;
  s21_from_int_to_decimal(2, &a);
  s21_from_int_to_decimal(10, &b);
  ck_assert_int_eq(s21_is_greater_or_equal(a, b), 0);
}
END_TEST

START_TEST(is_equal_with_scale) {
  s21_decimal a, b;
  s21_from_float_to_decimal(1.0f, &a);
  s21_from_float_to_decimal(1.00f, &b);
  ck_assert_int_eq(s21_is_equal(a, b), 1);
}
END_TEST

START_TEST(is_less_with_fraction) {
  s21_decimal a, b;
  s21_from_float_to_decimal(1.23f, &a);
  s21_from_float_to_decimal(1.24f, &b);
  ck_assert_int_eq(s21_is_less(a, b), 1);
}
END_TEST

START_TEST(is_greater_with_fraction) {
  s21_decimal a, b;
  s21_from_float_to_decimal(2.01f, &a);
  s21_from_float_to_decimal(2.001f, &b);
  ck_assert_int_eq(s21_is_greater(a, b), 1);
}
END_TEST

START_TEST(is_less_invalid_decimal_1) {
  s21_decimal a = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF}}; // invalid
  s21_decimal b;
  s21_from_int_to_decimal(5, &b);
  ck_assert_int_eq(s21_is_less(a, b), FALSE);
}
END_TEST

START_TEST(is_less_invalid_decimal_2) {
  s21_decimal a;
  s21_decimal b = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF}}; // invalid
  s21_from_int_to_decimal(5, &a);
  ck_assert_int_eq(s21_is_less(a, b), FALSE);
}
END_TEST

START_TEST(is_equal_invalid_decimal_1) {
  s21_decimal a = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF}}; // invalid
  s21_decimal b;
  s21_from_int_to_decimal(5, &b);
  ck_assert_int_eq(s21_is_equal(a, b), FALSE);
}
END_TEST

START_TEST(is_equal_invalid_decimal_2) {
  s21_decimal a;
  s21_decimal b = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF}}; // invalid
  s21_from_int_to_decimal(5, &a);
  ck_assert_int_eq(s21_is_equal(a, b), FALSE);
}
END_TEST

START_TEST(is_less_large_scale) {
  s21_decimal a, b;
  s21_reset_to_zero(&a);
  s21_reset_to_zero(&b);
  // 1.5
  a.bits[0] = 15;
  s21_set_scale(&a, 1);

  // 1.500
  b.bits[0] = 1500;
  s21_set_scale(&b, 3);

  ck_assert_int_eq(s21_is_less(a, b), FALSE);
  ck_assert_int_eq(s21_is_equal(a, b), TRUE);
}
END_TEST

START_TEST(is_less_different_scales) {
  s21_decimal a, b;
  s21_reset_to_zero(&a);
  s21_reset_to_zero(&b);
  a.bits[0] = 123;
  s21_set_scale(&a, 2); // scale = 2
  // 1.234
  b.bits[0] = 1234;
  s21_set_scale(&b, 3); // scale = 3
  ck_assert_int_eq(s21_is_less(a, b), TRUE);
}
END_TEST

START_TEST(is_greater_different_scales) {
  s21_decimal a, b;
  s21_reset_to_zero(&a);
  s21_reset_to_zero(&b);
  // 1.235
  a.bits[0] = 1235;
  s21_set_scale(&a, 3); // scale = 3
  // 1.24
  b.bits[0] = 124;
  s21_set_scale(&b, 2); // scale = 2
  ck_assert_int_eq(s21_is_greater(a, b), FALSE);
}
END_TEST

START_TEST(is_less_max_values) {
  s21_decimal a, b;
  // Максимальный положительный
  a.bits[0] = 0xFFFFFFFF;
  a.bits[1] = 0xFFFFFFFF;
  a.bits[2] = 0xFFFFFFFF;
  a.bits[3] = 0;
  // Чуть меньше
  b.bits[0] = 0xFFFFFFFE;
  b.bits[1] = 0xFFFFFFFF;
  b.bits[2] = 0xFFFFFFFF;
  b.bits[3] = 0;
  ck_assert_int_eq(s21_is_less(b, a), TRUE);
  ck_assert_int_eq(s21_is_less(a, b), FALSE);
}
END_TEST

START_TEST(is_less_min_values) {
  s21_decimal a, b;
  // Минимальный отрицательный (самый отрицательный)
  a.bits[0] = 0xFFFFFFFF;
  a.bits[1] = 0xFFFFFFFF;
  a.bits[2] = 0xFFFFFFFF;
  a.bits[3] = 0x80000000; // отрицательный
  // Чуть больше (меньше по модулю)
  b.bits[0] = 0xFFFFFFFE;
  b.bits[1] = 0xFFFFFFFF;
  b.bits[2] = 0xFFFFFFFF;
  b.bits[3] = 0x80000000;
  ck_assert_int_eq(s21_is_less(a, b), TRUE); // -max < -max+1
  ck_assert_int_eq(s21_is_less(b, a), FALSE);
}
END_TEST

START_TEST(is_less_mantissa_equal_but_different_sign) {
  s21_decimal a, b;
  s21_from_int_to_decimal(123, &a);
  s21_from_int_to_decimal(123, &b);
  s21_set_sign(&b, 1); // делаем b отрицательным
  ck_assert_int_eq(s21_is_less(a, b), FALSE);
  ck_assert_int_eq(s21_is_less(b, a), TRUE);
}
END_TEST

START_TEST(is_equal_large_numbers) {
  s21_decimal a, b;
  // Большое число 79228162514264337593543950335
  a.bits[0] = 0xFFFFFFFF;
  a.bits[1] = 0xFFFFFFFF;
  a.bits[2] = 0xFFFFFFFF;
  a.bits[3] = 0;
  // То же число
  b.bits[0] = 0xFFFFFFFF;
  b.bits[1] = 0xFFFFFFFF;
  b.bits[2] = 0xFFFFFFFF;
  b.bits[3] = 0;
  ck_assert_int_eq(s21_is_equal(a, b), TRUE);

  // Меняем один бит
  b.bits[0] = 0xFFFFFFFE;
  ck_assert_int_eq(s21_is_equal(a, b), FALSE);
}
END_TEST

START_TEST(is_less_or_equal_edge) {
  s21_decimal a, b;
  // Тестируем граничное условие <=
  s21_from_int_to_decimal(100, &a);
  s21_from_int_to_decimal(100, &b);
  ck_assert_int_eq(s21_is_less_or_equal(a, b), TRUE);

  s21_from_int_to_decimal(99, &a);
  ck_assert_int_eq(s21_is_less_or_equal(a, b), TRUE);

  s21_from_int_to_decimal(101, &a);
  ck_assert_int_eq(s21_is_less_or_equal(a, b), FALSE);
}
END_TEST

START_TEST(is_greater_or_equal_edge) {
  s21_decimal a, b;
  // Тестируем граничное условие >=
  s21_from_int_to_decimal(100, &a);
  s21_from_int_to_decimal(100, &b);
  ck_assert_int_eq(s21_is_greater_or_equal(a, b), TRUE);

  s21_from_int_to_decimal(101, &a);
  ck_assert_int_eq(s21_is_greater_or_equal(a, b), TRUE);

  s21_from_int_to_decimal(99, &a);
  ck_assert_int_eq(s21_is_greater_or_equal(a, b), FALSE);
}
END_TEST

START_TEST(is_not_equal_comprehensive) {
  s21_decimal a, b;
  s21_from_int_to_decimal(0, &a);
  s21_from_int_to_decimal(0, &b);
  ck_assert_int_eq(s21_is_not_equal(a, b), FALSE);

  s21_from_int_to_decimal(1, &b);
  ck_assert_int_eq(s21_is_not_equal(a, b), TRUE);

  s21_from_int_to_decimal(-1, &b);
  ck_assert_int_eq(s21_is_not_equal(a, b), TRUE);
}
END_TEST

START_TEST(is_less_with_overflow_scale) {
  s21_decimal a, b;
  s21_reset_to_zero(&a);
  s21_reset_to_zero(&b);
  // Числа с очень большим scale, которые могут вызвать проблемы при
  // нормализации
  a.bits[0] = 123456789;
  s21_set_scale(&a, 28); // scale = 28
  b.bits[0] = 123456789;
  s21_set_scale(&b, 28); // scale = 28
  ck_assert_int_eq(s21_is_less(a, b), FALSE);
  ck_assert_int_eq(s21_is_equal(a, b), TRUE);
}
END_TEST

START_TEST(is_equal_with_extreme_scales) {
  s21_decimal a, b;
  s21_reset_to_zero(&a);
  s21_reset_to_zero(&b);
  // 0.0000000000000000000000000001
  a.bits[0] = 1;
  s21_set_scale(&a, 28); // scale = 28
  // 0.0000000000000000000000000010
  b.bits[0] = 10;
  s21_set_scale(&b, 28); // scale = 28
  ck_assert_int_eq(s21_is_equal(a, b), FALSE);
  ck_assert_int_eq(s21_is_less(a, b), TRUE);
}
END_TEST

START_TEST(is_less_overflow_normalization) {
  s21_decimal a, b;

  s21_reset_to_zero(&a);
  s21_reset_to_zero(&b);

  a.bits[0] = 0xFFFFFFFF;
  a.bits[1] = 0xFFFFFFFF;
  a.bits[2] = 0xFFFFFFFF;
  s21_set_scale(&a, 28);
  s21_set_sign(&a, 0);

  b.bits[0] = 1;
  s21_set_scale(&b, 27);
  s21_set_sign(&b, 0);

  // a ≈ 7.92, b = 0.000000000000000000000000001
  // a > b, поэтому is_less должен быть FALSE
  ck_assert_int_eq(s21_is_less(a, b), FALSE);
}
END_TEST

START_TEST(is_equal_overflow_normalization) {
  s21_decimal a, b;

  a.bits[0] = 0xFFFFFFFF;
  a.bits[1] = 0xFFFFFFFF;
  a.bits[2] = 0xFFFFFFFF;
  s21_set_scale(&a, 28);

  b.bits[0] = 0xFFFFFFFF;
  b.bits[1] = 0xFFFFFFFF;
  b.bits[2] = 0xFFFFFFFF;
  s21_set_scale(&b, 27);

  ck_assert_int_eq(s21_is_equal(a, b), FALSE);
}
END_TEST

// ========== ТЕСТЫ ДЛЯ ПОКРЫТИЯ СЛУЧАЕВ НЕУДАЧНОЙ НОРМАЛИЗАЦИИ ==========

START_TEST(is_less_normalization_fails_scale1_less) {
  s21_decimal a, b;

  // Число, которое нельзя уменьшить (уже с масштабом 0)
  a.bits[0] = 0xFFFFFFFF;
  a.bits[1] = 0xFFFFFFFF;
  a.bits[2] = 0xFFFFFFFF;
  s21_set_scale(&a, 0);
  s21_set_sign(&a, 0);

  // Число, которое нельзя увеличить (уже с масштабом 28)
  b.bits[0] = 0xFFFFFFFF;
  b.bits[1] = 0xFFFFFFFF;
  b.bits[2] = 0xFFFFFFFF;
  s21_set_scale(&b, 28);
  s21_set_sign(&b, 0);

  // При нормализации:
  // - Не можем увеличить scale a (переполнение)
  // - Не можем уменьшить scale b (так как scale2 > 0, но это все равно
  // делается!) Но функция уменьшит scale b, поэтому числа станут сравнимы
  ck_assert_int_eq(s21_is_less(a, b), FALSE); // a > b
}
END_TEST

START_TEST(is_less_normalization_fails_scale1_greater) {
  s21_decimal a, b;

  // Большое число с масштабом 0
  a.bits[0] = 0xFFFFFFFF;
  a.bits[1] = 0xFFFFFFFF;
  a.bits[2] = 0xFFFFFFFF;
  s21_set_scale(&a, 0);
  s21_set_sign(&a, 0);

  // Максимальное число с масштабом 28
  b.bits[0] = 0xFFFFFFFF;
  b.bits[1] = 0xFFFFFFFF;
  b.bits[2] = 0xFFFFFFFF;
  s21_set_scale(&b, 28);
  s21_set_sign(&b, 0);

  // При нормализации:
  // - Не можем увеличить scale a (переполнение)
  // - Не можем уменьшить scale b (так как scale2 > scale1)
  // Должен сработать блок с прямой проверкой
  ck_assert_int_eq(s21_is_less(a, b),
                   FALSE); // a > b, так как a имеет меньший масштаб (больше)
}
END_TEST

START_TEST(is_less_normalization_fails_negative) {
  s21_decimal a, b;

  // Максимальное отрицательное число с масштабом 28
  a.bits[0] = 0xFFFFFFFF;
  a.bits[1] = 0xFFFFFFFF;
  a.bits[2] = 0xFFFFFFFF;
  s21_set_scale(&a, 28);
  s21_set_sign(&a, 1);

  // Максимальное положительное число с масштабом 0
  b.bits[0] = 0xFFFFFFFF;
  b.bits[1] = 0xFFFFFFFF;
  b.bits[2] = 0xFFFFFFFF;
  s21_set_scale(&b, 0);
  s21_set_sign(&b, 0);

  // Отрицательное всегда меньше положительного, даже если нормализация не
  // удалась
  ck_assert_int_eq(s21_is_less(a, b), TRUE);
}
END_TEST

START_TEST(is_less_normalization_fails_equal_scale) {
  s21_decimal a, b;

  // Два числа с одинаковым масштабом, но разными мантиссами
  a.bits[0] = 0xFFFFFFFF;
  a.bits[1] = 0xFFFFFFFF;
  a.bits[2] = 0xFFFFFFFF;
  s21_set_scale(&a, 0);
  s21_set_sign(&a, 0);

  b.bits[0] = 0xFFFFFFFE;
  b.bits[1] = 0xFFFFFFFF;
  b.bits[2] = 0xFFFFFFFF;
  s21_set_scale(&b, 0);
  s21_set_sign(&b, 0);

  // При нормализации масштабы равны, но нормализация может не понадобиться
  // Проверяем прямое сравнение мантисс
  ck_assert_int_eq(s21_is_less(a, b), FALSE); // a > b
  ck_assert_int_eq(s21_is_less(b, a), TRUE);  // b < a
}
END_TEST

START_TEST(is_less_normalization_fails_equal_mantissa) {
  s21_decimal a, b;

  // Одинаковые мантиссы, но разные масштабы
  a.bits[0] = 0xFFFFFFFF;
  a.bits[1] = 0xFFFFFFFF;
  a.bits[2] = 0xFFFFFFFF;
  s21_set_scale(&a, 28);
  s21_set_sign(&a, 0);

  b.bits[0] = 0xFFFFFFFF;
  b.bits[1] = 0xFFFFFFFF;
  b.bits[2] = 0xFFFFFFFF;
  s21_set_scale(&b, 27);
  s21_set_sign(&b, 0);

  // При неудачной нормализации, если мантиссы равны, должны вернуть FALSE
  ck_assert_int_eq(s21_is_less(a, b), FALSE);
  ck_assert_int_eq(s21_is_less(b, a), FALSE);
}
END_TEST

// ========== ТЕСТЫ ДЛЯ ПОКРЫТИЯ ВСЕХ ВЕТВЕЙ ПРЯМОГО СРАВНЕНИЯ ==========

START_TEST(is_less_normalization_fails_scale1_less_diff_mantissa) {
  s21_decimal a, b;

  // Число a: максимальное с масштабом 0
  a.bits[0] = 0xFFFFFFFF;
  a.bits[1] = 0xFFFFFFFF;
  a.bits[2] = 0xFFFFFFFF;
  s21_set_scale(&a, 0);
  s21_set_sign(&a, 0);

  // Число b: чуть меньше с масштабом 28
  b.bits[0] = 0xFFFFFFFE;
  b.bits[1] = 0xFFFFFFFF;
  b.bits[2] = 0xFFFFFFFF;
  s21_set_scale(&b, 28);
  s21_set_sign(&b, 0);

  // При нормализации:
  // - Не можем увеличить scale a (переполнение)
  // - Можем уменьшить scale b (деление на 10)
  // Должен сработать блок с прямой проверкой
  // scale1 (0) < scale2 (28), поэтому a > b (меньший масштаб = больший вес)
  ck_assert_int_eq(s21_is_less(a, b), FALSE);
}
END_TEST

START_TEST(is_less_normalization_fails_scale1_greater_diff_mantissa) {
  s21_decimal a, b;

  // Число a: максимальное с масштабом 28
  a.bits[0] = 0xFFFFFFFF;
  a.bits[1] = 0xFFFFFFFF;
  a.bits[2] = 0xFFFFFFFF;
  s21_set_scale(&a, 28);
  s21_set_sign(&a, 0);

  // Число b: чуть меньше с масштабом 0
  b.bits[0] = 0xFFFFFFFE;
  b.bits[1] = 0xFFFFFFFF;
  b.bits[2] = 0xFFFFFFFF;
  s21_set_scale(&b, 0);
  s21_set_sign(&b, 0);

  // scale1 (28) > scale2 (0), поэтому a < b (больший масштаб = меньший вес)
  ck_assert_int_eq(s21_is_less(a, b), TRUE);
}
END_TEST

START_TEST(is_less_normalization_fails_equal_scale_diff_mantissa) {
  s21_decimal a, b;

  // Оба числа с масштабом 0, но разные мантиссы
  a.bits[0] = 0xFFFFFFFF;
  a.bits[1] = 0xFFFFFFFF;
  a.bits[2] = 0xFFFFFFFF;
  s21_set_scale(&a, 0);
  s21_set_sign(&a, 0);

  b.bits[0] = 0xFFFFFFFE;
  b.bits[1] = 0xFFFFFFFF;
  b.bits[2] = 0xFFFFFFFF;
  s21_set_scale(&b, 0);
  s21_set_sign(&b, 0);

  // Масштабы равны, сравниваем мантиссы напрямую
  ck_assert_int_eq(s21_is_less(a, b), FALSE); // a > b
  ck_assert_int_eq(s21_is_less(b, a), TRUE);  // b < a
}
END_TEST

START_TEST(is_less_normalization_fails_negative_scale1_less) {
  s21_decimal a, b;

  // Отрицательное число a с масштабом 0 (максимальное по модулю)
  a.bits[0] = 0xFFFFFFFF;
  a.bits[1] = 0xFFFFFFFF;
  a.bits[2] = 0xFFFFFFFF;
  s21_set_scale(&a, 0);
  s21_set_sign(&a, 1);

  // Отрицательное число b чуть меньше по модулю с масштабом 28
  b.bits[0] = 0xFFFFFFFE;
  b.bits[1] = 0xFFFFFFFF;
  b.bits[2] = 0xFFFFFFFF;
  s21_set_scale(&b, 28);
  s21_set_sign(&b, 1);

  // Для отрицательных чисел: чем меньше модуль, тем число больше
  // a имеет модуль больше (0xFFFFFFFF...), b имеет модуль меньше
  // (0xFFFFFFFE...) Поэтому a должно быть МЕНЬШЕ b (так как -100 < -99)
  ck_assert_int_eq(s21_is_less(a, b), TRUE);
}
END_TEST

START_TEST(is_less_normalization_fails_negative_scale1_greater) {
  s21_decimal a, b;

  // Отрицательное число a с масштабом 28 (меньший модуль)
  a.bits[0] = 0xFFFFFFFE;
  a.bits[1] = 0xFFFFFFFF;
  a.bits[2] = 0xFFFFFFFF;
  s21_set_scale(&a, 28);
  s21_set_sign(&a, 1);

  // Отрицательное число b с масштабом 0 (больший модуль)
  b.bits[0] = 0xFFFFFFFF;
  b.bits[1] = 0xFFFFFFFF;
  b.bits[2] = 0xFFFFFFFF;
  s21_set_scale(&b, 0);
  s21_set_sign(&b, 1);

  // Для отрицательных чисел:
  ck_assert_int_eq(s21_is_less(a, b), FALSE);
}
END_TEST

// ========== ТЕСТЫ ДЛЯ ПОКРЫТИЯ НЕПОКРЫТЫХ СТРОК ==========

START_TEST(is_less_normalization_fails_equal_scale_diff_mantissa_positive) {
  s21_decimal a, b;

  // Оба числа положительные, масштаб 0, но разные мантиссы
  // Создаем числа, которые нельзя нормализовать из-за переполнения
  a.bits[0] = 0xFFFFFFFF;
  a.bits[1] = 0xFFFFFFFF;
  a.bits[2] = 0xFFFFFFFF;
  s21_set_scale(&a, 0);
  s21_set_sign(&a, 0);

  b.bits[0] = 0xFFFFFFFE;
  b.bits[1] = 0xFFFFFFFF;
  b.bits[2] = 0xFFFFFFFF;
  s21_set_scale(&b, 0);
  s21_set_sign(&b, 0);

  ck_assert_int_eq(s21_is_less(a, b),
                   FALSE); // a > b, так как a.bits[0] > b.bits[0]
}
END_TEST

START_TEST(is_less_normalization_fails_equal_scale_diff_mantissa_negative) {
  s21_decimal a, b;

  // Оба числа отрицательные, масштаб 0, но разные мантиссы
  a.bits[0] = 0xFFFFFFFF;
  a.bits[1] = 0xFFFFFFFF;
  a.bits[2] = 0xFFFFFFFF;
  s21_set_scale(&a, 0);
  s21_set_sign(&a, 1); // отрицательное

  b.bits[0] = 0xFFFFFFFE;
  b.bits[1] = 0xFFFFFFFF;
  b.bits[2] = 0xFFFFFFFF;
  s21_set_scale(&b, 0);
  s21_set_sign(&b, 1); // отрицательное
  ck_assert_int_eq(s21_is_less(a, b), TRUE);
}
END_TEST

START_TEST(is_less_normalization_fails_equal_scale_diff_mantissa_middle_bit) {
  s21_decimal a, b;

  // Создаем числа, где разница в среднем бите (bits[1])
  a.bits[0] = 0xFFFFFFFF;
  a.bits[1] = 0xFFFFFFFF;
  a.bits[2] = 0x0;
  s21_set_scale(&a, 0);
  s21_set_sign(&a, 0);

  b.bits[0] = 0xFFFFFFFF;
  b.bits[1] = 0xFFFFFFFE;
  b.bits[2] = 0x0;
  s21_set_scale(&b, 0);
  s21_set_sign(&b, 0);

  // Масштабы равны, сравниваем bits[1]
  ck_assert_int_eq(s21_is_less(a, b), FALSE); // a > b
  ck_assert_int_eq(s21_is_less(b, a), TRUE);  // b < a
}
END_TEST

START_TEST(is_less_normalization_fails_equal_scale_diff_mantissa_high_bit) {
  s21_decimal a, b;

  // Создаем числа, где разница в старшем бите (bits[2])
  a.bits[0] = 0xFFFFFFFF;
  a.bits[1] = 0xFFFFFFFF;
  a.bits[2] = 0x1;
  s21_set_scale(&a, 0);
  s21_set_sign(&a, 0);

  b.bits[0] = 0xFFFFFFFF;
  b.bits[1] = 0xFFFFFFFF;
  b.bits[2] = 0x0;
  s21_set_scale(&b, 0);
  s21_set_sign(&b, 0);

  // Масштабы равны, сравниваем bits[2]
  ck_assert_int_eq(s21_is_less(a, b), FALSE); // a > b
  ck_assert_int_eq(s21_is_less(b, a), TRUE);  // b < a
}
END_TEST

START_TEST(
    is_less_normalization_fails_equal_scale_diff_mantissa_negative_middle) {
  s21_decimal a, b;

  // Отрицательные числа с разницей в среднем бите
  a.bits[0] = 0xFFFFFFFF;
  a.bits[1] = 0xFFFFFFFF;
  a.bits[2] = 0x0;
  s21_set_scale(&a, 0);
  s21_set_sign(&a, 1);

  b.bits[0] = 0xFFFFFFFF;
  b.bits[1] = 0xFFFFFFFE;
  b.bits[2] = 0x0;
  s21_set_scale(&b, 0);
  s21_set_sign(&b, 1);

  // Для отрицательных: сравниваем модули
  ck_assert_int_eq(s21_is_less(a, b),
                   TRUE); // a (модуль больше) < b (модуль меньше)
  ck_assert_int_eq(s21_is_less(b, a), FALSE); // b > a
}
END_TEST

// Тест, где нормализация не удается из-за невозможности увеличить scale
START_TEST(is_less_normalization_fails_cant_increase_scale_equal_mantissa) {
  s21_decimal a, b;

  // a - максимальное число с масштабом 0 (нельзя увеличить)
  a.bits[0] = 0xFFFFFFFF;
  a.bits[1] = 0xFFFFFFFF;
  a.bits[2] = 0xFFFFFFFF;
  s21_set_scale(&a, 0);
  s21_set_sign(&a, 0);

  // b - такое же число, но с масштабом 28
  b.bits[0] = 0xFFFFFFFF;
  b.bits[1] = 0xFFFFFFFF;
  b.bits[2] = 0xFFFFFFFF;
  s21_set_scale(&b, 28);
  s21_set_sign(&b, 0);

  // scale1 < scale2, но scale1 нельзя увеличить
  // Мантиссы равны, поэтому проходим по всем i и доходим до return FALSE
  ck_assert_int_eq(s21_is_less(a, b), FALSE); // числа не равны, но a > b
}
END_TEST

// Тест для ветки с одинаковыми мантиссами после цикла
START_TEST(is_less_normalization_fails_equal_mantissa_after_loop) {
  s21_decimal a, b;

  a.bits[0] = 0xFFFFFFFF;
  a.bits[1] = 0xFFFFFFFF;
  a.bits[2] = 0xFFFFFFFF;
  s21_set_scale(&a, 28);
  s21_set_sign(&a, 0);

  b.bits[0] = 0xFFFFFFFF;
  b.bits[1] = 0xFFFFFFFF;
  b.bits[2] = 0xFFFFFFFF;
  s21_set_scale(&b, 27);
  s21_set_sign(&b, 0);

  ck_assert_int_eq(s21_is_less(a, b), FALSE);
}
END_TEST

// Тест для отрицательных чисел с одинаковыми мантиссами
START_TEST(is_less_normalization_fails_equal_mantissa_negative) {
  s21_decimal a, b;

  a.bits[0] = 0xFFFFFFFF;
  a.bits[1] = 0xFFFFFFFF;
  a.bits[2] = 0xFFFFFFFF;
  s21_set_scale(&a, 28);
  s21_set_sign(&a, 1);

  b.bits[0] = 0xFFFFFFFF;
  b.bits[1] = 0xFFFFFFFF;
  b.bits[2] = 0xFFFFFFFF;
  s21_set_scale(&b, 27);
  s21_set_sign(&b, 1);

  ck_assert_int_eq(s21_is_less(a, b), FALSE);
}
END_TEST

START_TEST(is_less_normalization_fails_equal_scale_diff_mantissa_exact) {
  s21_decimal a, b;

  a.bits[0] = 0xFFFFFFFF;
  a.bits[1] = 0xFFFFFFFF;
  a.bits[2] = 0xFFFFFFFF;
  s21_set_scale(&a, 0); // масштаб 0
  s21_set_sign(&a, 0);  // положительное

  b.bits[0] = 0xFFFFFFFE; // чуть меньше в младшем бите
  b.bits[1] = 0xFFFFFFFF;
  b.bits[2] = 0xFFFFFFFF;
  s21_set_scale(&b, 0); // ТОТ ЖЕ масштаб 0
  s21_set_sign(&b, 0);  // положительное
  ck_assert_int_eq(s21_is_less(a, b), FALSE);
  ck_assert_int_eq(s21_is_less(b, a), TRUE);
}
END_TEST

Suite *comparison_suite(void) {
  Suite *s = suite_create("comparison");
  TCase *tc = tcase_create("core");

  tcase_add_test(tc, is_less_equal_positive);
  tcase_add_test(tc, is_less_positive);
  tcase_add_test(tc, is_less_positive_false);
  tcase_add_test(tc, is_less_negative);
  tcase_add_test(tc, is_less_negative_positive);
  tcase_add_test(tc, is_less_zero_positive);
  tcase_add_test(tc, is_less_positive_zero);
  tcase_add_test(tc, is_less_zero_negative);
  tcase_add_test(tc, is_less_negative_zero);
  tcase_add_test(tc, is_equal_positive);
  tcase_add_test(tc, is_equal_diff_positive);
  tcase_add_test(tc, is_equal_positive_negative);
  tcase_add_test(tc, is_equal_negatives);
  tcase_add_test(tc, is_equal_diff_negatives);
  tcase_add_test(tc, is_equal_zeros);
  tcase_add_test(tc, is_equal_minus_zeros);
  tcase_add_test(tc, is_greater_equal_positive);
  tcase_add_test(tc, is_greater_positive);
  tcase_add_test(tc, is_greater_positive_false);
  tcase_add_test(tc, is_greater_negative);
  tcase_add_test(tc, is_greater_negative_false);
  tcase_add_test(tc, is_greater_positive_negative);
  tcase_add_test(tc, is_greater_zero_negative);
  tcase_add_test(tc, is_greater_positive_zero);
  tcase_add_test(tc, is_greater_zeros);
  tcase_add_test(tc, is_not_equal_equal);
  tcase_add_test(tc, is_not_equal_diff);
  tcase_add_test(tc, is_not_equal_negative);
  tcase_add_test(tc, is_less_or_equal_equal);
  tcase_add_test(tc, is_less_or_equal_less);
  tcase_add_test(tc, is_less_or_equal_false);
  tcase_add_test(tc, is_greater_or_equal_equal);
  tcase_add_test(tc, is_greater_or_equal_greater);
  tcase_add_test(tc, is_greater_or_equal_false);
  tcase_add_test(tc, is_equal_with_scale);
  tcase_add_test(tc, is_less_with_fraction);
  tcase_add_test(tc, is_greater_with_fraction);

  tcase_add_test(tc, is_less_invalid_decimal_1);
  tcase_add_test(tc, is_less_invalid_decimal_2);
  tcase_add_test(tc, is_equal_invalid_decimal_1);
  tcase_add_test(tc, is_equal_invalid_decimal_2);
  tcase_add_test(tc, is_less_large_scale);
  tcase_add_test(tc, is_less_different_scales);
  tcase_add_test(tc, is_greater_different_scales);
  tcase_add_test(tc, is_less_max_values);
  tcase_add_test(tc, is_less_min_values);
  tcase_add_test(tc, is_less_mantissa_equal_but_different_sign);
  tcase_add_test(tc, is_equal_large_numbers);
  tcase_add_test(tc, is_less_or_equal_edge);
  tcase_add_test(tc, is_greater_or_equal_edge);
  tcase_add_test(tc, is_not_equal_comprehensive);
  tcase_add_test(tc, is_less_with_overflow_scale);
  tcase_add_test(tc, is_equal_with_extreme_scales);
  tcase_add_test(tc, is_less_overflow_normalization);
  tcase_add_test(tc, is_equal_overflow_normalization);

  tcase_add_test(tc, is_less_normalization_fails_scale1_less);
  tcase_add_test(tc, is_less_normalization_fails_scale1_greater);
  tcase_add_test(tc, is_less_normalization_fails_negative);
  tcase_add_test(tc, is_less_normalization_fails_equal_scale);
  tcase_add_test(tc, is_less_normalization_fails_equal_mantissa);

  tcase_add_test(tc, is_less_normalization_fails_scale1_less_diff_mantissa);
  tcase_add_test(tc, is_less_normalization_fails_scale1_greater_diff_mantissa);
  tcase_add_test(tc, is_less_normalization_fails_equal_scale_diff_mantissa);
  tcase_add_test(tc, is_less_normalization_fails_negative_scale1_less);
  tcase_add_test(tc, is_less_normalization_fails_negative_scale1_greater);

  tcase_add_test(
      tc, is_less_normalization_fails_equal_scale_diff_mantissa_positive);
  tcase_add_test(
      tc, is_less_normalization_fails_equal_scale_diff_mantissa_negative);
  tcase_add_test(
      tc, is_less_normalization_fails_equal_scale_diff_mantissa_middle_bit);
  tcase_add_test(
      tc, is_less_normalization_fails_equal_scale_diff_mantissa_high_bit);
  tcase_add_test(
      tc,
      is_less_normalization_fails_equal_scale_diff_mantissa_negative_middle);
  tcase_add_test(
      tc, is_less_normalization_fails_cant_increase_scale_equal_mantissa);
  tcase_add_test(tc, is_less_normalization_fails_equal_mantissa_after_loop);
  tcase_add_test(tc, is_less_normalization_fails_equal_mantissa_negative);

  tcase_add_test(tc,
                 is_less_normalization_fails_equal_scale_diff_mantissa_exact);

  suite_add_tcase(s, tc);
  return s;
}
