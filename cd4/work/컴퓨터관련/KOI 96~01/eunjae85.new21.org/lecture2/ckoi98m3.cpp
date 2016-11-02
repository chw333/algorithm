#include <fstream.h>

typedef struct {
	int width, height, weight;
	int on;
} block;

int n;
block a[101];

int table[101];
int trace[101];

void input ()
{
	ifstream in ("input.txt");

	in >> n;
	for (int i = 1; i <= n; i++) {
		in >> a[i].width >> a[i].height >> a[i].weight;
		a[i].on = i;
	}

	in.close ();
}

void process ()
{
	int i, j;
	block t;

	for (i = 1; i <= n; i++)
		for (j = i + 1; j <= n; j++)
			if (a[i].width > a[j].width) {
				t = a[i];
				a[i] = a[j];
				a[j] = t;
			}

	a[0].width = 0;
	a[0].height = 0;
	a[0].weight = 0;

	table[0] = 0;

	int max = 0;

	for (i = 1; i <= n; i++) {
		table[i] = 0;

		for (j = 0; j < i; j++)
			if ((a[j].weight < a[i].weight) && (table[i] < table[j] + a[i].height)) {
				table[i] = table[j] + a[i].height;
				trace[i] = j;
			}

		if (table[max] < table[i]) max = i;
	}

	int temp[100];
	int c = 0;

	while (max != 0) {
		temp[c] = max;
		max = trace[max];
		c++;
	}

	ofstream out ("output.txt");

	out << c << endl;

	for (i = c - 1; i >= 0; i--)
		out << a[temp[i]].on << endl;

	out.close ();
}

void main ()
{
	input ();
	process ();
}
