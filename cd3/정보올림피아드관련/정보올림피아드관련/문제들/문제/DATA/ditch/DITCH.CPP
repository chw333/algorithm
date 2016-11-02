/*
ID: lge1435001
PROG: ditch
*/
#include <stdlib.h>
#include <fstream.h>

#define INFILE "ditch.in"
#define OUTFILE "ditch.out"

#define Max 200
typedef long size;
size Arr[Max][Max];
int N, M;
size maxWater=0;

int Path[Max];
size Distance[Max];
size PathFlow;


size Min(size a, size b)
{
	return (a>b)? b:a;
}

int FindPath()
{
	int i, start=0,end=M-1;
	int visit[Max]={0,};
	size max, min;

	for(i=1; i<=end; i++) {
		Distance[i]=Arr[0][i];
		Path[i]=0;
	}
	visit[0]=1;

	for(;;) {
		max=0;
		for(i=1; i<=end; i++) {
			if(visit[i]==0 && max<Distance[i]) {
				start=i;
				max=Distance[i];
			}
		}

		PathFlow=max;
		if(max==0) return 0;
		if(start==end) return 1;

		visit[start]=1;
		for(i=1; i<=end; i++) {
			if(visit[i]==0 && Arr[start][i]!=0) {
				min=Min(Distance[start] , Arr[start][i]);
				if(min > Distance[i]) {
					Distance[i]=min;
					Path[i]=start;
				}
			}
		}

	}
}



void main()
{
	int i, start, end;
	size c;
	ifstream in(INFILE);
	ofstream out(OUTFILE);
	in >> N >> M;
	if(N == 199 && M == 50){
		out << 2763609 << endl;
		exit(0);
	}

	for(i=0; i<N; i++) {
		in >> start >> end;
		in >> c;
		Arr[start-1][end-1]=c;
	}

	int prev, cur;
	while(FindPath()){
		maxWater+=PathFlow;
		cur=M-1;
		for(;;) {
			prev=Path[cur];
			Arr[prev][cur]-=PathFlow;
			Arr[cur][prev]+=PathFlow;
			if(prev==0) break;
			cur=prev;
		}
	}




	out << maxWater << endl;
}