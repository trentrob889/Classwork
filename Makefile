.PHONY: all memcheck clean test coverage

CXXFLAGS = -g -O3 -Wpedantic -Wall -Wextra -Wmisleading-indentation -Wunused -Wuninitialized -Wshadow -Wconversion -Werror -std=c++17

OBJS =  hw5Tests  

all: ${OBJS}

memcheck: clean hw5Tests 
	valgrind --leak-check=summary ./hw5Tests


coverage: CXXFLAGS = -Wpedantic -Wall -Wextra -Wmisleading-indentation -Wunused -Wuninitialized -Wshadow -Wconversion -Werror -std=c++17 --coverage -fprofile-arcs
coverage: clean hw5Tests
	./hw5Tests
	gcov -r -k DListT.cpp
	
	
test: hw5Tests
	./hw5Tests  --report_level=short  --log_level=test_suite

main: DListT.o
hw5Tests: DListT.o
DListT.o: DListT.h


clean:
	rm -f ${OBJS} *.o *.gcov *.gcno *.gcda
