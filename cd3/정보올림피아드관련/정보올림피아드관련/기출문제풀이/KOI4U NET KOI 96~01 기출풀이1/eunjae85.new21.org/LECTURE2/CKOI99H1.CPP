#include <fstream.h>

int n;
int a[100];

int t1[100][100] = {0, };
int t2[100][100] = {0, };
int t3[100][100];

ofstream out ("output.txt");

void input ()
{
	ifstream in ("input.txt");

	in >> n;

	char str[200];
	in >> str;
	for (int i = 0; i < n; i++)
		if (str[i] == '1') a[i] = 1;
									else a[i] = 0;

	in.close ();
}

int max (int a, int b)
{
	if (a > b) return a;
				else return b;
}

void process ()
{
	int i, j, k, g;

	for (i = 0; i < n; i++)
		t1[i][i] = 9999;

	for (g = 1; g < n; g++)
		for (i = 0; i < n - g; i++) {
			j = i + g;
			t1[i][j] = 9999;

			for (k = i + 1; k <= j; k++)
				if (a[i] != a[k])
					if (t1[i+1][k-1] + t1[k+1][j] + (k-i) + 2 * (t2[i+1][k-1] + 1) < t1[i][j]) {
						t1[i][j] = t1[i+1][k-1] + t1[k+1][j] + (k-i) + 2 * (t2[i+1][k-1] + 1);
						t2[i][j] = max (t2[i + 1][k - 1] + 1, t2[k + 1][j]);
						t3[i][j] = k;
					}
		}
}

void recur (int i, int j)
{
	if (i >= j) return;

	out << i + 1 << ' ' << t3[i][j] + 1 << endl;
	recur (i + 1, t3[i][j] - 1);
	recur (t3[i][j] + 1, j);
}

void output ()
{
	out << t1[0][n - 1] << endl;

	recur (0, n - 1);

	out.close ();
}

void main()
{
	input ();
	process ();
	output ();
}
