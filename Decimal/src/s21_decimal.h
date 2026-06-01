#ifndef S21_DECIMAL_H
#define S21_DECIMAL_H

#include <limits.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  unsigned int bits[4];
} s21_decimal;

#define S21_BIG_WORDS 7
typedef struct {
  uint32_t w[S21_BIG_WORDS];
} s21_big;

/* Коды ошибок арифметики */
#define S21_ARITH_OK 0
#define S21_ARITH_TOO_LARGE 1
#define S21_ARITH_TOO_SMALL 2
#define S21_ARITH_DIV_BY_ZERO 3

/* Операторы сравнения */
#define FALSE 0
#define TRUE 1

/* Коды ошибок конвертации */
#define S21_CONV_OK 0
#define S21_CONV_ERROR 1

/* Коды ошибок других функций */
#define S21_OTHER_OK 0
#define S21_OTHER_ERROR 1

#define S21_DECIMAL_SIGN_PLUS 0x80000000U
#define S21_DECIMAL_SIGN_MINUS 0x7FFFFFFFU

#define S21_DECIMAL_SCALE_MASK 0x00FF0000U // выделить scale (биты 16-23)
#define S21_CLEAR_SCALE_MASK 0xFF00FFFFU // очистить scale
#define S21_DECIMAL_MAX_SCALE 28         // максимальный scale
#define S21_DECIMAL_SCALE_SHIFT 16       // сдвиг для scale
#define S21_DECIMAL_NEXT_INT_SHIFT 32    // следующий инт
#define S21_DECIMAL_ALL_BITS 0xFFFFFFFFu // включены все биты инта

/* Мин и Макс для float */
#define S21_FLOAT_MIN 1e-28f
#define S21_FLOAT_MAX 7.922816e+28f

// Арифметические операторы
int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

int s21_is_greater_abs(s21_decimal a, s21_decimal b);

// Операторы сравнения
int s21_is_less(s21_decimal value_1, s21_decimal value_2);
int s21_is_less_or_equal(s21_decimal value_1, s21_decimal value_2);
int s21_is_greater(s21_decimal value_1, s21_decimal value_2);
int s21_is_greater_or_equal(s21_decimal value_1, s21_decimal value_2);
int s21_is_equal(s21_decimal value_1, s21_decimal value_2);
int s21_is_not_equal(s21_decimal value_1, s21_decimal value_2);

// Преобразователи

int s21_from_int_to_decimal(int src, s21_decimal *dst);

int s21_from_float_to_decimal(float src, s21_decimal *dst);

int s21_from_decimal_to_int(s21_decimal src, int *dst);

int s21_from_decimal_to_float(s21_decimal src, float *dst);

// Округляет указанное Decimal число до ближайшего целого числа в сторону
// отрицательной бесконечности.
int s21_floor(s21_decimal value, s21_decimal *result);
// Округляет Decimal до ближайшего целого числа.
int s21_round(s21_decimal value, s21_decimal *result);
// Возвращает целые цифры указанного Decimal числа; любые дробные цифры
// отбрасываются, включая конечные нули.
int s21_truncate(s21_decimal value, s21_decimal *result);
// Возвращает результат умножения указанного Decimal на -1.
int s21_negate(s21_decimal value, s21_decimal *result);

/* Вспомогательные функции */
void s21_reset_to_zero(s21_decimal *d);
int s21_get_sign(const s21_decimal *d);
void s21_set_sign(s21_decimal *d, int sign);
int s21_get_scale(const s21_decimal *d);
void s21_set_scale(s21_decimal *d, int scale);
int s21_is_valid_decimal(s21_decimal d);
// отбрасывание знака для int
int s21_trim_fractional_part(s21_decimal src, s21_decimal *dst);
int s21_zero_value(s21_decimal d);
int s21_normal_scale_decimal(s21_decimal *value_1, s21_decimal *value_2,
                             s21_decimal *normal_value_1,
                             s21_decimal *normal_value_2, int *normal_scale);
int s21_multiplication_by_10(s21_decimal *value);
int s21_mantissa_equal(s21_decimal value_1, s21_decimal value_2);
int my_isfinite(float x);

int s21_mod(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

/* Сравнение */
int s21_is_less(s21_decimal value_1, s21_decimal value_2);
int s21_is_less_or_equal(s21_decimal value_1, s21_decimal value_2);
int s21_is_greater(s21_decimal value_1, s21_decimal value_2);
int s21_is_greater_or_equal(s21_decimal value_1, s21_decimal value_2);
int s21_is_equal(s21_decimal value_1, s21_decimal value_2);
int s21_is_not_equal(s21_decimal value_1, s21_decimal value_2);

/* Преобразования */
int s21_from_int_to_decimal(int src, s21_decimal *dst);
int s21_from_float_to_decimal(float src, s21_decimal *dst);
int s21_from_decimal_to_int(s21_decimal src, int *dst);
int s21_from_decimal_to_float(s21_decimal src, float *dst);

/* Прочие функции */
int s21_floor(s21_decimal value, s21_decimal *result);
int s21_round(s21_decimal value, s21_decimal *result);
int s21_truncate(s21_decimal value, s21_decimal *result);
int s21_negate(s21_decimal value, s21_decimal *result);

/* Базовые */
void s21_decimal_zero(s21_decimal *d);
int s21_get_sign(const s21_decimal *d);      /* 0/1 */
void s21_set_sign(s21_decimal *d, int sign); /* 0/1 */
int s21_get_scale(const s21_decimal *d);     /* 0..28 */
void s21_set_scale(s21_decimal *d, int scale);
int s21_is_zero(s21_decimal d);

/* Валидация: разрешены только sign + scale, scale 0..28 */
int s21_is_valid_decimal(s21_decimal d);

/* 96-битная мантисса (bits[0..2]) */
int s21_cmp_mantissa_96(const s21_decimal *a,
                        const s21_decimal *b); /* -1/0/1 */
int s21_add_mantissa_96(const s21_decimal *a, const s21_decimal *b,
                        s21_decimal *res); /* carry 0/1 */
int s21_sub_mantissa_96(const s21_decimal *a, const s21_decimal *b,
                        s21_decimal *res); /* a>=b, borrow 0/1 */
int s21_inc_mantissa_96(s21_decimal *v);   /* +1, return 1 ok, 0 overflow */
int s21_mul_mantissa_by_10_96(
    s21_decimal *v); /* v*=10, return 1 ok, 0 overflow */
uint32_t
s21_div_mantissa_by_10_96(s21_decimal *v); /* v/=10, return remainder 0..9 */

/* Банковское округление: решает, надо ли округлять вверх */
int s21_need_bankers_round_up(int last_digit, int tail_nonzero, int lsd_even);

/* Уменьшить scale до new_scale с банковским округлением (делением на 10) */
int s21_reduce_scale_bankers_96(s21_decimal *v, int new_scale);

/* Выравнивание scale двух чисел (по модулю): пытаемся поднять меньший scale
   умножением на 10, если нельзя — уменьшаем больший scale (с банковским
   округлением). */
int s21_normalize_pair_scales_96(s21_decimal *a, s21_decimal *b);

/* bigint базовые */
void s21_big_zero(s21_big *x);
void s21_big_from_mantissa_96(s21_big *x,
                              const s21_decimal *d); /* берет bits[0..2] */
int s21_big_fits_96(const s21_big *x);               /* high words == 0 */
int s21_big_is_zero(const s21_big *x);
int s21_big_cmp(const s21_big *a, const s21_big *b); /* -1/0/1 */
void s21_big_add(const s21_big *a, const s21_big *b, s21_big *r);
void s21_big_sub(const s21_big *a, const s21_big *b, s21_big *r); /* a>=b */
void s21_big_mul_96x96(const s21_decimal *a, const s21_decimal *b,
                       s21_big *r);                   /* 192бит в r */
uint32_t s21_big_div_small(s21_big *a, uint32_t div); /* a/=div, return rem */
int s21_big_mul_small(s21_big *a,
                      uint32_t mul); /* a*=mul, return 1 ok, 0 overflow 224 */
int s21_big_add_small(s21_big *a, uint32_t add); /* a+=add, 1 ok, 0 overflow */
void s21_big_to_mantissa_96(const s21_big *x,
                            s21_decimal *d); /* кладет в bits[0..2] */

/* Деление bigint: q = n/d, r = n%d (d!=0) */
void s21_big_divmod(const s21_big *n, const s21_big *d, s21_big *q, s21_big *r);

/* Для mod: умножение на 10^pow */
int s21_big_mul_pow10(s21_big *x, int pow);

/* Для mod: попытка уместить в 96 бит за счёт деления на 10 только при нулевом
 * остатке */
int s21_big_fit_96_by_trailing_zeros(s21_big *m, int *scale);

int my_isfinite(float x);

uint32_t s21_pow10_u32(int p);
uint32_t s21_round_bankers_u32(long double x);

int s21_pack_result(s21_decimal mantissa_only, int sign, int scale,
                    s21_decimal *result);

int s21_is_odd(const s21_decimal *dec);
int s21_bank_round(s21_decimal value, s21_decimal *result);

#endif // S21_DECIMAL_H