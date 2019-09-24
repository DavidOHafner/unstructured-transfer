#ifndef ARRAY
#define ARRAY

int dimensions(void * array);
int * size(void * array);
void * declare_array(int payload_size, int dimensions, int * size);
void * get(void * array, int * address);
void * clone(void * array);

#endif
