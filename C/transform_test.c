#include "transform.h"
#include "utils.h"
#include "array_type.h"
#include <stdio.h>

int main() {
	printf("hello world\n");

	int size_[] = {3, 4};
	void * arr = declare_array_type(float, 3, size_);

	for(int j = 0; j < 3; j++)
		for(int k = 0; k < 4; k++) {
			int dimensions[] = {j, k};
			get_type(float, arr, dimensions) = (float) j*k*17.001;
		}


	for(int j = 0; j < 3; j++)
		for(int k = 0; k < 4; k++) {
			int dimensions[] = {j, k};
			printf("%d, %d, %f\n", j, k, get_type(float, arr, dimensions));
		}

	blur2D(arr, 1);

	for(int j = 0; j < 3; j++)
		for(int k = 0; k < 4; k++) {
			int dimensions[] = {j, k};
			printf("%d, %d, %f\n", j, k, get_type(float, arr, dimensions));
		}

}
