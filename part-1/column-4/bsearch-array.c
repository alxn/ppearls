#include <stdio.h>
#include <stdlib.h>


int
bsearch_mine (const int array[], int len, int target)
{
    int start, end, probe;
    int pos = -1;

    start = 0;
    end = len;
    while (start < end) {
	probe = (start + end) / 2;

	if (target == array[probe]) {
	    pos = probe;
	    break;
	} else if (target < array[probe]) {
	    end = probe;
	} else  {
	    start = probe + 1;
	}
    }

    return (pos);
}

int
main (int argc, const char *argv[])
{
    int array[argc];
    int i, t, p;

    if (argc<3) {
	fprintf(stderr, "Usage: %s <number> <list-of-ints>\n", argv[0]);
	exit(1);
    }

    t = atoi(argv[1]);

    for (i=0; i<argc-2; i++) {
	array[i] = atoi(argv[i+2]);
    }

    printf("Target = %d\n", t);

    p = bsearch_mine(array, argc-2, t);

    for (i=0; i<argc-2; i++) {
	printf("%c  [%d] = %d\n",
	       (p == i) ? '>' : ' ',
	       i, array[i]);
    }
    if (p<0) {
	printf("Not found!\n");
    }

    return (0);
}
