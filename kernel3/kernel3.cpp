#include "kernel3.h"

void kernel3(int a[ARRAY_SIZE], int factor[ARRAY_SIZE], int targetIndex)
{
    LOOP1: for (int i=targetIndex+1; i<ARRAY_SIZE-1; ++i){
    #pragma HLS PIPELINE off
        a[targetIndex] = a[targetIndex] - (factor[i]*a[i]) + (factor[i]*a[i+1]);
    }
}
