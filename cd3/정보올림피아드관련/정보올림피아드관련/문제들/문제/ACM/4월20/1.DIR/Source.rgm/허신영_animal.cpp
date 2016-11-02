#include <stdio.h>
#include <fstream.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

int C, R;
char Data[1000][1000];
bool v[1000][1000];

int Q[700000][3], QA, QB;
int max = 0;

int oc = clock();

void Input()
{
	int i, j;

	ifstream in("animal.in");

	in >> C >> R;
	for( i = 0; i < R; i++ )
		for( j = 0; j < C; j++ )
			in >> Data[i][j];

	in.close();
}

void EnQ( int xx, int yy, int hh )
{
	Q[QB][0] = xx;
	Q[QB][1] = yy;
	Q[QB++][2] = hh;
	if( QB >= 700000 ) QB = 0;
}

void DeQ( int *xx, int *yy, int *hh )
{
	*xx = Q[QA][0];
	*yy = Q[QA][1];
	*hh = Q[QA++][2];
	if( QA >= 700000 ) QA = 0;
}

void Process()
{
	int xx, yy, hh;

	srand( (unsigned)time( NULL ) );
	while( clock() - oc <= 5 * CLOCKS_PER_SEC )
	{
		for(;;)
		{
			xx = rand() % C;
			yy = rand() % R;
			if( Data[yy][xx] == '.' ) break;
		}

		memset( v, false, sizeof( v ) );
		EnQ( xx, yy, 0 );
		while( !( QA == QB ) )
		{
			DeQ( &xx, &yy, &hh );
			if( v[yy][xx] == true ) continue;
			if( hh > max ) max = hh;
			v[yy][xx] = true;
			
			if( xx > 0 && Data[yy][xx - 1] == '.' && v[yy][xx - 1] == false )
				EnQ( xx - 1, yy, hh + 1 );
			if( yy > 0 && Data[yy - 1][xx] == '.' && v[yy - 1][xx] == false )
				EnQ( xx, yy - 1, hh + 1 );
			if( xx < C - 1 && Data[yy][xx + 1] == '.' && v[yy][xx + 1] == false )
				EnQ( xx + 1, yy, hh + 1 );
			if( yy < R - 1 && Data[yy + 1][xx] == '.' && v[yy + 1][xx] == false )
				EnQ( xx, yy + 1, hh + 1 );
		}
	}
}

void Output()
{
	ofstream out("animal.out");

	out << max;

	out.close();
}

void main()
{
	Input();
	Process();
	Output();
}