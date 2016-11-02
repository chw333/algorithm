#include <fstream.h>
#include <string.h>

#define maxn 1000
#define infilename "seq.inp"
#define outfilename "seq.out"

int n, a0, b0, l0, a1, b1, l1;
char Outstr[maxn + 1];

void input()
{
	ifstream fin(infilename);
	fin >> n >> a0 >> b0 >> l0 >> a1 >> b1 >> l1;
	fin.close();
}

int min(int a, int b)
{
	return (a > b) ? b : a;
}

int max(int a, int b)
{
	return (a > b) ? a : b;
}

void process()
{
	int lp1, lp2, lp3, m1, m2, t, max, maxi, maxj;
	int pt;

	if (l0 + l1 <= n)
	{
		for (lp1 = 0; lp1 < a0; lp1++) Outstr[lp1] = '0';
		for (lp1 = a0; lp1 < l0; lp1++) Outstr[lp1] = '1';
		for (lp1 = l0; lp1 < l0 + a1; lp1++) Outstr[lp1] = '1';
		for (lp1 = l0 + a1; lp1 < l0 + l1; lp1++) Outstr[lp1] = '0';
		for (lp1 = l0 + l1; lp1 < n; lp1++) Outstr[lp1] = '0';
		return;
	}
	else
	{
		max = -32768;
		for (lp1 = a0; lp1 <= b0; lp1++)
		{
			for (lp2 = a1; lp2 <= b1; lp2++)
				if (min(lp1, l1 - lp2) + min(l0 - lp1, lp2) > max)
				{
					max = min(lp1, l1 - lp2) + min(l0 - lp1, lp2);
					maxi = lp1; maxj = lp2;
				}
		}
		pt = 0;
		m1 = min(maxi, l1 - maxj); m2 = min(l0 - maxi, maxj);
		if (l0 + l1 - m1 - m2 > n) { strcpy(Outstr, "-1"); return; }
		for (lp1 = 1; lp1 <= maxi - m1; lp1++) Outstr[pt++] = '0';
		for (lp1 = 1; lp1 <= l0 - maxi - m2; lp1++) Outstr[pt++] = '1';
		for (lp1 = 1; lp1 <= m1; lp1++) Outstr[pt++] = '0';
		for (lp1 = 1; lp1 <= m2; lp1++) Outstr[pt++] = '1';
		for (lp1 = 1; lp1 <= l1 - maxj - m1; lp1++) Outstr[pt++] = '0';
		for (lp1 = 1; lp1 <= maxj - m2; lp1++) Outstr[pt++] = '1';
		for (; pt < n; pt++)
			Outstr[pt] = '0';
	}
}

void output()
{
	ofstream fout(outfilename);
	fout << Outstr;
}

int main()
{
	input();
	process();
	output();
	return 0;
}