#include <stdlib.h>
#include "set.h"
#include "da.h"

struct set {
    DA *da;
    void (*origDisplay)(FILE *, void *);
};

typedef struct setnode {
    void *value;
    int rank;
    int index;
    struct setnode *parent;
    void (*display)(FILE *, void *);
} SETNODE;

static SETNODE *newSETNODE(void (*d)(FILE *, void *), void *value);
static void displaySETNODE(FILE *fp, void *node);
static void link(SETNODE *x, SETNODE *y);
static void printChain(FILE *fp, SETNODE *node);

SET *newSET(void (*d)(FILE *, void *)) {
    SET *set = (SET *)malloc(sizeof(SET));
    set->origDisplay = d;
    set->da = newDA(displaySETNODE);
    return set;
}

int makeSET(SET *d, void *value) {
    SETNODE *rep = newSETNODE(d->origDisplay, value);
    rep->index = sizeDA(d->da);
    insertDA(d->da, rep);
    return rep->index;
}

int findSET(SET *d, int index) {
    SETNODE *x = getDA(d->da, index);
    if (x != x->parent) {
        x->parent = getDA(d->da, findSET(d, x->parent->index));
    }
    return x->parent->index;
}

int unionSET(SET *d, int index1, int index2) {
    SETNODE *x = getDA(d->da, findSET(d, index1));
    SETNODE *y = getDA(d->da, findSET(d, index2));
    if (x == y) {
        return 0;
    }
    link(x, y);
    return 1;    
}

int countSET(SET *d) {
    return sizeDA(d->da);
}

int displaySET(FILE *fp, SET *d) {
    for (int i = 0; i < sizeDA(d->da); i++) {
        fprintf(fp, "%d: ", i);
        printChain(fp, getDA(d->da, i));
        fprintf(fp, "\n");
    }
    return 0;
}

// static methods

static SETNODE *newSETNODE(void (*d)(FILE *, void *), void *value) {
    SETNODE *setnode = (SETNODE *)malloc(sizeof(SETNODE));
    setnode->value = value;
    setnode->rank = 0;
    setnode->index = 0;
    setnode->parent = setnode;
    setnode->display = d;
    return setnode;
}

static void displaySETNODE(FILE *fp, void *node) {
    SETNODE *setnode = node;
    setnode->display(fp, setnode->value);
}

static void link(SETNODE *x, SETNODE *y) {
    if (x->rank > y->rank) {
        y->parent = x;
    }
    else if (x->rank < y->rank) {
        x->parent = y;
    }
    else if (x->index < y->index) {
        y->parent = x;
        x->rank += 1;
    }
    else {
        x->parent = y;
        y->rank += 1;
    }
}

static void printChain(FILE *fp, SETNODE *node) {
    while (node != node->parent) {
        node->display(fp, node->value);
        fprintf(fp, " ");
        node = node->parent;
    }
    node->display(fp, node->value);
}
