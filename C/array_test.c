#include "array.h"
#include <stdio.h>

int main(){
	int size_[] = {2, 3, 4};
	void * arr = declare_array(sizeof(double), 3, size_);

	for(int i = 0; i < 2; i++)
		for(int j = 0; j < 3; j++)
			for(int k = 0; k < 4; k++) {
				int dimensions[] = {i, j, k};
				*((double*)get(arr, dimensions)) = i*j*k*17.001;
			}


	for(int i = 0; i < 2; i++)
		for(int j = 0; j < 3; j++)
			for(int k = 0; k < 4; k++) {
				int dimensions[] = {i, j, k};
				printf("%d, %d, %d, %lf\n", i, j, k, *((double*)get(arr, dimensions)));
			}


	void * arr2 = clone(arr);

	int l = 0;
	for(int i = 0; i < 2; i++)
		for(int j = 0; j < 3; j++)
			for(int k = 0; k < 4; k++) {
				int dimensions[] = {i, j, k};
				*((double*)get(arr2, dimensions)) = l++;
			}


	for(int i = 0; i < 2; i++)
		for(int j = 0; j < 3; j++)
			for(int k = 0; k < 4; k++) {
				int dimensions[] = {i, j, k};
				printf("%d, %d, %d, %lf\n", i, j, k, *((double*)get(arr2, dimensions)));
			}


	for(int i = 0; i < 2; i++)
		for(int j = 0; j < 3; j++)
			for(int k = 0; k < 4; k++) {
				int dimensions[] = {i, j, k};
				printf("%d, %d, %d, %lf\n", i, j, k, *((double*)get(arr, dimensions)));
			}


	void * arri = declare_array(sizeof(int), 3, size_);
	l = 0;
	for(int i = 0; i < 2; i++)
		for(int j = 0; j < 3; j++)
			for(int k = 0; k < 4; k++) {
				int dimensions[] = {i, j, k};
				*((int*)get(arri, dimensions)) = l++;
			}

	for(int i = 0; i < 2*3*4+2+3; i++)
		printf("%d: %d\n", i, ((int*)arri)[i]);

	printf("%d\n", dimensions(arr));
	for(int i = 0; i < 3; i++)
		printf("%d\n", size(arr)[i]);

}
