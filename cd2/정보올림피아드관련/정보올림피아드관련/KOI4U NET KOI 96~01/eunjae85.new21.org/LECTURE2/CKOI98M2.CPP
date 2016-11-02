#include <fstream.h>
#include <stdlib.h>
#include <math.h>
#include <mem.h>

typedef struct {
	int x1, y1, x2, y2;
} box;

typedef struct {
	int value;
	int com[50];
} sol;

int n;
box a[50];
sol now, temp, best;

long far *timer = (long *)(0x0040006c), stime;

void input ()
{
	stime = *timer;

	ifstream in ("input.txt");

	in >> n;
	for (int i = 0; i < n; i++) {
		in >> a[i].x1 >> a[i].y1 >> a[i].x2 >> a[i].y2;

		int t;

		if (a[i].x1 > a[i].x2) {
			t = a[i].x1;
			a[i].x1 = a[i].x2;
			a[i].x2 = t;
		}

		if (a[i].y1 > a[i].y2) {
			t = a[i].y1;
			a[i].y1 = a[i].y2;
			a[i].y2 = t;
		}
	}
}

int hit (box a, box b)
{
	if ((a.x2 >= b.x1) && (a.x1 <= b.x2) &&
			(a.y2 >= b.y1) && (a.y1 <= b.y2)) return 1;
																	 else return 0;
}

void process ()
{
	randomize ();
	best.value = 0;

	double t;
	const double k = 1000;

	for (;;) {

		for (int i = 0; i < n; i++)
			now.com[i] = 0;
		now.value = 0;

		t = 1.0;

		do {
			do
				i = random (n);
			while (now.com[i]);

			temp.value = 0;

			for (int j = 0; j < n; j++) {
				temp.com[j] = now.com[j];
				if ((i != j) && temp.com[j] && hit (a[i], a[j]))
					temp.com[j] = 0;

				if (i == j) temp.com[i] = 1;
				if (temp.com[j]) temp.value += j + 1;
			}

			if (exp ((temp.value - now.value) / (k * t)) > rand ()/ 32767.0)
				now = temp;

			if (now.value > best.value) {
				best = now;
			}

			t = t * 0.997;
			if (*timer - stime > 170) return;
		} while (t > 0.001);
	}
}

void output ()
{
	ofstream out ("output.txt");

	out << best.value << endl;

	for (int i = 0; i < n; i++)
		if (best.com[i]) out << i + 1 << ' ';
	out << endl;

	out.close ();
}

void main ()
{
	input ();
	process ();
	output ();
}
