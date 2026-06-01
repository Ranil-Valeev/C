CC = gcc
CHECK_CFLAGS := $(shell pkg-config --cflags check 2>/dev/null)
CFLAGS = -Wall -Wextra -Werror -std=c11 -Wno-format $(CHECK_CFLAGS)

# Исходные файлы библиотеки (ВСЕ файлы .c кроме tests/)
LIB_SRC := $(wildcard *.c)
LIB_SRC := $(filter-out tests/%, $(LIB_SRC))
LIB_SRC := $(filter-out %test.c, $(LIB_SRC))

# Объектные файлы библиотеки
LIB_OBJ = $(LIB_SRC:.c=.o)

# Флаги для gcov (не для библиотеки)
GCOV_FLAGS = -coverage

UNAME := $(shell uname)
ifeq ($(UNAME), Darwin)
    GCOV_LIBS =
else
    GCOV_LIBS = -lgcov
endif

# Тестовые файлы
TEST_SRC := $(wildcard tests/s21_tests.c)
TEST_BIN = test_runner

# Библиотеки для тестов
LIBS = $(shell pkg-config --libs check 2>/dev/null) -lm -lpthread

# Файлы для форматирования
FMT_ROOT_C := $(wildcard *.c)
FMT_ROOT_H := $(wildcard *.h)
FMT_SUB_C  := $(wildcard */*.c)
FMT_SUB_H  := $(wildcard */*.h)
FMT_FILES := $(FMT_ROOT_C) $(FMT_ROOT_H) $(FMT_SUB_C) $(FMT_SUB_H)

.PHONY: all s21_string.a clean test sanitizer gcov_report clang cppcheck rebuild

# Только библиотека
all: s21_string.a

# Статическая библиотека (БЕЗ флагов gcov!)
s21_string.a: $(LIB_OBJ)
	ar rcs s21_string.a $(LIB_OBJ)
	ranlib s21_string.a

# Компиляция объектных файлов библиотеки (БЕЗ GCOV_FLAGS!)
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Тесты (отдельная цель)
test: s21_string.a
	$(CC) $(CFLAGS) $(GCOV_FLAGS) $(TEST_SRC) -o $(TEST_BIN) s21_string.a $(LIBS)
	./$(TEST_BIN)

# Отчет о покрытии
gcov_report: clean
	mkdir -p logs
	# Компилируем библиотеку с флагами покрытия
	$(CC) $(CFLAGS) $(GCOV_FLAGS) -c $(LIB_SRC)
	ar rcs s21_string.a $(LIB_OBJ)
	ranlib s21_string.a
	# Компилируем и запускаем тесты
	$(CC) $(CFLAGS) $(GCOV_FLAGS) $(TEST_SRC) -o logs/$(TEST_BIN) s21_string.a $(LIBS) $(GCOV_LIBS)
	./logs/$(TEST_BIN)
	# Генерируем отчет
	gcovr --html-details logs/report.html \
	      --exclude 'tests/*' \
	      --print-summary
	@echo "HTML-отчёт: logs/report.html"
	@open logs/report.html 2>/dev/null || true


# Валгринд-тесты
# valgrind_test: s21_string.a
# 	$(CC) $(CFLAGS) $(TEST_SRC) -o $(TEST_BIN) s21_string.a $(LIBS)
# 	valgrind --tool=memcheck --leak-check=full --show-reachable=yes --track-origins=yes ./$(TEST_BIN) | tee valgrind.txt


# Валгринд-тесты с фильтрацией системных ошибок
valgrind_test: s21_string.a
	$(CC) $(CFLAGS) $(TEST_SRC) -o $(TEST_BIN) s21_string.a $(LIBS)
	valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all \
	         --track-origins=yes --errors-for-leak-kinds=definite \
	         ./$(TEST_BIN) 2>&1 | \
	         grep -v "libobjc\|libxpc\|libdispatch\|libSystem\|dyld\|in /usr/lib\|in /System/Library\|objc::\|_objc_\|map_images\|realizeClass" \
	         | grep -v "xpc_\|_xpc_\|dispatch_\|_dispatch_\|os_object" \
	         | tee valgrind.txt
	@echo ""
	@echo "=== РЕЗУЛЬТАТЫ ВАШЕГО КОДА (фильтровано) ==="
	@if grep -q "ERROR SUMMARY: 0 errors" valgrind.txt; then \
	    echo "✓ Память в порядке!"; \
	else \
	    echo "Посмотрите файл valgrind.txt для деталей"; \
	fi


# Форматирование
clang:
	@if [ -n "$(FMT_FILES)" ]; then \
	    clang-format -n $(FMT_FILES); \
	    clang-format -i $(FMT_FILES); \
	else \
	    echo "Нет файлов для форматирования."; \
	fi

# Проверка
cppcheck:
	cppcheck --enable=all \
	         --suppress=missingIncludeSystem \
	         --suppress=unusedStructMember \
	         --suppress=unmatchedSuppression \
	         --suppress=checkersReport \
	         *.c */*.c *.h */*.h

# Очистка
clean:
	rm -f $(TEST_BIN)
	rm -f s21_string.a
	rm -rf logs
	rm -rf *.txt
	find . -name '*.gcda' -delete
	find . -name '*.gcno' -delete
	find . -name '*.gcov' -delete
	rm -f *.o
	rm -f */*.o

# Пересборка
rebuild: clean all