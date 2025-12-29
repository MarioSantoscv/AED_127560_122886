//
// Algoritmos e Estruturas de Dados --- 2025/2026
//
// Complex tests for Dominating Sets
//
// Joaquim Madeira, Joao Manuel Rodrigues - Nov 2025
//
// MODIFY THIS FILE FOR FURTHER TESTS
//

#include <assert.h>
#include <stdio.h>

#include "Graph.h"
#include "GraphDominatingSets.h"
#include "IndicesSet.h"

int main(void) {

  /* ============================================================
     TESTE 1: Grafo não dirigido, médio, estruturado (10 vértices)
     ============================================================ */

  Graph* g1 = GraphCreate(10, 0, 0);

  // Estrutura em "anel + diagonais"
  for (unsigned int i = 0; i < 10; i++) {
    GraphAddEdge(g1, i, (i + 1) % 10);     // ciclo
    GraphAddEdge(g1, i, (i + 5) % 10);     // oposto
  }

  printf("Grafo g1 (anel + diagonais):\n");
  GraphDisplayDOT(g1);
  GraphCheckInvariants(g1);
  printf("\n");

  // Full set
  IndicesSet* full = IndicesSetCreateFull(GraphGetNumVertices(g1));
  printf("Full set dominating? %d\n",
         GraphIsDominatingSet(g1, full));
  IndicesSetDestroy(&full);
  printf("\n");

  printf("MIN Dominating Set (g1):\n");
  IndicesSet* md1 = GraphComputeMinDominatingSet(g1);
  IndicesSetDisplay(md1);
  printf("Subgraph induced by MD set:\n");
  Graph* md1g = GraphGetSubgraph(g1, md1);
  GraphDisplayDOT(md1g);

  IndicesSetDestroy(&md1);
  GraphDestroy(&md1g);
  printf("\n");

  printf("MIN WEIGHT Dominating Set (g1):\n");
  IndicesSet* mwd1 = GraphComputeMinWeightDominatingSet(g1);
  IndicesSetDisplay(mwd1);
  Graph* mwd1g = GraphGetSubgraph(g1, mwd1);
  GraphDisplayDOT(mwd1g);

  IndicesSetDestroy(&mwd1);
  GraphDestroy(&mwd1g);
  printf("\n");


  /* ============================================================
     TESTE 2: Grafo não dirigido denso (12 vértices)
     ============================================================ */

  Graph* g2 = GraphCreate(12, 0, 0);

  for (unsigned int i = 0; i < 12; i++) {
    for (unsigned int j = i + 1; j < 12; j++) {
      if ((i + j) % 3 == 0) {
        GraphAddEdge(g2, i, j);
      }
    }
  }

  printf("Grafo g2 (denso, padrão modular):\n");
  GraphDisplayDOT(g2);
  GraphCheckInvariants(g2);
  printf("\n");

  printf("MIN Dominating Set (g2):\n");
  IndicesSet* md2 = GraphComputeMinDominatingSet(g2);
  IndicesSetDisplay(md2);
  Graph* md2g = GraphGetSubgraph(g2, md2);
  GraphDisplayDOT(md2g);

  IndicesSetDestroy(&md2);
  GraphDestroy(&md2g);
  printf("\n");


  /* ============================================================
     TESTE 3: Grafo bipartido completo K(4,6)
     ============================================================ */

  Graph* g3 = GraphCreate(10, 0, 0);

  // Partições: {0,1,2,3} e {4..9}
  for (unsigned int i = 0; i < 4; i++) {
    for (unsigned int j = 4; j < 10; j++) {
      GraphAddEdge(g3, i, j);
    }
  }

  printf("Grafo g3 (bipartido completo K(4,6)):\n");
  GraphDisplayDOT(g3);
  GraphCheckInvariants(g3);
  printf("\n");

  printf("MIN Dominating Set (g3):\n");
  IndicesSet* md3 = GraphComputeMinDominatingSet(g3);
  IndicesSetDisplay(md3);

  printf("MIN WEIGHT Dominating Set (g3):\n");
  IndicesSet* mwd3 = GraphComputeMinWeightDominatingSet(g3);
  IndicesSetDisplay(mwd3);

  IndicesSetDestroy(&md3);
  IndicesSetDestroy(&mwd3);
  printf("\n");


  /* ============================================================
     LIMPEZA
     ============================================================ */

  GraphDestroy(&g1);
  GraphDestroy(&g2);
  GraphDestroy(&g3);

  return 0;
}
