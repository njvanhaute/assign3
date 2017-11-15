#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include "algos.h"
#include "args.h"
#include "da.h"
#include "edge.h"
#include "integer.h"
#include "rbt.h"
#include "set.h"
#include "utils.h"

#define EMPTY -1

int main(int argc, char **argv) {  
    clock_t begin = clock();
    FILE *graphFP = openGraphFile(argc, argv);
    SET *vertexSET = newSET(displayINTEGER);
    RBT *edgeRBT = newRBT(displayEDGE, compareVertices); 
    DA *edgeDA = newDA(displayEDGE);
    int maxVertex = readEdges(graphFP, edgeRBT, edgeDA);
    fclose(graphFP);
    int edgeArraySize = sizeDA(edgeDA);
    void **edgeArray = extractDA(edgeDA);
    int *vertexArray = (int *)malloc(sizeof(int) * (maxVertex + 1));
    initArray(vertexArray, maxVertex + 1, EMPTY); 
    mergeSort(edgeArray, edgeArraySize, compareWeight);
    for (int i = 0; i < edgeArraySize; i++) {
        displayEDGE(stdout, edgeArray[i]);
        printf(" ");
    }
    printf("\n");
    makeAllSets(edgeArray, vertexArray, edgeArraySize, vertexSET);    
    DA *teaDA = kruskal(edgeArray, edgeArraySize, vertexArray, vertexSET);
    int teaSize = sizeDA(teaDA);
    void **tea = extractDA(teaDA); 
    mergeSort(tea, teaSize, compareVertices);
    int maxVl = getVl(tea[teaSize - 1]);
    DA **adjList = (DA **)malloc(sizeof(DA *) * (maxVl + 1));
    for (int i = 0; i < maxVl + 1; i++) {
        adjList[i] = newDA(displayEDGE);
    }
    /*for (int i = 0; i < teaSize; i++) {
        int vl = getVl(tea[i]);
        insertDA(adjList[vl], tea[i]);
    }*/
    clock_t end = clock();
    double time_spent = (end - begin) / CLOCKS_PER_SEC;
    printf("Time spent: %lf secs\n", time_spent);
    return 0;
}
