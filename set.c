#include <stdlib.h>
#include "set.h"
#include "da.h"

struct set {
    DA *da;
    int numReps;
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

// Function: newSET
// Takes in a function pointer to display the type of object stored.
// Returns the newly allocated disjoint-set data structure.

SET *newSET(void (*d)(FILE *, void *)) {
    SET *set = (SET *)malloc(sizeof(SET));
    set->origDisplay = d;
    set->da = newDA(displaySETNODE);
    set->numReps = 0;
    return set;
}

// Function: makeSET
// Takes in a disjoint-set object and a void pointer
// Inserts a wrapped value into the underlying dynamic array and returns the index of the inserted value.
// The caller of makeSET should save the return value so that findSET and unionSET can be called in the future.

int makeSET(SET *d, void *value) {
    SETNODE *rep = newSETNODE(d->origDisplay, value);
    rep->index = sizeDA(d->da);
    insertDA(d->da, rep);
    d->numReps += 1;
    return rep->index;
}

// Function: findSET
// Takes in a disjoint-set object and an integral index
// Returns the index of the representative of the value stored at the given index.

int findSET(SET *d, int index) {
    SETNODE *x = getDA(d->da, index);
    if (x != x->parent) {
        x->parent = getDA(d->da, findSET(d, x->parent->index));
    }
    return x->parent->index;
}

// Function: unionSET
// Takes in a disjoint-set object and two index variables
// Unites the two sets of the set members located at index1 and index2
// Returns 1 if successful and 0 otherwise

int unionSET(SET *d, int index1, int index2) {
    SETNODE *x = getDA(d->da, findSET(d, index1));
    SETNODE *y = getDA(d->da, findSET(d, index2));
    if (x == y) {
        return 0;
    }
    link(x, y);
    d->numReps -= 1;
    return 1;    
}

// Function: countSET
// Takes in a disjoint-set object
// Returns the number of representatives in the set.

int countSET(SET *d) {
    return d->numReps;
}

// Function: displaySET
// Takes in a FILE pointer and a disjoint-set object
// Prints each value in the underlying dynamic array

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
        displaySETNODE(fp, node); 
        fprintf(fp, " ");
        node = node->parent;
    }
    node->display(fp, node->value);
}
