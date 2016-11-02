#include <fstream.h>

#define maxn 10
#define lim 10000
#define infilename "coin.inp"
#define outfilename "coin.out"

int n, Coin[maxn + 1], Dyn[lim + 1];

void input()
{
	int l1;

	ifstream fin(infilename);
	fin >> n;
	for (l1 = 1; l1 <= n; l1++)
		fin >> Coin[l1];
}

int func1(int a, int b)
{
	if (b == -1 || a < b) return a;
	return b;
}

int process()
{
	int l1, l2, s, grd, tmp;

	for (l1 = 1; l1 < n; l1++)
		for (l2 = l1 + 1; l2 <= n; l2++)
			if (Coin[l1] < Coin[l2])
			{
				tmp = Coin[l1]; Coin[l1] = Coin[l2]; Coin[l2] = tmp;
			}
	memset(Dyn, -1, sizeof(Dyn));
	Dyn[0] = 0;
	for (l1 = 1; l1 <= lim; l1++)
	{
		s = l1;	grd = 0;
		for (l2 = 1; l2 <= n; l2++)
		{
			if (l1 >= Coin[l2] && Dyn[l1 - Coin[l2]] != -1)
			{
				Dyn[l1] = func1(Dyn[l1 - Coin[l2]] + 1, Dyn[l1]);
			}
			grd += (s / Coin[l2]);
			s %= Coin[l2];
		}
		if (Dyn[l1] == -1 || grd > Dyn[l1])
			return l1;
	}
	return -1;
}

void output(int sw)
{
	ofstream fout(outfilename);
	if (sw != -1) { fout << "No" << endl << sw; }
	else fout << "Yes" << endl;
}

int main()
{
	int sw;

	input();
	sw = process();
	output(sw);
	return 0;
}