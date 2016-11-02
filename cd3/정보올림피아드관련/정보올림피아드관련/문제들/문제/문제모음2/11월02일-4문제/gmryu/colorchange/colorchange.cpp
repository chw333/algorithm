#include <fstream.h>
#include <conio.h>

#define MAX(a,b) (((a)>(b))?(a):(b))
#define MIN(a,b) (((a)<(b))?(a):(b))

ifstream in  ( "colorchange10.in"  );
ofstream out ( "colorchange10.out" );

int B[5][5], Min = 2000000000;

void input()
{
	char b[26], c;
	int i, j, count = 0;
	in >> b;
	for ( i = 0; i < 5; i ++ ) {
		for ( j = 0; j < 5; j ++ ) {
			c = b[count ++];
			if ( c == 'r' ) B[i][j] = 0;
			else if ( c == 'y' ) B[i][j] = 1;
			else B[i][j] = 2;
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

int is_ok( int l, int c )
{
	if ( l-1 < 0 || c-1 < 0 ) return 1;
	if ( B[l-1][c-1] != 2 ) return 0;
	if ( l > 0 && c == 4 ) {
		if ( B[l-1][c] != 2 ) return 0;
	}
	if ( c > 0 && l == 4 ) {
		if ( B[l][c-1] != 2 ) return 0;
	}
	if ( l == 4 && c == 4 ) {
		if ( B[l][c] != 2 ) return 0;
	}
	return 1;
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

void recur ( int l, int c, int count ) 
{
	int b[5][5];
	int i, j, nl = l, nc = c + 1;
	for ( i = 0; i < 5; i ++ ) {
		for ( j = 0; j < 5; j ++ ) {
			b[i][j] = B[i][j];
		}
	}
	if ( nc > 4 ) { nc = 0; nl ++; }
	for ( i = 0; i < 3; i ++ ) {
		if ( Min <= count + i ) break;
		if ( i != 0 ) { colorchange( l, c ); }
//		display();
		if ( is_ok( l, c ) ) {			
			if ( l == 4 && c == 4 ) {
				if ( Min > count + i ) {
					Min = count + i;
				}
//       		cout << Min;	display();
				break;
			} else {
				recur ( nl, nc, count + i );
			}
		}
	}
	for ( i = 0; i < 5; i ++ ) {
		for ( j = 0; j < 5; j ++ ) {
			B[i][j] = b[i][j];
		}
	}
}

void process()
{
	recur ( 0, 0, 0 ); 
}

void output()
{
	if ( Min == 2000000000 ) out << "impossible";
	else out << Min;
}

void main()
{
	input();
	process();
	output();
}