/* Copyright (C) 1999 Lucent Technologies */
/* From 'Programming Pearls' by Jon Bentley */

/* priqueue.cpp -- priority queues (using heaps) */

#include <iostream>
using namespace std;

// define and implement priority queues

template<class T>
class priqueue {
private:
	int	n, maxsize;
	T	*x;
	void swap(int i, int j)
	{	T t = x[i]; x[i] = x[j]; x[j] = t; }
public:
	priqueue(int m)
	{	maxsize = m;
		x = new T[maxsize+1];
		n = 0;
	}
	void insert(T t)
	{	int i, p;
		x[++n] = t;
		for (i = n; i > 1 && x[p=i/2] > x[i]; i = p)
			swap(p, i);
	}
	T extractmin()
	{	int i, c;
		T t = x[1];
		x[1] = x[n--];
		for (i = 1; (c=2*i) <= n; i = c) {
			if (c+1<=n && x[c+1]<x[c])
				c++;
			if (x[i] <= x[c])
				break;
			swap(c, i);
		}
		return t;
	}
};

// sort with priority queues (heap sort is strictly better)

template<class T>
void pqsort(T v[], int n)
{	priqueue<T> pq(n);
	int i;
	for (i = 0; i < n; i++)
		pq.insert(v[i]);
	for (i = 0; i < n; i++)
		v[i] = pq.extractmin();
}

// main

int main()
{	const int	n = 10;
	int	i, v[n];
	if (0) { // Generate and sort
		for (i = 0; i < n; i++)
			v[i] = n-i;
		pqsort(v, n);
		for (i = 0; i < n; i++)
			cout << v[i] << "\n";
	} else { // Insert integers; extract with 0
		priqueue<int> pq(100);
		while (cin >> i)
			if (i == 0)
				cout << pq.extractmin() << "\n";
			else
				pq.insert(i);
	}
	return 0;
}
