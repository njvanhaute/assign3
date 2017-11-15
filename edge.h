#ifndef __EDGE_INCLUDED__
#define __EDGE_INCLUDED__

#include "da.h"
#include "rbt.h"

typedef struct edge EDGE;

extern EDGE *newEDGE(int, int, int);
extern int readEdges(FILE *, RBT *, DA *);
extern void displayEDGE(FILE *, void *);
extern int compareVertices(void *, void *);
extern int compareWeight(void *, void *);
extern int getVl(void *);
extern int getVh(void *);
extern int getWeight(void *);

#endif
