# ===================== НАСТРОЙКИ =====================
CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c11 -Wno-format

# Проверяем наличие check
CHECK_CFLAGS := $(shell pkg-config --cflags check 2>/dev/null)
ifneq ($(CHECK_CFLAGS),)
    CFLAGS += $(CHECK_CFLAGS)
endif

# Определяем ОС
UNAME := $(shell uname)
ifeq ($(UNAME), Darwin)
    # macOS
    GCOV_LIBS =
    CHECK_LIBS = $(shell pkg-config --libs check 2>/dev/null || echo "-lcheck")
else
    # Linux
    GCOV_LIBS = -lgcov
    CHECK_LIBS = $(shell pkg-config --libs check 2>/dev/null || echo "-lcheck -lrt -lm -lsubunit")
endif

# Дополнительные библиотеки
LIBS = $(CHECK_LIBS) -lm -lpthread

# ===================== ФАЙЛЫ =====================
# Исходные файлы библиотеки decimal (все .c файлы в текущей директории)
LIB_SRC := $(wildcard s21_*.c)  # Предполагаем, что файлы начинаются с s21_
LIB_OBJ := $(LIB_SRC:.c=.o)

# Тестовые файлы
# TEST_SRC := tests/s21_tests_3.c  # Или $(wildcard tests/*.c)
TEST_SRC := $(wildcard tests/*.c)
TEST_BIN := test_decimal_runner

# Флаги для покрытия
GCOV_FLAGS := -coverage

# Файлы для форматирования
FMT_FILES := $(wildcard *.c *.h */*.c */*.h)

# ===================== PHONY ЦЕЛИ =====================
.PHONY: all clean test decimal gcov_report valgrind_test clang cppcheck rebuild help

# ===================== ОСНОВНЫЕ ЦЕЛИ =====================
all: s21_decimal.a

help:
	@echo "Доступные команды:"
	@echo "  make all        - собрать библиотеку s21_decimal.a"
	@echo "  make decimal    - собрать библиотеку"
	@echo "  make test       - запустить тесты"
	@echo "  make gcov_report- отчет покрытия кода"
	@echo "  make valgrind_test - проверка памяти"
	@echo "  make clean      - очистка"
	@echo "  make clang      - форматирование кода"
	@echo "  make cppcheck   - статический анализ"
	@echo "  make rebuild    - полная пересборка"

# Статическая библиотека decimal
s21_decimal.a: $(LIB_OBJ)
	ar rcs s21_decimal.a $(LIB_OBJ)
	ranlib s21_decimal.a

# Синоним для удобства
decimal: s21_decimal.a

# Компиляция объектных файлов (обычная, без gcov)
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# ===================== ТЕСТИРОВАНИЕ =====================
test: s21_decimal.a
	$(CC) $(CFLAGS) $(TEST_SRC) -o $(TEST_BIN) s21_decimal.a $(LIBS)
	./$(TEST_BIN)

# ===================== ПОКРЫТИЕ КОДА =====================
gcov_report: clean
	mkdir -p logs
	# Компилируем библиотеку С флагами покрытия
	$(CC) $(CFLAGS) $(GCOV_FLAGS) -c $(LIB_SRC)
	ar rcs s21_decimal.a $(LIB_OBJ)
	ranlib s21_decimal.a
	# Компилируем и запускаем тесты С флагами покрытия
	$(CC) $(CFLAGS) $(GCOV_FLAGS) $(TEST_SRC) -o logs/$(TEST_BIN) s21_decimal.a $(LIBS) $(GCOV_LIBS)
	-./logs/$(TEST_BIN)  # Дефис для игнорирования ошибок тестов
	# Генерируем отчет
	gcovr --html-details logs/report.html \
	      --exclude 'tests/*' \
	      --exclude 'usr/*' \
	      --print-summary
	@echo "HTML-отчёт: logs/report.html"
	@open logs/report.html 2>/dev/null || echo "Открыть вручную: logs/report.html"

# ===================== ПРОВЕРКА ПАМЯТИ =====================
valgrind_test: s21_decimal.a
	$(CC) $(CFLAGS) $(TEST_SRC) -o $(TEST_BIN) s21_decimal.a $(LIBS)
	valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all \
	         --track-origins=yes --errors-for-leak-kinds=definite \
	         ./$(TEST_BIN) 2>&1 | \
	         grep -v "libobjc\|libxpc\|libdispatch\|libSystem\|dyld\|in /usr/lib\|in /System/Library" \
	         | tee logs/valgrind.txt
	@echo "=== РЕЗУЛЬТАТЫ ВАШЕГО КОДА ==="
	@if grep -q "ERROR SUMMARY: 0 errors" logs/valgrind.txt; then \
	    echo "✓ Память в порядке!"; \
	else \
	    echo "Найдены ошибки памяти. Смотрите logs/valgrind.txt"; \
	fi

# ===================== ФОРМАТИРОВАНИЕ И АНАЛИЗ =====================
clang:
	@if command -v clang-format >/dev/null 2>&1; then \
	    if [ -n "$(FMT_FILES)" ]; then \
	        echo "Форматирование файлов..."; \
	        clang-format -i $(FMT_FILES); \
	        echo "Готово!"; \
	    else \
	        echo "Нет файлов для форматирования."; \
	    fi \
	else \
	    echo "clang-format не установлен. Установите: sudo apt install clang-format"; \
	fi

cppcheck:
	@if command -v cppcheck >/dev/null 2>&1; then \
	    echo "Запуск cppcheck..."; \
	    cppcheck --enable=all \
	             --suppress=missingIncludeSystem \
	             --suppress=unmatchedSuppression \
	             --language=c \
	             *.c *.h tests/*.c tests/*.h 2>&1 | tee logs/cppcheck.txt; \
	    echo "Результаты в logs/cppcheck.txt"; \
	else \
	    echo "cppcheck не установлен. Установите: sudo apt install cppcheck"; \
	fi

# lcov:
# 	@if brew --version; then \
# 		if ! lcov --version; then \
# 			brew install lcov; \
# 		fi \
# 	else \
# 		sh script/brew_lcov.sh; \
# 		if ! lcov --version; then \
# 			brew install lcov; \
# 		fi \
# 	fi

# retest: clean test
# relcov: clean gcov_report

# ===================== ОЧИСТКА =====================
clean:
	rm -f $(TEST_BIN) s21_decimal.a
	rm -rf logs
	rm -rf *.txt coverage_report
	find . -name '*.gcda' -delete
	find . -name '*.gcno' -delete
	find . -name '*.gcov' -delete
	find . -name '*.o' -delete

# ===================== ПЕРЕСБОРКА =====================
rebuild: clean all

# ===================== ДОПОЛНИТЕЛЬНО =====================
# Цель для отладки (без -Werror)
debug: CFLAGS = -Wall -Wextra -std=c11 -g -O0
debug: clean s21_decimal.a
	$(CC) $(CFLAGS) $(TEST_SRC) -o $(TEST_BIN)_debug s21_decimal.a $(LIBS)
	@echo "Собран отладочный бинарник: $(TEST_BIN)_debug"

# Быстрая проверка компиляции
check:
	$(CC) $(CFLAGS) -c $(LIB_SRC)
	@echo "Компиляция успешна!"
	rm -f *.o