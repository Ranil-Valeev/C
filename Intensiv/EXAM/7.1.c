#include <stdio.h>
#include <string.h>
#include <ctype.h>

void removeExtraSpaces(char *str) {
    int i, j = 0;
    int inSpace = 0;

    for (i = 0; str[i] != '\0'; i++) {
        if (!isspace(str[i])) {
            str[j++] = str[i];
            inSpace = 0;
        } else if (!inSpace) {
            str[j++] = ' ';
            inSpace = 1;
        }
    }
    str[j] = '\0'; // Завершаем строку
}

int main() {
    char str[100];
    fgets(str, sizeof(str), stdin);
    str[strcspn(str, "\n")] = '\0';
    removeExtraSpaces(str); 
    printf("%s", str); 
    return 0;
}
