#include "kernel4.h"

float kernel4(float max, float array1[ARRAY_SIZE], float array2[ARRAY_SIZE])
{
    int i=0;
    float sum = 0.0;
    LOOP1: while (sum<max && i<ARRAY_SIZE)
    {
    #pragma HLS PIPELINE off
        sum = array1[i] + array2[i];
        i++;
    }
    return sum;
}
