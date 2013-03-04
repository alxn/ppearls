/* Copyright (C) 1999 Lucent Technologies */
/* From 'Programming Pearls' by Jon Bentley */

/* sort.cpp -- test and time sorting algorithms
	Input lines:  algnum n mod
	Output lines: algnum n mod clicks nanosecs_per_elem
   This is predominantly a C program; the only use of C++
   sort function immediately below the include line.
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// To change from C++ back to C, remove the following two lines
// and the call to sort in main
#include <algorithm>
using namespace std;

/* Data and supporting functions */

#define MAXN 10000000

typedef int DType;

DType realx[MAXN];
int *x = realx;	/* allow x to shift for heaps */
int n;

void swap(int i, int j)
{	DType t = x[i];
	x[i] = x[j];
	x[j] = t;
}

int randint(int l, int u)
{	return l + (RAND_MAX*rand() + rand()) % (u-l+1);
}

/* LIBRARY QSORT */

int intcomp(int *x, int *y)
{	return *x - *y;
}

/* INSERTION SORTS */

/* Simplest insertion sort */
void isort1()
{	int i, j;
	for (i = 1; i < n; i++)
		for (j = i; j > 0 && x[j-1] > x[j]; j--)
			swap(j-1, j);
}

/* Write swap function inline */
void isort2()
{	int i, j;
	DType t;
	for (i = 1; i < n; i++)
		for (j = i; j > 0 && x[j-1] > x[j]; j--) {
			t = x[j];
			x[j] = x[j-1];
			x[j-1] = t;
		}
}

/* Move assignments to and from t out of loop */
void isort3()
{	int i, j;
	DType t;
	for (i = 1; i < n; i++) {
		t = x[i];
		for (j = i; j > 0 && x[j-1] > t; j--)
			x[j] = x[j-1];
		x[j] = t;
	}
}

/* QUICKSORTS */

/* Simplest version, Lomuto partitioning */
void qsort1(int l, int u)
{	int i, m;
	if (l >= u)
		return;
	m = l;
	for (i = l+1; i <= u; i++)
		if (x[i] < x[l])
			swap(++m, i);
	swap(l, m);
	qsort1(l, m-1);
	qsort1(m+1, u);
}

/* Sedgewick's version of Lomuto, with sentinel */
void qsort2(int l, int u)
{	int i, m;
	if (l >= u)
		return;
	m = i = u+1;
	do {
		do i--; while (x[i] < x[l]);
		swap(--m, i);
	} while (i > l);
	qsort2(l, m-1);
	qsort2(m+1, u);
}

/* Two-way partitioning */
void qsort3(int l, int u)
{	int i, j;
	DType t;
	if (l >= u)
		return;
	t = x[l];
	i = l;
	j = u+1;
	for (;;) {
		do i++; while (i <= u && x[i] < t);
		do j--; while (x[j] > t);
		if (i > j)
			break;
		swap(i, j);
	}
	swap(l, j);
	qsort3(l, j-1);
	qsort3(j+1, u);
}

/* qsort3 + randomization + isort small subarrays + swap inline */
int cutoff = 50;
void qsort4(int l, int u)
{	int i, j;
	DType t, temp;
	if (u - l < cutoff)
		return;
	swap(l, randint(l, u));
	t = x[l];
	i = l;
	j = u+1;
	for (;;) {
		do i++; while (i <= u && x[i] < t);
		do j--; while (x[j] > t);
		if (i > j)
			break;
		temp = x[i]; x[i] = x[j]; x[j] = temp;
	}
	swap(l, j);
	qsort4(l, j-1);
	qsort4(j+1, u);
}

/* selection */

void select1(int l, int u, int k)
{	int i, j;
	DType t, temp;
	if (l >= u)
		return;
	swap(l, randint(l, u));
	t = x[l];
	i = l;
	j = u+1;
	for (;;) {
		do i++; while (i <= u && x[i] < t);
		do j--; while (x[j] > t);
		if (i > j)
			break;
		temp = x[i]; x[i] = x[j]; x[j] = temp;
	}
	swap(l, j);
	if (j < k)
		select1(j+1, u, k);
	else if (j > k)
		select1(l, j-1, k);
}

/* HEAP SORTS */

void siftup(int u)
{	int i, p;
	i = u;
	for (;;) {
		if (i == 1)
			break;
		p = i / 2;
		if (x[p] >= x[i])
			break;
		swap(p, i);
		i = p;
	}
}

void siftdown1(int l, int u)
{	int i, c;
	i = l;
	for (;;) {
		c = 2*i;
		if (c > u)
			break;
		if (c+1 <= u && x[c+1] > x[c])
			c++;
		if (x[i] > x[c])
			break;
		swap(i, c);
		i = c;
	}
}

void siftdown1b(int l, int u) /* More C-ish version of 1 */
{	int i, c;
	for (i = l; (c = 2*i) <= u; i = c) {
		if (c+1 <= u && x[c+1] > x[c])
			c++;
		if (x[i] > x[c])
			break;
		swap(i, c);
	}
}

void hsort1()
{	int i;
	x--;
	for (i = 2; i <= n; i++)
		siftup(i);
	for (i = n; i >= 2; i--) {
		swap(1, i);
		siftdown1(1, i-1);
	}
	x++;
}

void hsort2()
{	int i;
	x--;
	for (i = n/2; i >= 1; i--)
		siftdown1(i, n);
	for (i = n; i >= 2; i--) {
		swap(1, i);
		siftdown1(1, i-1);
	}
	x++;
}

void siftdown3(int l, int u) /* push to bottom, then back up */
{	int i, c, p;
	i = l;
	for (;;) {
		c = 2*i;
		if (c > u)
			break;
		if (c+1 <= u && x[c+1] > x[c])
			c++;
		swap(i, c);
		i = c;
	}
	for (;;) {
		p = i/2;
		if (p < l)
			break;
		if (x[p] > x[i])
			break;
		swap(p, i);
		i = p;
	}
}

void hsort3()
{	int i;
	x--;
	for (i = n/2; i >= 1; i--)
		siftdown3(i, n);
	for (i = n; i >= 2; i--) {
		swap(1, i);
		siftdown3(1, i-1);
	}
	x++;
}

void siftdown4(int l, int u) /* replace swap with assignments */
{	int i, c, p;
	DType t;
	t = x[l];
	i = l;
	for (;;) {
		c = 2*i;
		if (c > u)
			break;
		if (c+1 <= u && x[c+1] > x[c])
			c++;
		x[i] = x[c];
		i = c;
	}
	x[i] = t;
	for (;;) {
		p = i/2;
		if (p < l)
			break;
		if (x[p] > x[i])
			break;
		swap(p, i);
		i = p;
	}
}

void hsort4()
{	int i;
	x--;
	for (i = n/2; i >= 1; i--)
		siftdown4(i, n);
	for (i = n; i >= 2; i--) {
		swap(1, i);
		siftdown4(1, i-1);
	}
	x++;
}


/* Other Sorts -- Exercises in Column 11 */

void selsort()  /* Selection sort */
{	int i, j;
	for (i = 0; i < n-1; i++)
		for (j = i; j < n; j++)
			if (x[j] < x[i])
				swap(i, j);
}

void shellsort()
{	int i, j, h;
	for (h = 1; h < n; h = 3*h + 1)
		;
	for (;;) {
		h /= 3;
		if (h < 1) break;
		for (i = h; i < n; i++) {
			for (j = i; j >= h; j -= h) {
				if (x[j-h] < x[j]) break;
				swap(j-h, j);
			}
		}
	}
}



/* SCAFFOLDING */

/* Timing */

void timedriver()
{	int i, k, algnum, mod, start, clicks;
	while (scanf("%d %d %d", &algnum, &n, &mod) != EOF) {
		if (mod <= 0)
			mod = 10*n;
		for (i = 0; i < n; i++)
			x[i] = randint(0, mod-1);
		k = n/2;
		start = clock();
		switch (algnum) {
		case 11: qsort(x, n, sizeof(int), (int (__cdecl *)(const void *,const void *)) intcomp); break;
		case 12: sort(x, x+n); break;
		case 21: isort1(); break;
		case 22: isort2(); break;
		case 23: isort3(); break;
		case 31: qsort1(0, n-1); break;
		case 32: qsort2(0, n-1); break;
		case 33: qsort3(0, n-1); break;
		case 34: qsort4(0, n-1); isort3(); break;
		case 41: select1(0, n-1, k); break;
		case 51: hsort1(); break;
		case 52: hsort2(); break;
		case 53: hsort3(); break;
		case 54: hsort4(); break;
		case 61: selsort(); break;
		case 62: shellsort(); break;
		}
		clicks = clock() - start;
		if (algnum == 41) { /* Test selection */
			for (i = 0; i < k; i++)
				if (x[i] > x[k])
					printf("  SELECT BUG i=%d\n", i);
			for (i = k+1; i < n; i++)
				if (x[i] < x[k])
					printf("  SELECT BUG i=%d\n", i);
		} else { /* Test sort */
			for (i = 0; i < n-1; i++)
				if (x[i] > x[i+1])
					printf("  SORT BUG i=%d\n", i);
		}
		printf("%d\t%d\t%d\t%d\t%g\n",
			algnum, n, mod, clicks,
			1e9*clicks/((float) CLOCKS_PER_SEC*n));
	}
}

/* Main */

int main()
{	timedriver();
	return 0;
}
