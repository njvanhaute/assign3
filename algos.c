#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "algos.h"
#include "edge.h"
#include "integer.h"
#include "queue.h"
#include "stack.h"
#include "utils.h"

#define EMPTY -1

typedef struct vpw {
    int vertex;
    int parent;
    int weight;
} VPW;

static VPW *newVPW(int, int, int);
static void bottomUpMerge(void **, void **, int, int, int, int (*)(void *, void *));
static void copyArray(void **, void **, int);
static int compareVPW(void *, void *);
// Bottom up implementation of merge sort
// Takes in an array of generic values, the size of the array, and a callback function to compare the generic type stored in the array

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

// Makes a singleton set for each vertex
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

// Runs Kruskal's algorithm on the array of edges and returns a dynamic array containing the minimum spanning tree edges
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

// Generates an adjacency list of the edges in the minimum spanning tree
DA **buildAdjList(void **arr, int size, int teaSize) {
    DA **adjList = (DA **)malloc(sizeof(DA *) * (size));
    for (int i = 0; i < size; i++) {
        adjList[i] = newDA(displayEDGE);
    }
    for (int i = 0; i < teaSize; i++) {
        int vl = getVl(arr[i]);
        int vh = getVh(arr[i]);
        int weight = getWeight(arr[i]);
        insertDA(adjList[vl], arr[i]);
        EDGE *edge = newEDGE(vh, vl, weight);
        insertDA(adjList[vh], edge);
    }
    return adjList;
}

// Runs breadth-first search on the MST adjacency list
void BFS(FILE *fp, DA **adjList, int n) {
    bool *visited = (bool *)malloc(sizeof(bool) * n);
    for (int i = 0; i < n; i++) {
        visited[i] = false;
    }
    for (int i = 0; i < n; i++) {
        if (sizeDA(adjList[i]) > 0 && !visited[i]) {
            unsigned long long totalWeight = 0;
            QUEUE *vertexQueue = newQUEUE(displayINTEGER);
            QUEUE *parentQueue = newQUEUE(displayINTEGER);
            QUEUE *weightQueue = newQUEUE(displayINTEGER);
            visited[i] = true;
            enqueue(vertexQueue, newINTEGER(i)); 
            int level = 0;
            while (sizeQUEUE(vertexQueue) > 0) {
                int levelNodes = sizeQUEUE(vertexQueue);
                fprintf(fp, "%d: ", level);
                DA *VPWDA = newDA(0);
                while (levelNodes > 0) {
                    int s = getINTEGER(dequeue(vertexQueue)); 
                    if (level == 0) {
                        fprintf(fp, "%d", s);
                    }
                    else {
                        int parent = getINTEGER(dequeue(parentQueue));
                        int weight = getINTEGER(dequeue(weightQueue));
                        VPW *vpw = newVPW(s, parent, weight);
                        insertDA(VPWDA, vpw);
                        /*fprintf(fp, "%d(%d)%d", s, parent, weight);
                        if (levelNodes > 1) {
                            fprintf(fp, " ");
                        }*/
                        totalWeight += weight;  
                    }
                    for (int j = 0; j < sizeDA(adjList[s]); j++) {
                        EDGE *edge = getDA(adjList[s], j);
                        int vh = getVh(edge);
                        int weight = getWeight(edge);
                        if (!visited[vh]) {
                            visited[vh] = true;
                            enqueue(vertexQueue, newINTEGER(vh));
                            enqueue(parentQueue, newINTEGER(s));
                            enqueue(weightQueue, newINTEGER(weight));
                        }

                    }
                    levelNodes--;
                }
                int vpwArrLen = sizeDA(VPWDA);
                void **vpwArr = extractDA(VPWDA);
                mergeSort(vpwArr, vpwArrLen, compareVPW);
                for (int i = 0; i < vpwArrLen; i++) {
                    VPW *item = vpwArr[i];
                    fprintf(fp, "%d(%d)%d", item->vertex, item->parent, item->weight);
                    if (i < vpwArrLen - 1) {
                        fprintf(fp, " ");
                    }
                }
                level++;
                fprintf(fp, "\n");
            }
            fprintf(fp, "total weight: %llu\n----\n", totalWeight);
        }
    }
}

static VPW *newVPW(int vertex, int parent, int weight) {
    VPW *vpw = (VPW *)malloc(sizeof(VPW));
    vpw->vertex = vertex;
    vpw->parent = parent;
    vpw->weight = weight;
    return vpw;
}

// Helper function for merge sort
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

// Also a helper function for merge sort
static void copyArray(void **work, void **arr, int n) {
    for (int i = 0; i < n; i++) {
        arr[i] = work[i];
    }
}

static int compareVPW(void *a, void *b) {
    VPW *vpwA = a;
    VPW *vpwB = b;
    return vpwA->vertex - vpwB->vertex;
}
