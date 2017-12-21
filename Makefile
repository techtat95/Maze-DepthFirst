CFLAGS = -std=c99 -g -Wall -Wshadow --pedantic -Wvla -Werror
COVFLAGS = -fprofile-arcs -ftest-coverage
PROFFLAG = -pg
DEFINES = -DTEST_READ -DTEST_WRITE -DTEST_SORTID -DTEST_SORTFIRSTNAME -DTEST_SORTLASTNAME
VALGRIND = valgrind --tool=memcheck --leak-check=full
VALGRIND += --verbose --track-origins=yes  --log-file=
GCC = gcc $(CFLAGS) $(COVFLAGS)
OBJS = pa08.o 

all: pa08

pa08: pa08.o maze.o path.o solver.o
	$(GCC) pa08.o maze.o path.o solver.o -o pa08 -lm

pa08.o: pa08.c maze.h path.h
	$(GCC) -c pa08.c -o pa08.o

maze.o: maze.c maze.h
	$(GCC) -c maze.c -o maze.o

path.o: path.c path.h
	$(GCC) -c path.c -o path.o

solver.o: solver.c solver.h path.h
	$(GCC) -c solver.c -o solver.o

test: pa08
	for n in 1 2 3 4 5 6 7 8 9 10 ; do \
	  echo "Testing Maze #$$n" ; \
	./pa08 inputs/maze$$n ; \
	done

clean: 
	/bin/rm -f *.o
	/bin/rm -f testgen
	/bin/rm -f *.gcda *.gcno gmon.out *gcov
	/bin/rm -f pa08
	/bin/rm -f vallog

memory: pa08
	$(VALGRIND)vallog ./pa08 inputs/maze1


