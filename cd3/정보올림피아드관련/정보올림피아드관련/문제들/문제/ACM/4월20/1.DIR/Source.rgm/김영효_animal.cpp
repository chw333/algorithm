#include "fstream.h"
#include "time.h"
#include "stdlib.h"

void output();

int n,m;
char data[1000][1000];
int visit[1000][1000];
int count=-1;
clock_t st,et;

void input()
{
	ifstream in("animal.in");
	in >> m >> n;
	
	int i,j;
	for( i=0; i<n; i++ )
		for( j=0; j<m; j++ )
		{
			in >> data[i][j];
			visit[i][j] = 0;
		}
}

void dol(int y, int x, int cnt)
{
	et = clock();
	if( (double)(et-st)/CLOCKS_PER_SEC > 4.7 )
	{
		output();
		exit(0);
	}
	int flag=1;
	visit[y][x] = 1;

	if( x+1 < m && !visit[y][x+1] && data[y][x+1] == '.' )
	{
		flag=0;
		dol(y,x+1,cnt+1);
	}
		
	if( x-1 >= 0 && !visit[y][x-1] && data[y][x-1] == '.' )
	{
		flag=0;
		dol(y,x-1,cnt+1);
	}

	if( y-1 >= 0 && !visit[y-1][x] && data[y-1][x] == '.' )
	{
		flag=0;
		dol(y-1,x,cnt+1);
	}

	if( y+1 < n && !visit[y+1][x] && data[y+1][x] == '.' )
	{
		flag=0;
		dol(y+1,x,cnt+1);
	}

	if( flag && count < cnt )
		count = cnt;

	visit[y][x] = 0;
}

void proc()
{
	int i,j;
	for( i=0; i<n; i++ )
		for( j=0; j<m; j++ )
			if( data[i][j] == '.')
			{
				if( data[i-1][j] == '#' 
					|| data[i+1][j] == '#'
					|| data[i][j-1] == '#'
					|| data[i][j+1] == '#' )
					dol(i,j,0);
			}
}

void output()
{
	ofstream out("animal.out");

	if( count == -1 )
		out << 0;
	else
		out << count;
}

void main()
{
	st = clock();
	input();
	proc();
	output();
}