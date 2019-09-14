#ifndef ARRAYS
#define ARRAYS

#define length(arr) (sizeof(arr) == 0? 0 : sizeof(arr)/sizeof(arr[0]))

#define sum(arr) (sum_(arr, length(arr))) 
int sum_(int * arr, int len);

#define complementsum(x, y, arr) (complementsum_(x, y, length(arr), length(arr[0]), arr)) 
int complementsum_(int x, int y, int len1, int len2, int arr[len1][len2]);

#endif
