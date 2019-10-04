#ifndef HEAP
#define HEAP

typedef struct Heap Heap;
typedef struct {
  double value;
  void * payload;
} HeapEntry;


Heap * heap_new();
void heap_free(Heap * h);
void heap_push(Heap * h, HeapEntry entry);
HeapEntry heap_peek(Heap * h);
HeapEntry heap_pop(Heap * h);
int heap_size(Heap * h);

#endif
