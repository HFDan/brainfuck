#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef unsigned char byte;

signed int stackSize = 30000;
bool extensions = false;
bool verboseOutput = false;
char* file;

int main(int argc, char** argv) {

	for (int i = 1; i < argc; i++) {

		if (strcmp(argv[i], "-s") == 0) {
			stackSize = (signed int)(*argv[i+1] - '0');
			continue;
		}

		if (strcmp(argv[i], "-e") == 0) {
			extensions = true;
			continue;
		}

		if (strcmp(argv[i], "-v") == 0) {
			verboseOutput = true;
			continue;
		}

		////////////////////////////////////////////////////
		// WARNING: do not add any arguments after this line
		////////////////////////////////////////////////////
		
		// We only switch the pointers around instead of copying strings
		file = argv[i];

	}
	
	// Define the memory space that the brainfuck program is allowed to access
    byte* memorySpace = (byte*)malloc(stackSize*sizeof(byte));
    unsigned int address = 0; // The address starts at 0
    
	FILE* sourcecode = fopen(file, "r");
	if (sourcecode == NULL) {
	
		printf("File %s does not exist! Aborting...\n", file);
		exit(1);

	}
	
	while (!feof(sourcecode)) {
		char instruction;
		fscanf(sourcecode, "%c", &instruction);

		switch (instruction) {
			
			case '+':
				memorySpace[address]++;
				break;

			case '-':
				memorySpace[address]--;
				break;

			case '>':
				address++;
				break;

			case '<':
				address--;
				break;

			case ',':
				{
				char input;
				scanf("%c", &input);
				memorySpace[address] = input;
				break;
				}

			case '.':
				printf("%c", memorySpace[address]);
				break;

			default:
				// Anything that is not an instruction is automatically a comment and will be ignored
				break;
		
		}
	}
	
	fclose(sourcecode);

	return 0;
}
