#include <stdio.h>
#include "arraylist.h"
#include "utils.h"

void * ptr(int x){
  int * out = alloc(int);
  *out = x;
  return out;
}

int main() {
  printf("A\n");
  ArrayList * arr = arraylist_new();
         
  printf("B\n");
  for(int i = 0; i < 10; i++) {
    arraylist_append(arr, ptr(i));
  }
  printf("C\n");
  for(int i = 0; i < 10; i++) {
    printf("%d\n", *(int*)arraylist_get(arr, i));
  }
  printf("D\n");
  for(int i = 0; i < 10; i++) {
    arraylist_set(arr, i, ptr(2*i));
  }
  printf("E\n");
  for(int i = 0; i < 10; i++) {
    printf("%d\n", *(int*)arraylist_pop(arr));
  }
  printf("F\n");
  
}
    
