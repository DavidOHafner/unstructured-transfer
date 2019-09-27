#include <stdio.h>
#include "arraylist.h"
#include "utils.h"
#include <math.h>
#include <time.h>

void * ptr(int x){
  int * out = alloc(int);
  *out = x;
  return out;
}

#define abs(x) (x) < 0?-(x):(x)

double f(int n, int m) {
  double out = 0;
  ArrayList
  for(int i = 0; i < m; i++) {
    double x = 0;
    for(int j = 0; j < n; j++)
      x += rand()*1.0/RAND_MAX/i;
    double err = abs(x-.5);

    if(err > 1/pow(n, .1))
      out += 1.0/m;
  }
  return out;
}

int main() {
  srand(time(0));
  for(int i = 0;; i++) {
    int n = 1<<i;
    printf("%d: %lf\n", n, f(n, 10000));
  }
}
    
