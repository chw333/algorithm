#include <fstream.h>
#include <stdio.h>

typedef struct {
	double x1, y1, x2, y2;
} Tbox;

Tbox a[30];
int n;

void input ()
{
	ifstream in ("input.txt");

	in >> n;

	for (int i = 0 ; i < n; i++) {
		in >> a[i].x1 >> a[i].y1 >> a[i].x2 >> a[i].y2;
		a[i].x2 += a[i].x1;
		a[i].y2 += a[i].y1;
	}

	in.close ();
}

int hit (double ax1, double ay1, double ax2, double ay2,
				 double bx1, double by1, double bx2, double by2)
{
	if ((ax2 > bx1) && (ax1 < bx2) &&
			(ay2 > by1) && (ay1 < by2)) return 1;
														 else return 0;
}

void swap (double *a, double *b)
{
	double t;

	t = *a;
	*a = *b;
	*b = t;
}

void process ()
{
	double x[60], y[60];
	int i, j, k;

	for (i = 0; i < n; i++) {
		x[i * 2    ] = a[i].x1;
		x[i * 2 + 1] = a[i].x2;
		y[i * 2    ] = a[i].y1;
		y[i * 2 + 1] = a[i].y2;
	}

	for (i = 0; i < n * 2; i++)
		for (j = i + 1; j < n * 2; j++) {
			if (x[i] > x[j]) swap (&x[i], &x[j]);
			if (y[i] > y[j]) swap (&y[i], &y[j]);
		}

	double area = 0;
	int flag;

	for (i = 0; i < n * 2 - 1; i++)
		for (j = 0; j < n * 2 - 1; j++) {
			flag = 0;

			for (k = 0; k < n; k++)
				if (hit (x[i],    y[j],    x[i + 1], y[j + 1],
								 a[k].x1, a[k].y1, a[k].x2 , a[k].y2 )) flag = 1;

			if (flag) area += (x[i + 1] - x[i]) * (y[j + 1] - y[j]);
		}

	ofstream out ("output.txt");

	char str[30];
	sprintf (str, "%.2f", area);
	out << str << endl;

	out.close ();
}

void main ()
{
	input ();
	process ();
}
