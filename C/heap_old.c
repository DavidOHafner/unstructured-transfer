#include "heap.h"
#include "utils.h"
#include <stdlib.h>
#include <stdio.h>

struct Heap {
  Heap * children[2];
  int size;
  double value;
  void * payload;
};

Heap * heap_new() {
  return NULL;//A null heap is empty, but not the only epty heap.
}

int heap_size(Heap * h) {
  return h?h->size:0;
}

void heap_free(Heap * h) {
  while(h)
    heap_pop(h);
  free(h);
}

void heap_push(Heap * h, HeapEntry * entry) {
  printf("B\n");
  Heap ** ch = h->children;
  int i = heap_size(ch[0]) <= heap_size(ch[1]) ? 0 : 1;
  printf("B\n");
  if(!h->children[i]) {
    ch[i] = alloc(Heap);
    ch[i]->children[0] = NULL;
    ch[i]->children[1] = NULL;
    ch[i]->size = 1;
    ch[i]->value = entry->value;
    ch[i]->payload = entry->payload;
    printf("B\n");
  }
  else {
    heap_push(ch[i], entry);
    h->size++;
    if(ch[i]->value < h->value) {
      double tval = ch[i]->value;
      void * tpay = ch[i]->payload;
      ch[i]->value = h->value;
      ch[i]->payload = h->payload;
      h->value = tval;
      h->payload = tpay;
    }
  }
  printf("B\n");
}

Heap * trickledown(Heap * h) {
  if(!h)
    return NULL;
  int i = !h->children[1] || (h->children[0] && h->children[0]->value < h->children[1]->value) ? 0 : 1;
  Heap * newroot = h->children[i];
  newroot->children[0] = trickledown(newroot);
  newroot->children[1] = h->children[1-i];
  newroot->size = h->size-1;
  return newroot;
}
HeapEntry * heap_pop(Heap * h) {
  if(!h)
    printf("Pop from empty heap\n");
  
  HeapEntry * out = alloc(HeapEntry);
  out->value = h->value;
  out->payload = h->payload;

  int i = !h->children[1] || (h->children[0] && h->children[0]->value < h->children[1]->value) ? 0 : 1;
  Heap * cpyfrom = h->children[i];
  
  h->children[0] = trickledown(cpyfrom);
  h->children[1] = h->children[1-i];
  h->size--;
  h->value = cpyfrom->value;
  h->payload = cpyfrom->payload;

  free(cpyfrom);
  
  return out;
}
