#include <stdlib.h>
#include <string.h>
#include <stdio.h>
//TODO check for excessive allocation


int dimensions(void * array) {
	return ((int*)array)[0];
}

int * size(void * array) {
	int size = sizeof(int)*dimensions(array);
	return (int *) memcpy(malloc(size), ((int*)array)+2, size);
}

void * declare_array(int payload_size, int dimensions, int * size) {
	int data_size = payload_size;
	for(int i = 0; i < dimensions; i++)
		data_size *= size[i];
	int * out = malloc(sizeof(int)*(2+dimensions) + data_size);
	out[0] = dimensions;
	out[1] = payload_size;
	memcpy(out+2, size, sizeof(int)*dimensions);
	return (void *) out;
}

int get_address(void * array, int * indecies) {
	int d = dimensions(array);
	int size = 1, address = (d+2)*sizeof(int);
	for(int i = 0; i < d; i++) {//Loop through dimensions
		size *= ((int*)array)[1+i];
		address += size*indecies[i];
	}
	return address;
}

void * get(void * array, int * indecies) {
	return (void *)(((char*)array) + get_address(array, indecies));
}

void * clone(void * array) {
	int d = dimensions(array);
	int size = 1;
	for(int i = 1; i < d+2; i++)//Loop through dimensions and payload_size
		size *= ((int*)array)[i];
	size += (d+2)*sizeof(int);
	return memcpy(malloc(size), array, size);
}
