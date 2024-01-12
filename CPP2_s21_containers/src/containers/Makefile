CC=g++
STRICT_CFLAGS=-Wall -std=c++17 -Wextra -g -Werror
# STRICT_CFLAGS=-Wall -std=c++17 -Wextra -pedantic -g

OS = $(shell uname)
ifeq ($(OS), Darwin)
	LEAK_CHECK = leaks -atExit --
	OPEN_CMD = open
endif
ifeq ($(OS), Linux)
	LEAK_CHECK = valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes -s
	OPEN_CMD = xdg-open
endif

GCOVR_CFLAGS=-fprofile-arcs -ftest-coverage -fPIC
GCOVR_CFLAGS=--coverage
GCOVR_LFLAGS=-lgcov
GCOVR_LFLAGS=--coverage

GTEST_LFLAGS=-lgtest -lgtest_main

REPORT_DIRECTORY=report
VALGRIND_DIR=valgrind_report

TESTS_VECTOR_DIR=tests/vector
TESTS_QUEUE_DIR=tests/queue
TESTS_DIRS=tests

CC_DIR=./
H_DIR=./

# ALL_TESTS_C = $(notdir $(shell find $(TESTS_VECTOR_DIR) -maxdepth 1 -name "*.cc"))
# SOURCES = $(shell find $(TESTS_VECTOR_DIR) -maxdepth 1 -name "*.cc")
SOURCES = $(shell find $(CC_DIR) -name "*.cc")
SOURCES_TPP = $(shell find $(CC_DIR) -name "*.tpp")
HEADERS = $(shell find $(CC_DIR) -name "*.h")

BINARIES=$(patsubst %.cc,%.o,$(SOURCES))


all: test

test: run_tests gcov_report

tests/tests_main.exe: $(BINARIES)
		$(CC) -o $@ $^ $(GTEST_LFLAGS) $(GCOVR_LFLAGS) -g

%.o: %.cc $(HEADERS)
		$(CC) -c $(STRICT_CFLAGS) $< -o $@ $(GCOVR_CFLAGS) $(GTEST_CFLAGS)

run_tests: tests/tests_main.exe
		valgrind --tool=memcheck --leak-check=yes  ./tests/tests_main.exe


EXCLUDE_FROM_COVERAGE=--exclude-lines-by-pattern '.*assert.*' --exclude-throw-branches

gcov_report: run_tests
		mkdir -p $(REPORT_DIRECTORY)
		gcovr . --html --html-details $(EXCLUDE_FROM_COVERAGE) -o $(REPORT_DIRECTORY)/coverage_report.html
		$(OPEN_CMD) $(REPORT_DIRECTORY)/coverage_report.html  
# START "" $(REPORT_DIRECTORY)/coverage_report.functions.html  

valgrind: run_tests
		mkdir -p $(VALGRIND_DIR)
		-valgrind --leak-check=full --show-reachable=no --track-origins=yes --log-file=$(VALGRIND_DIR)/valgrind_report.txt -s ./tests/tests_main.exe > $(VALGRIND_DIR)/test_report.txt
		cat $(VALGRIND_DIR)/test_report.txt
		cat $(VALGRIND_DIR)/valgrind_report.txt

valgrind_full: run_tests
		mkdir -p $(VALGRIND_DIR)
		-valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --log-file=$(VALGRIND_DIR)/valgrind_full_report.txt -s ./tests/tests_main.exe > $(VALGRIND_DIR)/test_report.txt
		cat $(VALGRIND_DIR)/test_report.txt
		cat $(VALGRIND_DIR)/valgrind_full_report.txt

check_style:
		-clang-format --style=Google -n $(SOURCES)
		-clang-format --style=Google -n $(SOURCES_TPP)
		-clang-format --style=Google -n $(HEADERS)

format_style:
		-clang-format --style=Google -i $(SOURCES)
		-clang-format --style=Google -i $(SOURCES_TPP)
		-clang-format --style=Google -i $(HEADERS)

#clean

clean:
		find ./ -name *.o -delete
		find ./ -name *.gcda -delete
		find ./ -name *.gcno -delete
		find ./ -name *.gcov -delete
		find ./ -name *.exe -delete
		find ./ -name *.a -delete
		rm -rf $(REPORT_DIRECTORY)/*.css $(REPORT_DIRECTORY)/*.html
		rm -rf $(VALGRIND_DIR)/*.txt
