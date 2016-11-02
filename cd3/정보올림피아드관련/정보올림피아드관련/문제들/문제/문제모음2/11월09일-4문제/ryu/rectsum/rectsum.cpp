#include <fstream.h>
#include <stdlib.h>
#include <time.h>

#define Nx 500

int N, Tb[Nx][Nx], R;

ifstream in ("rectsum10.in");
ofstream out("rectsum10.out");

void input()
{
	int i, j, tmp;
	in>>N;
	for(i=0; i<N; i++) in>>Tb[0][i];
	for(i=1; i<N; i++){
		for(j=0; j<N; j++){
			in>>tmp;
			Tb[i][j]=Tb[i-1][j]+tmp;
		}
	}
}

void process()
{
	int i, j, k, max, tmp;
	max=Tb[0][0]; 
	for(tmp=0, i=0; i<N; i++){
		if(tmp>0) tmp+=Tb[0][i];
		else tmp=Tb[0][i];
		if(max<tmp)max=tmp;
	}
	for(i=1; i<N; i++){
		for(j=i; j<N; j++){
			for(tmp=0, k=0; k<N; k++) {
				if(tmp>0) tmp+=Tb[j][k]-Tb[i-1][k];
				else tmp=Tb[j][k]-Tb[i-1][k];
				if(max<tmp)max=tmp;
			}
		}
	}
	R=max;	
}

void output()
{
	out<<R;
}

void datagen()
{
	int i, j, n=500;
	ofstream out2("rectsum10.in");
	srand((unsigned) time(NULL));
	out2<<n<<endl;
	for(i=0; i<n; i++){
		if(i!=0)out2<<endl;
		for(j=0; j<n; j++){
			if(j!=0)out2<<" ";
			out2<<rand()%19-9;
		}
	}
}

void main() 
{
//	datagen();
	input();
	process();
	output();
}
