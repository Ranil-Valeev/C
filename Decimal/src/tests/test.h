#ifndef S21_TEST_H
#define S21_TEST_H

#include <check.h>

#include "../s21_decimal.h"

/* Определяем стандартные коды ошибок для Школы 21 */
#define S21_ARITHMETIC_OK 0
#define S21_ARITHMETIC_BIG 1   // или TOO_BIG
#define S21_ARITHMETIC_SMALL 2 // или TOO_SMALL
#define S21_ARITHMETIC_DIV_BY_ZERO 3

#define S21_CONVERTATION_OK 0
#define S21_CONVERTATION_ERROR 1

/* Для совместимости с вашим кодом */
#ifndef S21_ARITH_OK
// #define S21_ARITH_OK S21_ARITHMETIC_OK
#endif

#ifndef S21_ARITH_TOO_LARGE
// #define S21_ARITH_TOO_LARGE S21_ARITHMETIC_BIG
#endif

#ifndef S21_CONV_OK
// #define S21_CONV_OK S21_CONVERTATION_OK
#endif

/* Основные тестовые сьюты */
Suite *arithmetic_suite(void);
Suite *comparison_suite(void);
Suite *converters_suite(void);
Suite *decimal_suite(void);
Suite *other_suite(void);

#endif // S21_TEST_H