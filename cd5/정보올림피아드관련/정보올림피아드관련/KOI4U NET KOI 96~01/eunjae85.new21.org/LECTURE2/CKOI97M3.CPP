#include <fstream.h>
#include <stdlib.h>

typedef struct {
	int x, y;
} point;

point p[3000];
int c;

void input ()
{
	ifstream in ("input.txt");

	int t, x, y;
	in >> t;

	in >> x >> y;
	p[0].x = x;
	p[0].y = y;
	c = 0;

	for (int i = 1; i < t; i++) {
		in >> x >> y;

		while ((p[c].x != x) || (p[c].y != y)) {

			p[c + 1].x = p[c].x;
			p[c + 1].y = p[c].y;

			if (p[c].x < x) p[c + 1].x = p[c].x + 1;
			if (p[c].x > x) p[c + 1].x = p[c].x - 1;
			if (p[c].y < y) p[c + 1].y = p[c].y + 1;
			if (p[c].y > y) p[c + 1].y = p[c].y - 1;
			c++;
		}
	}

	x = p[0].x;
	y = p[0].y;

	while ((p[c].x != x) || (p[c].y != y)) {

		p[c + 1].x = p[c].x;
		p[c + 1].y = p[c].y;

		if (p[c].x < x) p[c + 1].x = p[c].x + 1;
		if (p[c].x > x) p[c + 1].x = p[c].x - 1;
		if (p[c].y < y) p[c + 1].y = p[c].y + 1;
		if (p[c].y > y) p[c + 1].y = p[c].y - 1;
		c++;
	}

	in.close ();
}

int area (point a[], int n)
{
	long sum = 0;

	for (int i = 0; i < n - 1; i++)
		sum += a[i].x * a[i + 1].y;
	sum += a[n - 1].x * a[0].y;

	for (i = 1; i < n; i++)
		sum -= a[i].x * a[i - 1].y;
	sum -= a[0].x * a[n - 1].y;

	return sum / 2;
}

void process ()
{
	double o, len;
	o = area (p, c);

	point t[3000];
	int q;

	double max = 0;
	int size;
	int sx1, sy1, sx2, sy2;

	int i, j, k;
	for (i = 0; i < c; i++)
		for (j = i + 1; j < c; j++)
			if ((p[i].x == p[j].x) || (p[i].y == p[j].y)) {
				q = 0;

				for (k = 0; k < c; k++)
					if ((k <= i) || (k >= j)) {
						t[q].x = p[k].x;
						t[q].y = p[k].y;
						q++;
					}

				len = abs (p[i].x - p[j].x) + abs (p[i].y - p[j].y);
				if ((area (t, q) - o) / len > max) {
					max = (area (t, q) - o) / len;
					size = area (t, q) - o;
					sx1 = p[i].x;
					sy1 = p[i].y;
					sx2 = p[j].x;
					sy2 = p[j].y;
				}
			}

	for (i = 0; i < c; i++)
		for (j = i + 1; j < c; j++)
			if ((p[i].x == p[j].x) || (p[i].y == p[j].y)) {
				q = 0;

				for (k = 0; k < c; k++)
					if ((k >= i) && (k <= j)) {
						t[q].x = p[k].x;
						t[q].y = p[k].y;
						q++;
					}

				len = abs (p[i].x - p[j].x) + abs (p[i].y - p[j].y);
				if ((area (t, q) - o) / len > max) {
					max = (area (t, q) - o) / len;
					size = area (t, q) - o;
					sx1 = p[i].x;
					sy1 = p[i].y;
					sx2 = p[j].x;
					sy2 = p[j].y;
				}
			}

	ofstream out ("output.txt");

	out << sx1 << ' ' << sy1 << endl;
	out << sx2 << ' ' << sy2 << endl;
	out << size << endl;

	out.close ();
}

void main ()
{
	input ();
	process ();
}
