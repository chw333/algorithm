#include <fstream.h>
#define End 1

ifstream in ("ladder.in");
ofstream out("ladder.out");

int n,Arr[1000];
int i,j,M,G,T,A[1000];
char c;

void main()
{
	in >> n;
	for(i=0;i<n-1;i++) {
		in >> Arr[i];
	}	
	for(i=0;i<n;i++) {
		A[i]=i+1;
	}

	// |  |  |--|
	// |--|  |  |
	// |  |--|  |
	// |  |  |  |
	for(i=0;i<n-1;i++) {
		M=999999;
		for(j=0;j<n-1;j++) {
			if(Arr[j]<M && Arr[j]!=0) {G=j;M=Arr[j];}
		}
		Arr[G]=0;
		T=A[G];
		A[G]=A[G+1];
		A[G+1]=T;		
	}
	for(i=0;i<n;i++) {
		for(j=0;j<n;j++) {
			if(A[j]==i+1) {c=65+j;out << i+1 << " " << c << endl;break;}
		}
	}
}

// j ¶û j+1 À» change
