#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <limits.h>
#include <math.h>

#include "includes/validate.h"
#include "includes/endian.h"
#include "includes/internal.h"
#include "includes/readable.h"

/* Questions
- Should we remove leading 0s? 255.06.22.1
-
*/

// Parsing IP Addresses
int main(int argc, char *argv[]) {
	int i;
	char p2s[16];

	// Check for the correct amount of arguments
	if (argc != 4) {
		print_error("Invalid number of arguments");
		return 0;
	}

	// hold p2s because of token manipulation loses data
	strcpy(p2s,argv[2]);

	// Make sure all arguments are valid
	if (!validate_arguments(argv+1)) {
		return 0;
	}

	// Perform conversion
	int p1n = strtol(argv[1],NULL,10);
	int p3n = strtol(argv[3],NULL,10);
	if (p1n) {
		// Internal -> Readable
		internal_to_readable(p2s,p3n);
	} else {
		// Readable -> Internal
		readable_to_internal(p2s,p3n);
	}


}