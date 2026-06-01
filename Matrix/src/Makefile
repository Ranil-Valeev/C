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
# Исходные файлы библиотеки matrix (все .c файлы в текущей директории)
LIB_SRC := $(wildcard s21_*.c)  # Предполагаем, что файлы начинаются с s21_
LIB_OBJ := $(LIB_SRC:.c=.o)

# Тестовые файлы
# TEST_SRC := tests/s21_tests_3.c  # Или $(wildcard tests/*.c)
TEST_SRC := $(wildcard tests/*.c)
TEST_BIN := test_matrix_runner

# Флаги для покрытия
GCOV_FLAGS := -coverage

# Файлы для форматирования
FMT_FILES := $(wildcard *.c *.h */*.c */*.h)

# ===================== PHONY ЦЕЛИ =====================
.PHONY: all clean test s21_matrix.a matrix gcov_report valgrind_test clang cppcheck rebuild help lcov_install gcovr_report

# ===================== ОСНОВНЫЕ ЦЕЛИ =====================
all: s21_matrix.a

# ===================== МЕНЮ "help" ========================
help:
	@echo "Доступные команды:"
	@echo "  make all           - собрать библиотеку s21_matrix.a"
	@echo "  make s21_matrix.a  - собрать библиотеку"
	@echo "  make matrix        - собрать библиотеку"
	@echo "  make test          - запустить тесты"
	@echo "  make gcov_report   - отчет покрытия кода gcov"
	@echo "  make gcovr_report  - отчет покрытия кода gcovr"
	@echo "  make valgrind_test - проверка памяти"
	@echo "  make clean         - очистка"
	@echo "  make clang         - форматирование кода"
	@echo "  make cppcheck      - статический анализ"
	@echo "  make rebuild       - полная пересборка"
	@echo "  make lcov_install  - установка lcov"

# Статическая библиотека matrix
s21_matrix.a: $(LIB_OBJ)
	ar rcs s21_matrix.a $(LIB_OBJ)
	ranlib s21_matrix.a

# Синоним для удобства
matrix: s21_matrix.a

# Компиляция объектных файлов (обычная, без gcov)
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

logs:
	mkdir -p logs

# ===================== ТЕСТИРОВАНИЕ =====================
test: s21_matrix.a
	$(CC) $(CFLAGS) $(TEST_SRC) -o $(TEST_BIN) s21_matrix.a $(LIBS)
	./$(TEST_BIN)

# ===================== ПОКРЫТИЕ КОДА GCOVR =====================
gcovr_report: clean | logs
	# Компилируем библиотеку С флагами покрытия
	$(CC) $(CFLAGS) $(GCOV_FLAGS) -c $(LIB_SRC)
	ar rcs s21_matrix.a $(LIB_OBJ)
	ranlib s21_matrix.a
	# Компилируем и запускаем тесты С флагами покрытия
	$(CC) $(CFLAGS) $(GCOV_FLAGS) $(TEST_SRC) -o logs/$(TEST_BIN) s21_matrix.a $(LIBS) $(GCOV_LIBS)
	-./logs/$(TEST_BIN)  # Дефис для игнорирования ошибок тестов
	# Генерируем отчет
	gcovr --html-details logs/report.html \
	      --exclude 'tests/*' \
	      --exclude 'usr/*' \
	      --print-summary
	@echo "HTML-отчёт: logs/report.html"
	@open logs/report.html 2>/dev/null || echo "Открыть вручную: logs/report.html"

# ===================== ПОКРЫТИЕ КОДА GCOV =====================
gcov_report: clean lcov_install | logs
	# Компилируем с флагами покрытия
	$(CC) $(CFLAGS) $(GCOV_FLAGS) -c $(LIB_SRC)
	ar rcs s21_matrix.a $(LIB_OBJ)
	ranlib s21_matrix.a
	
	# Компилируем и запускаем тесты
	$(CC) $(CFLAGS) $(GCOV_FLAGS) $(TEST_SRC) -o logs/$(TEST_BIN) s21_matrix.a $(LIBS) $(GCOV_LIBS)
	-./logs/$(TEST_BIN)  # Дефис для игнорирования ошибок тестов
	
	# Генерируем отчет с игнорированием ошибок неиспользуемых паттернов
	lcov --capture --directory . --output-file logs/coverage.info --ignore-errors unused
	lcov --remove logs/coverage.info '/usr/*' '*/tests/*' --output-file logs/coverage_filtered.info --ignore-errors unused
	genhtml logs/coverage_filtered.info --output-directory logs/coverage_report
	
	@echo "HTML-отчёт: logs/coverage_report/index.html"
	@open logs/coverage_report/index.html 2>/dev/null || \
	     xdg-open logs/coverage_report/index.html 2>/dev/null || \
	     echo "Открыть вручную: logs/coverage_report/index.html"

# ===================== ПРОВЕРКА ПАМЯТИ =====================
valgrind_test: clean s21_matrix.a | logs
	$(CC) $(CFLAGS) $(TEST_SRC) -o $(TEST_BIN) s21_matrix.a $(LIBS)
	valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all \
	         --track-origins=yes --errors-for-leak-kinds=definite \
	         ./$(TEST_BIN) 2>&1 | \
	         grep -v "libobjc\|libxpc\|libdispatch\|libSystem\|dyld\|in /usr/lib\|in /System/Library" \
	         | tee logs/valgrind.txt
	@echo "=== РЕЗУЛЬТАТЫ ВАШЕГО КОДА ==="
	@if grep -q "ERROR SUMMARY: 0 errors" logs/valgrind.txt; then \
	    echo "\033[1;32m+++ Память в порядке! +++\033[0m"; \
	else \
	    echo "\033[1;31m Найдены ошибки памяти...\033[0m Смотрите logs/valgrind.txt"; \
	fi

# ======================= ФОРМАТ ========================
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

# ====================== CPPCHECK ==========================
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

# ===================== УСТАНОВКА LCOV =====================
lcov_install:
	@if ! command -v lcov >/dev/null 2>&1; then \
		echo "\033[1;33mУстанавливаю lcov...\033[0m"; \
		if command -v brew >/dev/null 2>&1; then \
			brew install lcov; \
		elif command -v apt-get >/dev/null 2>&1; then \
			sudo apt-get update && sudo apt-get install -y lcov; \
		else \
			echo "\033[1;31mНе удалось определить менеджер пакетов.\033[0m Установите lcov вручную."; \
			exit 1; \
		fi \
	else \
		echo "\033[1;32mlcov уже установлен.\033[0m"; \
	fi

# ===================== ОЧИСТКА =====================
clean:
	rm -f $(TEST_BIN) s21_matrix.a
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
debug: clean s21_matrix.a
	$(CC) $(CFLAGS) $(TEST_SRC) -o $(TEST_BIN)_debug s21_matrix.a $(LIBS)
	@echo "Собран отладочный бинарник: $(TEST_BIN)_debug"

# Быстрая проверка компиляции
check:
	$(CC) $(CFLAGS) -c $(LIB_SRC)
	@echo "\033[1;32m Компиляция успешна! \033[0m"
	rm -f *.o
