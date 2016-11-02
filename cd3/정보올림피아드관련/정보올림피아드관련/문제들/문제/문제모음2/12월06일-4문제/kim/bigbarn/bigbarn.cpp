/*
ID: cee09001
PROG: bigbarn
*/

#include <fstream.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <iomanip.h>

#define MAXN 1000

int N, T;
int Area[MAXN+1][MAXN+1];
int D[MAXN+1][MAXN+1][3];


#define INFILE "bigbarn14.in"
#define OUTFILE "bigbarn14.out"

int min(int a, int b, int c)
{
	if(a > b) {
		a=b;
	}
	if(a > c) {
		a=c;
	}
	return a;
}


void main()
{
	int i, j, x, y;
	ifstream in(INFILE);

	in >> N >> T;
	for(i=0; i<T; i++) {
		in >> y >> x;
		Area[y][x]=1;
	}

	//다이나믹 계산
	int max=0;
	for(i=1; i<=N; i++) {
		for(j=1; j<=N; j++) {
			if(Area[i][j]==1) {
				D[i][j][0]=0;
				D[i][j][1]=0;
				D[i][j][2]=0;
			} else {
				D[i][j][0]=D[i][j-1][0]+1;
				D[i][j][1]=D[i-1][j][1]+1;
				D[i][j][2]=min(D[i][j][0], D[i][j][1], D[i-1][j-1][2]+1);
				if(max < D[i][j][2]) {
					max=D[i][j][2];
				}
			}
		}
	}

	ofstream out(OUTFILE);
	out << max << endl;
}

