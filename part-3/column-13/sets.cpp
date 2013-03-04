/* Copyright (C) 1999 Lucent Technologies */
/* From 'Programming Pearls' by Jon Bentley */

/* sets.cpp -- exercise set implementations on random numbers */

#include <iostream>
#include <set>
using namespace std;


class IntSetSTL {
private:
	set<int> S;
public:
	IntSetSTL(int maxelements, int maxval) { }
	int size() { return S.size(); }
	void insert(int t) { S.insert(t);}
	void report(int *v)
	{	int j = 0;
		set<int>::iterator i;
		for (i = S.begin(); i != S.end(); ++i)
			v[j++] = *i;
	}
};


class IntSetBitVec {
private:
	enum { BITSPERWORD = 32, SHIFT = 5, MASK = 0x1F };
	int	n, hi, *x;
	void set(int i)  {        x[i>>SHIFT] |=  (1<<(i & MASK)); }
	void clr(int i)  {        x[i>>SHIFT] &= ~(1<<(i & MASK)); }
	int  test(int i) { return x[i>>SHIFT] &   (1<<(i & MASK)); }
public:
	IntSetBitVec(int maxelements, int maxval)
	{	hi = maxval;
		x = new int[1 + hi/BITSPERWORD];
		for (int i = 0; i < hi; i++)
			clr(i);
		n = 0;
	}
	int size() { return n; }
	void insert(int t)
	{	if (test(t))
			return;
		set(t);
		n++;
	}
	void report(int *v)
	{	int j=0;
		for (int i = 0; i < hi; i++)
			if (test(i))
				v[j++] = i;
	}
};


class IntSetArr {
private:
	int	n, *x;
public:
	IntSetArr(int maxelements, int maxval)
	{	x = new int[1 + maxelements];
		n=0;
		x[0] = maxval; /* sentinel at x[n] */
	}
	int size() { return n; }
	void insert(int t)
	{	int i, j;
		for (i = 0; x[i] < t; i++)
			;
		if (x[i] == t)
			return;
		for (j = n; j >= i; j--)
			x[j+1] = x[j];
		x[i] = t;
		n++;
	}
	void report(int *v)
	{	for (int i = 0; i < n; i++)
			v[i] = x[i];
	}
};


class IntSetList {
private:
	int	n;
	struct node {
		int val;
		node *next;
		node(int i, node *p) { val = i; next = p; }
	};
	node *head, *sentinel;
	node *rinsert(node *p, int t)
	{	if (p->val < t) {
			p->next = rinsert(p->next, t);
		} else if (p->val > t) {
			p = new node(t, p);
			n++;
		}
		return p;
	}
public:
	IntSetList(int maxelements, int maxval)
	{	sentinel = head = new node(maxval, 0);
		n = 0;
	}
	int size() { return n; }
	void insert(int t) { head = rinsert(head, t); }
	void insert2(int t)
	{	node *p;
		if (head->val == t)
			return;
		if (head->val > t) {
			head = new node(t, head);
			n++;
			return;
		}
		for (p = head; p->next->val < t; p = p->next)
			;
		if (p->next->val == t)
			return;
		p->next = new node(t, p->next);
		n++;
	}
	void insert3(int t)
	{	node **p;
		for (p = &head; (*p)->val < t; p = &((*p)->next))
			;
		if ((*p)->val == t)
			return;
		*p = new node(t, *p);
		n++;
	}
	void report(int *v)
	{	int j = 0;
		for (node *p = head; p != sentinel; p = p->next)
			v[j++] = p->val;
	}
};

// Change from new per node to one new at init
// Factor of 2.5 on VC 5.0, 6% on SGI CC
class IntSetList2 {
private:
	int	n;
	struct node {
		int val;
		node *next;
	};
	node *head, *sentinel, *freenode;
public:
	IntSetList2(int maxelements, int maxval)
	{	sentinel = head = new node;
		sentinel->val = maxval;
		freenode = new node[maxelements];
		n = 0;
	}
	int size() { return n; }
	void insert(int t)
	{	node **p;
		for (p = &head; (*p)->val < t; p = &((*p)->next))
			;
		if ((*p)->val == t)
			return;
		freenode->val = t;
		freenode->next = *p;
		*p = freenode++;
		n++;
	}
	void report(int *v)
	{	int j = 0;
		for (node *p = head; p != sentinel; p = p->next)
			v[j++] = p->val;
	}
};


class IntSetBST {
private:
	int	n, *v, vn;
	struct node {
		int val;
		node *left, *right;
		node(int v) { val = v; left = right = 0; }
	};
	node *root;
	node *rinsert(node *p, int t)
	{	if (p == 0) {
			p = new node(t);
			n++;
		} else if (t < p->val) {
			p->left = rinsert(p->left, t);
		} else if (t > p->val) {
			p->right = rinsert(p->right, t);
		} // do nothing if p->val == t
		return p;
	}
	void traverse(node *p)
	{	if (p == 0)
			return;
		traverse(p->left);
		v[vn++] = p->val;
		traverse(p->right);
	}
public:
	IntSetBST(int maxelements, int maxval) { root = 0; n = 0; }
	int size() { return n; }
	void insert(int t) { root = rinsert(root, t); }
	void report(int *x) { v = x; vn = 0; traverse(root); }
};


class IntSetBST2 {
private:
	int	n, *v, vn;
	struct node {
		int val;
		node *left, *right;
	};
	node *root, *freenode, *sentinel;
	node *rinsert(node *p, int t)
	{	if (p == sentinel) {
			p = freenode++;
			p->val = t;
			p->left = p->right = sentinel;
			n++;
		} else if (t < p->val) {
			p->left = rinsert(p->left, t);
		} else if (t > p->val) {
			p->right = rinsert(p->right, t);
		} // do nothing if p->val == t
		return p;
	}
	void traverse(node *p)
	{	if (p == sentinel)
			return;
		traverse(p->left);
		v[vn++] = p->val;
		traverse(p->right);
	}
public:
	IntSetBST2(int maxelements, int maxval)
	{	root = sentinel = new node;  // 0 if using insert1
		n = 0;
		freenode = new node[maxelements];
	}
	int size() { return n; }
	void insert1(int t) { root = rinsert(root, t); }
	void insert(int t)
	{	sentinel->val = t;
		node **p = &root;
		while ((*p)->val != t)
			if (t < (*p)->val)
				p = &((*p)->left);
			else
				p = &((*p)->right);
		if (*p == sentinel) {
			*p = freenode++;
			(*p)->val = t;
			(*p)->left = (*p)->right = sentinel;
			n++;
		}
	}
	void report(int *x) { v = x; vn = 0; traverse(root); }
};


class IntSetBins {
private:
	int	n, bins, maxval;
	struct node {
		int val;
		node *next;
		node(int v, node *p) { val = v; next = p; }
	};
	node **bin, *sentinel;
	node *rinsert(node *p, int t)
	{	if (p->val < t) {
			p->next = rinsert(p->next, t);
		} else if (p->val > t) {
			p = new node(t, p);
			n++;
		}
		return p;
	}
public:
	IntSetBins(int maxelements, int pmaxval)
	{	bins = maxelements;
		maxval = pmaxval;
		bin = new node*[bins];
		sentinel = new node(maxval, 0);
		for (int i = 0; i < bins; i++)
			bin[i] = sentinel;
		n = 0;
	}
	int size() { return n; }
	void insert(int t)
	{	int i = t / (1 + maxval/bins);  // CHECK !
		bin[i] = rinsert(bin[i], t);
	}
	void report(int *v)
	{	int j = 0;
		for (int i = 0; i < bins; i++)
			for (node *p = bin[i]; p != sentinel; p = p->next)
				v[j++] = p->val;
	}
};


class IntSetBins2 {
private:
	int	n, bins, maxval;
	struct node {
		int val;
		node *next;
	};
	node **bin, *sentinel, *freenode;
	node *rinsert(node *p, int t)
	{	if (p->val < t) {
			p->next = rinsert(p->next, t);
		} else if (p->val > t) {
			freenode->val = t;
			freenode->next = p;
			p = freenode++;
			n++;
		}
		return p;
	}
public:
	IntSetBins2(int maxelements, int pmaxval)
	{	bins = maxelements;
		maxval = pmaxval;
		freenode = new node[maxelements];
		bin = new node*[bins];
		sentinel = new node;
		sentinel->val = maxval;
		for (int i = 0; i < bins; i++)
			bin[i] = sentinel;
		n = 0;
	}
	int size() { return n; }
	void insert1(int t)
	{	int i = t / (1 + maxval/bins);
		bin[i] = rinsert(bin[i], t);
	}
	void insert(int t)
	{	node **p;
		int i = t / (1 + maxval/bins);
		for (p = &bin[i]; (*p)->val < t; p = &((*p)->next))
			;
		if ((*p)->val == t)
			return;
		freenode->val = t;
		freenode->next = *p;
		*p = freenode++;
		n++;
	}
	void report(int *v)
	{	int j = 0;
		for (int i = 0; i < bins; i++)
			for (node *p = bin[i]; p != sentinel; p = p->next)
				v[j++] = p->val;
	}
};


// Drivers for the set data structures

int bigrand()
{	return RAND_MAX*rand() + rand();
}

int randint(int l, int u)
{	return l + bigrand() % (u-l+1);
}

void gensets(int m, int maxval)
{	int *v = new int[m];
	IntSetList S(m, maxval);
	while (S.size() < m)
		S.insert(bigrand() % maxval);
	S.report(v);
//	for (int i = 0; i < m; i++)
	for (int i = 0; i < 2; i++)
		cout << v[i] << "\n";
}

void genfloyd(int m, int maxval)
{	int *v = new int[m];
	IntSetSTL S(m, maxval);
	for (int j = maxval-m; j < maxval; j++) {
		int t = bigrand() % (j+1);
		int oldsize = S.size();
		S.insert(t);
		if (S.size() == oldsize) // t already in S
			S.insert(j);
	}
	S.report(v);
	for (int i = 0; i < m; i++)
		cout << v[i] << "\n";
}

void memaccesstest(int m, int n)
{	IntSetList S(m, n);	// change among Arr, List and List2
	for (int i = 0; i < m; i++)
		S.insert(i);
}

void overheadonly(int m, int n)
{	int i, *v = new int[m];
	for (i = 0; i < m; i++)
		v[i] = bigrand() % n;
	for (i = 0; i < m; i++)
		cout << v[i] << "\n";
}

int main(int argc, char *argv[])
{	int m = atoi(argv[1]);
	int maxval = atoi(argv[2]);
	gensets(m, maxval);
	// overheadonly(m, n);
	// memaccesstest(m, n);
	return 0;
}
