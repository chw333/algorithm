#include <fstream.h>

int width;
int n;
int w[22];
int l, r;

int t[22][21][21] = {0, };

void input ()
{
	ifstream in ("input.txt");

	in >> width;

	in >> l >> r;
	if (l > r) {
		int t;
		t = l;
		l = r;
		r = t;
	}

	in >> n;

	for (int i = 1; i <= n; i++)
		in >> w[i];

	in.close ();
}

int min (int a, int b)
{
	if (a > b) return b;
						 return a;
}

void process ()
{
	for (int i = n; i >= 1; i--)
		for (int j = 1; j <= width - 1; j++)
			for (int k = j + 1; k <= width; k++) {
				t[i][j][k] = 32767;

				if (w[i] <= j) t[i][j][k] = t[i+1][w[i]][k] + (j - w[i]);
				if (w[i] >= k) t[i][j][k] = t[i+1][j][w[i]] + (w[i] - k);
				if ((w[i] > j) && (w[i] < k))
					t[i][j][k] = min (t[i+1][w[i]][k] + (w[i] - j),
														t[i+1][j][w[i]] + (k - w[i]));
			}
}

void output ()
{
	ofstream out ("output.txt");

	out << t[1][l][r] << endl;

	out.close ();
}

void main ()
{
	input ();
	process ();
	output ();
}
