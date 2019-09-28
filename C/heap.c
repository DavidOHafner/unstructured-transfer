#include "heap2.h"
#include "utils.h"
#include <stdlib.h>
#include <stdio.h>

struct Heap {
  int size;
  Heap * left; Heap * right;
  HeapEntry entry;
};

Heap * heap_new() {//TODO Large empty heaps makes for high space overhead.
  Heap * out = alloc(Heap);
  out->size = 0;
  return out;
}

int heap_size(Heap * h) {
  return h->size;
}

void heap_free(Heap * h) {
  while(heap_size(h))
    heap_pop(h);
  free(h);
}

void heap_push(Heap * h, HeapEntry entry) {
  if(h->size++) {
    if(entry.value < h->entry.value) // Propagate the higher value
      SWAP(HeapEntry, entry, h->entry) // Entry is now the higher value

    if(heap_size(h->left) < heap_size(h->right))
      heap_push(h->left, entry);
    else
      heap_push(h->right, entry);
  }
  else {
    h->left = heap_new();
    h->right = heap_new();
    h->entry = entry;
  }
}

HeapEntry heap_peek(Heap * h) {
  return h->entry;
}

void heap_remove(Heap * h) {
  if(--h->size) {
    if(!heap_size(h->right) || (heap_size(h->left) && h->left->entry.value < h->right->entry.value)) {
      h->entry = h->left->entry;
      heap_remove(h->left);
    }
    else {
      h->entry = h->right->entry;
      heap_remove(h->right);
    }
  }
  else {
    free(h->left);
    free(h->right);
  }
}

HeapEntry heap_pop(Heap * h) {
  if(!heap_size(h))
    printf("Pop from empty heap\n");
  HeapEntry out = heap_peek(h);
  heap_remove(h);
  return out;
}
