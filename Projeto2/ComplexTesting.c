#include <assert.h>
#include <stdio.h>

#include "Graph.h"
#include "GraphDominatingSets.h"
#include "IndicesSet.h"
#include "instrumentation.h"

int main(void) {

  InstrName[0] = "memops";
  InstrName[1] = "adds";
  InstrCalibrate();

  printf("\n");
  printf("===============================================================================================\n");
  printf("| %7s | %10s | %10s | %10s | %10s || %10s | %10s | %10s | %10s |\n",
         "Verts",
         "Time_MD", "Cal_MD", "Mem_MD", "Add_MD",
         "Time_MWD", "Cal_MWD", "Mem_MWD", "Add_MWD");
  printf("===============================================================================================\n");

  for (unsigned int n = 4; n <= 10; n++) {

    Graph* g = GraphCreate(n, 0, 0);

    /* Grafo ciclo */
    for (unsigned int i = 0; i < n; i++) {
      GraphAddEdge(g, i, (i + 1) % n);
    }

    /* ===============================
       MIN DOMINATING SET
       =============================== */
    InstrReset();
    IndicesSet* md = GraphComputeMinDominatingSet(g);

    double time_md = cpu_time() - InstrTime;
    double cal_md  = time_md / InstrCTU;
    unsigned long mem_md = InstrCount[0];
    unsigned long add_md = InstrCount[1];

    IndicesSetDestroy(&md);

    /* ===============================
       MIN WEIGHT DOMINATING SET
       =============================== */
    InstrReset();
    IndicesSet* mwd = GraphComputeMinWeightDominatingSet(g);

    double time_mwd = cpu_time() - InstrTime;
    double cal_mwd  = time_mwd / InstrCTU;
    unsigned long mem_mwd = InstrCount[0];
    unsigned long add_mwd = InstrCount[1];

    IndicesSetDestroy(&mwd);
    GraphDestroy(&g);

    /* Linha da tabela */
    printf("| %7u | %10.6f | %10.6f | %10lu | %10lu || %10.6f | %10.6f | %10lu | %10lu |\n",
           n,
           time_md, cal_md, mem_md, add_md,
           time_mwd, cal_mwd, mem_mwd, add_mwd);
  }

  printf("===============================================================================================\n");
  printf("\n");

  return 0;
}
