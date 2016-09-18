WARNING = -Wall

ALL =

default: clean shredder

debug: default
	valgrind --leak-check=full -v ./shredder

shredder: ${ALL}
	$(CC) ${WARNING} $@.c $^ -o $@
	./$@

clean:
	rm ${ALL} shredder
