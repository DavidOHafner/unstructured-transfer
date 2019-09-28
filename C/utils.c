#include "utils.h"

void * ptr_to_int(int x){
  int * out = alloc(int);
  *out = x;
  return out;
}
void * ptr_to_long(long x){
  long * out = alloc(long);
  *out = x;
  return out;
}
void * ptr_to_double(double x){
  double * out = alloc(double);
  *out = x;
  return out;
}
void * ptr_to_float(double x){
  double * out = alloc(double);
  *out = x;
  return out;
}
