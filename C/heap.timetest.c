#include "timetestgen.h"
#include "heap2.h"

HeapEntry entry(double x, int y) {
  return (HeapEntry) {x, ptr_to_int(y)};
}

start(int, 1, *= 2)

Heap * h = heap_new();

long total = 0;
double last;

for(int i = 0; i < n*2; i++) {
  double x = 1.0*(i*8234758192628487);
  int y = i*98378739319263498;
  total += y;
  heap_push(h, entry(x, y));
}

last = -INFINITY;
for(int i = 0; i < n; i++) {
  HeapEntry e = heap_pop(h);
  if(e.value < last)
    printf("Computational Inaccuracy: %lf after %lf\n", e.value, last);
  last = e.value;
  total -= *(int*)e.payload;
}

for(int i = 0; i < n; i++) {
  double x = 1.0*(i*98223476413476782);
  int y = i*623415908292632345;
  total += y;
  heap_push(h, entry(x, y));
}

last = -INFINITY;
for(int i = 0; i < n*2; i++) {
  HeapEntry e = heap_pop(h);
  if(e.value < last)
    printf("Computational Inaccuracy: %lf after %lf\n", e.value, last);
  last = e.value;
  total -= *(int*)e.payload;
}

heap_free(h);

if(total)
  printf("Computational Inaccuracy: n=%d, total=%ld\n", n, total);

end(n*log(n)*6)
