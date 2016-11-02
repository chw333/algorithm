#include <fstream.h>

#define LEFT 0
#define RIGHT 1
#define UP 2
#define DOWN 3

typedef struct {
	long x, y;
} point;

int n, d;
point a[50], b[50], c[50];

int q = 1;

int ccw (point a, point b, point c)
{
	if (a.x * b.y + b.x * c.y + c.x * a.y -
			a.x * c.y - b.x * a.y - c.x * b.y > 0) return LEFT;
																				else return RIGHT;
}

void input ()
{
	ifstream in ("input.txt");

	in >> d;
	in >> n;

	int x, y, st;

	in >> b[0].x >> b[0].y;
	a[0].x = b[0].x - d;
	a[0].y = b[0].y - d;

	in >> b[1].x >> b[1].y;
	a[1].x = b[1].x + d;
	a[1].y = b[1].y - d;

	in >> b[2].x >> b[2].y;

	st = UP;

	for (int i = 3; i <= n; i++) {
		if (i != n) in >> b[i].x >> b[i].y;
					 else {b[i].x = b[0].x; b[i].y = b[0].y;}

		if (ccw (b[i - 2], b[i - 1], b[i]) == LEFT) {
			switch (st) {
				case RIGHT : { a[i - 1].x = b[i - 1].x + d;
											 a[i - 1].y = b[i - 1].y - d;
											 st = UP;
											 break; }
				case LEFT  : { a[i - 1].x = b[i - 1].x - d;
											 a[i - 1].y = b[i - 1].y + d;
											 st = DOWN;
											 break; }
				case UP    : { a[i - 1].x = b[i - 1].x + d;
											 a[i - 1].y = b[i - 1].y + d;
											 st = LEFT;
											 break; }
				case DOWN  : { a[i - 1].x = b[i - 1].x - d;
											 a[i - 1].y = b[i - 1].y - d;
											 st = RIGHT;
											 break; }
			}
		} else {
			switch (st) {
				case RIGHT : { a[i - 1].x = b[i - 1].x - d;
											 a[i - 1].y = b[i - 1].y - d;
											 st = DOWN;
											 break; }
				case LEFT  : { a[i - 1].x = b[i - 1].x + d;
											 a[i - 1].y = b[i - 1].y + d;
											 st = UP;
											 break; }
				case UP    : { a[i - 1].x = b[i - 1].x + d;
											 a[i - 1].y = b[i - 1].y - d;
											 st = RIGHT;
											 break; }
				case DOWN  : { a[i - 1].x = b[i - 1].x - d;
											 a[i - 1].y = b[i - 1].y + d;
											 st = LEFT;
											 break; }
			}
		}
	}

	in.close ();
}

void swap (long *a, long *b)
{
	long t;
	t = *a;
	*a = *b;
	*b = t;
}

int is (point la1, point la2, point lb1, point lb2, int *x, int *y)
{
	if (la1.x > la2.x) swap (&la1.x, &la2.x);
	if (la1.y > la2.y) swap (&la1.y, &la2.y);
	if (lb1.x > lb2.x) swap (&lb1.x, &lb2.x);
	if (lb1.y > lb2.y) swap (&lb1.y, &lb2.y);

	if (la1.y == la2.y) {  // if la is horizon
		swap (&la1.x, &lb1.x);
		swap (&la1.y, &lb1.y);
		swap (&la2.x, &lb2.x);
		swap (&la2.y, &lb2.y);
	}

	if ((la1.y <= lb1.y ) && (lb1.y <= la2.y) &&
			(lb1.x <= la1.x ) && (la1.x <= lb2.x)) {

		*x = la1.x;
		*y = lb1.y;
		return 1;
	}

	return 0;
}

void process ()
{
	int x, y;
	int flag;

	c[0].x = a[0].x;
	c[0].y = a[0].y;

	for (int i = 1; i < n; i++) {
		flag = 0;
		for (int j = 0; j < q - 2; j++)
			if (is (c[q - 1], a[i], c[j], c[j + 1], &x, &y)) {
				c[j + 1].x = x;
				c[j + 1].y = y;
				c[j + 2].x = a[i].x;
				c[j + 2].y = a[i].y;
				q = j + 3;
				flag = 1;
				break;
			}

		if (flag == 1) continue;

		c[q].x = a[i].x;
		c[q].y = a[i].y;
		q++;
	}
}

void output ()
{
	ofstream out ("output.txt");

	out << q << endl;

	for (int i = 0; i < q; i++)
		out << c[i].x << ' ' << c[i].y << endl;

	out.close ();
}

void main ()
{
	input ();
	process ();
	output ();
}
