/* Copyright (C) 1999 Lucent Technologies */
/* From 'Programming Pearls' by Jon Bentley */

/* longdup.c -- Print longest string duplicated M times */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int pstrcmp(char **p, char **q)
{   return strcmp(*p, *q); }

int comlen(char *p, char *q)
{	int i = 0;
	while (*p && (*p++ == *q++))
		i++;
	return i;
}

#define M 1
#define MAXN 5000000
char c[MAXN], *a[MAXN];

int main()
{   int i, ch, n = 0, maxi, maxlen = -1;
    while ((ch = getchar()) != EOF) {
        a[n] = &c[n];
        c[n++] = ch;
    }
    c[n] = 0;
    qsort(a, n, sizeof(char *), pstrcmp);
    for (i = 0; i < n-M; i++)
        if (comlen(a[i], a[i+M]) > maxlen) {
            maxlen = comlen(a[i], a[i+M]);
            maxi = i;
        }
    printf("%.*s\n", maxlen, a[maxi]);
    return 0;
}
