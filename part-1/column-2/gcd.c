
int euclid_gcd (int a, int b)
{
    int t;

    if (!a) return (b);
    if (!b) return (a);

    if (a > b) {
	t = b;
	b = a;
	a = t;
    }

    while (b != 0) {
	t = b;
	b = a % b;
	a = t;
    }

    return (a);
}

