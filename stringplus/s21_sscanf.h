#ifndef S21_SSCANF_H
#define S21_SSCANF_H

#include <stdarg.h>

// структура s21_sscanf
typedef struct {
  char specifier;  // 'd', 's', 'f', 'c', 'u', '%'
  int asterisk;    // 1 если есть '*', иначе 0
  int width;       // 0 если не указана
  char length;     // '\0', 'h', 'l', 'L' ???
} format_options_scanf;

// s21_sscanf
int s21_sscanf(const char *str, const char *format, ...);

// обнулени структуры
void s21_ResetStructSscanf(format_options_scanf *options);

// парсеры
int s21_ParserSpecifiersSscanf(const char **input_str, va_list *args_VA,
                               format_options_scanf *options);
const char *s21_ParserFormatLineSscanf(const char **format_str,
                                       format_options_scanf *options);

// функции спецификаторов
int s21_SpecifiersCSscanf(const char **input_str, va_list *args_VA,
                          format_options_scanf *options);
int s21_SpecifiersDSscanf(const char **input_str, va_list *args_VA,
                          format_options_scanf *options);
int s21_SpecifiersFSscanf(const char **input_str, va_list *args_VA,
                          format_options_scanf *options);
int s21_SpecifiersSSscanf(const char **input_str, va_list *args_VA,
                          format_options_scanf *options);
int s21_SpecifiersUSscanf(const char **input_str, va_list *args_VA,
                          format_options_scanf *options);

// звездочка / подавлени присваивания
int s21_StarCheckSscanf(const char **input_str, format_options_scanf *options);

// пропуск пробелов для input
void s21_SkipSpaceSymbolInputSscanf(const char **input_str);

// пропуск пробелов для format
void s21_SkipSpaceSymbolFormatSscanf(const char **format_str);

// проверки на минус
int s21_IsMinusSscanf(const char *input_str, s21_size *iconic_simbol);

// двойной %%
void s21_DoublePercentSscanf(const char **input_str, const char **format_str);

// общий пропуск пробелов
int s21_IsSpaceSscanf(int c);

// проверка на цифры
int s21_IsDigitSscanf(char symbol);

// строка в лонг лонг
long long s21_StrtollSscanf(const char *input_str, char **end_ptr);

// строка в ансигнед лонг лонг
unsigned long long s21_StrtoullSscanf(const char *input_str, char **end_ptr);

// строка в дабл
double s21_StrtodSscanf(const char *input_str, char **end_ptr);

#endif  // S21_SSCANF_H