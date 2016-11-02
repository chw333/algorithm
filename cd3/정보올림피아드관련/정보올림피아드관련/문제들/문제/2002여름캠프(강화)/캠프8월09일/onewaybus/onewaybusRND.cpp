#include <fstream.h>
#include <time.h>
#include <stdlib.h>

#define OUTFILE "onewaybus10.in"
#define MAXN 101
const int A=84, B=2;
const int N=100, K=110;
const int Time=12;

int Arr[MAXN][MAXN];

void main()
{
	srand(time(NULL));

	ofstream out(OUTFILE);
	out << A << " " << B << endl;
	out << N << " " << K << endl;
	int i, j;
	int s, e, time;

	i=0;
	while(i<N) {
		s=rand()%N+1;
		e=rand()%N+1;
		time=rand()%Time+1;
		if(s==e) continue;

		if(Arr[s][e]==0 && Arr[e][s]==0) {
			Arr[s][e]=time;
			i++;
		}
	}
	while(i<K) {
		s=rand()%N+1;
		e=rand()%N+1;
		time=rand()%Time+1;

		if(Arr[s][e]==0) {
			Arr[s][e]=time;
			i++;
		}
	}

	int cnt=0;
	for(i=1; i<=N; i++) {
		for(j=1; j<=N; j++) {
			if(Arr[i][j]>0) {
				out << i << " " << j << " " << Arr[i][j] << endl;
				cnt++;
			}
		}
	}

	out << cnt << endl;

}

