/*
ID: cee09001
PROG: stall4
*/

#include <fstream.h>

#define INFILE "piramid3.in"
#define OUTFILE "piramid3.out"

#define Max 202
typedef int size;
int Arr[Max][Max];
int N, M;
int maxWater=0;

int Path[Max];
int Distance[Max];
int PathFlow;

ifstream in(INFILE);
ofstream out(OUTFILE);


void print()
{
	int i,j;
	for(i=0; i<=N*N+1; i++) {
		for(j=0; j<=N*N+1; j++) {
			cout << Arr[i][j];
		}
		cout << endl;
	}
	cout << endl;
}

int Min(int a, int b)
{
	return (a>b)? b:a;
}

int FindPath()
{
	int i, start=0,end=N*N+1;
	int visit[Max]={0,};
	int max, min;

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
		if(start==end)
			return 1;

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

void init()
{
    int i, j, d, man, up, down, left, right;
    in >> N >> M;
    for(i=0;i<N;i++)
    {
        for(j=0;j<N;j++)
        {
			d=i*N+j+1;
			left=d-1;
			right=d+1;
			up=d-N;
			down=d+N;
			if(i>0) Arr[d][up]=1;
			if(i<N-1) Arr[d][down]=1;
			if(j>0) Arr[d][left]=1;
			if(j<N-1) Arr[d][right]=1;
            in >> man;
            if(man==1) Arr[0][d]=1; //from start point
            if(i==0 || i==N-1 || j==0 || j==N-1) Arr[d][N*N+1]=1; // to end point
        }
    }

	print();
	for(i=0;i<=N*N+1;i++){
		for(j=0;j<=N*N+1;j++) {
			out << Arr[i][j] << " ";
		}
		out << endl;
	}
}


void main()
{
	int i,j;
	int c;

	init();
	int prev, cur;
	while(FindPath()){
		maxWater+=PathFlow;
		cur=N*N+1;
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