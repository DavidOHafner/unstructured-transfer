#include "utils.h"
#include <stdio.h>
#include "doubletime.h"
#include <math.h>

int main() {
  printf("hello world time=%lf\n", fmod(1.2, 1.0));
  printf("hello world time=%lf\n", fmod(.2, 1.0));
  printf("hello world time=%lf\n", fmod(2.2, 1.0));
  printf("hello world time=%lf\n", fmod(-.8, 1.0));
	return 0;
}
