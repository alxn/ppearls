/* Copyright (C) 1999 Lucent Technologies */
/* From 'Programming Pearls' by Jon Bentley */

/* maxsum.c -- time algs for maximum-sum subsequence
 * Input:  algnum, n
 * Output: algnum, n, answer, ticks, secs
 *		See main for algnum codes
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAXN 10000000
int n;
float x[MAXN];

void sprinkle() /* Fill x[n] with reals uniform on [-1,1] */
{   int i;
    for (i = 0; i < n; i++)
        x[i] = 1 - 2*( (float) rand()/RAND_MAX);
}

float alg1()
{   int i, j, k;
    float sum, maxsofar = 0;
    for (i = 0; i < n; i++)
        for (j = i; j < n; j++) {
            sum = 0;
            for (k = i; k <= j; k++)
                sum += x[k];
            if (sum > maxsofar)
                maxsofar = sum;
        }
    return maxsofar;
}

float alg2()
{   int i, j;
    float sum, maxsofar = 0;
    for (i = 0; i < n; i++) {
        sum = 0;
        for (j = i; j < n; j++) {
            sum += x[j];
            if (sum > maxsofar)
                maxsofar = sum;
        }
    }
    return maxsofar;
}

float cumvec[MAXN+1];

float alg2b()
{   int i, j;
    float *cumarr, sum, maxsofar = 0;
    cumarr = cumvec+1; /* to access cumarr[-1] */
    cumarr[-1] = 0;
    for (i = 0; i < n; i++)
        cumarr[i] = cumarr[i-1] + x[i];
    for (i = 0; i < n; i++) {
        for (j = i; j < n; j++) {
            sum = cumarr[j] - cumarr[i-1];
            if (sum > maxsofar)
                maxsofar = sum;
        }
    }
    return maxsofar;
}

/* MS VC++ has a max macro, and therefore a perf bug */

#ifdef max
#undef max
#endif


#define maxmac(a, b) ((a) > (b) ? (a) : (b) )

float maxfun(float a, float b)
{   return a > b ? a : b;
}

#define max(a, b) maxfun(a, b)

float recmax(int l, int u)
{   int i, m;
    float lmax, rmax, sum;
    if (l > u)  /* zero elements */
		return 0;
    if (l == u)  /* one element */
		return max(0, x[l]);
    m = (l+u) / 2;
	/* find max crossing to left */
    lmax = sum = 0;
    for (i = m; i >= l; i--) {
		sum += x[i];
		if (sum > lmax)
			lmax = sum;
    }
	/* find max crossing to right */
    rmax = sum = 0;
    for (i = m+1; i <= u; i++) {
		sum += x[i];
		if (sum > rmax)
			rmax = sum;
    }
    return max(lmax + rmax,
		max(recmax(l, m), recmax(m+1, u)));
}

float alg3()
{   return recmax(0, n-1);
}

float alg4()
{   int i;
    float maxsofar = 0, maxendinghere = 0;
    for (i = 0; i < n; i++) {
        maxendinghere += x[i];
        if (maxendinghere < 0)
            maxendinghere = 0;
        if (maxsofar < maxendinghere)
            maxsofar = maxendinghere;
    }
    return maxsofar;
}

float alg4b()
{   int i;
    float maxsofar = 0, maxendinghere = 0;
    for (i = 0; i < n; i++) {
        maxendinghere += x[i];
        maxendinghere = maxmac(maxendinghere, 0);
       	maxsofar = maxmac(maxsofar, maxendinghere);
    }
    return maxsofar;
}

float alg4c()
{   int i;
    float maxsofar = 0, maxendinghere = 0;
    for (i = 0; i < n; i++) {
        maxendinghere += x[i];
        maxendinghere = maxfun(maxendinghere, 0);
       	maxsofar = maxfun(maxsofar, maxendinghere);
    }
    return maxsofar;
}

int main()
{   int algnum, start, clicks;
    float thisans;

    while (scanf("%d %d", &algnum, &n) != EOF) {
        sprinkle();
        start = clock();
        thisans = -1;
        switch (algnum) {
			case 1:  thisans = alg1();  break;
			case 2:  thisans = alg2();  break;
			case 22: thisans = alg2b(); break;
			case 3:  thisans = alg3();  break;
			case 4:  thisans = alg4();  break;
			case 42: thisans = alg4b(); break;
			case 43: thisans = alg4c(); break;
			default: break;
		}
        clicks = clock()-start;
        printf("%d\t%d\t%f\t%d\t%f\n", algnum, n, thisans,
            clicks, clicks / (float) CLOCKS_PER_SEC);
        if  (alg4() != thisans)
            printf(" maxsum error: mismatch with alg4: %f\n", alg4());
    }
    return 0;
}
