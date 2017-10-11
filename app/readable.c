#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <limits.h>
#include <math.h>
#include "includes/endian.h"

char* char_to_binary(char k) {
    static char c[65];
    c[0] = '\0';

    unsigned char val;
    for (val = 1UL << (sizeof(char)*8-1); val > 0; val >>= 1) {
        strcat(c, ((k & val) == val) ? "1" : "0");
    }
    return c;
}

int readable_to_internal(char *ip_address, int endianness) {
	long segment_array[4];
	int i = 0;
	char *token;
	const char *c = ".";

	// Split string to tokens
	token = strtok(ip_address, c);
	errno = 0;
	while (token != NULL) {
		long segment = strtol(token,NULL,10);
		if (errno != 0 || segment < 0 || segment > 255) {
			return 0;
		}
		segment_array[i++] = segment;
		// Continue processing
		token = strtok(NULL, c);
	}

	if (endianness) {
		// big-endian
		//to_big_endian(segment_array);
	} else {
		// little-endian
		to_little_endian(segment_array);
	}

	// Convert decimals to binary
	// Convert binary to decimal
	char * many_bits = malloc(32+1);
	for (i = 0; i < 4; i++) {
		char *b = malloc(9);
		b = char_to_binary(segment_array[i]);
		strcat(many_bits,b);
	}

	// Convert binary to decimal
	long l;
	char *endptr;
	unsigned long val = strtol(many_bits,&endptr,2);
	//printf("bits:%s\n",many_bits);
	printf("%lu\n",val);

	return 1;
}