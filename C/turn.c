#include <time.h>
#include <stdio.h>
#include <math.h>
#include "MyroC.h"

const int width = 256, height = 192, stdevish = 10;
const double speed = .5, time_guess=6, sensetivity = .0005;


double doubletime() {
  struct timespec t;
  clock_gettime(CLOCK_REALTIME,&t);
  return t.tv_sec + t.tv_nsec/1000.0/1000.0/1000.0;
}
void doublesleep(double t) {
  rBeep(t, 400);
  // struct timespec ts = {(time_t) ((long) t), (long) ((t-((long) t))*1000*1000*1000)};
  //	nanosleep(&ts, NULL);
}
double normal(double x, double y) {
  return exp(-(x-y)*(x-y)/stdevish/stdevish);
}

int main() {
  printf("Init\n");

  Picture p0;
  double dist_traveled = 0;

  rConnect("/dev/rfcomm0");
  printf("Started\n");

  for(int n = 0;;n++) {
    rBeep(1, 550);

    rMotors(-speed, speed);
		
    double t0 = doubletime();
		
    Picture p = rTakePicture();

    //------------------------------------------------------------------------

    double dist_to_travel;
    if(n == 0) {
      p0 = p;
      dist_to_travel = 1;
    }
    else {
      double bestval = -1;
      int best_offset;

      for(int offset = -width; offset < width; offset++) {
        double value = 0;
        for(int x = 0; x < width && x+offset < width; x++)
          if(x + offset >= 0)
            for(int y = 0; y < height; y++) {
              value += normal(p.pix_array[y][x+offset].R, p0.pix_array[y][x].R);
              value += normal(p.pix_array[y][x+offset].G, p0.pix_array[y][x].G);
              value += normal(p.pix_array[y][x+offset].B, p0.pix_array[y][x].B);
            }
        value /= width+2*(width-(offset < 0 ? -offset : offset));

        if(value > bestval) {
          bestval = value;
          best_offset = offset;
        }
      }

      double position = -best_offset*sensetivity;
      printf("position: %f\n", position);
      dist_to_travel = (1-position)*dist_traveled/(n+position);
    }

    dist_traveled += dist_to_travel;

    //------------------------------------------------------------------------

    double travel_time = time_guess*dist_to_travel;

    double t1 = doubletime();
    doublesleep(t0+travel_time-t1);

    rMotors(0, 0);
  }
}
