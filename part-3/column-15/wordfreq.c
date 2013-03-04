/* Copyright (C) 1999 Lucent Technologies */
/* From 'Programming Pearls' by Jon Bentley */

/* wordfreq.c -- list of words in file, with counts */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node *nodeptr;
typedef struct node {
	char *word;
	int count;
	nodeptr next;
} node;

#define NHASH 29989
#define MULT 31
nodeptr bin[NHASH];

unsigned int hash(char *p)
{	unsigned int h = 0;
	for ( ; *p; p++)
		h = MULT * h + *p;
	return h % NHASH;
}

#define NODEGROUP 1000
int nodesleft = 0;
nodeptr freenode;

nodeptr nmalloc()
{	if (nodesleft == 0) {
		freenode = malloc(NODEGROUP*sizeof(node));
		nodesleft = NODEGROUP;
	}
	nodesleft--;
	return freenode++;
}

#define CHARGROUP 10000
int charsleft = 0;
char *freechar;

char *smalloc(int n)
{	if (charsleft < n) {
		freechar = malloc(n+CHARGROUP);
		charsleft = n+CHARGROUP;
	}
	charsleft -= n;
	freechar += n;
	return freechar - n;
}

void incword(char *s)
{	nodeptr p;
	int h = hash(s);
	for (p = bin[h]; p != NULL; p = p->next)
		if (strcmp(s, p->word) == 0) {
			(p->count)++;
			return;
		}
	p = nmalloc();
	p->count = 1;
	p->word = smalloc(strlen(s)+1);
	strcpy(p->word, s);
	p->next = bin[h];
	bin[h] = p;
}

int main()
{	int i;
	nodeptr p;
	char buf[100];
	for (i = 0; i < NHASH; i++)
		bin[i] = NULL;
	while (scanf("%s", buf) != EOF)
		incword(buf);
	for (i = 0; i < NHASH; i++)
		for (p = bin[i]; p != NULL; p = p->next)
			printf("%s %d\n", p->word, p->count);
	return 0;
}
