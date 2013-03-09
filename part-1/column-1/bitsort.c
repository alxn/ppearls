/* Copyright (C) 1999 Lucent Technologies */
/* From 'Programming Pearls' by Jon Bentley */

/* bitsort.c -- bitmap sort from Column 1
 *   Sort distinct integers in the range [0..N-1]
 */

#include <stdio.h>
#include <stdlib.h>

/*
 * How would you implement bit vectors using bitwise logical operations (such
 * as and, or and shift)?
 *
 *  Given e.g. 165 (1010 0101) to store:
 *
 *  a[1010 0101>>5] =  1 << (1010 0101 & 0x1F)
 *  a[101]          =  1 <<     0 0101
 *  a[5]            =  1 << 5
 *  a[5]            =  0010 0000; well, plus a lot more leading 0's.
 */
#define BITSPERWORD 32	// err uint32_t ...
#define SHIFT	5	// log2(BITSPERWORD); i.e. how many numbers we can
			// store per element in the array[].
#define MASK	0x1F	// i.e. 0001 1111 (5 bits) to mask of all but the
			// contents.
#define N	10000000

int a[1 + N/BITSPERWORD];

void set(int i) {        a[i>>SHIFT] |=  (1<<(i & MASK)); }
void clr(int i) {        a[i>>SHIFT] &= ~(1<<(i & MASK)); }
int  tst(int i) { return a[i>>SHIFT] &   (1<<(i & MASK)); }

int main()
{
    /*
     * Define for word-parallel init
     */
#ifndef PARALLEL_INIT
    int i;

    for (i = 0; i < N; i++)
	clr(i);
#else
    int top = 1 + N/BITSPERWORD;

    for (i = 0; i < top; i++)
	a[i] = 0;
#endif

    // Need to check other scanf return values for error.
    while (scanf("%d", &i) != EOF) {
	if ((i < 0) || (i >= N)) {
	    fprintf(stderr, "Out of range 0 >= %d < %d\n", i, N);
	    exit(1);
	}
	if (tst(i)) {
	    fprintf(stderr, "Already passed %d\n", i);
	    exit(1);
	}
	set(i);
    }

    for (i = 0; i < N; i++)
	if (tst(i)) 
	    printf("%d\n", i);

    return 0;
}
