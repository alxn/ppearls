/* Copyright (C) 1999 Lucent Technologies */
/* From 'Programming Pearls' by Jon Bentley */

/* timemod.c -- Produce table of C run time costs */

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>

#define MAXN 100000
int x[MAXN];
int startn = 5000;
int n;

/* FUNCTIONS TO BE TIMED */

int intcmp(int *i, int *j)
{   return *i - *j; }

#define swapmac(i, j) { t = x[i]; x[i] = x[j]; x[j] = t; }

void swapfunc(int i, int j)
 {  int t = x[i];
	x[i] = x[j];
	x[j] = t;
 }

#define maxmac(a, b) ((a) > (b) ? (a) : (b))

int maxfunc(int a, int b)
{	return a > b ? a : b; }


/* WORKHORSE */

#define T(s) printf("%s (n=%d)\n", s, n);
#define TRIALS 5
#define M(op)							\
	printf(" %-22s", #op);				\
	k = 0;								\
	timesum = 0;						\
	for (ex = 0; ex < TRIALS; ex++) {	\
		start = clock();				\
		for (i = 1; i <= n; i++) {		\
			fi = (float) i;				\
			for (j = 1; j <= n; j++) {	\
				op;						\
			}							\
		}								\
		t = clock()-start;				\
		printf("%6d", t);				\
		timesum += t;					\
	}									\
	nans = 1e9 * timesum / ((double)	\
		n*n * TRIALS * CLOCKS_PER_SEC);	\
	printf("%8.0f\n", nans);


int main()
{   int i, j, k;
	float fi, fj, fk;
	int t, ex, timesum, start, globalstart;
	double nans;
	globalstart = clock();
	for (i = 0; i < n; i++)
		x[i] = rand();
	n = startn;
	printf("C Time Cost Model, n=%d\n", n);
	T("Integer Arithmetic");
	M({});
	M(k++);
	M(k = i + j);
	M(k = i - j);
	M(k = i * j);
	M(k = i / j);
	M(k = i % j);
	M(k = i & j);
	M(k = i | j);
	T("Floating Point Arithmetic");
	M(fj=j;);
	M(fj=j; fk = fi + fj;);
	M(fj=j; fk = fi - fj;);
	M(fj=j; fk = fi * fj;);
	M(fj=j; fk = fi / fj;);
	T("Array Operations");
	M(k = i + j);
	M(k = x[i] + j);
	M(k = i + x[j]);
	M(k = x[i] + x[j]);
	T("Comparisons");
	M(if (i < j) k++);
	M(if (x[i] < x[j]) k++);
	T("Array Comparisons and Swaps");
	M(k = (x[i]<x[k]) ? -1:1);
	M(k = intcmp(x+i, x+j));
	M(swapmac(i, j));
	M(swapfunc(i, j));
	T("Max Function, Macro and Inline");
	M(k = (i > j) ? i : j);
	M(k = maxmac(i, j));
	M(k = maxfunc(i, j));
	n = startn / 5;
	T("Math Functions");
	M(fk = j+fi;);
	M(k = rand(););
	M(fk = sqrt(j+fi));
	M(fk = sin(j+fi));
	M(fk = sinh(j+fi));
	M(fk = asin(j+fi));
	M(fk = cos(j+fi));
	M(fk = tan(j+fi));
	n = startn / 10;
	T("Memory Allocation");
	M(free(malloc(16)););
	M(free(malloc(100)););
	M(free(malloc(2000)););

	/* Possible additions: input, output, malloc */
	printf("  Secs: %4.2f\n",
		((double) clock()-globalstart)
		/ CLOCKS_PER_SEC);
	return 0;
}
