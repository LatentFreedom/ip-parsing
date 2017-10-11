#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <limits.h>
#include <math.h>
#include "includes/endian.h"

int convertBinaryToDecimal(long n)
{
    int decimalNumber = 0, i = 0, remainder;
    while (n!=0)
    {
        remainder = n%10;
        n /= 10;
        decimalNumber += remainder*pow(2,i);
        ++i;
    }
    return decimalNumber;
}

char* long_to_binary(unsigned long k, int endianness) {
	long segment_array[4];
    static char c[65];
    c[0] = '\0';

    // Convert long to char binary
    unsigned long val;
    for (val = 1UL << (sizeof(int)*8-1); val > 0; val >>= 1) {
        strcat(c, ((k & val) == val) ? "1" : "0");
    }

    // Split binary string into 4 8 length segments
	int i, j;
	for (i = 0; i < 4; i++) {
		char temp[8];
		for (j = 0; j < 8; j++) {
			temp[j] = c[i*8+j];
		}
		segment_array[i] = strtol(temp,NULL,10);
		segment_array[i] = convertBinaryToDecimal(segment_array[i]);
	}

	// Endianess
	if (endianness) {
		// big-endian
		//to_big_endian(segment_array);
	} else {
		// little-endian
		to_little_endian(segment_array);
	}

	// Convert each bit segment into long
	char ip_address[16];
	ip_address[0] = '\0';
	for (i = 0; i < 4; i++) {
		char temp[4];
		sprintf(temp, "%ld", segment_array[i]);
		strcat(ip_address,temp);
		if (i < 3)
			strcat(ip_address,".");
	}

	printf("%s\n",ip_address);
    return c;
}

int internal_to_readable(char *ip_address, int endianness) {
	long segment_array[4];
	int i, j;
	const char *c = ".";
	// Convert decimals to binary
	unsigned long l = strtol(ip_address,NULL,10);
	char *b = malloc(33);
	b = long_to_binary(l,endianness);

	return 1;
}

