#ifndef ARRAY_TYPE
#define ARRAY_TYPE

#include "array.h"

#define get_type(type, array, indecies) *(type *)get(array, indecies)
#define set_type(type, array, indecies, value) *(type *)get(array, indecies) = value
#define declare_array_type(type, dimensions, size) declare_array(sizeof(type), dimensions, size)

#endif
