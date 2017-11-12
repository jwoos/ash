CC = gcc
CFLAGS = -Wall -Wextra -std=gnu11 -ggdb -O0
LDLIBS =
LDFLAGS =

# data/vector.o data/linked-list.o data/hash-table.o
OBJECTS = utils/etc.o utils/io.o utils/string.o utils/math.o \
		  command/command.o command/line.o command/parse.o \
		  data/vector.o \
		  vendor/hash.o \
		  shell.o

EXECUTABLES = tester ash

default: clean ash

test: clean tester

debug-memory: default
	valgrind --leak-check=full -v ./ash

debug-gdb: default
	gdb ash

# implicit rule for %.o
# $(CC) $(CPPFLAGS) $(CFLAGS) -c $@

# shell main
ash: $(OBJECTS)
	$(CC) $(CFLAGS) main.c $^ $(LDFLAGS) $(LDLIBS) -o $@

# separate compilation point for testing reasons
tester: tester.c $(OBJECTS)

clean-objects:
	touch $(OBJECTS) && rm $(OBJECTS)

clean-executables:
	touch $(EXECUTABLES) && rm $(EXECUTABLES)

clean: clean-objects clean-executables
