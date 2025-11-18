#include <stdio.h>
#include "imageRGB.h"
#include "instrumentation.h"

int run_and_print(Image a, Image b, const char* label) {
  InstrReset();
  int eq = ImageIsEqual(a, b);
  printf("Result (%s): %s\n", label, eq ? "equal" : "different");
  InstrPrint();
  return eq;
}

int main(void) {
  ImageInit(); // calibra e define nomes dos contadores (executar apenas uma vez)

  // Exemplos de tamanhos a testar
  const int sizes[][2] = { {10,10}, {50,50}, {100,100}, {150,150} };

  for (int s = 0; s < (int)(sizeof(sizes)/sizeof(sizes[0])); ++s) {
    int w = sizes[s][0];
    int h = sizes[s][1];
    printf("\n--- Test size %dx%d ---\n", w, h);

    // Criar imagem xadrez com edge=1 (cada pixel é região isolada)
    Image img1 = ImageCreateChess((uint32)w, (uint32)h, 1, 0xff0000 /* vermelho */);

    // Caso A: imagens idênticas (pior caso: compara todos os pixels)
    Image img_copy = ImageCopy(img1);
    run_and_print(img1, img_copy, "identical");

    // Caso B: diferença no primeiro pixel (melhor caso)
    Image img_first_diff = ImageCopy(img1);
    // pintar o pixel (0,0) com outra etiqueta (ex: etiqueta 1) -> como edge=1 a região é só esse pixel
    ImageRegionFillingRecursive(img_first_diff, 0, 0, 1);
    run_and_print(img1, img_first_diff, "first pixel different");

    // Caso C: diferença no pixel central (caso intermédio)
    Image img_mid_diff = ImageCopy(img1);
    int midx = w/2;
    int midy = h/2;
    ImageRegionFillingRecursive(img_mid_diff, midx, midy, 1);
    run_and_print(img1, img_mid_diff, "middle pixel different");

    // Caso D: diferença no último pixel (quase pior caso)
    Image img_last_diff = ImageCopy(img1);
    ImageRegionFillingRecursive(img_last_diff, w-1, h-1, 1);
    run_and_print(img1, img_last_diff, "last pixel different");

    // cleanup
    ImageDestroy(&img1);
    ImageDestroy(&img_copy);
    ImageDestroy(&img_first_diff);
    ImageDestroy(&img_mid_diff);
    ImageDestroy(&img_last_diff);
  }

  return 0;
}