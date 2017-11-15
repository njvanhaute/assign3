#include <stdio.h>
#include <stdlib.h>
#include "args.h"
#include "da.h"
#include "edge.h"
#include "integer.h"
#include "rbt.h"
#include "set.h"

int main(int argc, char **argv) {  
    FILE *graphFP = openGraphFile(argc, argv);        
    RBT *edgeRBT = newRBT(displayEDGE, compareEDGE); 
    DA *edgeDA = newDA(displayEDGE);
    readEdges(graphFP, edgeRBT, edgeDA);
    displayRBT(stdout, edgeRBT);
    displayDA(stdout, edgeDA);
    printf("\n"); 
    return 0;
}
