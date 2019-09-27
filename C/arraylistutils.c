#include <stdlib.h>

void arraylist_free_with_alll_elements(ArrayList * arr) {
	while(arraylist_size(arr))
		free(arraylist_pop(arr));
	arraylist_free(arr);
}