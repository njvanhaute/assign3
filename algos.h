#ifndef __ALGOS_INCLUDED__
#define __ALGOS_INCLUDED__

#include "da.h"
#include "set.h"

extern void mergeSort(void **, int, int (*)(void *, void *));
extern void makeAllSets(void **, int *, int, SET *);
extern DA *kruskal(void **, int, int *, SET *);
extern DA **buildAdjList(void **, int, int);
extern void BFS(FILE *, DA **, int);

#endif
