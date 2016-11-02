#include <fstream.h>
#include <math.h>

#define INFILE  "bridge.in"
#define OUTFILE "bridge.out"
#define Max 1400
#define BIG    2000000000

int C[Max][2];
int D[Max][Max];
char W[Max][Max];
int N, M, Lmax;
int S, E, Min;

void input()
{
	int i, j, a, b, x1, y1, x2, y2;
	ifstream in ( INFILE );
	in >> N >> M >> Lmax;
	Min = BIG;
	for ( i = 0; i < N; i ++ ) {
		for ( j = 0; j < N; j ++ ) {
			D[i][j] = BIG;
		}
	}
	for ( i = 0; i < N; i ++ ) {
		in >> a >> b;
		C[i][0] = a; C[i][1] = b;
	}
	for ( i = 0; i < M; i ++ ) {
		in >> a >> b;
		x1 = C[a-1][0]; y1 = C[a-1][1];
		x2 = C[b-1][0]; y2 = C[b-1][1];
		W[a-1][b-1] = W[b-1][a-1] = 1;
		D[a-1][b-1] = D[b-1][a-1] = sqrt( (x1-x2)*(x1-x2) + (y1-y2)*(y1-y2) );
	}
}

void floyd()
{
	int i, j, k, a, b;
	for ( k = 0; k < N; k ++ ) {
		for ( i = 0; i < N; i ++ ) {
			for ( j = 0; j < N; j ++ ) {
				if ( D[i][k] != BIG && D[k][j] != BIG ) {
					a = D[i][j]; 
					b = D[i][k] + D[k][j];
					D[i][j] = (a<b)?a:b;
				}
			}
		}
	}
	Min = D[0][1] + D[0][2];
}

void process()
{
	int i, j, x1, y1, x2, y2, dis, dis1, dis2, dishome, dishakwon, g;
	floyd();
	for ( i = 0; i < N; i ++ ) {
		for ( j = 0; j < N; j ++ ) {
			if ( W[i][j] || i == j ) continue;
			x1 = C[i][0]; y1 = C[i][1];
			x2 = C[j][0]; y2 = C[j][1];
			dis = sqrt( (x1-x2)*(x1-x2) + (y1-y2)*(y1-y2) );
/* 1 to 2 */
			dis1 = D[0][i] + dis + D[j][1];
			dis2 = D[0][j] + dis + D[i][1];
			dishome = (dis1<dis2)?dis1:dis2;
			if ( dishome >= D[0][1] ) continue;
/* 1 to 3 */
			dis1 = D[0][i] + dis + D[j][2];
			dis2 = D[0][j] + dis + D[i][2];
			dishakwon = (dis1<dis2)?dis1:dis2;
			if ( dishakwon >= D[0][2] ) continue;

			g = dishome + dishakwon;
			if ( Min > g) {
				Min = g;
				S = ((i<j)?i:j) + 1;
				E = ((i>j)?i:j) + 1;
			}	
		}
	}
}

void output()
{
	ofstream out ( OUTFILE );
	if ( Min == D[0][1] + D[0][2] ) {
		out << "0 0";
	} else {
		out << S << " " << E;
	}
}

void main()
{
	input();
	process();
	output();
}