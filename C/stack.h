#ifndef STACK
#define STACK

#include <stdbool.h>

typedef struct Stack Stack;
Stack * push(Stack * st, int x);
Stack * pop(Stack * st);
int peek(Stack * st);
bool isempty(Stack * st);
Stack * emptystack();

#endif
