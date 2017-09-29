CC = gcc
WARNING = -Wall -Wextra
OPTIMIZE = -O0
DEBUG = -ggdb
STD = -std=gnu11
CFLAGS = $(WARNING) $(OPTIMIZE) $(DEBUG) $(STD)
LDLIBS =
LDFLAGS =

OBJECTS = utils.o shell.o vector.o
EXECUTABLES = tester ash

default: clean ash

test: clean tester

debug: default
	valgrind --leak-check=full -v ./ash

# shell main
ash: ${OBJECTS}
	${CC} ${ARGS} $@.c $^ -o $@

# separate compilation point for testing reasons
tester: ${OBJECTS}
	${CC} ${ARGS} $@.c $^ -o $@

%.o: %.cpp
	${CXX} ${ARGS} -c $^ -o $@

clean: .FORCE force
	rm ${OBJECTS} ${EXECUTABLES}

force:
	touch ${OBJECTS} ${EXECUTABLES}

.FORCE:

