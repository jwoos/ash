WARNING = -Wall

ALL = utils
ALL_O = $(addsuffix .o, ${ALL})

default: clean shredder

debug: default
	valgrind --leak-check=full -v ./shredder

shredder: ${ALL}
	${CC} ${WARNING} $@.c ${ALL_O} -o $@
	./$@

tester: ${ALL}
	${CC} ${WARNING} $@.c ${ALL_O} -o $@
	./$@

utils:
	${CC} ${WARNING} -c $@.c

clean:
	rm ${ALL} shredder
