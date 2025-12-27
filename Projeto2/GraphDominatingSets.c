//
// Algoritmos e Estruturas de Dados --- 2025/2026
//
// Joaquim Madeira - Nov 2025
//
// GraphDominatingSets - Computing Vertex Dominating Sets for UNDIRECTED graphs
//

// Student Name :
// Student Number :
// Student Name :
// Student Number :

/*** COMPLETE THE GraphIsDominatingSet FUNCTION ***/
/*** COMPLETE THE GraphMinDominatingSet FUNCTION ***/
/*** COMPLETE THE GraphMinWeightDominatingSet FUNCTION ***/

#include "GraphDominatingSets.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"
#include "IndicesSet.h"
#include "instrumentation.h"

//
// TO BE COMPLETED
//
// Check if the given set is a dominating set for the graph
// Return 1 if true, or 0 otherwise
//
// A dominating set is a set of graph vertices such that every other
// graph vertex not in the set is adjacent to a graph vertex in the set
//
int GraphIsDominatingSet(const Graph* g, IndicesSet* vertSet) {

  assert(g != NULL);
  assert(GraphIsDigraph(g) == 0);
  assert(IndicesSetIsEmpty(vertSet) == 0);

  // iterar pelo grafo
  for (unsigned int v = 0; v < GraphGetVertexRange(g); v++) {
    if (!IndicesSetContains(GraphGetSetVertices(g), v)) continue; // só vértices existentes
    if (IndicesSetContains(vertSet, v)) continue; // vértice faz parte do conjunto dominante

    // v esta fora entao temos que verificar se é dominado ou não
    IndicesSet* adj = GraphGetSetAdjacentsTo(g, v);

    int dominado = 0;
    // Procura se existe pelo menos um adjacente que está no vertSet
    for (unsigned int u = 0; u < GraphGetVertexRange(g); u++) {
      if (IndicesSetContains(adj, u) && IndicesSetContains(vertSet, u)) {
        dominado = 1;
        break;
      }
    }

    IndicesSetDestroy(&adj);

    // Se não tem vizinho no vertSet, não é conjunto dominante
    if (!dominado) return 0;
  }

  //se for dominating set
  return 1;
}

//
// TO BE COMPLETED
//
// Compute a MIN VERTEX DOMINATING SET of the graph
// using an EXHAUSTIVE SEARCH approach
// Return the/a dominating set
//

IndicesSet* GraphComputeMinDominatingSet(const Graph* g) {
  assert(g != NULL);
  assert(GraphIsDigraph(g) == 0);
  uint16_t totalVertices = GraphGetVertexRange(g);
  int menorTamanho = totalVertices + 1;
  IndicesSet* result = IndicesSetCreateEmpty(totalVertices);

  IndicesSet* conjuntoTeste = IndicesSetCreateEmpty(totalVertices);

  while (1) {
    InstrCount[0]++; // Contador de memops : chamada uma vez que chamamos a indicesSetGetNumElems
    int tamanhoAtual = IndicesSetGetNumElems(conjuntoTeste);

    // Ignora conjuntos vazios e maiores do que o melhor já achado
    if (tamanhoAtual > 0 && tamanhoAtual < menorTamanho) {

      InstrCount[1]++; // Contador de adds uma vez que chamamos a GraphIsDominatingSet
      if (GraphIsDominatingSet(g, conjuntoTeste)) {
        // Encontramos um melhor
        IndicesSetDestroy(&result);
        result = IndicesSetCreateCopy(conjuntoTeste);
        menorTamanho = tamanhoAtual;
      }
    }

    InstrCount[0]++; // Contador de memops : chamada uma vez que chamamos a IndicesSetNextSubset
    // Avançar para o proximo subconjunto
    if (!IndicesSetNextSubset(conjuntoTeste)) break;
  }

  IndicesSetDestroy(&conjuntoTeste);

  return result;
}

//
// TO BE COMPLETED
//
// Compute a MIN WEIGHT VERTEX DOMINATING SET of the graph
// using an EXHAUSTIVE SEARCH approach
// Return the dominating set
//
IndicesSet* GraphComputeMinWeightDominatingSet(const Graph* g) {

  //instrumentation
  InstrName[0] = "memops";
  InstrName[1] = "adds";
  InstrCalibrate();
  //
  assert(g != NULL);
  assert(GraphIsDigraph(g) == 0);

  unsigned int range = GraphGetVertexRange(g);

  double* weights = GraphComputeVertexWeights(g);
  double currentMinWeight = -1.0;

  IndicesSet* result = IndicesSetCreateEmpty(range);
  IndicesSet* testSet = IndicesSetCreateEmpty(range);

  while (1) {
    int size = IndicesSetGetNumElems(testSet);

    if (size > 0) {
      if (GraphIsDominatingSet(g, testSet)) {

        // Calcula o peso total
        double totalWeight = 0.0;
        for (unsigned int v = 0; v < range; v++) {
          //instrumentation
          InstrCount[0] += 3;  // to count array acesses
          InstrCount[1] += 1;  // to count addition
          //a[k] = a[i] + a[j];
          //

          if (IndicesSetContains(testSet, v)) {
            totalWeight += weights[v];
          }
        }

        // Atualizar melhor solução se houver
        if (currentMinWeight < 0 || totalWeight < currentMinWeight) {
          IndicesSetDestroy(&result);
          result = IndicesSetCreateCopy(testSet);
          currentMinWeight = totalWeight;
        }
      }
    }

    // Próximo
    if (!IndicesSetNextSubset(testSet)) break;
  }

  IndicesSetDestroy(&testSet);
  free(weights);

  //instrumentation
  InstrPrint();
  //

  return result;
}
