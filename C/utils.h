#ifndef UTILS
#define UTILS

#include <stdlib.h>
#define alloc(type) malloc(sizeof(type))
#define MIN(a, b) ((a) > (b)? (b) : (a))
#define MAX(a, b) ((a) < (b)? (b) : (a))
#define SWAP(type, a, b) {type c = (a); (a) = (b); (b) = c;}

void * ptr_to_int(int x);
void * ptr_to_long(long x);
void * ptr_to_double(double x);
void * ptr_to_float(double x);

#endif
