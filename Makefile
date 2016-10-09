WARNING = -Wall

ARG =

ALL = utils.o shell.o sds.o
EXECUTABLES = tester ash

default: clean-ash ash

test: clean-tester tester

debug: default
	valgrind --leak-check=full -v ./shell

# shell main
ash: ${ALL}
	${CC} ${WARNING} $@.c ${ALL} -o $@

# separate compilation point for testing reasons
tester: ${ALL}
	${CC} ${WARNING} $@.c ${ALL} -o $@

# shell functionality
shell.o:
	${CC} ${WARNING} -c shell.c

# general usage functions
utils.o:
	${CC} ${WARNING} -c utils.c

sds.o:
	${CC} ${WARNING} -c sds/sds.c

clean-tester: clean-objects
	rm tester

clean-ash: clean-objects
	rm ash

clean-objects:
	rm ${ALL}

clean-executables:
	rm ${EXECUTABLES}

clean: clean-objects clean-executables
