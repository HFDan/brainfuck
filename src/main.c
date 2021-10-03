#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef unsigned char byte;

signed int stackSize = 30000;
bool extensions = false;

int main(int argc, char** argv) {

	for (int i = 1; i < argc; i++) {

		if (strcmp(argv[i], "-s") == 0)
			stackSize = (signed int)(*argv[i+1] - '0');

		if (strcmp(argv[i], "-e") == 0)
			extensions = true;
			
	}

	byte* mogus = (byte*)malloc(5*sizeof(byte));

	*mogus = 'z';
	++mogus;
	++mogus;
	*mogus = 'e';
	
	printf("%c, %c\n", mogus[0], mogus[2]);
	
	printf("DEBUG %c\n", *argv[1]);

	return 0;
}
