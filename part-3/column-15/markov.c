/* Copyright (C) 1999 Lucent Technologies */
/* From 'Programming Pearls' by Jon Bentley */

/* markov.c -- generate random text from input document */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char inputchars[4300000];
char *word[800000];
int nword = 0;
int k = 2;

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
{	int i, wordsleft = 10000, l, m, u;
	char *phrase, *p;
	word[0] = inputchars;
	while (scanf("%s", word[nword]) != EOF) {
		word[nword+1] = word[nword] + strlen(word[nword]) + 1;
		nword++;
	}
	for (i = 0; i < k; i++)
		word[nword][i] = 0;
	for (i = 0; i < k; i++)
		printf("%s\n", word[i]);
	qsort(word, nword, sizeof(word[0]), sortcmp);
	phrase = inputchars;
	for ( ; wordsleft > 0; wordsleft--) {
		l = -1;
		u = nword;
		while (l+1 != u) {
			m = (l + u) / 2;
			if (wordncmp(word[m], phrase) < 0)
				l = m;
			else
				u = m;
		}
		for (i = 0; wordncmp(phrase, word[u+i]) == 0; i++)
			if (rand() % (i+1) == 0)
				p = word[u+i];
		phrase = skip(p, 1);
		if (strlen(skip(phrase, k-1)) == 0)
			break;
		printf("%s\n", skip(phrase, k-1));
	}
	return 0;
}
