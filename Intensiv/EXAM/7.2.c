#include <stdio.h>
#include <string.h>

void removeLast(char *str, const char *sub){
    char *pos = strrstr(str, sub);
    if(pos != NULL){
        memmove(pos, pos + strlen(sub), strlen(pos + strlen(sub)) + 1);
    }
}

char *strrstr(counsr char *haystack, counst char *needle){
    char *result = NULL;
    char *current = (char *)haystack;

    while ((current = strstr(current, needle)) != NULL) {
        result = current; // Запоминаем текущее вхождение
        current++; // Продолжаем поиск с следующего символа
    }
    return result; // Возвращаем последнее вхождение
}

int main() {
    char str[100];
    const char *sub = "my";


    fgets(str, sizeof(str), stdin);
    
    // Удаляем символ новой строки, если он есть
    str[strcspn(str, "\n")] = '\0';

    removeLastOccurrence(str, sub); // Удаляем последнее вхождение подстроки

    printf("%s", str); // Выводим результат

    return 0;
}