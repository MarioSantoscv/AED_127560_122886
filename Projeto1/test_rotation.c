#include <stdio.h>
#include <stdlib.h>

#include "imageRGB.h"

int main(void) {
  ImageInit();

  Image c = ImageLoadPBM("newtest.pbm");
  if (c == NULL) {
    fprintf(stderr, "Failed to load newtest.pbm\n");
    return 1;
  }

  printf("Test rotate180 \n");
  Image rotated = ImageRotate90CW(c); 
  if (rotated == NULL) {
    fprintf(stderr, "ImageRotate90CW returned NULL\n");
    ImageDestroy(&c);
    return 1;
  }

  if (ImageSavePPM(rotated, "rotated90.ppm") != 0) {
    fprintf(stderr, "Failed to save rotated90.ppm\n");
  } else {
    printf("Saved: rotated90.ppm\n");
  }

  ImageDestroy(&rotated);
  ImageDestroy(&c);
  return 0;
}