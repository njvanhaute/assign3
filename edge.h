#ifndef __EDGE_INCLUDED__
#define __EDGE_INCLUDED__

#include "rbt.h"
#include "da.h"

typedef struct edge EDGE;

extern EDGE *newEDGE(int, int, int);
extern int readEdges(FILE *, RBT *, DA *);
extern void displayEDGE(FILE *, void *);
extern int compareEDGE(void *, void *);

#endif
