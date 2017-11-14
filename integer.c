#include <stdlib.h>
#include "integer.h"

struct integer {
    int value;
};

INTEGER *newINTEGER(int value) {
    INTEGER *p = (INTEGER *)malloc(sizeof(INTEGER));
    p->value = value;
    return p;
}

int getINTEGER(INTEGER *v) {
    return v->value;
}

void displayINTEGER(FILE *fp, void *v) {
    fprintf(fp, "%d", getINTEGER(v)); 
}

int compareINTEGER(void *a, void *b) {
    int c = getINTEGER(a);
    int d = getINTEGER(b);
    return c - d; // If negative, then a < b
}
