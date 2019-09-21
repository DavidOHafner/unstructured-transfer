#include <time.h>
double mytime() {
  struct timespec t;
  clock_gettime(CLOCK_REALTIME,&t);
  return t.tv_sec + t.tv_nsec/1000.0/1000.0/1000.0;
}
