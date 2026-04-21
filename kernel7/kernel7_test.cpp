#include <stdio.h>
#include <stdlib.h>
#include "kernel7.h"

void kernel7_sw(int a[16*ARRAY_SIZE], int b[16*ARRAY_SIZE], int c[16*ARRAY_SIZE], int x)
{
    LOOP1: for (int i=0; i < ARRAY_SIZE; i++)
    {
        x = x * a[i];
        a[b[c[x]]]=x;
    }
}

int main() 
{
    // Input and output arrays
    int a[16*ARRAY_SIZE];
    int b[16*ARRAY_SIZE];
    int c[16*ARRAY_SIZE];
    int a_sw[16*ARRAY_SIZE];
    int b_sw[16*ARRAY_SIZE];
    int c_sw[16*ARRAY_SIZE];
    int x;

    // Initialize arrays
    for (int i=0; i < 16*ARRAY_SIZE; i++) {
    	a[i] = 0;
    	b[i] = 0;
    	c[i] = 0;
    	a_sw[i] = 0;
        b_sw[i] = 0;
        c_sw[i] = 0;
    }

    x = rand() % 12;
    // Run the kernel
    kernel7(a, b, c, x);

    // Run the naive code to get results for comparison
    kernel7_sw(a_sw, b_sw, c_sw, x);

    // Check results
    bool pass = true;
    for (int i = 0; i < 16*ARRAY_SIZE; i++) {
    	if (a[i] != a_sw[i]) {
    		printf("Error in a at index %u \n", i);
    		pass = false;
    	}
    }
    
    if(pass)
    {
	printf("Test passed !\n");
    	return 0;    
    }

    printf("Test failed  !!!\n");
    return 1;
}

