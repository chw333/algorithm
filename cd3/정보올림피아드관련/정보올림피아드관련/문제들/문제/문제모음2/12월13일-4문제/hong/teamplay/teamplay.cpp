#include <fstream.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <iomanip.h>

#define MMAX 30 // 최대 사람수
#define WMAX 160 // 최대 몸무게
#define WMIN 45 // 최소 몸무게

ifstream in("teamplay01.in");
ofstream out("teamplay01.out");

struct _t {
	int D[MMAX+1][WMAX*MMAX+1];
	int W[MMAX+1];
	int M; // 사람수
	int L; // 팀 격차 한계
	int HS; // 전체 몸무게의 반(반올림)
	double dHS; // 전체 몸무게의 반
	int A; // 답
} T[10]; // 팀 사례수
int N;


int sortf(const void *p, const void *q)
{
	int *a=(int *)p;
	int *b=(int *)q;
	return ((*a)-(*b));
}
void inp()
{
	int i, j;

	in >> N;
	for(i=0;i<N;i++) {
		in >> T[i].M;
		in >> T[i].L;
		for(j=0;j<T[i].M;j++) { in >> T[i].W[j]; T[i].HS+=T[i].W[j];}
		qsort(T[i].W,T[i].M,sizeof(int),sortf); 
		T[i].dHS=(double)T[i].HS/2;
		T[i].HS/=2;
	}
}

void oup()
{
	int i;
	
	for(i=0;i<N;i++) out << T[i].A << endl;
}

void proc(int t)
{
	int i,j,m,hs;
	double dhs, hl;

	dhs=T[t].dHS;
	hs=T[t].HS;
	hl=T[t].L/2;
	m=T[t].M;

	for(j=0;j<=hs;j++) {
		if(j>=T[t].W[0]) T[t].D[0][j]=T[t].W[0]; else T[t].D[0][j]=0;
	}
	for(i=1;i<m;i++) {
		for(j=0;j<=hs;j++) {
			if(j-T[t].W[i]>=0) {
				if(T[t].D[i-1][j]<T[t].D[i-1][j-T[t].W[i]]+T[t].W[i]) {
					T[t].D[i][j]=T[t].D[i-1][j-T[t].W[i]]+T[t].W[i]; 
				} else {
					T[t].D[i][j]=T[t].D[i-1][j];
				}
			} else {
				T[t].D[i][j]=T[t].D[i-1][j];
			}
		}
	}
	if(T[t].D[m-1][hs]<=dhs && T[t].D[m-1][hs]>=(dhs-hl)) T[t].A=1; else T[t].A=0;
}
/*
void makedata()
{
	int i,j;
	int mmax, gap, limit=10;
	srand((unsigned)time(NULL));
	out << limit << endl;
	for(j=0;j<limit;j++) {
		mmax=rand()%(MMAX-1)+2;
		out << mmax << endl;
		gap=rand()%(WMIN/2);
		out << gap << endl;
		for(i=0;i<mmax;i++) {
			out << rand()%(WMAX-WMIN)+WMIN << " ";
		}
		out << endl;
	}

}
*/
void main()
{
	int i;
//	makedata();

	inp();
	for(i=0;i<N;i++) proc(i);
	oup();

}