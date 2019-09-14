#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "MyroC.h"

const int width = 256;
const int height = 192;

#define xyloop for(int x = 0; x < width; x++) for(int y = 0; y < height; y++)

typedef struct {
  int channels;
  float data[][width][height];
} Pic;

typedef struct {
  float data[width][height];
} Channel;

//Convert to external forms
Pic * PictureToPic(Picture * in) {
  Pic * out = malloc(sizeof(Pic) + 3*sizeof(float)*width*height);
out->channels = 3;
xyloop {
out->data[0][x][y] = in->pix_array[y][x].R;
out->data[1][x][y] = in->pix_array[y][x].G;
out->data[2][x][y] = in->pix_array[y][x].B;
}	return out;
}
Picture * PicToPicture(Pic * in) {
Picture * out = alloc(Picture);
xyloop
		out->pix_array[y][x] = (Pixel) {in[0][x][y], in[1][x][y], in[2][x][y]};
        
	return out;
}

//External accesses
Pic * getPic() {
  Picture in = rTakePicture();
  Pic out = PicturetoPic(&in);
  reutrn out;
}

void displayPic(Pic * pix, char * name) {

}

Channel * redness(Pic * in) {
	Channel * out = alloc(out);
	xyloop
		out->data[x][y] = in->data[0][x][y]-in->data[1][x][y]-in->data[2][x][y]-abs(in->data[1][x][y]-in->data[2][x][y]);
	return out;
}
