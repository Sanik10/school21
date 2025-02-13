CFLAGS_T = -Wall -Wextra -Werror -pedantic -std=c11 -fprofile-arcs -ftest-coverage
CFLAGS = -Wall -Wextra -Werror -pedantic -std=c11
GCOVFLAGS = -lcheck -lsubunit -fprofile-arcs -ftest-coverage

HEADERS = s21_string.h
SOURCES = s21_string.c s21_sscanf.c s21_sprintf.c
OBJ_FILES := $(patsubst %.c, %.o, $(SOURCES))

%.o: %.c $(HEADERS)
	gcc $(CFLAGS) -c $< -o $@

.PHONY: all test clean rebuild check

all: s21_string.a test gcov_report

s21_string.a: s21_string.o s21_sscanf.o s21_sprintf.o
	ar rcs $@ $^
	rm -rf *.o
	
test:
	gcc $(CFLAGS_T) -c s21_string.c s21_sscanf.c s21_sprintf.c s21_tests.c
	ar rcs libs21_string_test.a s21_string.o s21_sscanf.o s21_sprintf.o
	gcc $(CFLAGS) s21_tests.o -o s21_test $(GCOVFLAGS) -lm -L. -ls21_string_test
	./s21_test || true

gcov_report: test
	lcov --directory . --capture --output-file coverage.info
	genhtml coverage.info --output-directory coverage_report
	rm -f *.gcno *.gcda *.info *.out *.gcov

check:
	clang-format -style=Google -i ./*.c ./*.h

rebuild: clean all

clean:
	rm -f *.o *.a *.gcno *.gcda *.info *.out *.gcov
	rm -f s21_test
	rm -rf ./coverage_report
