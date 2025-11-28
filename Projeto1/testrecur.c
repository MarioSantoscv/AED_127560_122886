#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "imageRGB.h"
#include "instrumentation.h"

int main(int argc, char** argv) {
  if (argc < 2) {
    fprintf(stderr, "Usage: %s <file.pbm|file.ppm> [method]\n", argv[0]);
    return 1;
  }

  const char* path = argv[1];
  const char* method = (argc >= 3) ? argv[2] : "rec";

  ImageInit();

  Image img = NULL;
  const char *dot = strrchr(path, '.');
  if (dot) {
    if (strcasecmp(dot, ".pbm") == 0) img = ImageLoadPBM(path);
    else if (strcasecmp(dot, ".ppm") == 0) img = ImageLoadPPM(path);
    else {
      img = ImageLoadPBM(path);
      if (img == NULL) img = ImageLoadPPM(path);
    }
  } else {
    img = ImageLoadPBM(path);
    if (img == NULL) img = ImageLoadPPM(path);
  }

  if (img == NULL) {
    fprintf(stderr, "Failed to load image: %s\n", path);
    return 1;
  }

  FillingFunction ff = ImageRegionFillingRecursive;
  if (strcasecmp(method, "stack") == 0) ff = ImageRegionFillingWithSTACK;
  else if (strcasecmp(method, "queue") == 0) ff = ImageRegionFillingWithQUEUE;

  Image segcopy = ImageCopy(img);
  int regions = ImageSegmentation(segcopy, ff);
  printf("%d\n", regions);

  char outseg[1024];
  snprintf(outseg, sizeof(outseg), "%s_seg_%s.ppm", path, method);
  if (ImageSavePPM(segcopy, outseg) != 0) {
    fprintf(stderr, "Failed to save segmented image: %s\n", outseg);
    ImageDestroy(&segcopy);
    ImageDestroy(&img);
    return 1;
  }

  ImageDestroy(&segcopy);
  ImageDestroy(&img);
  return 0;
}