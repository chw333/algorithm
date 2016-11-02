#include <fstream.h>
#include <stdlib.h>

int n;
int hh[20][20], vh[20][20];

int a[21][21];

void input ()
{
	ifstream in ("input.txt");

	int i, j;
	in >> n;

	for (i = 0; i < n; i++) {
		in >> hh[n - i - 1][0];

		for (j = 1; j <= hh[n - i - 1][0]; j++)
			in >> hh[n - i - 1][j];
	}

	for (i = 0; i < n; i++) {
		in >> vh[i][0];

		for (j = vh[i][0]; j >= 1; j--)
			in >> vh[i][j];
	}

	in.close ();
}

int hcheck (int i, int j)
{
	int k, t = 1, len = 0;

	a[i][j + 1] = 0;

	for (k = 0; k <= j + 1; k++) {
		if (a[i][k]) len++;

		if ((!a[i][k]) && (len != 0)) {
			if (len > hh[i][t]) return 0;
			if (len < hh[i][t])
				if ((k != j + 1) || (j == i)) return 0;

			t++;
			len = 0;
		}
	}

	if ((i == j) && (t - 1 != hh[i][0])) return 0;

	return 1;
}

int vcheck (int i, int j)
{
	int k, t = 1, len = 0;

	a[i + 1][j] = 0;

	for (k = j; k <= i + 1; k++) {
		if (a[k][j]) len++;

		if ((!a[k][j]) && (len != 0)) {
			if (len > vh[j][t]) return 0;
			if (len < vh[j][t])
				if ((k != i + 1) || (i == n - 1)) return 0;

			t++;
			len = 0;
		}
	}

	if ((i == n - 1) && (t - 1 != vh[j][0])) return 0;

	return 1;
}


void recur (int i, int j)
{
	if (i == n) {
		ofstream out ("output.txt");

		for (i = n - 1; i >= 0; i--) {
			for (j = 0; j <= i; j++)
				out << a[i][j] << ' ';
			out << endl;
		}

		out.close ();

		exit (0);
	}

	a[i][j] = 0;
	if (hcheck (i, j) && vcheck (i, j)) {
		if (i == j) recur (i + 1, 0);
					 else recur (i, j + 1);
	}

	a[i][j] = 1;
	if (hcheck (i, j) && vcheck (i, j)) {
		if (i == j) recur (i + 1, 0);
					 else recur (i, j + 1);
	}
}

void process ()
{
	recur (0, 0);

	ofstream out ("output.txt");

	out << "No Answer" << endl;

	out.close ();
}

void main ()
{
	input ();
	process ();
}
