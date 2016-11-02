#include <fstream.h>

int n;
int a[101][101];
int table[101][101];
ifstream fin;
ofstream fout;

int max (int t1, int t2)
{
	if (t1 >= t2) return t1;
	else return t2;
}

void input ()
{
	fin.open ("2-5.in");
	fin >> n;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= i; j++)
			fin >> a[i][j];
	fin.close();
}

void solve ()
{
	table[1][1] = a[1][1];

	for (int i = 2; i <= n; i++)
	{
		table[i][1] = table[i-1][1] + a[i][1];
		for (int j = 2; j <= i; j++)
			table[i][j] = max (table[i-1][j-1], table[i-1][j]) + a[i][j];
	}
}

void output ()
{
	fout.open ("output.txt");
	int max = -2147483648l;
	for (int i = 1; i <= n; i++)
		if (table[n][i] > max) max = table[n][i];
	fout << max << endl;
	fout.close();
}

void main ()
{
	input ();
	solve ();
	output ();
}