#include "doubletime.h"
#include <stdio.h>
#include <math.h>
#include "MyroC.h"

const int width = 256, height = 192, stdevish = 10;
const double speed = .7, time_guess=5, sensetivity = .0005;


double normal(double x, double y) {
  return exp(-(x-y)*(x-y)/stdevish/stdevish);
}

const double tou = 2*M_PI;
double posmod(double x) {
  return fmod(fmod(x, tou)+tau, tou);
}
double error(double a, double b) {
  double out = abs(fmod(a-b, tou));
  if(out > tau/2)
    out = tau-out;
  return out;
}
double randangle() {
  return tou*rand()/RAND_MAX;
}

int main() {
  rConnect("/dev/rfcomm0");
  printf("Started\n");

  double expected = 0;
  double target = 0;
  double speed = 1;
  
  while(true) {

    //Localize [pos, distperspeedtime]

    if(pos == -INFINITY) {
      //Failed to localize: move randomly
      pos = 0;
      target = randangle();
    }
    else if (error(pos, expected) < .3){
      //Localized as expected (or at 0, on first localization)

      sleep(posmod(target-pos)/distperspeedtime/speed);//Finish motion

      if(target == 0)//Set target according to alternation
        target = randangle();
      else
        target = 0;
    }
    else {
      //Localized wrong
    }
    
    rMotors(0, 0);
    rBeep(.2, 500);
    
    
  }
    
    
    rBeep(.2, 500);

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
