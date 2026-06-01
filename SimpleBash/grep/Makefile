CC = gcc
CFLAGS = -Wall -Werror -Wextra -std=c11
TARGET = s21_grep

SOURCES = s21_grep.c 
HEADERS = s21_grep.h
OBJECTS = $(SOURCES:.c=.o)



all: $(TARGET)

$(TARGET): $(SOURCES) $(HEADERS)
	$(CC) $(CFLAGS) -o $(TARGET) $(SOURCES)

clean:
	rm -f $(TARGET)