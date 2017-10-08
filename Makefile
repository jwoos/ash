CC = gcc
CFLAGS = -Wall -Wextra -std=gnu11 -ggdb -O0
LDLIBS =
LDFLAGS =

OBJECTS = utils.o shell.o vector.o input.o
EXECUTABLES = tester ash

default: clean ash

test: clean tester

debug: default
	valgrind --leak-check=full -v ./ash


# implicit rule for %.o
# $(CC) $(CPPFLAGS) $(CFLAGS) -c $@

# shell main
ash: ${OBJECTS}
	$(CC) main.c $^ $(LDFLAGS) $(LDLIBS) -o $@

# separate compilation point for testing reasons
tester: tester.c ${OBJECTS}

clean-objects:
	touch ${OBJECTS} && rm ${OBJECTS}

clean-executables:
	touch ${EXECUTABLES} && rm ${EXECUTABLES}

clean: clean-objects clean-executables
