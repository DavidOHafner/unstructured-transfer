#include <stdio.h>
#include <stdlib.h>
#include "mytime.h"

struct Frame {
  float data[256][192];
};

void main() {

  struct Frame * f = malloc(sizeof(struct Frame));
  for(int x = 0; x < 256; x++)
    for(int y = 0; y < 192; y++)
      f->data[x][y] = 0;


  for(int j = 0; j < 40; j++) {
    
    double t0 = mytime();
    
    int n = 2<<j;
    for(int i = 0; i < n; i++)
      for(int x = 0; x < 256; x++)
        for(int y = 0; y < 192; y++)
          f->data[x][y]++;
  
    double t1 = mytime();
    double dt = t1-t0;
    printf("%d, %lf: %lf\n", j, dt, n/dt);
  }
}
