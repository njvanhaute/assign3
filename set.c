#include <stdlib.h>
#include "da.h"
#include "set.h"

struct set {
    DA *da;
    void (*display)(FILE *, void *);
};

typedef struct node { 
    int rank;
    void *value;
    struct node *parent;
} NODE;

static NODE *newNODE(void *value);
static NODE *compress(NODE *x);

SET *newSET(void (*d)(FILE *, void *)) {
    SET *set = (SET *)malloc(sizeof(SET));
    set->da = newDA(d);
    set->display = d;
    return set;
}

int makeSET(SET *d, void *value) {
    NODE *node = newNODE(value);
    insertDA(d->da, node);
    return sizeDA(d->da) - 1; // When size is 1, return 0, etc...    
}

int findSET(SET *d, int index) {
    NODE *node = (NODE *)getDA(d->da, index);
    
}

static NODE *newNODE(void *value) {
    NODE *node = (NODE *)malloc(sizeof(NODE));
    node->rank = 0;
    node->value = value;
    node->parent = node;
    return node;
}

static NODE *compress(NODE *x) {
    if (x != x->parent) {
        x->parent = compress(x->parent);
    }
    return x->parent;
}
