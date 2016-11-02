#include <fstream.h>
#include <stdlib.h>
#include <string.h>

int n;
int e[100][100] = {0, };

int c[100] = {0, };
int check[100];

void input ()
{
	ifstream in ("input.txt");

	(in >> n).get();

	for (int i = 0; i < n; i++) {
		char str[1024];

		in.getline (str, 1024);

		int t1, t2;
		t1 = atoi (str);

		for (int j = 0; j < strlen (str); j++)
			if (str[j] == ' ') {
				t2 = atoi (str + j + 1);
				if (t2 == 0) break;

				e[t1 - 1][t2 - 1] = 1;
			}
	}

	in.close ();
}

void recur (int a, int i)
{
	check[i] = 1;

	for (int j = 0; j < n; j++)
		if ((e[i][j]) && (!check[j]))
			recur (a, j);

	c[a]++;
}

void process ()
{
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++)
			check[j] = 0;

		recur (i, i);
	}

	int count = 0;
	for (i = 0; i < n; i++)
		check[i] = 0;

	check[0] = 1;

	int h1[300], h2[300];
	int hc = 0;

	for (;;) {
		for (i = 0; i < n; i++)
			if (check[i] == 1) {
				int j = -1;
				for (int t = 0; t < n; t++)
					if (e[i][t] && !check[t] && ((j == -1) || (c[t] > c[j])))
						j = t;

				if (j == -1) continue;

				h1[hc] = i;
				h2[hc] = j;
				hc++;
				check[j] = 2;
			}

		count++;

		for (i = 0; i < n; i++)
			if (check[i] == 2) check[i] = 1;

		h1[hc] = -1;
		h2[hc] = 0;
		hc++;

		int j = 0;
		for (i = 0; i < n; i++)
			if (!check[i]) j = 1;
		if (j == 0) break;
	}

	ofstream out ("output.txt");

	out << count << endl;

	for (i = 0; i < hc; i++)
		if (h1[i] == -1) out << endl;
								else out << h1[i] + 1 << ' ' << h2[i] + 1 << ' ';

	out.close ();
}

void main ()
{
	input ();
	process ();
}
