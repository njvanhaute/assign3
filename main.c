#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include "algos.h"
#include "args.h"
#include "da.h"
#include "edge.h"
#include "integer.h"
#include "queue.h"
#include "rbt.h"
#include "set.h"
#include "stack.h"
#include "utils.h"

#define EMPTY -1

int main(int argc, char **argv) {   
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
    makeAllSets(edgeArray, vertexArray, edgeArraySize, vertexSET);    
    DA *teaDA = kruskal(edgeArray, edgeArraySize, vertexArray, vertexSET);
    int teaSize = sizeDA(teaDA);
    void **tea = extractDA(teaDA); 
    mergeSort(tea, teaSize, compareVertices); 
    DA **adjList = buildAdjList(tea, maxVertex + 1, teaSize); 
    BFS(stdout, adjList, maxVertex + 1);
    return 0;
}
