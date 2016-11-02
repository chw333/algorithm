#include<fstream.h>

int D[100][100];
int Arr[100][100];
int N,M;

void process()
{
	char c;
	int i,j;
	ifstream in("animal.in");
	in >> M >> N;
	for(i=0; i<N; i++){
		for(j=0; j<M; j++){
			if(i==1 && j==1){
				int a=7;
			}
			in >> c;
			if(c=='#') Arr[i][j]=0;
			else Arr[i][j]=1;
			if(Arr[i-1][j]>Arr[i][j-1] && i-1>=0 && j-1>=0){
				D[i][j]=Arr[i][j]+D[i-1][j];
			}else if(Arr[i-1][j]<=Arr[i][j-1] && i-1>=0 && j-1>=0){
				D[i][j]=Arr[i][j]+D[i][j-1];
			}
		}
	}
}

void output()
{
	ofstream out("animal.out");
	out << D[N-1][M-1];
}

void main()
{
	process();
	output();
}