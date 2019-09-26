#ifndef ARRAYLIST
#define ARRAYLIST

typedef struct ArrayList ArrayList;

ArrayList * arraylist_new();
void arraylist_append(ArrayList * arr, void * element);
void * arraylist_pop(ArrayList * arr);
void arraylist_set(ArrayList * arr, int index, void * element);
void * arraylist_get(ArrayList * arr, int index);


#endif
