/* Copyright (C) 1999 Lucent Technologies */
/* From 'Programming Pearls' by Jon Bentley */

/* sign.c -- sign each line of a file for finding anagrams
   The input line "stop" gives the output line "opst stop"
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define WORDMAX 100

int charcomp(const void *x, const void *y)
{
    return *(char *)x - *(char *)y;
}

int main()
{
    char word[WORDMAX], sig[WORDMAX];
    while (scanf("%s", word) != EOF) {
        strcpy(sig, word);
        qsort(sig, strlen(sig), sizeof(char), charcomp);
        printf("%s %s\n", sig, word);
    }
    return 0;
}
