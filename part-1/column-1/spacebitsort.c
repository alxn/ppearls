/* Copyright (C) 1999 Lucent Technologies */
/* From 'Programming Pearls' by Jon Bentley */

/* Based on bitsort.c -- bitmap sort from Column 1
 *   Sort distinct integers in the range [0..N-1]
 *
 * See:
 * http://research.swtch.com/sparse
 */

#include <stdio.h>
#include <stdbool.h>

#define BITSPERWORD 32
#define SHIFT 5
#define MASK 0x1F
#define N 10000000

#define TOP	(1 + N/BITSPERWORD)
int a[TOP];
int from[TOP];
int to[TOP];
const int dtop = TOP;

void set(int i) {        a[i>>SHIFT] |=  (1<<(i & MASK)); }
void clr(int i) {        a[i>>SHIFT] &= ~(1<<(i & MASK)); }
int  tst(int i) { return a[i>>SHIFT] &   (1<<(i & MASK)); }

bool
is_member (int subscript, int top)
{
    return ((from[subscript] < top) &&
	    (to[from[subscript]] == subscript));
}

int main()
{
    int i;
    int subscript;
    int top = 0;

    while (scanf("%d", &i) != EOF) {
	subscript = (i>>SHIFT);
	if (!is_member(subscript, top)) {
	    from[subscript] = top;
	    to[top] = subscript;
	    a[subscript] = 0;
	    top++;
	}

	set(i);
    }

    for (i = 0; i < N; i++) {
	subscript = (i>>SHIFT);
	if (is_member(subscript, top)) {
	    if (tst(i)) {
		printf("%d\n", i);
	    }
	}
    }

    return 0;
}
