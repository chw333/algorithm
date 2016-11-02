#include <stdio.h>
#include <fstream.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>

#define MAX(a,b) (((a)>(b))?(a):(b))
#define MIN(a,b) (((a)<(b))?(a):(b))

int B[5][5];

void init()
{
	int i, j;
	for ( i = 0; i < 5; i ++ ) {
		for ( j = 0; j < 5; j ++ ) {
			B[i][j] = 2;
		}
	}
}

void colorchange( int l, int c )
{
	int i, j, sl, el, sc, ec;
	sl = MAX(0, l-1); el = MIN(4, l+1);
	sc = MAX(0, c-1); ec = MIN(4, c+1);
	for ( i = sl; i <= el; i ++ ) {
		for ( j = sc; j <= ec; j ++ ) {
			B[i][j] ++;
			if ( B[i][j] > 2 ) B[i][j] = 0;
		}
	}
}

void display()
{
	int i, j;
	cout << endl;
	for ( i = 0; i < 5; i ++ ) {
		for ( j = 0; j < 5; j ++ ) {
			cout << B[i][j];
		}
		cout << endl;
	}
	getch();
}

void output( char *p )
{
	char c;
	int i, j;
	ofstream out ( p );
	for ( i = 0; i < 5; i ++ ) {
		for ( j = 0; j < 5; j ++ ) {
			if ( B[i][j] == 0 )		 c = 'r';
			else if ( B[i][j] == 1 ) c = 'y';
			else if ( B[i][j] == 2 ) c = 'b';
			out << c;
		}
	}
}

void process()
{
	int i, g, l, c;
	g = rand() % 30000 + 2000;
	for ( i = 0; i < g; i ++ ) {
		l = rand() % 5;
		c = rand() % 5;
		colorchange( l, c );
	}		
}

void main()
{
	int i;
	char p[80] = "colorchange00.in";
	srand ( (unsigned) time( NULL ) );
	for ( i = 1; i <= 10; i ++ ) {
		sprintf ( &p[11], "%02d", i );
		p[13] = '.';
		init();
		if ( i != 10 )	process();
		output( p );
	}
}