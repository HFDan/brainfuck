#include <cstdlib>
#include <cstring>
#include <cstdint>
#include <iostream>
#include <fstream>
#include <cerrno>
#include <vector>
#include <stack>

int main(int argc, char** argv) {
    unsigned int stackSize = 30000;
    [[maybe_unused]] bool extensions = false;
    [[maybe_unused]] bool verboseOutput = false;
    const char* file = nullptr;

	for (int i = 1; i < argc; i++) {

		if (strcmp(argv[i], "-s") == 0) {
			stackSize = (unsigned int)atoi(argv[i+1]);
            if (stackSize == 0) { // Atoi error
                fprintf(stderr, "Invalid stack size\n");
                std::exit(EINVAL);
            }
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

    if (file == nullptr) {
        fprintf(stderr, "Please specify a file to open!\n");
        std::exit(EINVAL);
    }

    std::vector<unsigned char> mem(stackSize);
    size_t addy = 0;

    std::ifstream source(file);

	if (source.fail()) {
		fprintf(stderr, "File %s does not exist! Aborting...\n", file);
		std::exit(ENOENT);
	}

    std::stack<int64_t> jumptable;

    char instruction;
	while (source >> instruction) {
		switch (instruction) {
			
			case '+':
				mem[addy]++;
				break;

			case '-':
				mem[addy]--;
				break;

			case '>':
				addy++;
				break;

			case '<':
				addy--;
				break;

			case ',':
				{
				char input;
				scanf("%c", &input);
				mem[addy] = input;
				break;
				}

			case '.':
				printf("%c", (char)mem[addy]);
				break;
                
            case '[':
            {
                if (mem[addy] == 0) {
                    char foo = '\0';
                    while (foo != ']')
                        source >> foo;
                } else {
                    jumptable.push(source.tellg());
                }
                break;
            }

            case ']':
            {
                if (mem[addy] != 0) {
                    source.seekg(jumptable.top());
                } else {
                    jumptable.pop();
                }
                break;
            }

			default:
				// Anything that is not an instruction is automatically a comment and will be ignored
				break;
		
		}
	}
	
    source.close();

    return EXIT_SUCCESS;
}