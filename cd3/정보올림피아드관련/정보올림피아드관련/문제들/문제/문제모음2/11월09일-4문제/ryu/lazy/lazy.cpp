#include <fstream.h>
#include <stdlib.h>

#define Nx 100
#define Ax 250
#define Dx 250

ifstream in  ( "lazy.in" );
ofstream out ( "lazy.out" );

int N, J[Nx][3], V[Nx], Result;

void input()
{
	int i;
	in>>N;
	for(i=0; i<N; i++) {
		in>>J[i][0]>>J[i][1]>>J[i][2];
	}
}

int process(int t)
{
	int i, min=2000000000, tmp;
	if(t==Dx) return 0; 
	for(i=0; i<N; i++) {
		if(V[i]==0 && t>=J[i][1] && t<=J[i][2]-J[i][0]) {
			V[i]=1;
			tmp=process(t+J[i][0])+J[i][0];
			V[i]=0;
			if(min>tmp)min=tmp;
		}
	}	
	if(min==2000000000) {
		min=process(t+1);
	}
	return min;
}

void output()
{
	out<<Result;
}

void main()
{
	input();
	Result=process(0);
	output();
}