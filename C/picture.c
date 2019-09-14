#include <stdio.h>
#include "utils.h"

const int width = 256;
const int height = 192

#define xyloop for(int x = 0; x < width; x++) for(int y = 0; y < height; y++)

typedef struct {
	int channels;
	float data[][width][height];
} Picture;

typedef struct {
	float data[width][height];
} Channel;

//Convert to external forms
Picture * ???ToPicture(??? * in) {
	Picture * out = malloc(sizeof(Picture) + 3*sizeof(float)*width*height)
	out->channels = 3;
	xyloop {
		out->data[0][x][y] = in->pixarr[y][x].R;
		out->data[1][x][y] = in->pixarr[y][x].G;
		out->data[2][x][y] = in->pixarr[y][x].B;
	}
	return out;
}
??? * PictureTo???(Picture * in) {
	??? * out = alloc(???);
	xyloop
		out->data[y][x] = (???2) {in[0][x][y], in[1][x][y], in[2][x][y]};
	return out;
}

//External accesses
Picture * getPicture() {

}

void displayPicture(Picture * pix, char * name) {

}

Channel * redness(Picture * in) {
	Channel * out = alloc(out);
	xyloop
		out->data[x][y] = in->data[0][x][y]-in->data[1][x][y]-in->data[2][x][y]-abs(in->data[1][x][y]-in->data[2][x][y]);
	return out;
}