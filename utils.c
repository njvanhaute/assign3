#include "utils.h"

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int min(int a, int b) {
    return a < b ? a : b;
}

void initArray(int *arr, int n, int val) {
    for (int i = 0; i < n; i++) {
        arr[i] = val;
    }
}
