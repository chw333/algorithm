#include <fstream.h>
#include <stdlib.h>

int n;
int e[100][100];
int g[100];
int gc = 0;

void output2 ()
{
	ofstream out ("output.txt");

	out << 0 << endl;

	out.close ();

	exit (0);
}

void input ()
{
	ifstream in ("input.txt");

	in >> n;

	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++) {
			in >> e[i][j];
			if ((i > j) && (e[i][j] != e[j][i])) output2 ();
		}

	in.close ();
}

void process ()
{
	int flag;

	for (int i = 0; i < n; i++) {
		flag = 0;

		for (int j = 0; j < gc; j++) {
			for (int k = 0; k < i; k++)
				if ((g[k] == j) && e[i][k]) flag = 1;

			if (flag == 0) {
				g[i] = j;
				flag = 1;
				break;
			}

			flag = 0;
		}

		if (flag == 0) {
			g[i] = gc;
			gc++;
		}
	}

	int count;
	for (i = 0; i < gc; i++) {
		count = 0;

		for (int j = 0; j < n; j++)
			if (g[j] == i) count++;

		if (count < 2) output2 ();
	}
}

void output ()
{
	ofstream out ("output.txt");

	out << gc << endl;

	for (int i = 0; i < gc; i++) {
		for (int j = 0; j < n; j++)
			if (g[j] == i) out << j + 1 << ' ';
		out << endl;
	}

	out.close ();
}

void main()
{
	input ();
	process ();
	output ();
}
