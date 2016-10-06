WARNING = -Wall

ARG =

ALL = utils.o
EXECUTABLES = tester shell

default: clean shell tester

debug: default
	valgrind --leak-check=full -v ./shell

shell: ${ALL}
	${CC} ${WARNING} $@.c ${ALL} -o $@

tester: ${ALL}
	${CC} ${WARNING} $@.c ${ALL} -o $@

utils.o:
	${CC} ${WARNING} -c $(basename $@).c

clean:
	rm ${ALL} ${EXECUTABLES}
