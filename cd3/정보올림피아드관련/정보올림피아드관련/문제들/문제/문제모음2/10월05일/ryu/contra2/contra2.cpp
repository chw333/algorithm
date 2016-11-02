#include <fstream.h>
#include <math.h>

#define INFILE  "contra201.in"
#define OUTFILE "contra201.out"
#define Min    -2000000000
#define Maxx    2000000000

#define Max 20

int N, M;
int Node[Max];
int Edge[Max][Max];
char D[1048576][102];

void input ( )
{
	int i, a, b, c;
	ifstream in ( INFILE );
	in >> N;
	for ( i = 0; i < N; i ++ ) {
		in >> a >> b;
		a --; 
		Node[a] = b;
	}
	for ( i = 0; i < N - 1; i ++ ) {
		in >> a >> b >> c;
		a --; b --;
		Edge[a][b] = Edge[b][a] = c;
	}
}

void init ( int branch[Max][Max] )
{
	int i, j;
	for ( i = 0; i < N; i ++ ) {
		for ( j =0; j < N; j ++ ) {
			branch[i][j] = 0;
		}
	}
}

int dfs ( int edge[Max][Max], int p, int branch[Max][Max] )
{	
	int i, ret = -1;
	for ( i = 0; i < N; i ++ ) {
		if ( edge[p][i] && !branch[p][i] ) {
			ret = 0;
			branch[p][i] = branch[i][p] = edge[p][i];
			dfs ( edge, i, branch );
		}
	}
	return ret;
}

int calDpos ( int edge[Max][Max] )
{
	int i, j, g = 0;
	for ( i = 0; i < N; i ++ ) {
		for ( j = 0; j < N; j ++ ) {
			if ( edge[i][j] ) {
				g += (int)pow ( 2, i );
				break;
			}
		}
	}
	return g;
}

int recur( int edge[Max][Max] )
{
	int branch[Max][Max];
	int i, j, k, l, c, g, gl, gr, tmp;
	g = calDpos ( edge );
	if ( !D[g][101] ) {
		for ( i = 0; i < N - 1; i ++ ) {
			for ( j = i + 1; j < N; j ++ ) {
				if ( !edge[i][j] ) continue;
				c = edge[i][j];
				edge[i][j] = edge[j][i] = 0;
				init ( branch );
				tmp = dfs ( edge, i, branch );
				if ( tmp == -1 ) {
					gl = (int) pow ( 2, i );
					if ( D[gl][101] == 0 ) {
						D[gl][101] = 1;
						D[gl][Node[i]] = 1;
					}
				} else {
					gl = recur( branch );
				}
				init ( branch );
				tmp = dfs ( edge, j, branch );
				if ( tmp == -1 ) {
					gr = (int) pow ( 2, j );
					if ( D[gr][101] == 0 ) {
						D[gr][101] = 1;
						D[gr][Node[j]] = 1;
					}
				} else {
					gr = recur( branch );
				}
				edge[i][j] = edge[j][i] = c;
				for ( k = 0; k <= 100; k ++ ) {
					if ( D[gl][k] )
					for ( l = 0; l <=100; l ++ ) {
						if ( D[gr][l] ) {
							D[g][(k + l) % c] = 1; 
						}
					}
				}
			}
		}
		D[g][101] = 1;
	}
	return g;
}

void process ()
{
	int i, g, max = Min;
	g = recur ( Edge );
	for ( i = 0; i <= 100; i ++ ) {
		if ( D[g][i] && max < i ) {
			max = i;
		}
	}
	M = max;
}

void output()
{
	ofstream out ( OUTFILE );
	out << M;
}

void main()
{
	input();
	process();
	output();
}