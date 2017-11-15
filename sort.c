#include <stdlib.h>
#include "sort.h"
#include "utils.h"

static void bottomUpMerge(void **, void **, int, int, int, int (*)(void *, void *));
static void copyArray(void **, void **, int);

void mergeSort(void **arr, int n, int (*compare)(void *, void *)) {
    void **work = (void **)malloc(sizeof(void *) * n);
    for (int width = 1; width < n; width *= 2) {
        for (int i = 0; i < n; i += width * 2) {
            bottomUpMerge(arr, work, i, min(i + width, n), min(i + 2 * width, n), compare); 
        }
        copyArray(work, arr, n);
    }
}

static void bottomUpMerge(void **arr, void **work, int l, int r, int end, int (*compare)(void *, void *)) {
    int i = l, j = r;
    for (int k = l; k < end; k++) {
        if (i < r && (j >= end || compare(arr[i], arr[j]) <= 0)) {
            work[k] = arr[i];
            i++;
        }
        else {
            work[k] = arr[j];
            j++;
        }
    }
}

static void copyArray(void **work, void **arr, int n) {
    for (int i = 0; i < n; i++) {
        arr[i] = work[i];
    }
}
