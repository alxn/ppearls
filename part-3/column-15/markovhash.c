/* Copyright (C) 1999 Lucent Technologies */
/* From 'Programming Pearls' by Jon Bentley */

/* markovhash.c -- generate random text, sped up with hash tables */

/* For storage efficiency (and also to minimize changes from markov.c),
   the hash table is implemented in the integer array next.
   If bin[i]=j, then word[j] is the first element in the list,
   word[next[j]] is the next element, and so on.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char inputchars[4300000];
#define MAXWORDS 800000
char *word[MAXWORDS];
int nword = 0;
int k = 2;

int next[MAXWORDS];
#define NHASH 499979
int bin[NHASH];
#define MULT 31

unsigned int hash(char *ptr)
{	unsigned int h = 0;
	unsigned char *p = ptr;
	int n;
	for (n = k; n > 0; p++) {
		h = MULT * h + *p;
		if (*p == 0)
			n--;
	}
	return h % NHASH;
}

int wordncmp(char *p, char* q)
{	int n = k;
	for ( ; *p == *q; p++, q++)
		if (*p == 0 && --n == 0)
			return 0;
	return *p - *q;
}

int sortcmp(char **p, char **q)
{	return wordncmp(*p, *q);
}

char *skip(char *p, int n)
{	for ( ; n > 0; p++)
		if (*p == 0)
			n--;
	return p;
}

int main()
{	int i, wordsleft = 10000, j;
	char *phrase, *p;
	word[0] = inputchars;
	while (scanf("%s", word[nword]) != EOF) {
		word[nword+1] = word[nword] + strlen(word[nword]) + 1;
		nword++;
	}
	for (i = 0; i < k; i++)
		word[nword][i] = 0;
	for (i = 0; i < NHASH; i++)
		bin[i] = -1;
	for (i = 0; i <= nword - k; i++) { /* check */
		j = hash(word[i]);
		next[i] = bin[j];
		bin[j] = i;
	}
	for (i = 0; i < k; i++)
		printf("%s\n", word[i]);
	phrase = inputchars;
	for ( ; wordsleft > 0; wordsleft--) {
		i = 0;
		for (j = bin[hash(phrase)]; j >= 0; j = next[j])
			if ((wordncmp(phrase, word[j]) == 0)
				&& (rand() % (++i) == 0))
				p = word[j];
		phrase = skip(p, 1);
		if (strlen(skip(phrase, k-1)) == 0)
			break;
		printf("%s\n", skip(phrase, k-1));
	}
	return 0;
}
