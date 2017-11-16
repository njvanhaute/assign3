#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "args.h"

FILE *openGraphFile(int argc, char **argv) {
    if (argc != 2) {
        printf("Usage: kruskal [graphfile]\n");
        exit(0);
    }
    if (strcmp(argv[1], "-v") == 0) {
        printf("Nicholas J. Vanhaute\n");
        exit(0);
    }
    FILE *graphFile = fopen(argv[1], "r");
    if (graphFile == NULL) {
        printf("Error: File %s does not exist.\n", argv[1]);
        exit(1);
    }
    return graphFile;
}
