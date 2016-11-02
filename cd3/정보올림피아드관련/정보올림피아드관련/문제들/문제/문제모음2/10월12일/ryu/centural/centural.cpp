#include <fstream.h>
#include <math.h>

#define MaxN 500

ifstream in ( "centural10.in" );
ofstream out ("centural10.out" );

int N, X[MaxN], Y[MaxN];
double Dist[MaxN][MaxN];
int Min[2];

void input ()
{
	int i;
	in >> N;
	for ( i = 0; i < N; i ++ ) {
		in >> X[i] >> Y[i];
	}
}

void getdist ()
{
	int i, j;
	for ( i = 0; i < N - 1; i ++ ) {
		for ( j = i + 1; j < N; j ++ ) {
			Dist[j][i] = Dist[i][j] = sqrt ( pow(X[i]-X[j], 2) + pow(Y[i]-Y[j], 2) );   
		}
	}
}

void process ()
{
	int i, j, k;
	double maxa[2], maxb[2], Max, min = 999999999;
	getdist();
	for ( i = 0; i < N-1; i ++ ) {
		for ( j = i+1; j < N; j ++ ) {
			maxa[0] = maxa[1] = maxb[0] = maxb[1] = 0;
			for ( k = 0; k < N; k ++ ) {
				if ( i == k || j == k ) continue;
				if ( Dist[i][k] < Dist[j][k] ) {
					if ( maxa[0] < Dist[i][k] ) {
						maxa[1] = maxa[0];
						maxa[0] = Dist[i][k];
					} else if ( maxa[1] < Dist[i][k] ) {
						maxa[1] = Dist[i][k];
					}
				} else {
					if ( maxb[0] < Dist[j][k] ) {
						maxb[1] = maxb[0];
						maxb[0] = Dist[j][k];
					} else if ( maxb[1] < Dist[j][k] ) {
						maxb[1] = Dist[j][k];
					}
				}
			}
			Max = Dist[i][j] + maxa[0] + maxb[0];
			if ( Max < maxa[0] + maxa[1] ) Max = maxa[0] + maxa[1];
			if ( Max < maxb[0] + maxb[1] ) Max = maxb[0] + maxb[1];
			if ( min > Max ) {
				min = Max; 
				Min[0] = i + 1; Min[1] = j + 1;
			}
		}
	}				
}

void output ()
{
	out << Min[0] << " " << Min[1];
}

void main ()
{
	input();
	process();
	output();
}