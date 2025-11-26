#include <stdio.h>
#include <time.h>

#include "imageRGB.c"          // <-- torna a struct pública
#include "instrumentation.c"   // <-- acesso ao PIXMEM

// ---------------------------------------------
// Criar imagem com um quadrado branco
// ---------------------------------------------
Image CreateSquareImage(int W, int H, int sq_x, int sq_y, int sq_size)
{
    Image img = ImageCreate(W, H);

    for (int y = 0; y < H; y++)
        for (int x = 0; x < W; x++)
            img->image[y][x] = 1;  // fundo = não branco

    for (int y = sq_y; y < sq_y + sq_size; y++)
        for (int x = sq_x; x < sq_x + sq_size; x++)
            img->image[y][x] = 0;  // região a preencher

    return img;
}

// ---------------------------------------------
void RunTest(const char *name,
             int (*fillFunct)(Image, int, int, uint16),
             int W, int H, int sq_x, int sq_y, int sq_size)
{
    Image img = CreateSquareImage(W, H, sq_x, sq_y, sq_size);

    InstrReset();   // zera tempo + contadores
    ResetPIXMEM();  // zera acessos à memória

    clock_t start = clock();

    int filled = fillFunct(img, sq_x, sq_y, 5);

    clock_t end = clock();
    double t_ms = 1000.0 * (end - start) / CLOCKS_PER_SEC;

    printf("\n=== %s ===\n", name);
    printf("Pixels preenchidos: %d\n", filled);
    printf("PIXMEM: %d\n", GetPIXMEM());
    printf("Tempo: %.3f ms\n", t_ms);

    ImageDestroy(&img);
}

// ---------------------------------------------
int main()
{
    InstrCalibrate();

    int W = 800, H = 800;
    int sq_x = 100, sq_y = 100, sq_size = 300;

    printf("=== Teste Comparativo ===\n");

    RunTest("Recursive", ImageRegionFillingRecursive,
            W, H, sq_x, sq_y, sq_size);

    RunTest("STACK", ImageRegionFillingWithSTACK,
            W, H, sq_x, sq_y, sq_size);

    RunTest("QUEUE", ImageRegionFillingWithQUEUE,
            W, H, sq_x, sq_y, sq_size);

    return 0;
}
