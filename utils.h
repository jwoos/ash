void writeStdout(char [], int);

void writeStderr(char [], int);

char* readStdin();

char getCharFromStdin();

void printError(char*, int);

char* getCommand(char*);

char** getArgs(char*);

char** parseCommand(char*);

char** generateEmptyStringArr();
