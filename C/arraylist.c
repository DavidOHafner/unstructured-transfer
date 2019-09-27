#include "utils.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
  void *** data;
  int size;
  int columns;
} ArrayList;

ArrayList * arraylist_new() {
  ArrayList * out = alloc(ArrayList);
  out->size = 0;
  out->columns = 0;
  out->data = NULL;
  return out;
}

void arraylist_free(ArrayList * arr) {
  for(int i = 0; i < arr->columns; i++)
    free(arr->data[i]);
  free(arr->data);
  free(arr);
}

int * address (ArrayList * arr, int index) {
  if(index < 0 || index >= arr->size)
    printf("arraylist index %d out of bounds [0, %d)\n", index, arr->size);
  int * out = malloc(sizeof(int)*2);
  out[0] = 31 - __builtin_clz(index+1);
  out[1] = index - ((1<<out[0]) - 1);
  return out;
}

void arraylist_set(ArrayList * arr, int index, void * element) {
  int * adr = address(arr, index);
  arr->data[adr[0]][adr[1]] = element;
}

void * arraylist_get(ArrayList * arr, int index) {
  int * adr = address(arr, index);
  return arr->data[adr[0]][adr[1]];
}

void arraylist_append(ArrayList * arr, void * element) {
  arr->size++;
  if(arr->size == 1<<arr->columns) {
    void *** data = malloc(sizeof(void*)*(arr->columns+1));
    if(arr->columns != 0)
      memcpy(data, arr->data, sizeof(void*)*arr->columns);
    void ** newcolumn = malloc(sizeof(void*)*(1<<arr->columns));
    data[arr->columns] = newcolumn;
    free(arr->data);
    arr->data = data;
    arr->columns++;
  }
  arraylist_set(arr, arr->size-1, element);
  
}

void * arraylist_pop(ArrayList * arr) {
  if(arr->size == 0)
    printf("arraylist_pop on empty array\n");
  void * out = arraylist_get(arr, arr->size-1);
  arr->size--;
  return out;
}

int arraylist_size(ArrayList * arr) {
  return arr->size;
}
