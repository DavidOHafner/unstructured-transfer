#include <time.h>

double doubletime() {
  struct timespec t;
  clock_gettime(CLOCK_REALTIME,&t);
  return t.tv_sec + t.tv_nsec/1000.0/1000.0/1000.0;
}

void doublesleep(double t) {
  struct timespec ts = {(time_t) ((long) t), (long) ((t-((long) t))*1000*1000*1000)};
  nanosleep(&ts, NULL);
}
