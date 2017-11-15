#include "utils.h"

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int min(int a, int b) {
    return a < b ? a : b;
}
