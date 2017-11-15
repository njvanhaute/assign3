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
    FILE *graphFP = openGraphFile(argc, argv);
    SET *vertexSET = newSET(displayINTEGER);
    RBT *edgeRBT = newRBT(displayEDGE, compareVertices); 
    DA *edgeDA = newDA(displayEDGE);
    int maxVertex = readEdges(graphFP, edgeRBT, edgeDA);
    int edgeArraySize = sizeDA(edgeDA);
    void **edgeArray = extractDA(edgeDA);
    int *vertexArray = (int *)malloc(sizeof(int) * (maxVertex + 1));
    initArray(vertexArray, maxVertex + 1, EMPTY); 
    mergeSort(edgeArray, edgeArraySize, compareWeight);
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
    for (int i = 0; i < teaSize; i++) {
        int vl = getVl(tea[i]);
        insertDA(adjList[vl], tea[i]);
    }
    return 0;
}
