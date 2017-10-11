#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <limits.h>
#include <math.h>

void print_error(char *err) {
	//printf("Error: %s\n", err);
	printf("ERROR\n");
}

int valid_ip(char *ip_address) {
	int period_count = 0;
	char *token;
	const char *c = ".";
	int i;

	// Check for 3 periods
	for (i = 0; i < strlen(ip_address); i++) {
		if (ip_address[i] == '.') {
			period_count++;
		}
	}

	if (period_count != 3) {
		print_error("Not enough periods!");
		return 0;
	}

	// Split string to tokens
	token = strtok(ip_address, c);
	errno = 0;
	while (token != NULL) {
		long segment = strtol(token,NULL,10);
		if (errno != 0 || segment < 0 || segment > 255) {
			print_error("Invalid ip format.");
			return 0;
		}
		// Continue processing
		token = strtok(NULL, c);
	}

	return 1;
}

int validate_arguments(char *argv[]) {
	char *p1s;
	char *p2s;
	char *p3s;
	long p1n, p3n;
	long long p2n;

	// p1 [0|1] 0 convert IP address Readable -> Internal format
	// 			1 perform in opposite direction.
	p1s = argv[0];
	p1n = strtol(p1s,NULL,10);
	if (errno != 0 || (p1n != 0 && p1n != 1)) {
		print_error("p1 error");
		return 0;
	}


	// p2 [IP address] to be converted, either Readable format (when p1=0) or in internal decimal format (when p1=1).
	p2s = argv[1];
	if (p1n) {
		// Internal -> Readable
		// IP address 255.255.255.255 is equal to 4294967295
		p2n = strtol(p2s,NULL,10);
		if (errno != 0 || p2n < 0 || p2n > 4294967295) {
			print_error("p2 readable ip format error");
			return 0;
		}
	} else {
		// Readable -> Internal
		if (!valid_ip(p2s)) {
			return 0;
		}

	}


	// p3 [0|1] indicating the endianness of the internal format: 0 for little-endian and 1 for big-endian.
	p3s = argv[2];
	p3n = strtol(p3s,NULL,10);
	if (errno != 0 || (p3n != 0 && p3n != 1)) {
		print_error("p3 error");
		return 0;
	}


	return 1;
}