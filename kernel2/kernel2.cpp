#include "kernel2.h"

void kernel2( float a[ARRAY_SIZE], float bias[ARRAY_SIZE], int index[ARRAY_SIZE])
{
    LOOP1: for (int i=0; i<ARRAY_SIZE; ++i) {
    #pragma HLS PIPELINE off
        a[index[i]] = a[index[i]]+ bias[i];
      }
}
