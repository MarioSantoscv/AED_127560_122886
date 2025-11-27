#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>

#include "imageRGB.h"
#include "instrumentation.h"


//vou reutilizar o codigo já que é so para test vou testar todas aqui
int main(int argc, char** argv) {
  if (argc < 4) {
    fprintf(stderr, "Usage: %s <file.ppm|file.pbm> <u> <v> [label]\n", argv[0]);
    return 1;
  }

  const char* path = argv[1];
  int u = atoi(argv[2]);
  int v = atoi(argv[3]);
  int label = 1;
  if (argc >= 5) label = atoi(argv[4]);

  ImageInit();

  // fazer load da imagem
  Image img = NULL;
  /* Detectar extensão para evitar chamar o loader errado (que aborta em caso de formato inesperado) copilot*/ 
  const char *dot = strrchr(path, '.');
  if (dot != NULL) {
    if (strcasecmp(dot, ".pbm") == 0) {
      img = ImageLoadPBM(path);
    } else if (strcasecmp(dot, ".ppm") == 0) {
      img = ImageLoadPPM(path);
    } else {
      fprintf(stderr, "Unsupported file extension: %s\n", dot);
      return 1;
    }
  } else {
    fprintf(stderr, "No file extension found. Use .pbm or .ppm\n");
    return 1;
  }

  if (img == NULL) {
    fprintf(stderr, "Failed to load image: %s\n", path);
    return 1;
  }


 

  //copia para nao alterar a org
  Image copy = ImageCopy(img);
  int labeled = ImageRegionFillingWithSTACK(copy, u, v, (uint16)label);
  printf("Result (recursive): labeled_pixels = %d\n", labeled);

  //salvar the image
  char out[1024];
  snprintf(out, sizeof(out), "%s_stack.ppm", path);
  if (ImageSavePPM(copy, out) == 0) {
    printf("Saved: %s\n", out);
  } else {
    fprintf(stderr, "Failed to save: %s\n", out);
  }

  
  ImageDestroy(&img);
  ImageDestroy(&copy);
  return 0;
}