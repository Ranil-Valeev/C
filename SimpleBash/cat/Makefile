CC = gcc
CFLAGS = -Wall -Werror -Wextra -std=c11
TARGET = s21_cat

SOURCES = s21_cat.c 
HEADERS = s21_cat.h
OBJECTS = $(SOURCES:.c=.o)



all: $(TARGET)

$(TARGET): $(SOURCES) $(HEADERS)
	$(CC) $(CFLAGS) -o $(TARGET) $(SOURCES)

clean:
	rm -f $(TARGET)
