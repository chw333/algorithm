#include <fstream.h>
#include <stdio.h>

int n;
double max = -10000, now;

void main()
{
	ifstream in ("input.txt");
	in >> n;

	now = 0.0;

	for (int i = 0; i < n; i++) {
		double temp;
		in >> temp;

		if (now >= 1.0) now = now * temp;
							 else now = temp;

		if (now > max) max = now;
	}
	in.close ();

	ofstream out ("output.txt");

	char str[30];
	sprintf (str, "%.3f", max);
	out << str;

	out.close ();
}
