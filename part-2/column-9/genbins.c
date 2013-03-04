/* Copyright (C) 1999 Lucent Technologies */
/* From 'Programming Pearls' by Jon Bentley */

/* genbins.c -- generate random numbers with bins */

/* If NODESIZE is 8, this program uses the special-case malloc.
   Change NODESIZE to 0 to use the system malloc.
 */

#include <stdio.h>
#include <stdlib.h>

#define NODESIZE 8
#define NODEGROUP 1000
int nodesleft = 0;
char *freenode;

void *pmalloc(int size)
{	void *p;
	if (size != NODESIZE)
		return malloc(size);
	if (nodesleft == 0) {
		freenode = malloc(NODEGROUP*NODESIZE);
		nodesleft = NODEGROUP;
	}
	nodesleft--;
	p = (void *) freenode;
	freenode += NODESIZE;
	return p;
}

struct node {
	int val;
	struct node *next;
};

struct node **bin, *sentinel;
int bins, bincnt, maxval;

void initbins(int maxelms, int pmaxval)
{	int i;
	bins = maxelms;
	maxval = pmaxval;
	bin = pmalloc(bins*sizeof(struct node *));
	sentinel = pmalloc(sizeof(struct node));
	sentinel->val = maxval;
	for (i = 0; i < bins; i++)
		bin[i] = sentinel;
	bincnt = 0;
}

struct node *rinsert(struct node *p, int t)
{	if (p->val < t) {
		p->next = rinsert(p->next, t);
	} else if (p->val > t) {
		struct node *q = pmalloc(sizeof(struct node));
		q->val = t;
		q->next = p;
		p = q;
		bincnt++;
	}
	return p;
}

void insert(int t)
{	int i;
	i = t / (1 + maxval/bins);
	i = t / (1 + maxval/bins);
	bin[i] = rinsert(bin[i], t);
}

void report()
{	int i, j = 0;
	struct node *p;
	for (i = 0; i < bins; i++)
		for (p = bin[i]; p != sentinel; p = p->next)
			/* printf("%d\n", p->val) */;
			/* Uncomment for testing, comment for profiling */
}

int bigrand()
{	return RAND_MAX*rand() + rand();
}

int main(int argc, char *argv[])
{	int m = atoi(argv[1]);
	int n = atoi(argv[2]);
	initbins(m, n);
	while (bincnt < m) {
		insert(bigrand() % n);
	}
	report();
	return 0;
}