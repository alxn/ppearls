
#include <iostream>     // std::cout
#include <algorithm>    // std::rotate
#include <vector>       // std::vector

using namespace std;

int main (int argc, const char *argv[])
{
    std::vector<char> buf;

    if (argc < 2) {
	fprintf(stderr, "Usage: %s <rotate> <string>\n", argv[0]);
	exit(1);
    }

    std::rotate(myvector.begin(),myvector.begin()+3,myvector.end());

    r = atoi(argv[1]);
    // note works for negative as well.

    n = strlen(argv[2]);

    if ((r > n) || (r < -n)) {
	fprintf(stderr, "Usage: %s [<%d>] < <%d>\n",
		argv[0], r, n);
	exit(1);
    }

    buf = strdup(argv[2]);

    rotate();

    printf("input : %s\n", argv[2]);
    printf("output: %*s%s\n",
	   r, "",
	   buf);

    free(buf);

int main () {

  // set some values:
  for (int i=1; i<10; ++i) myvector.push_back(i); // 1 2 3 4 5 6 7 8 9

  // print out content:
  std::cout << "myvector contains:";
  for (std::vector<int>::iterator it=myvector.begin(); it!=myvector.end(); ++it)
    std::cout << ' ' << *it;
  std::cout << '\n';

  return 0;
}
    return 0;
}
