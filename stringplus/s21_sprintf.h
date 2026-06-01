#ifndef S21_SPRINTF_H
#define S21_SPRINTF_H

#include <stdarg.h>

typedef struct {
  char specifier;  // 'c', 'd', 'f', 's', 'u', '%'

  // Флаги
  int flag_minus;  // '-' - выравнивание влево
  int flag_plus;   // '+' - всегда показывать знак
  int flag_space;  // ' ' - пробел для положительных

  // Ширина и точность
  int width;  // минимальная ширина (0 если не указана)
  int accuracy;      // точность (-1 если не указана)
  int has_accuracy;  // 1 если точность указана явно

  // Длина
  char length;  // '\0', 'h', 'l'
  // Добавил это поле:
  int asterisk;  // для обработки '*'
} format_option_printf;

int s21_sprintf(char *str, const char *format, ...);

// Функции парсинга и обработки формата
const char *s21_ParserFormatLineSprintf(const char **format_str,
                                        format_option_printf *options);
int s21_ParserSpecifiersSprintf(char **output_str, va_list *args_VA,
                                format_option_printf *options);
void s21_ResetStructSprintf(format_option_printf *options);

// Обработчики спецификаторов
int s21_SpecifiersCSprintf(char **output_str, va_list *args_VA,
                           format_option_printf *options);
int s21_SpecifiersDSprintf(char **output_str, va_list *args_VA,
                           format_option_printf *options);
int s21_SpecifiersFSprintf(char **output_str, va_list *args_VA,
                           format_option_printf *options);
int s21_SpecifiersSSprintf(char **output_str, va_list *args_VA,
                           format_option_printf *options);
int s21_SpecifiersUSprintf(char **output_str, va_list *args_VA,
                           format_option_printf *options);
int s21_SpecifiersPercentSprintf(char **output_str,
                                 format_option_printf *options);

// выравнивание
void s21_AddSpaceSprintf(char **output_str, format_option_printf *options,
                         int length);

// Вспомогательные функции проверки символов
int s21_IsDigitSprintf(char symbol);
int s21_IsSpaceSprintf(int c);

// Функции преобразования чисел в строки

char *s21_lltoa_sprintf(long long num, char *str);
char *s21_ulltoa_sprintf(unsigned long long num, char *str);
char *s21_ftoa_sprintf(double num, char *str, int accuracy);
void s21_reverse(char *str);

#endif  // S21_SPRINTF_H