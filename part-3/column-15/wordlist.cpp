/* Copyright (C) 1999 Lucent Technologies */
/* From 'Programming Pearls' by Jon Bentley */

/* wordlist.cpp -- Sorted list of words (between white space) in file */

#include <iostream>
#include <set>
#include <string>
using namespace std;

int main()
{	set<string> S;
	string t;
 	set<string>::iterator j;
	while (cin >> t)
		S.insert(t);
	for (j = S.begin(); j != S.end(); ++j)
		cout << *j << "\n";
	return 0;
}
