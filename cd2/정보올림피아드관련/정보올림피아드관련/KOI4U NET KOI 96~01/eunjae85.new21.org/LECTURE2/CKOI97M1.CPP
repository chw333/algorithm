#include <fstream.h>
#include <stdlib.h>

int n;
int a[80];

void input ()
{
	ifstream in ("input.txt");

	in >> n;

	in.close ();
}

void output ()
{
	ofstream out ("output.txt");

	for (int i = 0; i < n; i++)
		out << a[i];
	out << endl;

	out.close ();

	exit (0);
}

int correct (int size )
{
	int i, j, k;
	int flag;

	for (i = 1; i <= size / 2; i++)
		for (j = 0; j <= size - i * 2; j++) {
			flag = 0;

			for (k = j; k < j + i; k++)
				if (a[k] != a[k + i]) flag = 1;

			if (flag == 0) return 0;
		}

	return 1;
}

void recur (int d)
{
	if (d == n) output ();

	for (int i = 1; i <= 3; i++) {
		a[d] = i;
		if (correct (d + 1)) recur (d + 1);
	}
}

void process ()
{
	recur (0);
}

void main ()
{
	input ();
	process ();
}