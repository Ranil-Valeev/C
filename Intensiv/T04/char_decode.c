#include <stdio.h>

void decode();
void encode();

int main(int argc, char *argv[]) {
  if (argc != 2) {
    printf("n/a");
    return 0;
  }

  if (argv[1][0] == '0') {
    encode();
  } else if (argv[1][0] == '1') {
    decode();
  } else {
    printf("n/a");
  }
  return 0;
}
void encode() {
  char c;
  while (1) {
    if (scanf(" %c", &c) != 1) {
      printf("n/a");
      return;
    }
    if (c == '\n') {
      break;
    }
    printf("%02X ", c);
  }
  printf("\n");
}

void decode() {
  char h1, h2;
  while (1) {
    if (scanf(" %c%c", &h1, &h2) != 2) {
      printf("n/a");
      return;
    }

    int num = 0;
    if (h1 >= '0' && h1 <= '9') {
      num = (h1 - '0') * 16;
    } else if (h1 >= 'A' && h1 <= 'F') {
      num = (h1 - 'A' + 10) * 16;
    } else {
      printf("n/a");
      return;
    }

    if (h2 >= '0' && h2 <= '9')
      num += h2 - '0';
    else if (h2 >= 'A' && h2 <= 'F')
      num += h2 - 'A' + 10;
    else {
      printf("n/a");
      return;
    }

    printf("%c ", num);

    char next;
    if (scanf("%c", &next) != 1 || next == '\n')
      break;
  }
  printf("\n");
}
