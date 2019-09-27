#include <stdlib.h>
#include "arraylist.h"

void arraylist_free_with_all_elements(ArrayList * arr) {
	while(arraylist_size(arr))
		free(arraylist_pop(arr));
	arraylist_free(arr);
}
