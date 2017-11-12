#include "parse.h"


CommandLine* parseCommand(char* raw) {
	Vector* commands = vectorConstruct(2);

	// parse stuff
	uint64_t bufferSize = ASH_BUFFER_SIZE;
	uint64_t bufferIndex = 0;
	uint64_t index = 0;

	char* buffer = malloc(sizeof (*buffer) * bufferSize);
	Vector* args = vectorConstruct(2);

	bool baseFound = false;

	while (raw[index] != '\0' && raw[index] != '\n') {
		if (raw[index] == ' ') {
			// push on the next space delimited string
			if (index != 0) {
				buffer[bufferIndex] = '\0';

				vectorPush(args, buffer);

				bufferSize = ASH_BUFFER_SIZE;
				bufferIndex = 0;
				buffer = malloc(sizeof (*buffer) * bufferSize);
			}

			// strip all whitespace
			while (raw[index] == ' ' && raw[index] != '\0' && raw[index] != '\n') {
				index++;
			}
		}

		if (bufferIndex == bufferSize) {
			bufferSize *= ASH_INCREASE_FACTOR;
			buffer = realloc(buffer, sizeof (*buffer) * bufferSize);
		}

		buffer[bufferIndex] = raw[index];

		index++;
		bufferIndex++;
	}

	if (buffer[0] != '\0') {
		vectorPush(args, buffer);
	}

	vectorPush(args, NULL);
	vectorPush(commands, commandConstruct(vectorGet(args, 0), args));

	return commandLineConstruct(raw, commands);
}

void cleanUpCommand(CommandLine* cl) {
	commandLineDeconstruct(cl, NULL);
}
