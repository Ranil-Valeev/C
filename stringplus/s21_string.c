#include "s21_string.h"

// 1
void *s21_memchr(const void *str, int c, s21_size n) {
  if (str == S21_NULL || n == 0) {
    return S21_NULL;
  }

  const unsigned char *ptr = (const unsigned char *)str;
  unsigned char uc = (unsigned char)c;

  for (s21_size i = 0; i < n; i++) {
    if (ptr[i] == uc) {
      return (void *)(ptr + i);
    }
  }

  return S21_NULL;
}

// 2
int s21_memcmp(const void *str1, const void *str2, s21_size n) {
  const unsigned char *s1 = str1;
  const unsigned char *s2 = str2;
  for (s21_size i = 0; i < n; i++) {
    if (s1[i] != s2[i]) {
      return s1[i] - s2[i];
    }
  }
  return 0;
}

// 3
void *s21_memcpy(void *str, const void *src, s21_size n) {
  unsigned char *new_bus = (unsigned char *)str;
  const unsigned char *s = (const unsigned char *)src;
  for (s21_size alina = 0; alina < n; ++alina) {
    new_bus[alina] = s[alina];
  }
  return new_bus;
}

// 4
void *s21_memset(void *str, int c, s21_size n) {
  unsigned char *alina_walking = (unsigned char *)str;
  unsigned char value = (unsigned char)c;
  for (s21_size alina = 0; alina < n; ++alina) {
    alina_walking[alina] = value;
  }
  return str;
}

// 5
char *s21_strncat(char *dest, const char *src, s21_size n) {
  char *p = dest;

  while (*p != '\0') {
    p++;
  }

  while (n-- && *src != '\0') {
    *p = *src;
    p++;
    src++;
  }
  *p = '\0';

  return dest;
}

// 6
char *s21_strchr(const char *str, int c) {
  while (*str != '\0') {
    if (*str == c) {
      return (char *)str;
    }
    str++;
  }
  if (c == '\0') {
    return (char *)str;
  }
  return S21_NULL;
}

// 7
int s21_strncmp(const char *str1, const char *str2, s21_size n) {
  if (n == 0) return 0;

  const unsigned char *s1 = (const unsigned char *)str1;
  const unsigned char *s2 = (const unsigned char *)str2;

  for (s21_size i = 0; i < n; i++) {
    if (s1[i] != s2[i]) {
      return s1[i] - s2[i];
    }
    if (s1[i] == '\0') {
      return 0;
    }
  }
  return 0;
}

// 8
char *s21_strncpy(char *dest, const char *src, s21_size n) {
  s21_size i = 0;

  while (i < n && src[i] != '\0') {
    dest[i] = src[i];
    i++;
  }
  while (i < n) {
    dest[i++] = '\0';
  }

  return dest;
}

// 9
s21_size s21_strcspn(const char *str1, const char *str2) {
  s21_size length = 0;

  for (int i = 0; str1[i] != '\0'; i++) {
    for (int j = 0; str2[j] != '\0'; j++) {
      if (str1[i] == str2[j]) {
        return length;
      }
    }
    length++;
  }
  return length;
}

// 10
char *s21_strerror(int errnum) {
#ifdef __APPLE__
  // Используем macOS макросы
  static const char *errors[] = MACOS_ERRORS;
#define MAX_ERROR MAX_ERROR_MAC
#define UNKNOWN_ERROR UNKNOWN_ERROR_MACOS
#else
  // Используем Linux макросы
  static const char *errors[] = LINUX_ERRORS;
#define MAX_ERROR MAX_ERROR_LINUX
#define UNKNOWN_ERROR UNKNOWN_ERROR_LINUX
#endif

  // Проверяем известную ошибку
  if (errnum >= 0 && errnum <= MAX_ERROR) {
    return (char *)errors[errnum];
  }

  // Неизвестная ошибка
  static char unknown[50];
  snprintf(unknown, sizeof(unknown), UNKNOWN_ERROR, errnum);
  return unknown;
}

// 11
s21_size s21_strlen(const char *str) {
  s21_size len = 0;
  for (s21_size alina = 0; str[alina] != '\0'; ++alina) {
    len++;
  }
  return len;
}

// 12
char *s21_strpbrk(const char *str1, const char *str2) {
  char *res = S21_NULL;

  for (const char *a = str1; *a; a++) {
    for (const char *b = str2; *b; b++) {
      if (*a == *b) {
        res = (char *)a;
        break;
      }
    }

    if (res) {
      break;
    }
  }

  return res;
}

// 13
char *s21_strrchr(const char *str, int c) {
  char *last = S21_NULL;
  unsigned char s = (unsigned char)c;
  while (*str != '\0') {
    if (*str == s) {
      last = (char *)str;
    }
    str++;
  }
  if (s == '\0') {
    return (char *)str;
  }
  return last;
}

// 14
char *s21_strstr(const char *haystack, const char *needle) {
  while (*haystack != '\0') {
    const char *s1 = haystack;
    const char *s2 = needle;
    while (*s2 != '\0' && *s1 == *s2) {
      s1++;
      s2++;
    }
    if (*s2 == '\0') {
      return (char *)haystack;
    }
    haystack++;
  }
  return S21_NULL;
}

// 15
char *s21_strtok(char *str,
                 const char *delim)  // delim - это втарока со списком
                                     // разделителей / delimiters
{
  static char *token_position = S21_NULL;
  char *new_token;
  int delim_found = 0;
  s21_size i, j;
  if (str != S21_NULL) token_position = str;
  if (token_position == S21_NULL || *token_position == '\0') return S21_NULL;
  for (i = 0; token_position[i] != '\0'; ++i) {
    for (j = 0; delim[j] != '\0'; ++j)
      if (token_position[i] == delim[j]) {
        delim_found = 1;
        break;
      }
    if (!delim_found) break;
  }
  if (token_position[i] == '\0') {
    token_position = S21_NULL;
    return S21_NULL;
  }
  new_token = &token_position[i];
  for (; token_position[i] != '\0'; ++i) {
    for (j = 0; delim[j] != '\0'; ++j) {
      if (token_position[i] == delim[j]) {
        delim_found = 1;
        break;
      }
    }
    if (delim_found) break;
  }
  if (token_position[i] != '\0') {
    token_position[i] = '\0';
    token_position = &token_position[i + 1];
  } else
    token_position = S21_NULL;
  return new_token;
}

// Бонус

void *s21_to_upper(const char *str) {
    if (str == S21_NULL) {
        return S21_NULL;
    }
    s21_size length = s21_strlen(str);
    char *result = (char *)calloc(length + 1, sizeof(char));
    if (result == S21_NULL) {
        return S21_NULL;
    }
    for (s21_size i = 0; i < length; ++i) {
        char letter = str[i];  
        if (letter >= 'a' && letter <= 'z') {
            result[i] = letter - 32;
        } else {
            result[i] = letter;
        }
    }
    result[length] = '\0';
    return (void *)result;
}

void *s21_to_lower(const char *str) {
    if (str == S21_NULL) {
        return S21_NULL;
    }
    s21_size length = s21_strlen(str);
    char *result = (char *)calloc(length + 1, sizeof(char));
    if (result == S21_NULL) {
        return S21_NULL;
    }  
    for (s21_size i = 0; i < length; ++i) {
        char current_char = str[i];
        
        if (current_char >= 'A' && current_char <= 'Z') {
            result[i] = current_char + 32;
        } else {
            result[i] = current_char;
        }
    }  
    result[length] = '\0'; 
    return (void *)result;
}


void *s21_insert(const char *src, const char *str, s21_size start_index) {
    if (src == S21_NULL || str == S21_NULL) {
        return S21_NULL;
    }
    
    s21_size src_len = s21_strlen(src);
    s21_size str_len = s21_strlen(str);
    
    // Проверяем индекс ДО выделения памяти
    if (start_index > src_len) {
        return S21_NULL;
    }
    
    char *result = (char *)malloc(src_len + str_len + 1);
    if (result == S21_NULL) {
        return S21_NULL;
    }
    
    // Копируем первую часть до start_index
    s21_size i;
    for (i = 0; i < start_index; i++) {
        result[i] = src[i];
    }
    
    // Вставляем str
    for (s21_size j = 0; j < str_len; j++) {
        result[i + j] = str[j];
    }
    
    // Копируем остаток src
    for (s21_size j = start_index; j < src_len; j++) {
        result[i + str_len + (j - start_index)] = src[j];
    }
    
    result[src_len + str_len] = '\0';
    return result;
}


void *s21_trim(const char *src, const char *trim_chars) {
    if (src == S21_NULL) {
        return S21_NULL;
    }

    // Формируем набор символов для обрезки
    if (trim_chars == S21_NULL || s21_strlen(trim_chars) == 0) {
        trim_chars = "\t\n\v\f\r ";  // набор всех возможных пробельных символов
    }

    // Начало строки
    s21_size start = 0;
    while (src[start] != '\0' && s21_strchr(trim_chars, src[start]) != S21_NULL) {
        start++;
    }

    // Конец строки
    s21_size end = s21_strlen(src);
    while (end > start && s21_strchr(trim_chars, src[end - 1]) != S21_NULL) {
        end--;
    }

    // Длина новой строки
    s21_size new_len = end - start;
    char *result = (char *)malloc(new_len + 1);
    if (result == S21_NULL) {
        return S21_NULL;
    }

    // Копируем строку без начальных и конечных пробельных символов
    for (s21_size i = 0; i < new_len; i++) {
        result[i] = src[start + i];
    }
    result[new_len] = '\0';

    return result;
}