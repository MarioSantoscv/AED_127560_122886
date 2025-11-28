#include <stdio.h>
#include <stdlib.h>

#include "imageRGB.h"
#include "instrumentation.h"

/*
  Test script to measure performance (time + pixel accesses) of:
    - ImageRegionFillingRecursive
    - ImageRegionFillingWithSTACK
    - ImageRegionFillingWithQUEUE
    - ImageSegmentation (using each of the above filling functions)

  The tests force a fill of a 50x50 square by creating an image of size 50x50
  whose entire area is a single WHITE region. Calling any region-filling
  function starting at the center will therefore visit (and relabel) all
  50*50 = 2500 pixels.

  Output formatting follows the style of the provided test_isequal.c:
    - It uses InstrReset() before each measured call and InstrPrint() after,
      so the instrumentation shows elapsed time and counters (pixmem, pixcmp, ...).
*/

static int run_region_fill(Image img, FillingFunction ff, const char* label,
                           int u, int v, uint16_t newlabel) {
  InstrReset();
  int changed = ff(img, u, v, newlabel);
  printf("Result (%s): labeled_pixels = %d\n", label, changed);
  InstrPrint();
  return changed;
}

static int run_segmentation(Image img, FillingFunction ff, const char* label) {
  InstrReset();
  int regions = ImageSegmentation(img, ff);
  printf("Result (%s): regions = %d\n", label, regions);
  InstrPrint();
  return regions;
}

void runTests(Image img, int Cx, int Cy, uint16_t fillLabel) {
  Image base = img;
  int cx = Cx;
  int cy = Cy;
  uint16_t fill_label = fillLabel;
  
  // 1) Recursive fill (direct)
  {
    Image img = ImageCopy(base);
    printf("\n--- Test: ImageRegionFillingRecursive (direct) ---\n");
    run_region_fill(img, ImageRegionFillingRecursive, "Recursive fill (direct)", cx, cy, fill_label);
    ImageDestroy(&img);
  }

  // 2) STACK-based fill (direct)
  {
    Image img = ImageCopy(base);
    printf("\n--- Test: ImageRegionFillingWithSTACK (direct) ---\n");
    run_region_fill(img, ImageRegionFillingWithSTACK, "STACK fill (direct)", cx, cy, fill_label);
    ImageDestroy(&img);
  }

  // 3) QUEUE-based fill (direct)
  {
    Image img = ImageCopy(base);
    printf("\n--- Test: ImageRegionFillingWithQUEUE (direct) ---\n");
    run_region_fill(img, ImageRegionFillingWithQUEUE, "QUEUE fill (direct)", cx, cy, fill_label);
    ImageDestroy(&img);
  }

  // 4) Segmentation using Recursive fill
  {
    Image img = ImageCopy(base);
    printf("\n--- Test: ImageSegmentation using Recursive fill ---\n");
    run_segmentation(img, ImageRegionFillingRecursive, "Segmentation + Recursive");
    ImageDestroy(&img);
  }

  // 5) Segmentation using STACK fill
  {
    Image img = ImageCopy(base);
    printf("\n--- Test: ImageSegmentation using STACK fill ---\n");
    run_segmentation(img, ImageRegionFillingWithSTACK, "Segmentation + STACK");
    ImageDestroy(&img);
  }

  // 6) Segmentation using QUEUE fill
  {
    Image img = ImageCopy(base);
    printf("\n--- Test: ImageSegmentation using QUEUE fill ---\n");
    run_segmentation(img, ImageRegionFillingWithQUEUE, "Segmentation + QUEUE");
    ImageDestroy(&img);
  }
}

int main(void) {
  for (size_t i = 1; i < 5; i++)
  {
    const int W = 50 * i;
    const int H = 50 * i;
    const int cx = W/2;
    const int cy = H/2;

    ImageInit(); // calibrate instrumentation and name counters

    printf("\n--- Region filling performance test: square %dx%d ---\n", W, H);

    // Create base image: background WHITE (single region of size W*H)
    Image base = ImageCreate((uint32)W, (uint32)H);

    // We'll use a new label for the fill (1 is BLACK already, but any valid label < FIXED_LUT_SIZE works)
    uint16_t fill_label = 1;

    runTests(base, cx, cy, fill_label);
    ImageDestroy(&base);
  }


  return 0;
}