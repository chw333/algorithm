#include <fstream.h>
#include <stdlib.h>

int n;
int e[100][100];
int w[100] = {0, };

int h1[2000], h2[2000];
int hc = 0;

long distance;

void input ()
{
	ifstream in ("input.txt");

	in >> n;

	for (int i = 1; i < n; i++)
		in >> w[i];

	for (i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			e[i][j] = 10000;

	for (i = 0; i < n - 1; i++) {
		int u, v, w;

		in >> u >> v >> w;
		e[u-1][v-1] = w;
		e[v-1][u-1] = w;
	}

	in.close ();
}

void floyd ()
{
	int i, j, k;

	for (k = 0; k < n; k++)
		for (i = 0; i < n; i++)
			for (j = 0; j < n; j++)
				if (e[i][k] + e[k][j] < e[i][j])
					e[i][j] = e[i][k] + e[k][j];
}

void output ()
{
	ofstream out ("output.txt");

	out << distance << endl;

	for (int i = 0; i < n; i++)
		if (h1[i] == 0) out << 1 << endl;
							 else out << h1[i] + 1 << " " << h2[i] << endl;

	out.close ();

	exit (0);
}

void process ()
{
	floyd ();

	distance = 0;

	while (1) {
		int i, j, k;

		j = 0;
		k = 10;

		for (i = 1; i < n; i++)
			if ((w[i] > 0) && ((j == 0) || (e[0][i] > e[0][j])))
				j = i;

		if (j == 0) output ();

		while (k > 0) {
			distance += e[0][j];

			if (k >= w[j]) {
				h1[hc] = j;
				h2[hc] = w[j];
				hc++;

				k -= w[j];
				w[j] = 0;
			} else {
				h1[hc] = j;
				h2[hc] = k;
				hc++;

				w[j] -= k;
				k = 0;
			}

			if (k != 0) {
				int t = 0;

				for (i = 1; i < n; i++)
					if ((w[i] > 0) && ((t == 0) || (e[j][i] < e[j][t])))
						t = i;

				if (t == 0) {
					k = 0;
				} else {
					distance += e[j][t];
					j = t;
				}
			}
		}

		h1[hc] = 0;
		hc++;
	}
}

void main ()
{
	input ();
	process ();
}
