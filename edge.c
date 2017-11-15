#include <stdlib.h>
#include "edge.h"
#include "scanner.h"
#include "utils.h"

struct edge {
    int vl, vh;
    int weight;
};

EDGE *newEDGE(int vl, int vh, int weight) {
    EDGE *edge = (EDGE *)malloc(sizeof(EDGE));
    edge->vl = vl;
    edge->vh = vh;
    edge->weight = weight;
    return edge;    
}

int readEdges(FILE *fp, RBT *rbt, DA *da) {
    int vl = readInt(fp);
    int maxVertex = -1;
    while (!feof(fp)) {
        int vh = readInt(fp);
        if (vl > vh) {
            swap(&vl, &vh);
        }
        if (vh > maxVertex) {
            maxVertex = vh;
        }
        char *weightStr = readToken(fp);
        int weight = atoi(weightStr);
        if (weight == 0) {
            weight = 1;
        }
        else {
            free(weightStr);
            weightStr = readToken(fp);
        }
        EDGE *edge = newEDGE(vl, vh, weight);
        EDGE *search = findRBT(rbt, edge);
        if (search == NULL) {
            insertRBT(rbt, edge);
            insertDA(da, edge);
        }
        else {
            if (edge->weight < search->weight) {
                search->weight = edge->weight;
            }
            free(edge);
        }
        free(weightStr);
        vl = readInt(fp);
    }
    return maxVertex;
}

void displayEDGE(FILE *fp, void *value) {
    EDGE *edge = value;
    fprintf(fp, "(%d,%d,%d)", edge->vl, edge->vh, edge->weight);
}

int compareVertices(void *a, void *b) {
    EDGE *edgeA = a;
    EDGE *edgeB = b;
    int result = 0;
    if (edgeA->vl != edgeB->vl) {
        result = edgeA->vl - edgeB->vl;
    }
    else {
        result = edgeA->vh - edgeB->vh;
    }
    return result;
}

int compareWeight(void *a, void *b) {
    EDGE *edgeA = a;
    EDGE *edgeB = b;
    int result = 0;
    if (edgeA->weight != edgeB->weight) {
        result = edgeA->weight - edgeB->weight;
    }
    else if (edgeA->vl != edgeB->vl) {
        result = edgeA->vl - edgeB->vl;
    }
    else {
        result = edgeA->vh - edgeB->vh;
    }
    return result;
}

int getVl(void *e) {
    EDGE *edge = e;
    return edge->vl;
}

int getVh(void *e) {
    EDGE *edge = e;
    return edge->vh;
}
