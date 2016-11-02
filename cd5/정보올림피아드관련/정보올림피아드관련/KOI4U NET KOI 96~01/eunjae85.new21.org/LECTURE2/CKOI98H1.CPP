#include <fstream.h>
#include <stdlib.h>

typedef struct {
	long x, y;
} point;

typedef struct {
	point a, b, c, d;
	long area;
} sol;

int n;
point a[1000];

sol best;

void input ()
{
	ifstream in ("input.txt");

	in >> n;
	for (int i = 0; i < n; i++)
		in >> a[i].x >> a[i].y;

	in.close ();
}

int ccw (point a, point b, point c)
{
	long t;

	t = (a.x * b.y + b.x * c.y + c.x * a.y) -
			(a.x * c.y + b.x * a.y + c.x * b.y);

	if (t > 0) return 1;  // left
	if (t == 0) return 0;  // straight
	return -1;
}

void swap (point *a, point *b)
{
	point t;

	t = *a;
	*a = *b;
	*b = t;
}

int gcd (long a, long b)
{
	if (a == 0) return b;
	if (b == 0) return a;

	if (a >= b) return gcd (a - b, b);

	return gcd (a, b - a);
}

int check (point u, point v, int t)
{
	for (int i = 0; i < n; i++) {
		int dummy;
		dummy = ccw (u, v, a[i]);
		if ((dummy != 0) && (dummy != t)) return 0;
	}

	return 1;
}

void findbox (point a, point b)
{
	long dx, dy, t;

	dx = b.x - a.x;
	dy = b.y - a.y;

	t = gcd (abs (dx), abs (dy));

	dx = dx / t;
	dy = dy / t;

	point c, d;
	c = a;
	d.x = a.x - dy;
	d.y = a.y + dx;

	while (!check (c, d, -1)) {
		c.x -= dx;
		c.y -= dy;
		d.x -= dx;
		d.y -= dy;
	}

	point e, f;
	e = b;
	f.x = b.x - dy;
	f.y = b.y + dx;

	while (!check (e, f, 1)) {
		e.x += dx;
		e.y += dy;
		f.x += dx;
		f.y += dy;
	}

	point g, h;
	g = c;
	h.x = c.x + dx;
	h.y = c.y + dy;

	while (!check (g, h, -1)) {
		g.x -= dy;
		g.y += dx;
		h.x -= dy;
		h.y += dx;
	}

	point i;
	i.x = g.x + (e.x - c.x);
	i.y = g.y + (e.y - c.y);

	t = (e.x * c.y + c.x * g.y + g.x * i.y + i.x * e.y) -
			(e.x * i.y + c.x * e.y + g.x * c.y + i.x * g.y);
	t = abs (t) / 2;

	if (t < best.area) {
		best.area = t;
		best.a = e;
		best.b = c;
		best.c = g;
		best.d = i;
	}
}

void sort ()
{
	int i, j;

	j = 0;
	for (i = 1; i < n; i++) {
		if (a[i].y < a[j].y) j = i;
		if ((a[i].y == a[j].y) && (a[i].x > a[j].x)) j = i;
	}

	swap (&a[0], &a[j]);

	for (i = 1; i < n; i++)
		for (j = i + 1; j < n; j++)
			if (ccw (a[0], a[i], a[j]) == -1) swap (&a[i], &a[j]);

	int stack[1001];
	int top = 1;

	stack[0] = 0;
	stack[1] = 1;

	for (i = 2; i < n; i++) {
		while (ccw (a[stack[top-1]], a[stack[top]], a[i]) != 1)
			top--;

		top++;
		stack[top] = i;
	}

	stack[top + 1] = stack[0];

	for (i = 0; i <= top; i++)
		findbox (a[stack[i]], a[stack[i + 1]]);
}

void process ()
{
	best.area = 999999999;

	sort ();
}

void output ()
{
	ofstream out ("output.txt");

	cout << best.area << endl;

	out << best.a.x << ' ' << best.a.y << endl;
	out << best.b.x << ' ' << best.b.y << endl;
	out << best.c.x << ' ' << best.c.y << endl;
	out << best.d.x << ' ' << best.d.y << endl;

	out.close ();
}

void main ()
{
	input ();
	process ();
	output ();
}
