#include <fstream.h>
#include <stdlib.h>

#define Nx 100000

ifstream in ( "ancestors.in" );
ofstream out ( "ancestors.out" );

int N, Y, Z, Node[Nx+1];
int Path[2][Nx+1], Yi, Zi;

void input()
{
	int i, mother, child;
	in>>N;
	for(i=0; i<N-1; i++) {
		in>>mother>>child;
		Node[child]=mother;
	}
	in>>Y>>Z;
}

void process()
{
	int ancestor, i, tmp;
	ancestor=Path[0][Yi++]=Y;
	while(Node[ancestor]) {
		ancestor=Path[0][Yi++]=Node[ancestor];
	}
	for(i=0; i<Yi/2; i++) {
		tmp=Path[0][i];
		Path[0][i]=Path[0][Yi-i-1];
		Path[0][Yi-i-1]=tmp;
	}
	ancestor=Path[1][Zi++]=Z; 
	while(Node[ancestor]) {
		ancestor=Path[1][Zi++]=Node[ancestor];
	}
	for(i=0; i<Zi/2; i++) {
		tmp=Path[1][i];
		Path[1][i]=Path[1][Zi-i-1];
		Path[1][Zi-i-1]=tmp;
	}
}

void output()
{
	int i=0, tmp;
	while(Path[0][i]==Path[1][i]) {
		tmp = Path[0][i++];
	}
	out << tmp;
}

void main()
{
	input();
	process();
	output();
}