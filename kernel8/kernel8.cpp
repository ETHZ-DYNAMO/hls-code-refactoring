#include "kernel8.h"

void kernel8 (int a[ARRAY_SIZE], int b[ARRAY_SIZE], int m[ARRAY_SIZE], int s) 
{
    LOOP1: for (int i=0; i < ARRAY_SIZE; i++) {
    #pragma HLS PIPELINE off
        LOOP2: for (int j=0; j < m[i]; j++) {
        #pragma HLS PIPELINE off
        #pragma HLS loop_flatten off
            s = a[j * s];
        }
        b[i] = s;
    }
}