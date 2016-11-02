#include <fstream.h>
#include <stdio.h>

#define MAX 20

#define INFILE "updown10.in"
ofstream out ( "updown10.out" );

int N, Visit[MAX+1], Dvisit[2][MAX][MAX];
__int64 P, D[2][MAX+1][MAX+1];
int Path[MAX+1];

int H, L;

void input()
{
	FILE *fin = fopen ( INFILE, "r" );
	fscanf ( fin, "%d %I64d", &N, &P );
//	in >> N >> P;
	D[0][0][0] = 1;
	D[1][0][0] = 1;
	Dvisit[0][0][0] = 1;
	Dvisit[1][0][0] = 1;
}

void counting ( int p )
{
	int i;
	H = L = 0;
	for ( i = 1; i <= N; i ++ ) {
		if ( Visit[i] ) continue;
		if ( p < i ) L ++;
		else H ++;
	}
}

__int64 recur ( int p, int p_up, int path, int count )
{
	int i, h, l, up;
	__int64 ret = 0, tmp;
	counting ( p );
	h = H; l = L;
	if ( !path && Dvisit[p_up][h][l] ) return D[p_up][h][l];
	for ( i = 1; i <= N; i ++ ) {
		if ( Visit[i] ) continue;
		if ( p > i ) up = 0;
		else up = 1;
		if ( p_up == up ) continue;
		Visit[i] = 1;
		tmp = ret;
		ret += recur( i, up, 0, count+1 );
		Visit[i] = 0;
		if ( path && ret >= P ) { 
			out << " " << i;
			P -= tmp; 
			if ( count == N - 1 && P == 1 ) return 0;
			Visit[i] = 1;
			recur ( i, up, 1, count+1 );
			Visit[i] = 0;
			P += tmp;
			break; 
		}
	}
	if ( !path ) {
		D[p_up][h][l] = ret;
		Dvisit[p_up][h][l] = 1;
		return ret;
	} 
	return 0;
}

void process()
{
	int i;
	__int64 ret = 0, tmp;
	for ( i = 1; i <= N; i ++ ) {
		Visit[i] = 1; 
		tmp = ret;
		ret += recur ( i, 1, 0, 1 );
		if ( ret >= P ) { 
			out << i; 
			P -= tmp; 
			recur ( i, 1, 1, 1 ); 
			break; 
		}
		tmp = ret;
		ret += recur ( i, 0, 0, 1 );				
		if ( ret >= P ) { 
			out << i; 
			P -= tmp; 
			recur ( i, 0, 1, 1 ); 
			break; 
		}
		Visit[i] = 0;
	}
	if ( i == N + 1 ) out << "impossible";
}

void main()
{
	input();
	process();
}