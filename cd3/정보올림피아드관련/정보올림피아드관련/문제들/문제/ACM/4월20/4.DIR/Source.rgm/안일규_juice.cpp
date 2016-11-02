#include<fstream.h>

#define MAX 32000

int N;
int limit;
int D[10002],L[10002],W[10002],V[10002];

void init()
{
	int a,b;
	int i;
	ifstream in("juice.in");
	in >> a >> b;
	limit=b-a;
	in >> N;
	for(i=0; i<N; i++){
		in >> L[i] >> W[i];
	}
}

void process()
{
	int i,j;

	for(i=1; i<=limit; i++){
		D[i]=MAX;
		V[i]=-1;
		for(j=0; j<N; j++){
			if(i>=W[j]){
				if(D[i]>D[i-W[j]]+L[j]){
					D[i]=D[i-W[j]]+L[j];
					V[i]=i-W[j];
				}
			}
		}
	}
}

void output()
{
	ofstream out("juice.out");

	if(V[limit]==-1) out << "impossible";
	else out << D[limit];
}

void main()
{
	init();
	process();
	output();
}