// int sscanf(const char *str, const char *format, ...)
// — считывает форматированный ввод из строки.
#include "s21_string.h"

#define ARRAY_LENGTH 10000

int s21_sscanf(const char *str, const char *format, ...) {
  va_list args_VA;
  va_start(args_VA, format);
  const char *input_str = str;
  const char *format_str = format;
  int count = 0;

  while (*format_str) {
    if (*format_str == '%') {
      format_str++;

      format_options_scanf options;

      // обнулили структуру
      s21_ResetStructSscanf(&options);

      // проверка флагов
      format_str = s21_ParserFormatLineSscanf(&format_str, &options);

      // '%%'
      s21_DoublePercentSscanf(&input_str, &format_str);

      if (options.specifier != 'c')  // '[' и 'n' у нас нет
      {
        s21_SkipSpaceSymbolInputSscanf(&input_str);  // пропуск пробелов
      }

      // парсинг спецификаторов
      int result = s21_ParserSpecifiersSscanf(&input_str, &args_VA, &options);
      if (result <= 0) break;
      count += result;
      // пропускаем пробелы
    } else if (s21_IsSpaceSscanf((unsigned char)*format_str)) {
      s21_SkipSpaceSymbolInputSscanf(&input_str);
      s21_SkipSpaceSymbolFormatSscanf(&format_str);
    } else {
      if (*input_str != *format_str) break;
      {
        input_str++;
        format_str++;
      }
    }
  }
  va_end(args_VA);
  return count;
}

// Порядок в форматной строке:
// % [*] [ширина] [длина] спецификатор

const char *s21_ParserFormatLineSscanf(const char **format_str,
                                       format_options_scanf *options) {
  s21_ResetStructSscanf(options);

  while (**format_str) {
    if (**format_str == '*') {
      options->asterisk = 1;
      (*format_str)++;
    } else if (s21_IsDigitSscanf(**format_str)) {
      // Чтение ширины
      options->width = 0;
      while (s21_IsDigitSscanf(**format_str)) {
        options->width = options->width * 10 + (**format_str - '0');
        (*format_str)++;
      }

    } else if (**format_str == 'h') {
      options->length = 'h';
      (*format_str)++;

    } else if (**format_str == 'l') {
      if (*(*format_str + 1) == 'l')  // Смотрим вперед БЕЗ увеличения указателя
      {
        options->length = 'L';  // проверка на ll
        (*format_str) += 2;
      } else {
        options->length = 'l';
        (*format_str)++;
      }
    } else {
      // Спецификатор достигнут
      options->specifier = **format_str;
      (*format_str)++;
      break;
    }
  }
  return *format_str;
}

int s21_ParserSpecifiersSscanf(const char **input_str, va_list *args_VA,
                               format_options_scanf *options) {
  switch (options->specifier) {
    case 'c':
      return s21_SpecifiersCSscanf(input_str, args_VA, options);

    case 'd':
      return s21_SpecifiersDSscanf(input_str, args_VA, options);

    case 'f':
      return s21_SpecifiersFSscanf(input_str, args_VA, options);

    case 's':
      return s21_SpecifiersSSscanf(input_str, args_VA, options);

    case 'u':
      return s21_SpecifiersUSscanf(input_str, args_VA, options);

    default:
      return 0;
  }
}

// Спецификатор %c
int s21_SpecifiersCSscanf(const char **input_str, va_list *args_VA,
                          format_options_scanf *options) {
  if (s21_StarCheckSscanf(input_str, options) == 0) return 0;

  char *input_symbol = va_arg(*args_VA, char *);

  *input_symbol = **input_str;
  (*input_str)++;
  return 1;  // успешно считали символ
}

// Спецификатор %d
int s21_SpecifiersDSscanf(const char **input_str, va_list *args_VA,
                          format_options_scanf *options) {
  char *end_ptr = S21_NULL;
  long long number;

  number = s21_StrtollSscanf(*input_str, &end_ptr);

  if (end_ptr == *input_str) {
    return 0;
  }

  *input_str = end_ptr;

  if (s21_StarCheckSscanf(input_str, options) == 0) {
    return 1;
  }

  switch (options->length) {
    case 'h': {
      short *ptr_short = va_arg(*args_VA, short *);
      *ptr_short = (short)number;
      break;
    }
    case 'l': {
      long *ptr_long = va_arg(*args_VA, long *);
      *ptr_long = (long)number;
      break;
    }

    case 'L': {
      long long *ptr_long_long = va_arg(*args_VA, long long *);
      *ptr_long_long = (long long)number;
      break;
    }

    default: {
      int *ptr_int = va_arg(*args_VA, int *);
      *ptr_int = (int)number;
      break;
    }
  }
  return 1;
}

// Спецификатор %f
int s21_SpecifiersFSscanf(const char **input_str, va_list *args_VA,
                          format_options_scanf *options) {
  char *end_ptr;
  double value =
      s21_StrtodSscanf(*input_str, &end_ptr);  // это тоже s21_StrtodSscanf

  // Проверка успешной конвертации
  if (end_ptr == *input_str || *end_ptr != '\0') {
    return 0;  // ошибка, неверный формат строки
  }

  // Обновление указателя на следующую позицию после прочтённого числа
  *input_str = end_ptr;

  // Запись результата в нужную переменную в зависимости от размера (length)
  switch (options->length) {
    case 'l': {
      double *ptr_double = va_arg(*args_VA, double *);
      *ptr_double = value;
      break;
    }
    case 'L': {
      long double *ptr_long_double = va_arg(*args_VA, long double *);
      *ptr_long_double = (long double)value;
      break;
    }
    default: {
      float *ptr_float = va_arg(*args_VA, float *);
      *ptr_float = (float)value;
      break;
    }
  }

  return 1;  // Успешно обработано
}

// Спецификатор %s
int s21_SpecifiersSSscanf(const char **input_str, va_list *args_VA,
                          format_options_scanf *options) {
  if (s21_StarCheckSscanf(input_str, options) == 0) return 0;

  // Получаем указатель на буфер для строки
  char *read_data = va_arg(*args_VA, char *);

  // Чтение символов до первого пробела
  const char *start = *input_str;
  while (**input_str && !s21_IsSpaceSscanf((unsigned char)**input_str))
    (*input_str)++;

  // Копируем слово в буфер
  s21_strncpy(read_data, start, (*input_str - start));
  read_data[(*input_str - start)] = '\0';

  return 1;
}

// Спецификатор %u
int s21_SpecifiersUSscanf(const char **input_str, va_list *args_VA,
                          format_options_scanf *options) {
  char *end_ptr;
  unsigned long long number =
      s21_StrtoullSscanf(*input_str, &end_ptr);  // эту тоже s21_StrtoullSscanf

  // Проверка успешной конвертации
  if (end_ptr == *input_str || *end_ptr != '\0') {
    return 0;  // ошибка, неверный формат строки
  }

  // Обновление указателя на следующую позицию после прочтённого числа
  *input_str = end_ptr;

  // Запись результата в нужную переменную в зависимости от размера (length)
  switch (options->length) {
    case 'h': {
      unsigned short *ptr_unsigned_short = va_arg(*args_VA, unsigned short *);
      *ptr_unsigned_short = (unsigned short)number;
      break;
    }
    case 'l': {
      unsigned long *ptr_unsigned_long = va_arg(*args_VA, unsigned long *);
      *ptr_unsigned_long = (unsigned long)number;
      break;
    }
    case 'L': {
      unsigned long long *ptr_unsigned_long_long =
          va_arg(*args_VA, unsigned long long *);
      *ptr_unsigned_long_long = (unsigned long long)number;
      break;
    }
    default: {
      unsigned int *ptr_unsigned_int = va_arg(*args_VA, unsigned int *);
      *ptr_unsigned_int = (unsigned int)number;
      break;
    }
  }

  return 1;  // Успешно обработано
}

void s21_ResetStructSscanf(format_options_scanf *options) {
  options->specifier = 0;  // 'd', 's', 'f', 'c', 'u', '%'
  options->asterisk = 0;   // 1 если есть '*', иначе 0
  options->width = 0;      // 0 если не указана
  options->length = 0;     // '\0', 'h', 'l', 'L'
}

int s21_StarCheckSscanf(const char **input_str, format_options_scanf *options) {
  if (options->asterisk) {
    (*input_str)++;
    return 0;  // подавляем запись значений
  }
  return 1;
}

// Пропуск пробелов во входной строке (с проверкой конца строки)
void s21_SkipSpaceSymbolInputSscanf(const char **input_str) {
  while (**input_str && s21_IsSpaceSscanf((unsigned char)**input_str)) {
    (*input_str)++;
  }
}

// Пропуск пробелов в формате (без проверки конца строки)
void s21_SkipSpaceSymbolFormatSscanf(const char **format_str) {
  while (s21_IsSpaceSscanf((unsigned char)**format_str)) {
    (*format_str)++;
  }
}

// Двойной процент / %%
void s21_DoublePercentSscanf(const char **input_str, const char **format_str) {
  if (**input_str == '%') {
    (*input_str)++;
    (*format_str)++;
  }
}

long long s21_StrtollSscanf(const char *input_str, char **end_ptr) {
  long long result = 0;
  s21_size i = 0;

  while (s21_IsSpaceSscanf((unsigned char)input_str[i])) {
    i++;
  }

  // minus минус

  int MINUS = s21_IsMinusSscanf(input_str, &i);

  while (s21_IsDigitSscanf((unsigned char)input_str[i])) {
    int digit = input_str[i] - '0';
    result = result * 10 + digit;
    i++;
  }

  if (MINUS) {
    result = -result;
  }
  if (end_ptr) {
    *end_ptr = (char *)(input_str + i);
  }
  return result;
}

// double strtod(const char* str, char** endptr);

double s21_StrtodSscanf(const char *input_str, char **end_ptr) {
  double result = 0.0;
  s21_size i = 0;

  // int count_digit = 0;
  double fractional_part = 0.0;
  double count_divisor = 1.0;

  while (s21_IsSpaceSscanf((unsigned char)input_str[i])) {
    i++;
  }

  // minus

  int MINUS = s21_IsMinusSscanf(input_str, &i);

  while (s21_IsDigitSscanf((unsigned char)input_str[i])) {
    result = result * 10 + (input_str[i] - '0');
    i++;
  }

  if (input_str[i] == '.') {
    i++;
    while (s21_IsDigitSscanf((unsigned char)input_str[i])) {
      fractional_part = fractional_part * 10 + (input_str[i] - '0');
      count_divisor *= 10.0;
      i++;
    }
    fractional_part /= count_divisor;
    result += fractional_part;
  }

  if (MINUS) {
    result = -result;
  }
  if (end_ptr) {
    *end_ptr = (char *)(input_str + i);
  }

  return result;
}

// Strtoull

unsigned long long s21_StrtoullSscanf(const char *input_str, char **end_ptr) {
#ifndef ULLONG_MAX
#define ULLONG_MAX 18446744073709551615ULL
#endif

  unsigned long long result = 0;
  s21_size i = 0;

  while (s21_IsSpaceSscanf((unsigned char)input_str[i])) {
    i++;
  }

  while (s21_IsDigitSscanf((unsigned char)input_str[i])) {
    int digit = input_str[i] - '0';

    if (result > (ULLONG_MAX - digit) / 10) {
      result = ULLONG_MAX;
      break;
    }
    result = result * 10 + digit;
    i++;
  }
  if (end_ptr) {
    *end_ptr = (char *)(input_str + i);
  }

  return result;
}

// пробельный символ
int s21_IsSpaceSscanf(int c) {
  return ((unsigned char)c == ' ' || (unsigned char)c == '\t' ||
          (unsigned char)c == '\n' || (unsigned char)c == '\v' ||
          (unsigned char)c == '\f' || (unsigned char)c == '\r');
}

// проверка на цифры
int s21_IsDigitSscanf(char symbol) {
  if (symbol >= '0' && symbol <= '9') {
    return 1;
  } else {
    return 0;
  }
}

// проверка на минус
int s21_IsMinusSscanf(const char *input_str, s21_size *iconic_simbol) {
  int MINUS = 0;
  if (input_str[*iconic_simbol] == '-') {
    MINUS = 1;
    (*iconic_simbol)++;
  } else if (input_str[*iconic_simbol] == '+') {
    (*iconic_simbol)++;
  }
  return MINUS;
}