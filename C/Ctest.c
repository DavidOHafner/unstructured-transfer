#include <stdio.h>
#include "stack.h"
#include "arrays.h"
#include "MyroC.h"
#include "picture.h"
#include "testlib.h"

int main(void) {
  printf("Hello World\n");
  
  Stack * s = emptystack();
  s = push(s, 2);
  printf("%d\n", peek(s));
  s = push(s, 3);
  printf("%d\n", peek(s));
  s = push(s, 8);
  printf("%d\n", peek(s));
  s = pop(s);
  printf("%d\n", peek(s));
  s = push(s, 4);
  printf("%d\n", peek(s));
  printf("Arrays:\n");
  
  int x[10] = {0};
  x[3] = 4;
  x[7] = 2;
  printf("%d\n", sum(x));
  
  int y[10][10] = {{0}};
  y[2][5] = 3;
  y[7][4] = 2;
  y[0][0] = 10;
  y[9][9] = 11;
  y[9][8] = 3;
  printf("%d\n", complementsum(2, 5, y));
  printf("%d\n", complementsum(7, 4, y));
  printf("%d\n", complementsum(0, 0, y));
  printf("%d\n", complementsum(0, 1, y));


  
  printf("Starting\n");
  rConnect("/dev/rfcomm0");
  printf("Started\n");
  //while(true) {
  Picture * p = getPicture();
    Channel * red = getRed(p);
    Channel * green = getGreen(p);
    Channel * blue = getBlue(p);
  /*Channel * grey = getGrey(p);
    Picture * out = createPictureFromChannels(red, green, blue);
    Picture * out2 = createPictureFromChannel(grey);*/
    Picture * outR = createPictureFromChannel(red);
    Picture * outG = createPictureFromChannel(green);
    Picture * outB = createPictureFromChannel(blue);
    //displayPictureForever(out, "Out");
    //displayPictureForever(out2, "Out2");
    displayPictureForever(outR, "OutR");
    displayPictureForever(outG, "OutG");
    displayPictureForever(outB, "OutB");
    Channel * red2 = redness(p);
    Picture * out3 = createPictureFromChannel(red2);
    displayPictureForever(p, "In");
    displayPictureForever(out3, "Out3");

    for(int x = 0; x < width; x++)
      printf("%d: (%d, %d, %d) -> %f\n", x,
             p->pix_array[height-1][x].R,
             p->pix_array[height-1][x].G,
             p->pix_array[height-1][x].B,
             red2->data[x][height-1]);
    
    //  }
  
  return 0;

}
