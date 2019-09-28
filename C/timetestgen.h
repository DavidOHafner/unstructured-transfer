#ifndef TIMETESTGEN
#define TIMETESTGEN

#include "doubletime.h"
#include "utils.h"
#include <stdio.h>
#include <math.h>

#define start(ntype, n0, inc) \
int main() { \
  for(ntype n = n0;; n*=2) { \
    double starttime = doubletime();

#define end(kexp) \
    double endtime = doubletime(); \
    printf("n = %d, K = %lf\n", n, 600*1000*1000*(endtime-starttime)/(kexp)); \
  }\
  return 1;\
}\

#endif
