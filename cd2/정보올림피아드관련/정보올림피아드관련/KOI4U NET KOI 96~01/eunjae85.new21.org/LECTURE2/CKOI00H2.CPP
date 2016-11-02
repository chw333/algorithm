#include <fstream.h>
#include <string.h>
#include <stdlib.h>

int c, n;
char a[200][70];
int l[200];
int on[200];
int size = 0;

char dna[20][700];
char dl[20] = {0, };
int dc[20] = {0, };
int ds[20][700] = {0, };

int check[200] = {0, };

void input ()
{
	ifstream in ("input.txt");

	in >> c >> n;

	for (int i = 0; i < n; i++) {
		in >> a[i];
		l[i] = strlen (a[i]);
		size += l[i];
		on[i] = i;
	}

	size /= c;

	in.close ();
}

void output ()
{
	ofstream out ("output.txt");

	for (int i = 0; i < c; i++) {
		for (int j = 0; j < dc[i]; j++)
			out << ds[i][j] << ' ';

		out << endl;
	}

	out.close ();

	exit (0);
}

int fmin (int a, int b)
{
	if (a > b) return b;
				else return a;
}

void recur (int d)
{
	if (d == n) output ();

	int min = 0, max = 0;
	for (int i = 1; i < c; i++) {
		if (dl[i] < dl[min]) min = i;
		if (dl[i] > dl[max]) max = i;
	}

	for (i = 0; i < n; i++)
		if (!check[i] && (l[i] + dl[min] <= size)) {
			int flag = 0;

			for (int j = dl[min]; j < fmin (l[i] + dl[min], dl[max]); j++)
				if (a[i][j - dl[min]] != dna[max][j]) {
					flag = 1;
					break;
				}

			if (!flag) {
				check[i] = 1;
				for (j = dl[min]; j < l[i] + dl[min]; j++)
					dna[min][j] = a[i][j - dl[min]];

				dl[min] += l[i];
				ds[min][dc[min]] = on[i] + 1;
				dc[min]++;

				recur (d + 1);

				check[i] = 0;
				dl[min] -= l[i];
				dc[min]--;
			}

// inverse -------------------------------------------------------

			flag = 0;

			for (j = dl[min]; j < fmin (l[i] + dl[min], dl[max]); j++)
				if (a[i][l[i] - (j - dl[min]) - 1] != dna[max][j]) {
					flag = 1;
					break;
				}

			if (!flag) {
				check[i] = 1;
				for (j = dl[min]; j < l[i] + dl[min]; j++)
					dna[min][j] = a[i][l[i] - (j - dl[min]) - 1];

				dl[min] += l[i];
				ds[min][dc[min]] = -(on[i] + 1);
				dc[min]++;

				recur (d + 1);

				check[i] = 0;
				dl[min] -= l[i];
				dc[min]--;
			}

		}
}

void process ()
{
	for (int i = 0; i < n; i++)
		for (int j = i + 1; j < n; j++)
			if (l[i] < l[j]) {
				for (int k = 0; k < 70; k++) {
					char t;
					t = a[i][k];
					a[i][k] = a[j][k];
					a[j][k] = t;
				}
				int z;
				z = l[i];
				l[i] = l[j];
				l[j] = z;

				z = on[i];
				on[i] = on[j];
				on[j] = z;
			}

	recur (0);
}

void main ()
{
	input ();
	process ();
}
