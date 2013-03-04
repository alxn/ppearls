/* Copyright (C) 1999 Lucent Technologies */
/* From 'Programming Pearls' by Jon Bentley */

/* timemod0.c -- Simple experiments on C run time costs */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main()
{	int i, n, ia, ib, ic;
	float fa, fb, fc;
	n = 1000000000;	/* run time in secs gives nanosecs/loop */
	ia = ib = ic = 9;
	fa = fb = 9.0;
	for (i = 0; i < n; i++) {
		/* null loop		19.1 */
		/* ia = ib + ic;	17.7 */
		/* ia = ib - ic;	17.6 */
		/* ia = ib * ic;	17.7 */
		/* ia = ib % ic;	98.3 */
		/* ia = ib / ic;	98.3 */
		/* ia = rand();		41.5 */
		/* fa = sqrt(fb);	184 */
		/* free(malloc(8));	2400 */
	}
	return 0;
}
