#include <time.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char **argv) {
    srand(time(NULL));
    if (argc != 4) {
        printf("Usage: generateGraphs [numEdges] [numRange] [outputFile]\n");
        return 1;
    }
    int numEdges = atoi(argv[1]);
    if (numEdges <= 0) {
        printf("Error: numEdges must be positive.\n");
        return 1;
    }
    int numRange = atoi(argv[2]);
    if (numRange <= 0) {
        printf("Error: numRange must be positive.\n");
        return 1;
    }
    FILE *outFP = fopen(argv[3], "w");
    if (outFP == NULL) {
        printf("Error: Couldn't open file.\n");
        return 1;
    }
    for (int i = 0; i < numEdges; i++) {
        int v1 = rand() % numRange;
        int v2 = rand() % numRange;
        int w = rand() % numRange;
        if (w == 0) {
            w = 1; // weights must be positive
        }
        fprintf(outFP, "%d %d %d ;\n", v1, v2, w);
    }
    fclose(outFP);
    return 0;
}
