#include <fstream.h>

long n, m, Box[31][11], Dyn[31], Name[31], Ind[31];

void input()
{
	long l1, l2;

	ifstream fin("boxes.inp");
	fin >> m >> n;
	for (l1 = 1; l1 <= m; l1++)
	{
		for (l2 = 1; l2 <= n; l2++)
			fin >> Box[l1][l2];
		Name[l1] = l1;
	}
}

void process()
{
	long l1, l2, l3, tmp, tmp2[11];

	for (l1 = 1; l1 <= m; l1++)
		for (l2 = 1; l2 <= n; l2++)
			for (l3 = l2 + 1; l3 <= n; l3++)
				if (Box[l1][l2] > Box[l1][l3])
				{
					tmp = Box[l1][l2]; Box[l1][l2] = Box[l1][l3]; Box[l1][l3] = tmp;
				}
	for (l1 = 1; l1 <= m; l1++)
	{
		for (l2 = l1 + 1; l2 <= m; l2++)
		{
			if (Box[l1][1] > Box[l2][1])
			{
				memcpy(tmp2, Box[l1], sizeof(Box[l1]));
				memcpy(Box[l1], Box[l2], sizeof(Box[l2]));
				memcpy(Box[l2], tmp2, sizeof(tmp2));
				tmp = Name[l2]; Name[l2] = Name[l1]; Name[l1] = tmp;
			}
		}
	}
	for (l1 = 1; l1 <= m; l1++)
	{
		Dyn[l1] = 1; Ind[l1] = 0;
		for (l2 = 1; l2 < l1; l2++)
		{
			if (Dyn[l2] + 1 > Dyn[l1])
			{
				for (l3 = 1; l3 <= n; l3++)
				{
					if (Box[l1][l3] <= Box[l2][l3]) break;
				}
				if (l3 > n)
				{
					Dyn[l1] = Dyn[l2] + 1;
					Ind[l1] = l2;
				}
			}
		}
	}
}

void output()
{
	long l1, max, maxi, length, Path[31];

	ofstream fout("boxes.out");
	max = -32768;
	for (l1 = 1; l1 <= m; l1++)
		if (Dyn[l1] > max) { max = Dyn[l1]; maxi = l1; }
	fout << max << endl;
	length = 0;
	while (maxi != 0)
	{
		Path[++length] = maxi;
		maxi = Ind[maxi];
	}
	for (l1 = length; l1 >= 1; l1--)
		fout << Name[Path[l1]] << ' ';
}

int main()
{
	input();
	process();
	output();
	return 0;
}