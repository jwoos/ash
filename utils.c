#include <unistd.h>

void writeStdout(char message[], int bytes) {
	write(1, message, bytes);
}

/*char* readStdin(int fd) {}*/

