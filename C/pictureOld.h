#ifndef PICTURE
#define PICTURE

#define width 256
#define height 192

typedef struct {
  int channels;
  float data[][width][height];
} Pic;

typedef struct {
  float data[width][height];
} Channel;

Pic * getPic();
void displayPic(Pic * pix, char * name);
Channel * redness(Pic * in);
Pic * createPic(int numChannels, Channel * channels);


#endif
