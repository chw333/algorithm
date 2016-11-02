#include <stdio.h>
#include <fstream.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <conio.h>

#define MAX(a,b) (((a)>(b))?(a):(b))
#define MIN(a,b) (((a)<(b))?(a):(b))

int N, B[6][6][4], Visit[5][5];

void init()
{
	int i, j;
	for ( i = 0; i < N; i ++ ) {
		B[0][i][0]   = rand()%10;
		B[N-1][i][2] = rand()%10;
		B[i][0][3]   = rand()%10;
		B[i][N-1][1] = rand()%10;
	}
	for ( i = 0; i < N; i ++ ) {
		for ( j = 0; j < N; j ++ ) {
			B[i+1][j][0] = B[i][j][2] = rand()%10;
			B[i][j+1][3] = B[i][j][1] = rand()%10;
			Visit[i][j] = 0;
		}
	}
}

void process ( char *p )
{
	int i, j, k, l, c, count = 0;
	ofstream out ( p );
	out << N;
/*
	do {
		do {
			l = rand()%N;
			c = rand()%N;
		} while ( Visit[l][c] );
		Visit[l][c] = 1;
		out << endl;
		for ( i = 0; i < 4; i ++ ) {
			if ( i != 0 ) out << " ";
			out << B[l][c][i];
		}
		count ++;
	} while ( count < N*N );
*/
	for ( i = N-1; i >= 0; i -- ) {
		for ( j = N-1; j >= 0; j -- ) {
			out << endl;
			for ( k = 0; k < 4; k ++ ) { 
				if ( k != 0 ) out << " ";
				out << B[i][j][k];
			}
		}
	}
}
	

void main()
{
	int i;
	char p[80] = "gnome00.in";
	char p1[80] = "copy gnome00.in gnome.in";
	char p2[80] = "copy gnome.out gnome00.out";
	srand ( (unsigned) time( NULL ) );
	for ( i = 12; i < 15; i ++ ) {
		sprintf ( &p[5], "%02d", i+1 );
		p[7] = '.';
		sprintf ( &p1[10], "%02d", i+1 );
		p1[12] = '.';
		sprintf ( &p2[20], "%02d", i+1 );
		p2[22] = '.';

		N = 5; 
		init();
		process( p );

//		output( p );
		WinExec ( p1, SW_SHOW );
		WinExec ( "gnome.exe", SW_SHOW );
		WinExec ( p2, SW_SHOW );
	}
}