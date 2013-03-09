/* Copyright (C) 1999 Lucent Technologies */
/* From 'Programming Pearls' by Jon Bentley */

/* bitsortgen.c -- gen $1 distinct integers from U[0,$2) 
 *
 * This is the Fisher–Yates shuffle...
 */

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <time.h>

uint32_t *x;

/*
 * Think of it like a pack of sorted pack of cards.
 *
 * Pick a random card out of the deck, and replace with the first card of the
 * deck.
 *
 * Continue until you have k cards.
 *
 * Starting with:
 *
 *   x[i] = i; for [0,n]
 *
 * Generate a random number in the range r=[a=[0,n],n]
 *
 * 0...a......n
 *      ^^^^^^
 *
 * Swap x[r] with x[a].
 *
 * i.e. guaranteed to pick random unused number.
 *
 */

uint32_t randint (uint32_t a, uint32_t b)
{
    uint32_t range;
    uint32_t r, max;

    /*
     * We want a number in the range a..b.
     */
    range = b - a + 1;

    /*
     * Discard top random numbers for uniform distribution in this range, by
     * removing the remainder.
     */
    max = RAND_MAX;
    if (range < RAND_MAX) {
	max -= (RAND_MAX % range);
    }

    do {
	r = rand();
    } while (r >= max);


    // if (RAND_MAX * RAND_MAX < INT_MAX)

//    if (b > RAND_MAX) {
//	r += RAND_MAX * rand();
//    }

    r %= range;

    return (a + r);
}

int main(int argc, const char *argv[])
{
    uint32_t i, k, n, t, p;

    if (argc < 2) {
	fprintf(stderr, "Usage %s: <num> <max>\n",
		argv[0]);
	exit(1);
    }

    k = atoi(argv[1]);
    n = atoi(argv[2]);

    if ((k <= 0) || (n <= k)) {
	fprintf(stderr, "Usage %s: <1..n-1> <n>\n",
		argv[0]);
	exit(1);
    }
    
    //srand((unsigned) time(NULL));
    srand(0);//could make arg.

    x = malloc(n * sizeof(*x));
    if (!x) {
	fprintf(stderr, "No mem!\n");
	exit(1);
    }

    for (i = 0; i < n; i++)
	x[i] = i;

    for (i = 0; i < k; i++) {
	p = randint(i, n-1);
	//printf("Result %u\n", p);
	t = x[p];
	x[p] = x[i];
	x[i] = t;
	printf("%d\n", x[i]);
    }

    free(x);

    return 0;
}
