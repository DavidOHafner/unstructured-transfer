#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"
#include "MyroC.h"
#include "picture.h"

#define xyloop for(int x = 0; x < width; x++) for(int y = 0; y < height; y++)

//Convert to external forms
Pic * PictureToPic(Picture * in) {
  Pic * out = malloc(sizeof(Pic) + 3*sizeof(float)*width*height);
  out->channels = 3;
  xyloop {
    out->data[0][x][y] = in->pix_array[y][x].R;
    out->data[1][x][y] = in->pix_array[y][x].G;
    out->data[2][x][y] = in->pix_array[y][x].B;
  }
  return out;
}
Picture * PicToPicture(Pic * in) {
  Picture * out = alloc(Picture);
  xyloop
    out->pix_array[y][x] = (Pixel) {in->data[0][x][y], in->data[1][x][y], in->data[2][x][y]};
  return out;
}

//External accesses
Pic * getPic() {
  Picture in = rTakePicture();
  Pic * out = PictureToPic(&in);
  return out;
}

void displayPic(Pic * pix, char * name) {
  rDisplayPicture(*PicToPicture(pix), -3, name);
}

Channel * redness(Pic * in) {
  Channel * out = alloc(Channel);
  xyloop {
    float red = in->data[0][x][y]*2-in->data[1][x][y]-in->data[2][x][y]+255*2;//0..255*4
    float bg = abs(in->data[1][x][y]-in->data[2][x][y]);//0..255
    out->data[x][y] = (red+bg)/5;
  }
  return out;
}

Pic * createPic(int numChannels, Channel channels[]) {
  int frameSize = sizeof(float)*width*height;
  Pic * out = malloc(sizeof(Pic) + numChannels*frameSize);
  out->channels = numChannels;
  for(int i = 0; i < 3; i++)
    memcpy(out->data[i], &channels[i], frameSize);
  printf("%f, %f\n", out->data[0][12][12], out->data[2][12][12]);
  free(channels);
  return out;
}
