#include <stdio.h>
int sum_(int * arr, int len)  {
	int out = 0;
	for(int i = 0; i < len; i++)
		out += arr[i];
	return out;
}

int complementsum_(int x, int y, int width, int height, int arr[width][height]) {
	return arr[x][y] + arr[width-1-x][height-1-y];
}
