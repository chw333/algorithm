#include <fstream.h>
#include <stdlib.h>

int n;
int a[50];
int t[50] = {0, };
int s[50];

int sum = 0;
int min = 9999;

void input ()
{
	ifstream in ("input.txt");

	in >> n;
	int i, j;

	for (i = 0; i < n; i++)
		in >> a[i];

	for (i = 0; i < n; i++)
		for (j = i + 1; j < n; j++)
			if (a[i] < a[j]) {
				int t;
				t = a[i];
				a[i] = a[j];
				a[j] = t;
			}

	in.close ();
}

void output (int target)
{
	ofstream out ("output.txt");

	out << target << endl;

	for (int i = 0; i < sum / target; i++) {
		for (int j = 0; j < n; j++)
			if (s[j] == i) out << a[j] << " ";

		out << endl;
	}

	out.close ();

	exit (0);
}

void recur (int target, int d, int c)
{
	if (d == n) output (target);

	for (int i = 0; i < c; i++)
		if (t[i] + a[d] <= target) {
			s[d] = i;
			t[i] += a[d];

			if ((target - t[i] == 0) || (target - t[i] >= min))
				recur (target, d + 1, c);

			t[i] -= a[d];
		}

	if (c != sum / target) {
		s[d] = c;
		t[c] = a[d];
		if (t[c] <= target) recur (target, d + 1, c + 1);
		t[c] = 0;
	}
}

void process ()
{
	for (int i = 0; i < n; i++) {
		sum += a[i];
		if (min > a[i]) min = a[i];
	}

	for (i = min; i <= sum; i++)
		if (sum % i == 0)
			recur (i, 0, 0);
}

void main ()
{
	input ();
	process ();
}
