#include "kernel7.h"

void kernel7(int a[16*ARRAY_SIZE], int b[16*ARRAY_SIZE], int c[16*ARRAY_SIZE], int x) 
{
    LOOP1: for (int i=0; i < ARRAY_SIZE; i++)
    {
    #pragma HLS PIPELINE off
        x = x * a[i];
        a[b[c[x]]]=x;
    }
}

