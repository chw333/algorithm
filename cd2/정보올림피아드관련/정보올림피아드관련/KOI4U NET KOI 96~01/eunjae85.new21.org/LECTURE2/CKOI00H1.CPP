#include <fstream.h>

int n, c;
int a[30];

char table[30][30][31] = {0, };
char trace[30][30][31] = {0, };

ofstream out ("output.txt");

void input ()
{
	ifstream in ("input.txt");

	in >> n;
	in >> c;

	for (int i = 0; i < n; i++)
		in >> a[i];

	in.close ();
}

void process ()
{
	int i, j, k, t, m, x;

	for (i = 0; i < n; i++)
		table[i][i][a[i]] = 1;

	for (t = 1; t < n; t++)
		for (i = 0; i < n - t; i++) {
			j = i + t;
			for (k = 0; k <= 30; k++)

				for (m = i; m < j; m++)
					for (x = 0; x <= 30; x++) {
						if ((x + k <= 30) && table[i][m][x] && table[m+1][j][x+k]) {
							table[i][j][k] = 1;
							trace[i][j][k] = m;
						}
						if ((x - k >= 0 ) && table[i][m][x] && table[m+1][j][x-k]) {
							table[i][j][k] = 1;
							trace[i][j][k] = m;
						}
					}
		}
}

void recur (int i, int j, int k, int base)
{
	if (i == j) return;

	int m = trace[i][j][k];

	for (int x = 0; x <= 30; x++) {
		if ((x + k <= 30) && table[i][m][x] && table[m+1][j][x+k]) {
			recur (i, m, x, base);
			recur (m + 1, j, x + k, base + 1);
			break;
		}
		if ((x - k >= 0 ) && table[i][m][x] && table[m+1][j][x-k]) {
			recur (i, m, x, base);
			recur (m + 1, j, x - k, base + 1);
			break;
		}
	}

	out << base << endl;
}

void output ()
{
	recur (0, n - 1, c, 1);

	out.close ();
}

void main ()
{
	input ();
	process ();
	output ();
}
