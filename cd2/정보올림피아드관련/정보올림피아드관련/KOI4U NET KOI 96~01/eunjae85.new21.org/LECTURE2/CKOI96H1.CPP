#include <fstream.h>
#include <string.h>

const int next[8][2][3] = {{{1, 5, 0}, {1, 1, 0}},  // start
						   {{1, 2, 0}, {1, 7, 0}},  // 1
						   {{1, 3, 0}, {1, 7, 0}},  // 2
						   {{1, 3, 0}, {1, 4, 0}},  // 3
						   {{1, 5, 0}, {2, 1, 4}},  // 4
						   {{1, 7, 0}, {1, 6, 0}},  // 5
						   {{1, 5, 0}, {1, 1, 0}},  // 6
						   {{1, 7, 0}, {1, 7, 0}}}; // error

int check (char str[])
{
  int oldstatus[8], newstatus[8];
  int i, j;

  for (i = 0; i < 8; i++) {
	oldstatus[i] = 0;
	newstatus[i] = 0;
  }
  oldstatus[0] = 1;

  for (i = 0; i < strlen (str); i++) {
	for (j = 0; j < 8; j++)
	  if (oldstatus[j] == 1)
		for (int k = 1; k <= next[j][str[i] - '0'][0]; k++)
		  newstatus [next[j][str[i] - '0'][k]] = 1;

	for (j = 0; j < 8; j++) {
	  oldstatus[j] = newstatus[j];
	  newstatus[j] = 0;
	}
  }

  if ((oldstatus[4] == 1) || (oldstatus[6] == 1)) return 1;
												  return 0;
}

void main ()
{
  int n;
  char str[255];

  ifstream in ("m6.in");
  ofstream out ("m6.out");
	in >> str;
	if (check (str)) out << "SUBMARINE" << endl;
				else out << "NOISE" << endl;
  in.close ();
  out.close ();
}
