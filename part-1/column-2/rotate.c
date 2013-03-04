/* Copyright (C) 1999 Lucent Technologies */
/* From 'Programming Pearls' by Jon Bentley */

/* rotate.c -- time algorithms for rotating a vector
	Input lines:
		algnum numtests n rotdist
		algnum:
		  1: reversal algorithm
		  2: juggling algorithm
		  22:  juggling algorithm with mod rather than if
		  3: gcd algorithm
		  4: slide (don't rotate): baseline alg for timing
	To test the algorithms, recompile and change main to call testrot
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAXN 10000000

int x[MAXN];
int rotdist, n;

/* Alg 1: Rotate by reversal */

void reverse(int i, int j)
{	int t;
	while (i < j) {
		t = x[i]; x[i] = x[j]; x[j] = t;
		i++;
		j--;
	}
}

void revrot(int rotdist, int n)
{	reverse(0, rotdist-1);
	reverse(rotdist, n-1);
	reverse(0, n-1);
}

/* Alg 2: Juggling (dolphin) rotation */

int gcd(int i, int j)
{	int t;
	while (i != 0) {
		if (j >= i)
			j -= i;
		else {
			t = i; i = j; j = t;
		}
	}
	return j;
}

void jugglerot(int rotdist, int n)
{	int cycles, i, j, k, t;
	cycles = gcd(rotdist, n);
	for (i = 0; i < cycles; i++) {
		/* move i-th values of blocks */
		t = x[i];
		j = i;
		for (;;) {
			k = j + rotdist;
			if (k >= n)
				k -= n;
			if (k == i)
				break;
			x[j] = x[k];
			j = k;
		}
		x[j] = t;
	}
}

void jugglerot2(int rotdist, int n)
{	int cycles, i, j, k, t;
	cycles = gcd(rotdist, n);
	for (i = 0; i < cycles; i++) {
		/* move i-th values of blocks */
		t = x[i];
		j = i;
		for (;;) {
          /* Replace with mod below
			k = j + rotdist;
			if (k >= n)
				k -= n;
           */
            k = (j + rotdist) % n;
			if (k == i)
				break;
			x[j] = x[k];
			j = k;
		}
		x[j] = t;
	}
}

/* Alg 3: Recursive rotate (using gcd structure) */

void swap(int i, int j, int k) /* swap x[i..i+k-1] with x[j..j+k-1] */
{	int t;
	while (k-- > 0) {
		t = x[i]; x[i] = x[j]; x[j] = t;
		i++;
		j++;
	}

}

void gcdrot(int rotdist, int n)
{	int i, j, p;
	if (rotdist == 0 || rotdist == n)
		return;
	i = p = rotdist;
	j = n - p;
	while (i != j) {
		/* invariant:
			x[0  ..p-i  ] is in final position
			x[p-i..p-1  ] = a (to be swapped with b)
			x[p  ..p+j-1] = b (to be swapped with a)
			x[p+j..n-1  ] in final position
		*/
		if (i > j) {
			swap(p-i, p, j);
			i -= j;
		} else {
			swap(p-i, p+j-i, i);
			j -= i;
		}
	}
	swap(p-i, p, i);
}

int isogcd(int i, int j)
{	if (i == 0) return j;
	if (j == 0) return i;
	while (i != j) {
		if (i > j)
			i -= j;
		else 
			j -= i;
	}
	return i;
}

void testgcd()
{
	int i,j;
	while (scanf("%d %d", &i, &j) != EOF)
		printf("%d\n", isogcd(i,j) );
}

/* Test all algs */

void slide(int rotdist, int n) /* Benchmark: slide left rotdist (lose 0..rotdist-1) */
{	int i;

	for (i = rotdist; i < n; i++)
		x[i-rotdist] = x[i];
}

void initx()
{
	int i;
	for (i = 0; i < n; i++)
		x[i] = i;
}

void printx()
{	int i;
	for (i = 0; i < n; i++)
		printf(" %d", x[i]);
	printf("\n");
}

void roterror()
{
	fprintf(stderr, " rotate bug %d %d\n", n, rotdist);
	printx();
	exit (1);
}

void checkrot()
{	int i;
	for (i = 0; i < n-rotdist; i++)
		if (x[i] != i+rotdist)
			roterror();
	for (i = 0; i < rotdist; i++)
		if (x[n-rotdist+i] != i)
			roterror();
}

void testrot()
{	for (n = 1; n <= 20; n++) {
		printf(" testing n=%d\n", n);
		for (rotdist = 0; rotdist <= n; rotdist++) {
			/* printf("  testing rotdist=%d\n", rotdist); */
			initx(); revrot(rotdist, n);     checkrot();
			initx(); jugglerot(rotdist, n);  checkrot();
			initx(); jugglerot2(rotdist, n); checkrot();
			initx(); gcdrot(rotdist, n);     checkrot();
		}
	}
}

/* Timing */

void timedriver()
{	int i, algnum, numtests, start, clicks;
	while (scanf("%d %d %d %d", &algnum, &numtests, &n, &rotdist) != EOF) {
		initx();
		start = clock();
		for (i = 0; i < numtests; i++) {
			if (algnum == 1)
				revrot(rotdist, n);
			else if (algnum == 2)
				jugglerot(rotdist, n);
			else if (algnum == 22)
				jugglerot2(rotdist, n);
			else if (algnum == 3)
				gcdrot(rotdist, n);
			else if (algnum == 4)
				slide(rotdist, n);
		}
		clicks = clock() - start;
		printf("%d\t%d\t%d\t%d\t%d\t%g\n",
			algnum, numtests, n, rotdist, clicks,
			1e9*clicks/((float) CLOCKS_PER_SEC*n*numtests));
	}
}

/* Main */

int main()
{	/* testrot(); */
	timedriver();
	return 0;
}