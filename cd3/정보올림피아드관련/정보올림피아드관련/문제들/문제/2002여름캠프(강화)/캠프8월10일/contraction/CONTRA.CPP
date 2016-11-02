#include <fstream.h>
#include <math.h>

#define INFILE  "contra14.in"
#define OUTFILE "contra14.out"
#define Min    -2000000000

#define Max 20

int N, M;
int Node[Max];
int Edge[Max][Max];
int D[1048576*2];

void input ( )
{
	char c;
	int i, a, b;
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
		Edge[a][b] = Edge[b][a] = (int) c;
	}
	for ( i = 0; i < 1048576*2; i ++ ) {
		D[i] = Min;
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
				g += pow ( 2, i );
				break;
			}
		}
	}
	return g;
}

int recur( int edge[Max][Max], int *a, int *b )
{
	int branch[Max][Max];
	int s, e, ta1, tb1, ta2, tb2, g;
	int i, j, c, gl, gr, tmp, max = Min, sw = 1;
	g = calDpos ( edge );
	if ( D[g] != Min ) return D[g];
	for ( i = 0; i < N - 1; i ++ ) {
		for ( j = i + 1; j < N; j ++ ) {
			if ( !edge[i][j] ) continue;
			sw = 0;
			c = edge[i][j];
			edge[i][j] = edge[j][i] = 0;

			init ( branch );
			if ( -1 == dfs ( edge, i, branch ) ) gl = Node[i]; 
			else gl = recur( branch, &ta1, &tb1 );

			init ( branch );
			if ( -1 == dfs ( edge, j, branch ) ) gr = Node[j];
			else gr = recur( branch, &ta2, &tb2 );

			edge[i][j] = edge[j][i] = c;
			if ( c == '*' ) tmp = gl * gr;
			else tmp = gl + gr;
			if ( tmp > max ) {
				s = i, e = j;
				max = tmp;
			}
		}
	}
	D[g] = max;
	*a = s; *b = e;
	return max;
}

void process ()
{
	int a, b;
	M = recur ( Edge, &a, &b );
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