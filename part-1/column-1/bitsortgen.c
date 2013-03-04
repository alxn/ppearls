/* Copyright (C) 1999 Lucent Technologies */
/* From 'Programming Pearls' by Jon Bentley */

/* bitsortgen.c -- gen $1 distinct integers from U[0,$2) */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAXN 2000000
int x[MAXN];

int randint(int a, int b)
{	return a + (RAND_MAX * rand() + rand()) % (b + 1 - a);
}

int main(int argc, char *argv[])
{	int i, k, n, t, p;
	srand((unsigned) time(NULL));
	k = atoi(argv[1]);
	n = atoi(argv[2]);
	for (i = 0; i < n; i++)
		x[i] = i;
	for (i = 0; i < k; i++) {
		p = randint(i, n-1);
		t = x[p]; x[p] = x[i]; x[i] = t;
		printf("%d\n", x[i]);
	}
	return 0;
}
