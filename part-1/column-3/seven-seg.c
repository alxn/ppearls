#include <stdio.h>
#include <inttypes.h>


#define BIT(a) 1<<(a)

// perhaps clearing the inverse would have been easier..
static int ssd_tbl[] = {
    [0x0] = BIT(0)|BIT(2)|BIT(3)|BIT(4)|BIT(5)|BIT(6)|BIT(7)|BIT(8),
    [0x1] = BIT(4)|BIT(6),
    [0x2] = BIT(0)|BIT(1)|BIT(2)|BIT(4)|BIT(5)|BIT(7)|BIT(8),
    [0x3] = BIT(0)|BIT(1)|BIT(2)|BIT(4)|BIT(6)|BIT(7)|BIT(8),
    [0x4] = BIT(1)|BIT(3)|BIT(4)|BIT(6)|BIT(7)|BIT(8),
    [0x5] = BIT(0)|BIT(1)|BIT(2)|BIT(3)|BIT(6)|BIT(7)|BIT(8),
    [0x6] = BIT(0)|BIT(1)|BIT(2)|BIT(3)|BIT(5)|BIT(6)|BIT(7)|BIT(8),
    [0x7] = BIT(2)|BIT(4)|BIT(6)|BIT(7)|BIT(8),
    [0x8] = BIT(0)|BIT(1)|BIT(2)|BIT(3)|BIT(4)|BIT(5)|BIT(6)|BIT(7)|BIT(8),
    [0x9] = BIT(0)|BIT(1)|BIT(2)|BIT(3)|BIT(4)|BIT(6)|BIT(7)|BIT(8),
    [0xa] = BIT(1)|BIT(2)|BIT(3)|BIT(4)|BIT(5)|BIT(6)|BIT(7)|BIT(8),
    [0xb] = BIT(0)|BIT(1)|BIT(3)|BIT(5)|BIT(6)|BIT(7)|BIT(8),
    [0xc] = BIT(0)|BIT(2)|BIT(3)|BIT(5)|BIT(7)|BIT(8),
    [0xd] = BIT(0)|BIT(1)|BIT(4)|BIT(5)|BIT(6)|BIT(7)|BIT(8),
    [0xe] = BIT(0)|BIT(1)|BIT(2)|BIT(3)|BIT(5)|BIT(7)|BIT(8),
    [0xf] = BIT(1)|BIT(2)|BIT(3)|BIT(5)|BIT(7)|BIT(8),
};

static void
ssd_base (int base, uint16_t input, uint8_t output[])
{
    int i;

    for (i=0; i<5; i++) {
	output[4-i] = ssd_tbl[input%base];
	input /= base;
    }
}

static void
ssd_display (uint8_t output[])
{
    int i;

    for (i=0; i<5;i++) {
	printf(" %c  ", output[i] & BIT(2) ? '_' : ' ');
    }
    printf("\n");

    for (i=0; i<5;i++) {
	printf("%c%c%c ",
	       output[i] & BIT(3) ? '|' : ' ',
	       output[i] & BIT(1) ? '_' : ' ',
	       output[i] & BIT(4) ? '|' : ' ');
    }
    printf("\n");
    for (i=0; i<5;i++) {
	printf("%c%c%c ",
	       output[i] & BIT(5) ? '|' : ' ',
	       output[i] & BIT(0) ? '_' : ' ',
	       output[i] & BIT(6) ? '|' : ' ');
    }
    printf("\n");
}

int main (void)
{
    uint8_t output[5];
    
    ssd_base(10, 12345, output);
    ssd_display(output);

    ssd_base(10, 6789, output);
    ssd_display(output);

    ssd_base(16, 0x0123, output);
    ssd_display(output);

    ssd_base(16, 0x4567, output);
    ssd_display(output);

    ssd_base(16, 0x89ab, output);
    ssd_display(output);

    ssd_base(16, 0xcdef, output);
    ssd_display(output);

    return (0);
}
