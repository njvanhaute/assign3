#include <stdio.h>
#include "integer.h"
#include "set.h"

int main(void) {
    SET *d = newSET(displayINTEGER);
    int nums[4] = {0, 0, 0, 0};
    for (int i = 1; i < 4; i++) {
        nums[i] = makeSET(d, newINTEGER(i));
    }    
    return 0;
}
