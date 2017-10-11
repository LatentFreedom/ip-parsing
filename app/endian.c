#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <limits.h>
#include <math.h>

void to_big_endian(long *segment_array) {
	long segment;

	segment = segment_array[3];
	segment_array[3] = segment_array[0];
	segment_array[0] = segment;
	segment = segment_array[2];
	segment_array[2] = segment_array[1];
	segment_array[1] = segment;

}

void to_little_endian(long *segment_array) {
	long segment;
	// ERROR: need to implement
	segment = segment_array[3];
	segment_array[3] = segment_array[0];
	segment_array[0] = segment;
	segment = segment_array[2];
	segment_array[2] = segment_array[1];
	segment_array[1] = segment;
}