#include <stdio.h>
#include <time.h>

double mytime() {
  struct timespec t;
  clock_gettime(CLOCK_REALTIME,&t);
  return t.tv_sec + t.tv_nsec/1000.0/1000.0/1000.0;
}

int main() {
  for(long i = 1;;i<<=1) {
    double t0 = mytime();
    for(int j = 0; j < i; j++);
    double t1 = mytime();
    printf("%lf\n", i/(t1-t0));
  }
}
