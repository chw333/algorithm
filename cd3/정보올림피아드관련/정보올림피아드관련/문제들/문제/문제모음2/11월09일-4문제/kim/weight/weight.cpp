#include <fstream.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAXN 1000

int N;
int SecondNum, EndNum;
int Flow[MAXN+MAXN+2][MAXN+MAXN+2],
    BkFlow[MAXN+MAXN+2][MAXN+MAXN+2];
int Visit[MAXN+MAXN+2];
int Path[MAXN+MAXN+2], PathCnt;

#define INFILE "weight10.in"
#define OUTFILE "weight10.out"



int findpath(int node)
{
	int i;
	Path[PathCnt]=node;
	PathCnt++;
	Visit[node]=1;
	if(node==EndNum) return 1;

	for(i=1; i<=EndNum; i++) {
		if(Visit[i]==0 && Flow[node][i]==1) {
			if( findpath(i) == 1) return 1;
		}
	}

	PathCnt--;
	return 0;
}

int ispower(int num)
{
	int v;
	v=2;
	for(;;) {
		if(v >= num) {
			if(num==v) return 1;
			return 0;
		}
		v=v*2;
	}
	return 0;
}



void main()
{
	int i, j;
	ifstream in(INFILE);
	in >> N;
	
	SecondNum=N+1;
	EndNum=N+N+1;
	for(i=1; i<=N; i++) {
		Flow[0][i]=1;
	}
	for(i=SecondNum; i<EndNum; i++) {
		Flow[i][EndNum]=1;
	}
	for(i=1; i<=N; i++) {
		for(j=1; j<=N; j++) {
			if( ispower(i+j) ==1) {
				Flow[i][N+j]=1;
			}
		}
	}

	//º¸°ü
	for(i=0; i<=EndNum; i++) {
		for(j=0; j<=EndNum; j++) {
			BkFlow[i][j]=Flow[i][j];
		}
	}


	//flow
	int start, end;
	int cnt=0;
	while(1) {
		for(i=0; i<=EndNum; i++) { Visit[i]=0; }
		PathCnt=0;
		if( findpath(0) ==0 ) break;
		cnt++;

		for(i=1; i<PathCnt; i++) {
			start=Path[i-1];
			end=Path[i];
			Flow[start][end]--;
			Flow[end][start]++;
		}
	}

	ofstream out(OUTFILE);
	if(cnt==N) {
		for(i=1; i<=N; i++) {
			for(j=N+1; j<EndNum; j++) {
				if( BkFlow[i][j]==1 && Flow[i][j]==0 ) {
					out << "(" << i << "," << j-N << ")" << endl;
				}
			}
		}
	} else {
		out << "no" << endl;
	}
}


