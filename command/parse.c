#include "parse.h"


CommandLine* parseCommand(char* raw) {
	Vector* commands = vectorConstruct(2);

	// parse stuff
	uint64_t bufferSize = ASH_BUFFER_SIZE;
	uint64_t bufferIndex = 0;
	uint64_t index = 0;

	char* buffer = malloc(sizeof (*buffer) * bufferSize);
	Vector* args = vectorConstruct(2);
	char quotation = '\0';

	bool baseFound = false;

	while (raw[index] != '\0' && raw[index] != '\n') {
		// deal with quotations
		if (raw[index] == '\'' || raw[index] == '"') {
			if (quotation == '\0') {
				// beginning
				quotation = raw[index];

				index += 1;
				continue;
			} else if (quotation == raw[index]) {
				// end
				buffer[bufferIndex] = '\0';
				vectorPush(args, buffer);
				bufferSize = ASH_BUFFER_SIZE;
				bufferIndex = 0;
				buffer = malloc(sizeof (*buffer) * bufferSize);
				quotation = '\0';

				index += 1;
				continue;
			}
		}

		if (quotation == '\0' && raw[index] == ' ') {
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
			continue;
		}

		if (bufferIndex == bufferSize) {
			bufferSize *= ASH_INCREASE_FACTOR;
			buffer = realloc(buffer, sizeof (*buffer) * bufferSize);
		}

		buffer[bufferIndex] = raw[index];

		index++;
		bufferIndex++;
	}

	if (quotation != '\0') {
		// error clean up
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
