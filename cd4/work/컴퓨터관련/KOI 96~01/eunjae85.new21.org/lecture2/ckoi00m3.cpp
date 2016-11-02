#include <fstream.h>
#include <stdlib.h>

#define horizon 0
#define vertical 1

typedef struct {
	int i, j;
	int d;
	int len;
} car;

typedef struct {
	int count;
	int h1[5000], h2[5000];
} sol;

long *timer = (long *)(0x0040006c), stime;

int n, m;
car a[150], original[150];

int t[20][20];

sol now, best;

void input ()
{
	ifstream in ("input.txt");

	in >> n;

	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			in >> t[i][j];

	in.close ();
}

void turn ()
{
	int flag = 0;

	for (int i = 0; i < n-1; i++)
		for (int j = 0; j < n-1; j++)
			if ((t[i][j] == 1) && (t[i + 1][j] == 1))
				flag = 1;

	if (!flag) return;

	int temp[20][20];

	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
			temp[j][n-i-1] = t[i][j];

	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
			t[i][j] = temp[i][j];
}

void initialize ()
{
	int i, j, k;

	m = 0;

	for (i = 0; i < 150; i++)
		a[i].len = 0;

	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
			if ((t[i][j] != 0) && (a[t[i][j] - 1].len == 0)) {
				k = t[i][j];
				a[k - 1].i = i;
				a[k - 1].j = j;

				if (k > m) m = k;

				if ((i != n - 1) && (t[i + 1][j] == k)) {
					a[k - 1].d = vertical;
					if ((i != n - 2) && t[i + 2][j] == k) a[k - 1].len = 3;
																					 else a[k - 1].len = 2;
				} else {
					a[k - 1].d = horizon;
					if ((j != n - 2) && t[i][j + 2] == k) a[k - 1].len = 3;
																					 else a[k - 1].len = 2;
				}
			}
}

int min (int a, int b)
{
	if (a > b) return b;
				else return a;
}

int max (int a, int b)
{
	if (a > b) return a;
				else return b;
}

int cango (int k, int d)
{
	int i, j, l;

	if (a[k].d == vertical) {
		d = -d;
		if (d > 0) {
			i = a[k].i + a[k].len - 1;
			j = a[k].j;
		} else {
			i = a[k].i;
			j = a[k].j;
		}

		if ((i + d < 0) || (i + d >= n)) return 0;

		for (l = 0; l < m; l++) {
			if (k == l) continue;

			if (a[l].d == horizon) {
				if ((a[l].j <= j) && (a[l].j + a[l].len - 1 >= j) &&
						(a[l].i >= min(i, i + d)) && (a[l].i <= max (i, i + d)))
					return 0;
			} else {
				if ((a[l].j == j) &&
						(((a[l].i > i) && (a[l].i <= i + d)) ||
						 ((a[l].i + a[l].len - 1 >= i + d) && (a[l].i + a[l].len - 1 < i))))
					return 0;
			}
		}

	} else {
		if (d > 0) {
			i = a[k].i;
			j = a[k].j + a[k].len - 1;
		} else {
			i = a[k].i;
			j = a[k].j;
		}

		if (k == 0) {
			if ((j + d < 0) || (j > n)) return 0;
		} else {
			if ((j + d < 0) || (j + d >= n)) return 0;
		}

		for (l = 0; l < m; l++) {
			if (k == l) continue;

			if (a[l].d == vertical) {
				if ((a[l].i <= i) && (a[l].i + a[l].len - 1 >= i) &&
						(a[l].j >= min(j, j + d)) && (a[l].j <= max (j, j + d)))
					return 0;
			} else {
				if ((a[l].i == i) &&
						(((a[l].j > j) && (a[l].j <= j + d)) ||
						 ((a[l].j + a[l].len - 1 >= j + d) && (a[l].j + a[l].len - 1 < j))))
					return 0;
			}
		}
	}

	return 1;
}

void go (int k, int d)
{
	if ((now.count != 0) && (now.h1[now.count - 1] == k))
		now.h2[now.count - 1] += d;
	else {
		now.h1[now.count] = k;
		now.h2[now.count] = d;
		now.count++;
	}

	if (a[k].d == vertical) a[k].i -= d;
	if (a[k].d == horizon)  a[k].j += d;
}

void output ()
{
	ofstream out ("output.txt");

	if (best.count == 32767) {
		out << "fuck!" << endl;
	} else {
		out << best.count << endl;
		for (int i = 0; i < best.count; i++)
			out << best.h1[i] + 1 << ' ' << best.h2[i] << endl;
	}

	out.close ();

	exit (0);
}

void process ()
{
	stime = *timer;
	best.count = 32767;

	randomize ();
	turn ();

	long count = 0;

	initialize ();
	for (int i = 0; i < m; i++)
		original[i] = a[i];

	for (long limit = 1; ; limit++) {
		for (i = 0; i < m; i++)
			a[i] = original[i];

		now.count = 0;

		if (limit > 1000) limit = 1000;

		count++;
		for (i = 0; i < limit; i++) {
			if (*timer - stime > 320) {
				output ();
			}

			if (now.count >= best.count) break;

			if (cango (0, 1)) {
				go (0, 1);
			} else {
				int j, k;

				do {
					j = random (m);
					k = random (2 * n - 1) - n + 1;
				} while ((k == 0) || (!cango (j, k)));
				go (j, k);
			}

			if (a[0].j == n) {
				if (now.count < best.count) {
					best = now;
				}
				break;
			}
		}
	}
}

void main ()
{
	input ();
	process ();
}
