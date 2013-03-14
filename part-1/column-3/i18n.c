#include <stdio.h>
#include <stdlib.h>

int
main (int argc, const char *argv[])
{
#if 0
    if (argc < 3) {
	fprintf(stderr, "Usage: %s <code> <name>\n", argv[0]);
	exit(1);
    }
#endif

    printf("%2$d %1$d\n", 1, 2);
    printf("%2$*1$d\n", 3, 4);

    return (0);
}
