#include <fstream.h>

#define MAX(a,b) (((a)>(b))?(a):(b))
#define MIN(a,b) (((a)<(b))?(a):(b))

#define Max 5

ifstream in  ( "gnome.in"  );
ofstream out ( "gnome.out" );

int N, Result;
int Input[Max*Max][4], Visit[Max*Max];
int B[Max][Max][4], R[Max][Max];

void inp ()
{
	int i, j;
	in >> N;
	for ( i = 0; i < N*N; i ++ ) {
		for ( j = 0; j < 4; j ++ ) {
			in >> Input[i][j];
		}
	}			
}

int isok ( int l, int c )
{
	int i, j, x, y, ret;
	for ( i = 0; i < N*N; i ++ ) {
		if ( Visit[i] ) continue;
		for ( j = 0; j < 4; j ++ ) {
			B[l][c][j] = Input[i][j];
		}
		y = l-1; x = c-1;
		if ( y >= 0 ) {
			if ( B[y][c][2] != B[l][c][0] ) continue;		
		}
		if ( x >= 0 ) {
			if ( B[l][x][1] != B[l][c][3] ) continue;
		}
		if ( l == N-1 && c == N-1 ) {
			R[l][c] = i;
			return 1;
		}
		y = l; x = c + 1;
		if ( x > N-1 ) { y ++; x = 0; } 
		Visit[i] = 1;
		ret = isok ( y, x );
		Visit[i] = 0;
		if ( ret ) {
			R[l][c] = i;
			return 1;
		}
	}
	return 0;
}	

void proc()
{
	if ( isok ( 0, 0 ) ) Result = 1;
}

void oup()
{
	int i, j;
	for ( i = 0; i < N; i ++ ) {
		if ( i != 0 ) out << endl;
		for ( j = 0; j < N; j ++ ) {
			if ( j != 0 ) out << " ";
			out << R[i][j] + 1;
		}
	}
}

void main()
{
	inp();
	proc();
	oup();
}