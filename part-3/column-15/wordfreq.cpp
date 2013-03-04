/* Copyright (C) 1999 Lucent Technologies */
/* From 'Programming Pearls' by Jon Bentley */

/* wordfreq.cpp -- List all words in input file, with counts */

#include <iostream>
#include <map>
#include <string>
using namespace std;

int main()
{	map<string, int> M;
 	map<string, int>::iterator j;
	string t;
	while (cin >> t)
		M[t]++;
	for (j = M.begin(); j != M.end(); ++j)
		cout << j->first << " " << j->second << "\n";
	return 0;
}
