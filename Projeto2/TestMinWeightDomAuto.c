#include <stdio.h>
#include "Graph.h"
#include "GraphDominatingSets.h"
#include "instrumentation.h"

void test_and_report(const char* name, Graph* g) {
    printf("| %-12s | %7u |", name, GraphGetNumVertices(g));

    InstrReset();

    IndicesSet* res = GraphComputeMinWeightDominatingSet(g);

    double time = cpu_time() - InstrTime;
    double caltime = time / InstrCTU;

    printf(" %10.6f | %10.6f", time, caltime);

    for (int i = 0; i < 2; i++) {
        if (InstrName[i] != NULL)
            printf(" | %15lu", InstrCount[i]);
    }
    printf(" |\n");

    IndicesSetDestroy(&res);
    GraphDestroy(&g);
}

int main() {
    InstrName[0] = "memops";
    InstrName[1] = "adds";
    InstrCalibrate();

    printf("===========================================================\n");
    printf("| %-12s | %7s | %10s | %10s | %15s | %15s |\n",
           "Graph", "Verts", "time", "caltime", "memops", "adds");
    printf("===========================================================\n");

    // Grafo ciclo com 4 vértices
    Graph* g1 = GraphCreate(4, 0, 1);
    GraphAddWeightedEdge(g1, 0, 1, 3.0);
    GraphAddWeightedEdge(g1, 1, 2, 8.0);
    GraphAddWeightedEdge(g1, 2, 3, 1.0);
    GraphAddWeightedEdge(g1, 3, 0, 4.0);
    test_and_report("Cycle4", g1);

    // Grafo completo 5 vértices
    Graph* g2 = GraphCreateComplete(5, 0);
    test_and_report("Complete5", g2);

    // Caminho com 6 vértices
    Graph* g3 = GraphCreate(6, 0, 1);
    GraphAddWeightedEdge(g3, 0, 1, 7.0);
    GraphAddWeightedEdge(g3, 1, 2, 1.0);
    GraphAddWeightedEdge(g3, 2, 3, 2.0);
    GraphAddWeightedEdge(g3, 3, 4, 5.0);
    GraphAddWeightedEdge(g3, 4, 5, 2.0);
    test_and_report("Path6", g3);

    // Estrela com 7 vértices
    Graph* g4 = GraphCreate(7, 0, 1);
    for (int i = 1; i < 7; ++i)
        GraphAddWeightedEdge(g4, 0, i, (i % 2 ? i + 1 : i - 1));
    test_and_report("Star7", g4);

    return 0;
}