#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include "args.h"
#include "da.h"
#include "edge.h"
#include "integer.h"
#include "rbt.h"
#include "set.h"
#include "sort.h"

#define N 1000000

int main(int argc, char **argv) {  
    FILE *graphFP = openGraphFile(argc, argv);        
    RBT *edgeRBT = newRBT(displayEDGE, compareEDGE); 
    DA *edgeDA = newDA(displayEDGE);
    int maxVl = readEdges(graphFP, edgeRBT, edgeDA); 
    printf("Max vl = %d\n", maxVl);
    return 0;
}
