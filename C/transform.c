#include "array_type.h"
#include "utils.h"
#include <stdlib.h>
#include <math.h>
#include <string.h>

void convolute2D(void * array, int * sz, float * convolution, int channel) {
	float buffer[sz[channel]];
	for(int i = 0; i < sz[1-channel]; i++) {
		for(int j = 0; j < sz[channel]; j++) {
			int index[] = {i, j};
			buffer[j] = get_type(float, array, index);
			set_type(float, array, index, 0);
		}
		for(int j1 = 0; j1 < sz[channel]; j1++)
			for(int j2 = 0; j2 < sz[channel]; j2++) {
				int index1[] = {i, j1};
				int index2[] = {i, j2};

				set_type(float, array, index1, get_type(float, array, index1) + get_type(float, array, index2)*buffer[abs(j1-j2)]);
			}
	}
}
void blur2D(void * array, float stdev) {
	int * sz = size(array);
	int max_sz = MAX(sz[0], sz[1]);
	float normal[max_sz];
	float var = stdev*stdev;
	for(int i = 0; i < max_sz; i++)
		normal[i] = exp(-i*i/2/var)/sqrt(2*M_PI*var);

	convolute2D(array, sz, normal, 0);
	convolute2D(array, sz, normal, 1);
}
