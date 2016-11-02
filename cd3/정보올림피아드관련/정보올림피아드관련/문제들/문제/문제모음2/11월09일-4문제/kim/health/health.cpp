#include <fstream.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAXN 10
#define MAXIDX 10000
#define INFINIT 100000

int T, N;
int List[MAXN], SortList[MAXN];
int Index[MAXIDX+1];

#define INFILE "health10.in"
#define OUTFILE "health10.out"

#define MAKET 10
int MAKEN[10]={
	65, 1000, 1000, 1000, 147, 425, 11, 1000, 1000, 1000
};
int RANGE[10]={
	10000, 1300, 2000, 10000, 10000, 10000, 10000, 10000, 10000, 10000
};
int MakeIndex[MAXIDX+1];


void makedata()
{
	int i,j,v;
	srand(time(NULL));
	ofstream out(INFILE);
	out << MAKET << endl;
	for(i=0; i<MAKET; i++) {
		out << MAKEN[i] << endl;
		for(j=0; j<=MAXIDX; j++) {
			MakeIndex[j]=0;
		}
		j=0;
		while(j<MAKEN[i]) {
			v=rand()%RANGE[i]+1;
			if( MakeIndex[v]==0) {
				MakeIndex[v]=1;
				if(j!=0) out << " ";
				out << v;
				j++;
			}
		}
		out << endl;
	}
}



int sortf(const void *a, const void *b)
{
	int *p=(int *)a, *q=(int *)b;
	return *p-*q;
}

int health()
{
	int i, idx;
	int value;
	int sum=0, startvalue;
	for(i=0; i<N; i++) {
		if(SortList[i]!=List[i]) {
			startvalue=SortList[i];
			idx= Index[startvalue];
			value=SortList[idx];
			while(1) {
				List[idx]=value;
				sum+=value;

				idx = Index[value];
				value= SortList[idx];
				if( idx==i ) break;
			}
			List[i]=startvalue;
			sum+=startvalue*2;
		}
	}
	return sum;
}


void main()
{
	makedata();

	ifstream in(INFILE);
	ofstream out(OUTFILE);
	int i, j;
	in >> T;
	for(i=0; i<T; i++) {
		in >> N;
		for(j=0; j<N; j++) {
			in >> List[j];
			SortList[j] = List[j];
			Index[ List[j] ] =j;
		}
		qsort(SortList, N, sizeof(SortList[0]), sortf);
		if(i!=0) out << endl;
		out << health();
	}
}
