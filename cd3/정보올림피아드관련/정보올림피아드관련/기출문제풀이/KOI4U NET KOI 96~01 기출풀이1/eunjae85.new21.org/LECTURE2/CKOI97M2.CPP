#include <fstream.h>

int m, n;

int a[21][301];
int t[21][301] = {0, };
int b[21][301];

void input ()
{
	ifstream in ("input.txt");

	in >> m >> n;

	int z;
	for (int i = 1; i <= m; i++) {
		in >> z;

		for (int j = 1; j <= n; j++)
			in >> a[j][z];
	}

	in.close ();
}

void process ()
{
	int i, j, k;

	for (i = 1; i <= n; i++)
		for (j = 0; j <= m; j++) {
			for (k = 0; k <= j; k++)
				if (t[i - 1][j - k] + a[i][k] > t[i][j]) {
					t[i][j] = t[i - 1][j - k] + a[i][k];
					b[i][j] = k;
				}
		}
}

void output ()
{
	int g[21];
	int i, j, k;

	j = m;
	for (i = n; i >= 1; i--) {
		g[i] = b[i][j];
		j -= g[i];
	}

	ofstream out ("output.txt");

	for (i = 1; i <= n; i++)
		out << g[i] << ' ';
	out << endl;

	out << t[n][m] << endl;

	out.close ();
}

void main ()
{
	input ();
	process ();
	output ();
}
