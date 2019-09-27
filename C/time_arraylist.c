#include "arraylistutils.h"
#include "doubletime.h"
#include "utils.h"
#include <stdio.h>
#include <math.h>

void * ptr(int x){
  int * out = alloc(int);
  *out = x;
  return out;
}

int main() {

  for(int n = 1000;; n*=1.1) {

    double t0 = doubletime();

    ArrayList * arr = arraylist_new();

    int total = 0;
    for(int i = 0; i < n*2; i++)
      arraylist_append(arr, ptr(i));
    for(int i = 0; i < n; i++)
      total += *(int*)arraylist_pop(arr);//(n+2*n-1)*n/2
    for(int i = 0; i < n; i++)
      arraylist_set(arr, i, ptr(*(int*)arraylist_get(arr, i)+1));
    for(int i = 0; i < n; i++)
      total += *(int*)arraylist_get(arr, i);//(1+n)*n/2
    for(int i = 0; i < n; i++)
      total += *(int*)arraylist_pop(arr);//(1+n)*n/2
            //(5n+1)*n/2

    double t1 = doubletime();

    arraylist_free_with_all_elements(arr);

    int t_should = (n*5+1)*n/2;
    if(total != t_should)
      printf("Computational Inaccuracy: n=%d, total=%ld, expected=%ld\n", n, total, t_should);

    double t = t1-t0;
    double k = n*7;

    printf("n = %d, K = %lf\n", n, 600*1000*1000/k*t);//  23.0

  }
}

