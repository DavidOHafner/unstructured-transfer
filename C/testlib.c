#include "picture.h"
#include "utils.h"
#include <math.h>

const float frequency = .1, theta = .1;
Channel * customSinusoidalChannel(float theta) {
  Channel * out = alloc(Channel);
  float X = frequency*cos(theta), Y = frequency*sin(theta);
  xyloop {
    float val = cos(X*(x-width/2)+Y*(y-height/2))*128+128;
    if(val > 255.999)
      val = 255.999;
    out->data[x][y] = val;
  }
  return out;
}

Channel * sinusoidalChannel() {
  return customSinusoidalChannel(theta);
}

Picture * sinusoidalPicture() {
  return createPictureFromChannels(customSinusoidalChannel(theta),
                                   customSinusoidalChannel(theta+M_PI*2/3),
                                   customSinusoidalChannel(theta+M_PI*4/3));
}
