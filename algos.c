#include <stdio.h>
#include <stdlib.h>
#include "algos.h"
#include "edge.h"
#include "integer.h"
#include "utils.h"

#define EMPTY -1

static void bottomUpMerge(void **, void **, int, int, int, int (*)(void *, void *));
static void copyArray(void **, void **, int);

void mergeSort(void **arr, int n, int (*compare)(void *, void *)) {
    void **work = (void **)malloc(sizeof(void *) * n);
    for (int width = 1; width < n; width *= 2) {
        for (int i = 0; i < n; i += width * 2) {
            bottomUpMerge(arr, work, i, min(i + width, n), min(i + 2 * width, n), compare); 
        }
        copyArray(work, arr, n);
    }
    free(work);
}

void makeAllSets(void **edgeArray, int *vertexArray, int edgeArraySize, SET *set) {
    for (int i = 0; i < edgeArraySize; i++) {
        int vl = getVl(edgeArray[i]);
        int vh = getVh(edgeArray[i]);
        if (vertexArray[vl] == EMPTY) {
            vertexArray[vl] = makeSET(set, newINTEGER(vl));
        }
        if (vertexArray[vh] == EMPTY) {
            vertexArray[vh] = makeSET(set, newINTEGER(vh));
        }
    } 
}

DA *kruskal(void **edgeArray, int edgeArraySize, int *vertexArray, SET *set) {
    DA *tea = newDA(displayEDGE);
    for (int i = 0; i < edgeArraySize; i++) {
        int u = getVl(edgeArray[i]);
        int v = getVh(edgeArray[i]);
        if (findSET(set, vertexArray[u]) != findSET(set, vertexArray[v])) {
            insertDA(tea, edgeArray[i]);
            unionSET(set, vertexArray[u], vertexArray[v]);
        }                
    }
    return tea;
}

static void bottomUpMerge(void **arr, void **work, int l, int r, int end, int (*compare)(void *, void *)) {
    int i = l, j = r;
    for (int k = l; k < end; k++) {
        if (i < r && (j >= end || compare(arr[i], arr[j]) <= 0)) {
            work[k] = arr[i];
            i++;
        }
        else {
            work[k] = arr[j];
            j++;
        }
    }
}

static void copyArray(void **work, void **arr, int n) {
    for (int i = 0; i < n; i++) {
        arr[i] = work[i];
    }
}
