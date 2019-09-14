#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Stack {
  int value;
  struct Stack * rest;
} Stack;
Stack * push(Stack * st, int x) {
	Stack * out = malloc(sizeof(Stack));
	out->value = x;
	out->rest = st;
	return out;
}
Stack * pop(Stack * st) {
	Stack * out = st->rest;
	free(st);
	return out;
}
int peek(Stack * st) {
	return st->value;
}
bool isempty(Stack * st) {
	return st == NULL;
}
Stack * emptystack() {
	return NULL;
}
