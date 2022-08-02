FLAGS = g++ -g -std=c++17 -Wall -Wextra #-Werror
OS = $(shell uname)
ifeq ($(OS), Linux)
	CHECK_FLAGS = -lgtest -pthread
else
	CHECK_FLAGS = -lgtest
endif

TEST_COMPILE = $(FLAGS) tests.cpp $(CHECK_FLAGS)

all: clean test

clean:
	rm -rf *.o *.g* *.info *.gcov_report report *.a *.dSYM a.out

gcov_report: gcov_report_build
	rm -rf *.gcda
	rm -rf *.gcno
	rm -rf *.info

gcov_report_build: vector.h
	$(FLAGS) tests.cpp $(CHECK_FLAGS) --coverage -o gcov_report
	./gcov_report
	lcov -t "./gcov_report" -o gcov_report.info -c -d .
	genhtml -o report gcov_report.info
	open ./report/index.html

test:
	$(TEST_COMPILE)
	./a.out

check_leaks:
	make test
ifeq ($(OS), Darwin)
	CK_FORK=no leaks --atExit -- ./a.out
else
	valgrind ./a.out --leak-check=full
endif

	make clean

check_style:
	python3 ../materials/linters/cpplint.py --extensions=cpp *.cpp *.h
