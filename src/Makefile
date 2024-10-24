CC=g++
CFLAGS= -Wall -Werror -Wextra -std=c++17
OS = $(shell uname)
SOURCES = s21_matrix_oop.cpp
TEST = tests.cpp
TFLAG = -lgtest -coverage

ifeq ($(OS),Linux)
    det_OS = -lm -lrt -lpthread
	for_lcov = 
else
    det_OS = -lpthread
	for_lcov = --ignore-errors inconsistent
endif


all: clean s21_matrix_oop.a gcov_report

test: clean
		$(CC) $(CFLAGS) $(SOURCES) $(TEST) -o test $(TFLAG) $(det_OS)
		./test

s21_matrix_oop.o:
		$(CC) $(CFLAGS) $(SOURCES) -c

s21_matrix_oop.a: s21_matrix_oop.o
		ar rcs s21_matrix_oop.a *.o
		ranlib s21_matrix_oop.a

gcov_report: test
		lcov --no-external -o res.info $(for_lcov) -c -d .
		genhtml -o report res.info
		open ./report/index.html

check:
		cp ../materials/linters/.clang-format ./
		clang-format -style=Google -n *.cpp *.h
		clang-format -style=Google -i *.cpp *.h
		rm .clang-format

valgrind: test
		CK_FORK=no valgrind --vgdb=no --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose -s ./test

clean:
		rm -rf ./comp report *.gc* *.o *.info *.a test.dSYM test

rebuild: clean all
