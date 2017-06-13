CC = gcc
WARNING = -Wall -Wextra
OPTIMIZE = -O0
DEBUG = -ggdb
STD = -std=gnu11
ARGS = $(WARNING) $(OPTIMIZE) $(DEBUG) $(STD)

ALL = utils.o shell.o vector.o
EXECUTABLES = tester ash

default: clean ash

test: clean tester

debug: default
	valgrind --leak-check=full -v ./ash

# shell main
ash: ${ALL}
	${CC} ${ARGS} $@.c $^ -o $@

# separate compilation point for testing reasons
tester: ${ALL}
	${CC} ${ARGS} $@.c $^ -o $@

%.o: %.cpp
	${CXX} ${ARGS} -c $^ -o $@

clean: .FORCE force
	rm ${ALL} ${EXECUTABLES}

force:
	touch ${ALL} ${EXECUTABLES}

.FORCE:

