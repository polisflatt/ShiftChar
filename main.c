#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "translator.c"

#include "settings.h"

extern int errno;

operation parse_operations(char* operation) { /* Parse our operations */
	if (!strcmp(operation, "--addition")) {
		return addition;
	} else if (!strcmp(operation, "--multiplication")) {
		return multiplication;
	} else if (!strcmp(operation, "--subtraction")) {
		return subtraction;
	} else if (!strcmp(operation, "--division")) {
		return division;
	} else {
		return neither;
	}

}

int main(int argc, char** argv) {
	if (argc > 0) {
		if (!strcmp(argv[1], "--shift")) {
			if (argc < 2) {
				printf("Too few arguments\n");
				exit(1);
			}
			int defaults = 0;

			char* source = argv[2];
			char* operation = argv[3];
			shift_t shift_rate = atoi(argv[4]);
			
			if (!strcmp(operation, "--default-method") || !strcmp(operation, "-d")) {
				defaults = 1;
				strcpy(default_operation, operation);
				shift_rate = default_shift_rate;
			}

			if (!source || !operation || !shift_rate) {
				if (!defaults) {
					printf("Imperative arguments ignored!\n");
					exit(1);
				}
			}

			int op = parse_operations(operation);
			printf("e");
			printf("%s\n", op);
			printf("c");
			if (!strcmp(source, "--file")) {
				char* filename;
				
				if (defaults) {
					filename = (char*) malloc(sizeof argv[4]);
					filename = argv[4];
				} else {
					filename = (char*) malloc(sizeof argv[5]);
					filename = argv[5];
				}

				FILE* fp = fopen(filename, "r");

				if (!fp) {
					printf("Error opening file: %s\n", strerror(errno));
					exit(1);
				}

				char _buffer[256];

				while (fgets(_buffer, sizeof _buffer, fp) != NULL) {
					char* translation = shift(_buffer, strlen(_buffer), op, shift_rate); 
					printf("%s", translation);
				}
			
			} else if (!strcmp(source, "--stdin")) {
				char input[256];
				fgets(input, sizeof input, stdin);
				printf(input);
				
				char* translation = shift((const char*) input, strlen(input), op, shift_rate);

				printf("%s", translation);
			
			} else {
				printf("Invalid argument\n");
			}

		} else if (!strcmp(argv[1], "--help") || !strcmp(argv[1], "-h")) {
			printf("A program for basic encryption of text involving shifting of the int to char conversions in C.\n");
			printf("Usage: shiftchar [options] [source]\n");

			printf("-h, --help	Show this menu!\n");
			printf("-s, --shift	Shift chars [source: -s/--stdin or -f/--file] [operation: -a/--addition, -s/--subtraction, -m/--multiplication, -d/--division] [shift-rate: any number you want to do the operation against the char(s) with] [\n");

		}	
	}
	
	return 0;
}
