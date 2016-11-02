#include <fstream.h>

char fall[100][101];
char data[100][101];
long fx, fy, dx, dy, freea, freeb;
char visit[200][101];
long max;

void i_stream()
{
	ifstream in ("tetris.in");
	in >> fx >> fy;
	long i,j;
	for (i = 0;i < fx;i++)
		in >> fall[i];
	in >> dx >> dy;
	for (i = 0;i < dx;i++)
		in >> data[i];
	
	for (i = 0;i < dx;i++)
	{
		for (j = 0;j < dy;j++)
			if (data[i][j] == '#')
				break;
		if (j != dy)
		{
			freea = i;
			break;
		}
	}
	for (i = fx-1;i >= 0;i--)
	{
		for (j = 0;j < fy;j++)
			if (fall[i][j] == '#')
				break;
		if (j != fy)
		{
			freeb = i;
			break;
		}
	}
}

int checkit(long x, long y)
{
	long i,j;
	for (i = x;i < x + fx && i < fx+dx;i++)
	{
		if (i+x <= fx)
			continue;
		for (j = y;j < y + fy && j < dy;j++)
		{
			if (data[i-fx][j] == '#' && fall[i-x][j-y] == '#')
				return 0;
		}
	}
	return 1;
}

void process(long x, long y)
{
	visit[x][y] = '#';
	if (checkit(x,y) != 1)
		return;
	if (x > max)
		max = x;
	if (x == dx + fx)
		return;
	if (y > 0 && visit[x][y-1] != '#')
		process(x,y-1);
	if (visit[x+1][y] != '#')
		process(x+1,y);
	if (y + 1 <= dy-fy && visit[x][y+1] != '#')
		process(x,y+1);
}

void o_stream()
{
	ofstream out ("tetris.out");
	if (max == dx + fx)
		out << "pass";
	else
		out << max - freea - (fx - freeb) + 1;
}

void main()
{
	i_stream();
	long i;
	for (i = 0;i <= dy - fy;i++)
	{
		if (data[0][i] == '.')
			process(0,i);
	}
	o_stream();
}