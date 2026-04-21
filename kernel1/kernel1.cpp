#include "kernel1.h"

void kernel1( int a[ARRAY_SIZE] )
{
    int i;
    LOOP1: for(i=3; i<ARRAY_SIZE; i++) {
    #pragma HLS PIPELINE off
        a[i] = a[i-1] + a[i-2] * a[i-3];
    }
}
