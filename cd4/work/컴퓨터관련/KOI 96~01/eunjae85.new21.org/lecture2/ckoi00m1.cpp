#include <fstream.h>

int n;
long e[100][100]= {0, };

long c[100] = {0, };

void input ()
{
	ifstream in ("input.txt");

	in >> n;

	int m;
	in >> m;
	for (int i = 0; i < m; i++) {
		int u, v, w;
		in >> u >> v >> w;

		e[u - 1][v - 1] = w;
	}

	in.close ();
}

void recur (int a, long t)
{
	for (int i = 0; i < n; i++)
		if (e[a][i] != 0)
			recur (i, t * e[a][i]);

	c[a] += t;
}

void process ()
{
	recur (n - 1, 1);

	ofstream out ("output.txt");

	for (int i = 0; i < n; i++) {
		int flag = 0;

		for (int j = 0; j < n; j++)
			if (e[i][j]) flag = 1;

		if (flag == 0) out << i + 1 << " " << c[i] << endl;
	}

	out.close ();
}

void main()
{
	input ();
	process ();
}
