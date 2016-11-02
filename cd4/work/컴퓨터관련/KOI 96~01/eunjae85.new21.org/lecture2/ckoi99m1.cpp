#include <fstream.h>

int n;
int a, b;

int p[100];
int d[100];

void input ()
{
	ifstream in ("input.txt");

	in >> n;
	in >> a >> b;

	a--;
	b--;

	int t;
	in >> t;

	for (int i = 0; i < n; i++)
		p[i] = -1;

	for (i = 0; i < t; i++) {
		int u, v;

		in >> u >> v;
		p[v - 1] = u - 1;
	}

	in.close ();
}

void process ()
{
	int i, c = 0;

	for (i = 0; i < n; i++)
		d[i] = -1;

	i = p[a];
	while (i != -1) {
		c++;
		d[i] = c;
		i = p[i];
	}

	ofstream out ("output.txt");

	int flag = 0;
	c = 0;

	i = p[b];
	while (i != -1) {
		c++;
		if (d[i] != -1) {
			out << d[i] + c << endl;
			flag = 1;
			break;
		}
		i = p[i];
	}

	if (flag == 0) out << -1 << endl;

	out.close ();
}

void main ()
{
	input ();
	process ();
}
