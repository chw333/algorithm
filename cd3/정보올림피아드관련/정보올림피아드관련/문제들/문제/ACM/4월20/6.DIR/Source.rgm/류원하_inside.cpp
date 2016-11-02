#include <fstream.h>

float data[20][2];
float dot[2];
short int n;
int did[20][20][20];
long cnt;

int ccw(int a, int b)
{
	float aa, bb, cc, dd, ee, ff;
	aa = data[b][0] - data[a][0];
	bb = data[b][1] - data[a][1];
	cc = dot[0] - data[a][0];
	dd = dot[1] - data[a][1];
	ee = aa * dd;
	ff = bb * cc;
	if (ee - ff < 0)
		return 1;
	if (ee - ff > 0)
		return 0;
	return -1;
}

void i_stream()
{
	ifstream in ("inside.in");
	in >> n;
	int i;
	for (i = 0;i < n;i++)
		in >> data[i][0] >> data[i][1];
	in >> dot[0] >> dot[1];
}

void process()
{
	int i,j,k;
	for (i = 0;i < n;i++)
	{
		for (j = 0;j < n;j++)
		{
			if (j != i)
			{
				for (k = 0;k < n;k++)
				{
					if (k != j && k != i && did[i][j][k] == 0)
					{
						did[i][j][k] = 1;
						did[i][k][j] = 1;
						did[j][i][k] = 1;
						did[j][k][i] = 1;
						did[k][i][j] = 1;
						did[k][j][i] = 1;
						int a = ccw(i,j), b = ccw(j,k), c = ccw(k,i);
						if (a == b && b == c && a != -1)
							cnt++;
					}
				}
			}
		}
	}
}

void o_stream()
{
	ofstream out ("inside.out");
	out << cnt;
}

void main()
{
	i_stream();
	process();
	o_stream();
}
