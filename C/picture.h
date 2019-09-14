#ifndef PICTURE
#define PICTURE

#define width 256
#define height 192

typedef struct {
  float data[width][height];
} Channel;

Picture * getPicture();
void displayPicture(Picture * pix, char * name);
void displayPictureForever(Picture * pix, char * name);
Channel * redness(Picture * in);
Channel * getRed(Picture * in);
Channel * getGreen(Picture * in);
Channel * getBlue(Picture * in);
Channel * getGrey(Picture * in);
Picture * createPictureFromChannel(Channel * channel);
Picture * createPictureFromChannels(Channel * red, Channel * green, Channel * blue);


#endif
