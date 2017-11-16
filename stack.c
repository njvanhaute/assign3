#include "stack.h"
#include "da.h"
#include <stdlib.h>

struct stack {
    DA *da;
    void (*display)(FILE *, void *);
};

STACK *newSTACK(void (*d)(FILE *, void *)) {
    STACK *stack = (STACK *)malloc(sizeof(STACK));
    stack->da = newDA(d);
    stack->display = d;
    return stack;
}

void push(STACK *items, void *value) {
    insertDA(items->da, value);
}

void *pop(STACK *items) {
    return removeDA(items->da);
}

void *peekSTACK(STACK *items) {
    return getDA(items->da, sizeDA(items->da) - 1);
}

int sizeSTACK(STACK *items) {
    return sizeDA(items->da);
}

void displaySTACK(FILE *fp, STACK *items) {
    fprintf(fp, "|");
    for (int i = sizeDA(items->da) - 1; i >= 0; i--) {
        items->display(fp, getDA(items->da, i));
        if (i > 0) {
            fprintf(fp, ",");
        }
    }
    fprintf(fp, "|");
}

void visualizeSTACK(FILE *fp, STACK *items) {
    displayDA(fp, items->da);
}
