#include "array_type.h"
#include <stdio.h>

int main(){
	int size_[] = {2, 3, 4};
	void * arr = declare_array_type(double, 3, size_);

	int index[] = {1, 2, 3};
	set_type(double, arr, index, 6.4);
	printf("%lf\n", get_type(double, arr, index));
}
