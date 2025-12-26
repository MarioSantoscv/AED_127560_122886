#include <stdio.h>
#include <stdlib.h>

#include "imageRGB.h"


int main(void) {
  ImageInit();

  Image c = ImageLoadPBM("homempau.pbm");
  if (c == NULL) {
    fprintf(stderr, "Failed to load homempau.pbm\n");
    return 1;
  }

  printf("Test rotate180 \n");
  Image rotated = ImageRotate180CW(c); 
  if (rotated == NULL) {
    fprintf(stderr, "ImageRotate180CW returned NULL\n");
    ImageDestroy(&c);
    return 1;
  }

  if (ImageSavePPM(rotated, "rotated180.ppm") != 0) {
    fprintf(stderr, "Failed to save rotated180.ppm\n");
  } else {
    printf("Saved: rotated180.ppm\n");
  }

  ImageDestroy(&rotated);
  ImageDestroy(&c);
  return 0;
}