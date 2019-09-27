#include "arraylist.h"
#include "doubletime.h"
#include "utils.h"
#include <stdio.h>
#include <math.h>

void printvis(double x) {
  for(int i = 0; i < x; i++)
    printf("-");
}
void print2vis(double x, double y) {
  if(y < x)
    printf("wrong order!\n");

  for(int i = 1; i < y; i++)
    if(i == x)
      printf("|");
    else
      printf("-");
  printf("|\n");
}
void print1vis(double y) {
  for(int i = 1; i < y; i++)
    printf("-");
  printf("|\n");
}

void * ptr(int x){
  int * out = alloc(int);
  *out = x;
  return out;
}

int main() {

  /*double t0 = doubletime();
  double sltime = 0;
  for(double sleeptime = .0001;;sleeptime *= 1.1) {
    double x = doubletime()-t0;
    print1vis((x-sltime)/log(sltime)*1000);
    doublesleep(sleeptime);
    sltime += sleeptime;
  }*/

  for(int n = 1;; n*=1) {

    double t0 = doubletime();

    ArrayList * arr = arraylist_new();

    long total = 0;
    for(int i = 0; i < n*2; i++)
      arraylist_append(arr, ptr(i));
    for(int i = 0; i < n; i++)
      total += *(int*)arraylist_pop(arr);
    for(int i = 0; i < n; i++)
      arraylist_set(arr, i, ptr(*(int*)arraylist_get(arr, i)+1));
    for(int i = 0; i < n; i++)
      total += *(int*)arraylist_get(arr, i);
    for(int i = 0; i < n; i++)
      total += *(int*)arraylist_pop(arr);

    double t1 = doubletime();

    long t_should = (n+(n*2-1))*n/2 + 1+n;
    if(total != t_should)
      printf("Oops!\n");

    double t = t1-t0;
    double k = n*7;

    printf("n = %d, K = %lf\n", n, 600*1000*1000/k*t);

  }

  return 0;

  /*for(double sleeptime = .00001;;sleeptime *= 1.4) {

  double t0 = doubletime();

  


  doublesleep(sleeptime);
  doublesleep(sleeptime);
  doublesleep(sleeptime);
  doublesleep(sleeptime);
  doublesleep(sleeptime);
  doublesleep(sleeptime);
  doublesleep(sleeptime);
  doublesleep(sleeptime);
  doublesleep(sleeptime);
  doublesleep(sleeptime);
  doublesleep(sleeptime);
  doublesleep(sleeptime);
  doublesleep(sleeptime);
  doublesleep(sleeptime);
  doublesleep(sleeptime);
  doublesleep(sleeptime);
  doublesleep(sleeptime);
  doublesleep(sleeptime);
  doublesleep(sleeptime);
  doublesleep(sleeptime);
  doublesleep(sleeptime);
  doublesleep(sleeptime);
  doublesleep(sleeptime);
  doublesleep(sleeptime);
  doublesleep(sleeptime);
  doublesleep(sleeptime);
  doublesleep(sleeptime);
  doublesleep(sleeptime);
  doublesleep(sleeptime);
  doublesleep(sleeptime);
  doublesleep(sleeptime);
  doublesleep(sleeptime);
  doublesleep(sleeptime);
  doublesleep(sleeptime);
  doublesleep(sleeptime);
  doublesleep(sleeptime);
  doublesleep(sleeptime);
  doublesleep(sleeptime);
  doublesleep(sleeptime);
  doublesleep(sleeptime);
  doublesleep(sleeptime);
  doublesleep(sleeptime);
  doublesleep(sleeptime);
  doublesleep(sleeptime);
  doublesleep(sleeptime);
  doublesleep(sleeptime);
  doublesleep(sleeptime);
  doublesleep(sleeptime);
  doublesleep(sleeptime);
  doublesleep(sleeptime);

  double t1 = doubletime();
  double x = (t1-t0)/50-sleeptime;
  printf("st = %lf -> t = %lf", sleeptime, x);
  printvis((x+.0001)*300*100);
  }*/
}

