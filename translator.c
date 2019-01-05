#include <stdio.h>
#include <string.h>
#include <stdint.h>

typedef enum operation { /* Mathematical/Arithimetical operations to use */
	division,
	multiplication,
	addition,
	subtraction,
	neither
} operation;


typedef int shift_t; /* Redundant? Might be useful when peering into code... */

char* shift(const char* str, size_t str_size, operation op, shift_t shift) {
	char* returned_str = (char*) malloc(str_size);

	for (int i = 0; i < str_size; i++) {
		switch (op) {
			case division:
				returned_str[i] = (char)(int) str[i] / shift;
				break;

			case multiplication:
				returned_str[i] = (char)(int) str[i] * shift;
				break;
			
			case addition:
				returned_str[i] = (char)(int) str[i] + shift;
				break;

			case subtraction:
				returned_str[i] = (char)(int) str[i] - shift;
				break;
		}

	}

	return returned_str;
}
