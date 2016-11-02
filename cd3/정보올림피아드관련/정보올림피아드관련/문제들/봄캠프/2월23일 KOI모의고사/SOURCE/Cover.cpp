#include <fstream.h>
#include <stdlib.h>

const char Infilename[30] = "cover.inp";
const char Outfilename[30] = "cover.out";

int n;
long res = 0;
long sum;
int y, x;
int check[100];
int max[20][20];
int mwho[20][20];
int table[20][20];
int twho[20][20];
int size[10][2];
int data[10][10][10];
int go[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
long *ti = (long far *)0x0040006c, st = *ti;

int main()
{
	ifstream fin(Infilename);
	fin >> y >> x;
	fin >> n;
	int i, j, k;
	randomize();
	for(k = 0; k < n; k++)
	{
		fin >> size[k][0] >> size[k][1];
		for(i = 0; i < size[k][0]; i++)
			for(j = 0; j < size[k][1]; j++)
				fin >> data[k][i][j];
	}
	fin.close();
	int que[1000][2];
	while((*ti - st) < 85)
	{
		sum = 0;
		for(i = 0; i < y; i++)
			for(j = 0; j < x; j++)
				table[i][j] = twho[i][j] = 0;
		for(i = 0; i < n; i++)
			check[i] = 0;
		for(int oo = 0; oo < n; oo++)
		{
			do
			{
				k = random(n);
			} while(check[k] == 1);
			check[k] = 1;
			int a = random(size[k][0] * 2 - 1) - size[k][0] + 1, b = random(size[k][1] * 2 - 1) - size[k][1] + 1;
			int c, d;
			for(int p = 0; p < 30; p++)
			{
				c = random(size[k][0]);
				d = random(size[k][1]);
				if (0 <= c + a && c + a < y && 0 <= d + b && b + d < x && twho[c + a][d + b] == 0 && data[k][c][d] != 0) break;
			}
			if (0 > c + a || c + a > y || 0 > d + b || d + b > x || twho[c + a][d + b] != 0) continue;
			int he = 0, ta = 1;
			que[0][0] = c;
			que[0][1] = d;
			while(random(100) < 87 && he != ta)
			{
				int q = que[he][0], w = que[he][1];
				int qq, ww;
				if (table[q + a][w + b] == 0 && data[k][q][w] != 0)
				{
					table[q + a][w + b] = data[k][q][w];
					sum += data[k][q][w];
					twho[q + a][w + b] = k  + 1;
				}
				for(int o = 0; o < 4; o++)
				{
					if (random(2))
					{
						qq = q + go[o][0];
						ww = w + go[o][1];
						if (0 <= qq && qq < size[k][0] && 0 <= ww && ww < size[k][1] && 0 <= qq + a && qq + a < y && 0 <= ww + b && ww + b < x && twho[qq + a][ww + b] == 0 && data[k][qq][ww] != 0)
						{
							que[ta][0] = qq;
							que[ta++][1] = ww;
						}
					}
				}
				he++;
			}
		}
		if (sum > res)
		{
			res = sum;
			for(i = 0; i < y; i++)
				for(j = 0; j < x; j++)
				{
					max[i][j] = table[i][j];
					mwho[i][j] = twho[i][j];
				}
		}
	}
	ofstream fout(Outfilename);
	fout << y << ' ' << x << endl;
	fout << res << endl;
	for(i = 0; i < y; i++)
	{
		for(j = 0; j < x; j++)
			fout << max[i][j] << ' ';
		fout << endl;
	}
	fout << endl;
	for(i = 0; i < y; i++)
	{
		for(j = 0; j < x; j++)
			fout << mwho[i][j] << ' ';
		fout << endl;
	}
	fout.close();
	return 0;
}