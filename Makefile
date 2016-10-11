ARGS = -Wall -std=gnu11 -ggdb -O0

ARG =

ALL = utils.o shell.o sds.o vector.o
EXECUTABLES = tester ash

default: clean-ash ash

test: clean-tester tester

debug: default
	valgrind --leak-check=full -v ./shell

# shell main
ash: ${ALL}
	${CC} ${ARGS} $@.c ${ALL} -o $@

# separate compilation point for testing reasons
tester: ${ALL}
	${CC} ${ARGS} $@.c ${ALL} -o $@

# shell functionality
shell.o:
	${CC} ${ARGS} -c shell.c

# general usage functions
utils.o:
	${CC} ${ARGS} -c utils.c

sds.o:
	${CC} ${ARGS} -c sds/sds.c

vector.o:
	${CC} ${ARGS} -c vector.c

objects: ${ALL}

clean-tester: clean-objects
	rm tester

clean-ash: clean-objects
	rm ash

clean-objects:
	rm ${ALL}

clean-executables:
	rm ${EXECUTABLES}

clean: clean-objects clean-executables
