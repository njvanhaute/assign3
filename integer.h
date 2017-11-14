#ifndef __INT_INCLUDED__
#define __INT_INCLUDED__

#include <stdio.h>

typedef struct integer INTEGER;

extern INTEGER *newINTEGER(int);
extern int getINTEGER(INTEGER *);
extern void displayINTEGER(FILE *, void *);
extern int compareINTEGER(void *, void *);

#endif
