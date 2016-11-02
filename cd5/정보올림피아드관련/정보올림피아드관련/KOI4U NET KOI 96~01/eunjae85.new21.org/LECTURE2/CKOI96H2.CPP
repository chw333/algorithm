#include <fstream.h>

int n;
char l[101][101] = {0, };

void input ()
{
	ifstream in ("input.txt");

	in >> n;

	int a, b;

	for (int i = 0; i < n; i++) {
		in >> a >> b;
		if (a < b) l[a][b] = 1;
					else l[b][a] = 1;
	}

	in.close ();
}

void process ()
{
	int table[101][101] = {0, };

	int i, j, k, t;

	for (t = 1; t <= 99; t++)
		for (i = 1; i <= 100 - t; i++) {
			j = i + t;
			for (k = i; k <= j; k++)
				if (table[i][k-1] + table[k+1][j-1] + l[k][j] > table[i][j])
					table[i][j] = table[i][k-1] + table[k+1][j-1] + l[k][j];
		}

	ofstream out ("output.txt");

	out << table[1][100];

	out.close ();
}

void main ()
{
	input ();

	process ();
}
