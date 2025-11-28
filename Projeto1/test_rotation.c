#include <stdio.h>
#include <stdlib.h>

#include "imageRGB.h"

int main(void) {
  ImageInit();

  Image c = ImageLoadPPM("Basic_human_drawing.ppm");
  if (c == NULL) {
    fprintf(stderr, "Failed to load Basic_human_drawing.ppm\n");
    return 1;
  }

  printf("Test rotate180 \n");
  Image rotated = ImageRotate180CW(c); 
  if (rotated == NULL) {
    fprintf(stderr, "ImageRotate180 returned NULL\n");
    ImageDestroy(&c);
    return 1;
  }

  if (ImageSavePPM(rotated, "rotated.ppm") != 0) {
    fprintf(stderr, "Failed to save rotated.ppm\n");
  } else {
    printf("Saved: rotated.ppm\n");
  }

  ImageDestroy(&rotated);
  ImageDestroy(&c);
  return 0;
}