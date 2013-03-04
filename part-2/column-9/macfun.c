/* Copyright (C) 1999 Lucent Technologies */
/* From 'Programming Pearls' by Jon Bentley */

/* macfun.c -- time macro and function implementations of max
 * Input: a sequence of (alg num, n) pairs.
 * Output: for each test, (alg num, n, ans, ticks, secs)
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAXN 1000000
float x[MAXN];


/* arrmax1 -- max is a macro */

#define max1(a, b) ((a) > (b) ? (a) : (b))

float arrmax1(int n)
{	if (n == 1)
		return x[0];
	else
		return max1(x[n-1], arrmax1(n-1));
}


/* arrmax2 -- max is a function */

float max2(float a, float b)
{	return a > b ? a : b;
}

float arrmax2(int n)
{	if (n == 1)
		return x[0];
	else
		return max2(x[n-1], arrmax2(n-1));
}


/* arrmax3 -- MS VC++ stdlib defines max as a macro */

#ifndef max
#define max(a, b) max2(a, b)
#endif

float arrmax3(int n)
{	if (n == 1)
		return x[0];
	else
		return max(x[n-1], arrmax3(n-1));
}


int main()
{   int algnum, i, n, start, clicks;
    float thisans;

	for (i = 0; i < MAXN; i++)
		x[i] = MAXN-i;
	while (scanf("%d %d", &algnum, &n) != EOF) {
		start = clock();
		thisans = -1;
		switch (algnum) {
			case 1: thisans = arrmax1(n); break;
			case 2: thisans = arrmax2(n); break;
			case 3: thisans = arrmax3(n); break;
			default: break;
		}
		clicks = clock()-start;
		printf("%d\t%d\t%g\t%d\t%g\n", algnum, n, thisans,
			clicks, clicks / (float) CLOCKS_PER_SEC);
    }
	return 0;
}
