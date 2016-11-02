#include <fstream.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

#define COUNT_LIMIT  498

int N;
char filename[80] = "stickmove00.in";

double Dot[5][4] = {
	{1, 10, 13, 5},
	{11, 3.5, 17, 6.5},
	{7, 4, 15, 1},
	{6, 4, 6, 1},
	{2, 2, 6, 7}
};

int Count[5];

void outfile ()
{
	int i, r; 
	double sx, sy, ex, ey;
	ofstream out ( filename );
	out << N;
	srand ( (unsigned) time (NULL) );
	for ( i = 0; i < 5; i ++ ) Count[i] = 0;
	for ( i = 0; i < N; i ++ ) {
		do {
			r = rand()%5;
		} while ( Count[r] > COUNT_LIMIT );
		Count[r] ++;
		sx = Dot[r][0] + Count[r] * 20;
		sy = Dot[r][1] + Count[r] * 20;
		ex = Dot[r][2] + Count[r] * 20;
		ey = Dot[r][3] + Count[r] * 20;
		out << endl << sx << " " << sy << " " << ex << " " << ey;
	}
}

void main ()
{
	int i;
	for ( i = 0; i < 10; i ++ ) {
		sprintf ( &filename[9], "%02d", i + 1 );
		filename[11] = '.';
		if ( i == 0 ) N = 10;
		else N = 100 * ( i + 1 );
		outfile();
	}
}