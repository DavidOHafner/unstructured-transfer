#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"
#include "MyroC.h"
#include "picture.h"

#define xyloop for(int x = 0; x < width; x++) for(int y = 0; y < height; y++)

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

Channel * redness(Picture * in) {
  Channel * out = alloc(Channel);
  xyloop {
    Pixel px = in->pix_array[y][x];
    //float sum = px.R*299+px.B*587+px.G*114;
    float red = px.R*2-px.G-px.B+255*2;//0..255*4
    float bg = abs(px.B-px.G);//0..255
    out->data[x][y] = (red-bg)/4.0;//0..255
    //printf("%d, %d, %d @ (%d, %d) -> %f\n", px.R, px.G, px.B, x, y, out->data[x][y]);
  }
  return out;
}
Channel * getGrey(Picture * in) {
  Channel * out = alloc(Channel);
  xyloop {
    Pixel px = in->pix_array[y][x];
    float sum = px.R*299+px.B*587+px.G*114;
    out->data[x][y] = sum/1000.0;
  }
  return out;
}
Channel * getRed(Picture * in) {
  Channel * out = alloc(Channel);
  xyloop {
    Pixel px = in->pix_array[y][x];
    out->data[x][y] = px.R;
  }
  return out;
}
Channel * getGreen(Picture * in) {
  Channel * out = alloc(Channel);
  xyloop {
    Pixel px = in->pix_array[y][x];
    out->data[x][y] = px.G*1.2;
  }
  return out;
}
Channel * getBlue(Picture * in) {
  Channel * out = alloc(Channel);
  xyloop {
    Pixel px = in->pix_array[y][x];
    out->data[x][y] = px.B*1.1;
  }
  return out;
}

Picture * createPictureFromChannel(Channel * channel) {
  Picture * out = alloc(Picture);
  float min = 0, max = 255;
  xyloop {
    float val = channel->data[x][y];
    if(val < min) min = val;
    if(val > max) max = val;
  }
  xyloop {
    printf("%f -> ", channel->data[x][y]);
    int val = (channel->data[x][y]-min)*255/(max-min);
    printf("%d\n", val);
    out->pix_array[y][x] = (Pixel) {val, val, val};
  }
  return out;
}
Picture * createPictureFromChannels(Channel * red, Channel * green, Channel * blue) {
  Picture * out = alloc(Picture);
  xyloop 
    out->pix_array[y][x] = (Pixel) {red->data[x][y], green->data[x][y]/1.2, blue->data[x][y]/1.1};
  return out;
}
