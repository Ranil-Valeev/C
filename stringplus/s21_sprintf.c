// int sprintf(char *str, const char *format, ...)
// отправляет форматированный вывод в строку, на которую указывает str.

#include "s21_string.h"

/*
typedef struct {
  char specifier;  // 'c', 'd', 'f', 's', 'u', '%'

  // Флаги
  int flag_minus;  // '-' - выравнивание влево
  int flag_plus;   // '+' - всегда показывать знак
  int flag_space;  // ' ' - пробел для положительных

  // Ширина и точность
  int width;  // минимальная ширина (0 если не указана)
  int accuracy;       // точность (-1 если не указана)
  int has_accuracy;  // 1 если точность указана явно

  // Длина
  char length;  // '\0', 'h', 'l'
} format_option_printf; */

// готова
int s21_sprintf(char *str, const char *format, ...) {
  va_list args_VA;
  va_start(args_VA, format);
  char *output_str = str;
  const char *format_str = format;

  while (*format_str) {
    if (*format_str != '%') {
      *output_str = *format_str;
      output_str++;
      format_str++;
      continue;
    }
    format_str++;

    format_option_printf options;

    s21_ResetStructSprintf(&options);

    options.accuracy = -1;

    format_str = s21_ParserFormatLineSprintf(&format_str, &options);

    // парсинг спецификаторов
    s21_ParserSpecifiersSprintf(&output_str, &args_VA, &options);
  }
  *output_str = '\0';
  va_end(args_VA);

  return output_str - str;
}

// готова
const char *s21_ParserFormatLineSprintf(const char **format_str,
                                        format_option_printf *options) {
  s21_ResetStructSprintf(options);

  // Парсим флаги
  while (**format_str) {
    if (**format_str == '-') {
      options->flag_minus = 1;
      (*format_str)++;
    } else if (**format_str == '+') {
      options->flag_plus = 1;
      (*format_str)++;
    } else if (**format_str == ' ') {
      options->flag_space = 1;
      (*format_str)++;
    } else if (**format_str == '0') {
      // Флаг 0 для заполнения нулями
      (*format_str)++;
    } else if (s21_IsDigitSprintf(**format_str)) {
      // Чтение ширины
      options->width = 0;
      while (s21_IsDigitSprintf(**format_str)) {
        options->width = options->width * 10 + (**format_str - '0');
        (*format_str)++;
      }
    } else if (**format_str == '.') {
      (*format_str)++;
      options->has_accuracy = 1;
      options->accuracy = 0;
      // Чтение точности
      while (s21_IsDigitSprintf(**format_str)) {
        options->accuracy = options->accuracy * 10 + (**format_str - '0');
        (*format_str)++;
      }
    } else if (**format_str == 'h' || **format_str == 'l') {
      // Длина
      if (**format_str == 'h') {
        options->length = 'h';
        (*format_str)++;
      } else if (**format_str == 'l') {
        if (*(*format_str + 1) == 'l') {
          options->length = 'L';
          (*format_str) += 2;
        } else {
          options->length = 'l';
          (*format_str)++;
        }
      }
    } else {
      // Спецификатор
      options->specifier = **format_str;
      (*format_str)++;
      break;
    }
  }

  return *format_str;
}

int s21_ParserSpecifiersSprintf(char **output_str, va_list *args_VA,
                                format_option_printf *options) {
  switch (options->specifier) {
    case 'c':
      return s21_SpecifiersCSprintf(output_str, args_VA, options);

    case 'd':
      return s21_SpecifiersDSprintf(output_str, args_VA, options);

    case 'f':
      return s21_SpecifiersFSprintf(output_str, args_VA, options);

    case 's':
      return s21_SpecifiersSSprintf(output_str, args_VA, options);

    case 'u':
      return s21_SpecifiersUSprintf(output_str, args_VA, options);

    case '%':
      return s21_SpecifiersPercentSprintf(output_str, options);

    default:
      return 0;
  }
}

int s21_SpecifiersPercentSprintf(char **output_str,
                                 format_option_printf *options) {
  (void)options;  // Не используем options для %
  *(*output_str)++ = '%';
  return 1;
}
// готово
// Спецификатор %c
int s21_SpecifiersCSprintf(char **output_str, va_list *args_VA,
                           format_option_printf *options) {
  char c = (char)va_arg(*args_VA, int);
  int len = 1;

  // Применяем ширину (выравнивание) 333
  if (!options->flag_minus) {
    s21_AddSpaceSprintf(output_str, options, len);
  }

  // Записываем символ
  *(*output_str)++ = c;

  // Выравнивание влево 333
  if (options->flag_minus) {
    s21_AddSpaceSprintf(output_str, options, len);
  }

  return 1;
}

// Спецификатор %d
int s21_SpecifiersDSprintf(char **output_str, va_list *args_VA,
                           format_option_printf *options) {
  long long num;

  // Получаем число в зависимости от длины
  switch (options->length) {
    case 'h':
      num = (short)va_arg(*args_VA, int);
      break;
    case 'l':
      num = va_arg(*args_VA, long);
      break;
    case 'L':
      num = va_arg(*args_VA, long long);
      break;
    default:
      num = va_arg(*args_VA, int);
      break;
  }

  // Преобразуем число в строку
  char buffer[32];
  char *num_str = buffer;

  // Нужна функция для преобразования long long в строку
  s21_lltoa_sprintf(num, buffer);

  // Обрабатываем знак
  char sign = 0;
  if (num < 0) {
    sign = '-';
    num_str++;  // Пропускаем минус в строке
  } else if (options->flag_plus) {
    sign = '+';
  } else if (options->flag_space) {
    sign = ' ';
  }

  int len = s21_strlen(num_str);
  int total_len = len + (sign ? 1 : 0);

  // Выравнивание вправо 333
  if (!options->flag_minus) {
    s21_AddSpaceSprintf(output_str, options, total_len);
  }

  // Знак
  if (sign) {
    *(*output_str)++ = sign;
  }

  // Число
  while (*num_str) {
    *(*output_str)++ = *num_str++;
  }

  // Выравнивание влево 333
  if (options->flag_minus) {
    s21_AddSpaceSprintf(output_str, options, total_len);
  }

  return 1;
}

// Спецификатор %f
int s21_SpecifiersFSprintf(char **output_str, va_list *args_VA,
                           format_option_printf *options) {
  // 1. Получаем значение double из аргументов
  double num;

  if (options->length == 'L') {
    long double ld = va_arg(*args_VA, long double);
    num = (double)ld;
  } else {
    num = va_arg(*args_VA, double);
  }

  // 2. Определяем точность
  int accuracy;
  if (options->has_accuracy) {
    accuracy = options->accuracy;
    if (accuracy < 0) accuracy = 0;
  } else {
    accuracy = 6;
  }

  // 3. Преобразуем double в строку
  char buffer[64];
  s21_ftoa_sprintf(num, buffer, accuracy);  // num и accuracy определены выше!

  // 4. Определяем длину строки
  int len = s21_strlen(buffer);

  // 5. Определяем знак (для правильного выравнивания)
  int has_sign = 0;
  char sign_char = 0;

  if (num < 0 || (options->flag_plus && num >= 0)) {
    has_sign = 1;
    sign_char = (num < 0) ? '-' : '+';
  } else if (options->flag_space && num >= 0) {
    has_sign = 1;
    sign_char = ' ';
  }

  // 6. РАСЧИТАЕМ ОБЩУЮ ДЛИНУ С УЧЕТОМ ЗНАКА
  int total_len = len;
  if (has_sign && num >= 0) {
    // Для положительных чисел, если добавляем знак + или пробел
    // (для отрицательных знак '-' уже входит в len)
    total_len = len + 1;
  }

  // 7. Выравнивание правая (без флага минус) - ИСПОЛЬЗУЕМ total_len
  if (!options->flag_minus) {
    s21_AddSpaceSprintf(output_str, options, total_len);  // ← total_len
  }

  // 8. Выводим знак, если есть
  if (has_sign && sign_char) {
    *(*output_str)++ = sign_char;
  }

  // 9. Выводим само число
  char *ptr = buffer;
  if (num < 0 && buffer[0] == '-') {
    ptr++;  // пропускаем '-'
  }

  while (*ptr) {
    *(*output_str)++ = *ptr++;
  }

  // 10. Выравнивание левая (с флагом минус) - ИСПОЛЬЗУЕМ total_len
  if (options->flag_minus) {
    s21_AddSpaceSprintf(output_str, options, total_len);  // ← total_len
  }

  return 1;
}

// готова
//  Спецификатор %s
int s21_SpecifiersSSprintf(char **output_str, va_list *args_VA,
                           format_option_printf *options) {
  char *s = va_arg(*args_VA, char *);
  if (s == S21_NULL) s = "(null)";

  // Определяем длину с учетом точности
  int len = s21_strlen(s);
  if (options->has_accuracy && options->accuracy < len) {
    len = options->accuracy;
  }

  // Выравнивание правая
  if (!options->flag_minus) {
    s21_AddSpaceSprintf(output_str, options, len);
  }

  // Копируем строку
  for (int i = 0; i < len; i++) {
    *(*output_str)++ = s[i];
  }

  // Выравнивание левая
  if (options->flag_minus) {
    s21_AddSpaceSprintf(output_str, options, len);
  }

  return 1;
}

// готова
// Спецификатор %u
int s21_SpecifiersUSprintf(char **output_str, va_list *args_VA,
                           format_option_printf *options) {
  unsigned long long num;

  switch (options->length) {
    case 'h':
      num = (unsigned short)va_arg(*args_VA, unsigned int);
      break;
    case 'l':
      num = va_arg(*args_VA, unsigned long);
      break;
    case 'L':
      num = va_arg(*args_VA, unsigned long long);
      break;
    default:
      num = va_arg(*args_VA, unsigned int);
      break;
  }

  char buffer[32];
  // Нужна функция для unsigned long long
  s21_ulltoa_sprintf(num, buffer);

  int len = s21_strlen(buffer);

  // Выравнивание правая
  if (!options->flag_minus) {
    s21_AddSpaceSprintf(output_str, options, len);
  }

  // Число
  char *ptr = buffer;
  while (*ptr) {
    *(*output_str)++ = *ptr++;
  }

  // левая
  if (options->flag_minus) {
    s21_AddSpaceSprintf(output_str, options, len);
  }

  return 1;
}

void s21_ResetStructSprintf(format_option_printf *options) {
  options->specifier = 0;  // 'c', 'd', 'f', 's', 'u', '%'

  // Флаги
  options->flag_minus = 0;  // '-' - выравнивание влево
  options->flag_plus = 0;   // '+' - всегда показывать знак
  options->flag_space = 0;  // ' ' - пробел для положительных

  // Ширина и точность
  options->width = 0;  // минимальная ширина (0 если не указана)
  options->accuracy = 0;  // точность (-1 если не указана)
  options->has_accuracy = 0;  // 1 если точность указана явно

  // Длина
  options->length = 0;  // '\0', 'h', 'l', 'L'
}

// Функция проверяет, является ли символ пробельным
int s21_IsSpaceSprintf(int c) {
  return ((unsigned char)c == ' ' || (unsigned char)c == '\t' ||
          (unsigned char)c == '\n' || (unsigned char)c == '\v' ||
          (unsigned char)c == '\f' || (unsigned char)c == '\r');
}

int s21_IsDigitSprintf(char symbol) {
  if (symbol >= '0' && symbol <= '9') {
    return 1;
  } else {
    return 0;
  }
}

// double to string
char *s21_ftoa_sprintf(double num, char *str, int accuracy) {
  int i = 0;

  // Обработка отрицательных чисел
  if (num < 0) {
    str[i++] = '-';
    num = -num;
  }

  // Целая часть (используем long long для больших чисел)
  long long int_part = (long long)num;
  double frac_part = num - (double)int_part;

  // Преобразуем целую часть
  if (int_part == 0) {
    str[i++] = '0';
  } else {
    char int_str[32];
    s21_lltoa_sprintf(int_part, int_str);  // Используем lltoa для long long
    char *ptr = int_str;
    while (*ptr) {
      str[i++] = *ptr++;
    }
  }

  // Десятичная часть
  if (accuracy > 0) {
    str[i++] = '.';
    for (int j = 0; j < accuracy; j++) {
      frac_part *= 10;
      int digit = (int)frac_part;
      str[i++] = '0' + digit;
      frac_part -= digit;
    }
  }

  str[i] = '\0';
  return str;
}
// unsigned int to string
char *s21_lltoa_sprintf(long long num, char *str) {
  char *ptr = str;
  int MINUS = 0;

  if (num < 0) {
    MINUS = 1;
    num = -num;
  }

  do {
    *ptr++ = (char)(num % 10 + '0');
    num /= 10;
  } while (num > 0);

  if (MINUS) {
    *ptr++ = '-';
  }

  *ptr = '\0';

  s21_reverse(str);
  return str;
}

// Разворот строки
void s21_reverse(char *str) {
  int len = s21_strlen(str);
  for (int i = 0; i < len / 2; i++) {
    char temp = str[i];
    str[i] = str[len - 1 - i];
    str[len - 1 - i] = temp;
  }
}
// unsigned long long to string
char *s21_ulltoa_sprintf(unsigned long long num, char *str) {
  char *ptr = str;

  if (num == 0) {
    *ptr++ = '0';
    *ptr = '\0';
    return str;
  }

  while (num > 0) {
    *ptr++ = (char)(num % 10 + '0');
    num /= 10;
  }

  *ptr = '\0';
  s21_reverse(str);
  return str;
}

void s21_AddSpaceSprintf(char **output_str, format_option_printf *options,
                         int length) {
  int count_length = options->width - length;
  if (count_length > 0) {
    for (int i = 0; i < count_length; i++) {
      *(*output_str)++ = ' ';
    }
  }
}