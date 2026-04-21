#include "kernel6.h"

void kernel6(int a[ARRAY_SIZE], int factor, int offset)
{
    LOOP1: for (int i=6; i<ARRAY_SIZE-1-offset; ++i)
    {
    #pragma HLS PIPELINE off
        a[i] = a[i-6+offset]*factor;
    }
}

