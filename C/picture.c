#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "utils.h"
#include "MyroC.h"
#include "picture.h"

const float colorWeights[] = {299.0/587, 1, 114.0/587};
const float totalColorWeight = 299.0/587+1+114.0/587;

//TODO the immages are composed of lage, non-coincident, pixels in each channel, with especially large ixels on the blue channel. This can be fixed with blurring.

//External accesses
Picture * getPicture() {
  Picture * out = alloc(Picture);
  *out = rTakePicture();
  return out;
}
void displayPicture(Picture * pic, char * name) {
  rDisplayPicture(*pic, -3, name);
}
void displayPictureForever(Picture * pic, char * name) {
  rDisplayPicture(*pic, 0, name);
}

int square(int x) {
  return x*x;
}
Channel * redness(Picture * in) {
  Channel * out = alloc(Channel);
  xyloop {
    Pixel px = in->pix_array[y][x];
    //float sum = px.R*299+px.B*587+px.G*114;
    float red = px.R*2-px.G-px.B+255*2;//0..255*4
    float bg = square(px.B-px.G)/255;//0..255
    float brt = (px.R*colorWeights[0]+px.G*colorWeights[1]+px.G*colorWeights[2])/totalColorWeight;//0..255
    float brttarget = 70;
    float brterror = square(brt-brttarget)/square(255-brttarget);//0..255
    int n = 2;
    if(y == height-1)
      printf("%d: %f\n", x, brt);
    out->data[x][y] = (red-bg-n*brterror+255*n)/(4.0+n);//0..255
    //printf("%d, %d, %d @ (%d, %d) -> %f\n", px.R, px.G, px.B, x, y, out->data[x][y]);
  }
  return out;
}
Channel * getGrey(Picture * in) {
  Channel * out = alloc(Channel);
  xyloop {
    Pixel px = in->pix_array[y][x];
    float sum = px.R*299+px.G*587+px.B*114;
    out->data[x][y] = sum/1000.0;
  }
  return out;
}
Channel * getWeightedRed(Picture * in) {
  Channel * out = alloc(Channel);
  xyloop
    out->data[x][y] = in->pix_array[y][x].R*colorWeights[0]+128*(1-colorWeights[0]);
  return out;
}
Channel * getWeightedGreen(Picture * in) {
  Channel * out = alloc(Channel);
  xyloop
    out->data[x][y] = in->pix_array[y][x].G*colorWeights[1]+128*(1-colorWeights[1]);
  return out;
}
Channel * getWeightedBlue(Picture * in) {
  Channel * out = alloc(Channel);
  xyloop
    out->data[x][y] = in->pix_array[y][x].B*colorWeights[2]+128*(1-colorWeights[2]);
  return out;
}
Channel * getRed(Picture * in) {
  Channel * out = alloc(Channel);
  xyloop
    out->data[x][y] = in->pix_array[y][x].R;
  return out;
}
Channel * getGreen(Picture * in) {
  Channel * out = alloc(Channel);
  xyloop
    out->data[x][y] = in->pix_array[y][x].G;
  return out;
}
Channel * getBlue(Picture * in) {
  Channel * out = alloc(Channel);
  xyloop
    out->data[x][y] = in->pix_array[y][x].B;
  return out;
}

//Scales channels so that they span [0..255.999].
//If integers [0..255] are scaled and then cast back to int,
//they will be unchanged.
void normalizeChannels(int count, Channel * channels[]) {
  float min = INFINITY, max = -INFINITY;
  for(int i = 0; i < count; i++)
    xyloop {
      float val = channels[i]->data[x][y];
      min = val < min ? val : min;
      max = val > max ? val : max;
    }
  for(int i = 0; i < count; i++)
    xyloop {
      float val = (channels[i]->data[x][y]-min)/(max-min)*256;
      channels[i]->data[x][y] = val > 255.999 ? 255.999 : val;
    }
}
void normalizeChannel(Channel * channel) {
  float min = INFINITY, max = -INFINITY;
  xyloop {
    float val = channel->data[x][y];
    min = val < min ? val : min;
    max = val > max ? val : max;
  }
  xyloop {
    float val = (channel->data[x][y]-min)/(max-min)*256;
    channel->data[x][y] = val > 255.999 ? 255.999 : val;
  }
}

Picture * createPictureFromChannel(Channel * channel) {
  /*Picture * out = alloc(Picture);
  float min = 0, max = 255;
  xyloop {
    float val = channel->data[x][y];
    if(val < min) min = val;
    if(val > max) max = val;
  }
  xyloop {
    int val = (channel->data[x][y]-min)*255/(max-min);
    out->pix_array[y][x] = (Pixel) {val, val, val};
    }*/
  normalizeChannels(1, &channel);//
  return createPictureFromChannels(channel, channel, channel);
}
Picture * createPictureFromChannels(Channel * red, Channel * green, Channel * blue) {
  Picture * out = alloc(Picture);
  Channel * channels[] = {red, green, blue};
  normalizeChannels(3, channels);
  xyloop
    out->pix_array[y][x] = (Pixel) {red->data[x][y], green->data[x][y], blue->data[x][y]};
  return out;
}
