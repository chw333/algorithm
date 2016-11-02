#include <fstream.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <iomanip.h>

#define MAXN 100
#define Dr 6

int N;
int Value[MAXN][3];
int Dy[MAXN+1][Dr];
int Path[MAXN+1][Dr];

int Shape[Dr][3]={
	0, 1, 2, //0(○△Ⅹ)
	0, 2, 1, //1(○Ⅹ△)
	1, 0, 2, //2(△○Ⅹ)
	1, 2, 0, //3(△Ⅹ○)
	2, 0, 1, //4(Ⅹ○△)
	2, 1, 0, //5(Ⅹ△○)
};
int ShapeIdx[Dr][3]={
	0, 1, 2, //0(○△Ⅹ)
	0, 2, 1, //1(○Ⅹ△)
	1, 0, 2, //2(△○Ⅹ)
	2, 0, 1, //3(△Ⅹ○)
	1, 2, 0, //4(Ⅹ○△)
	2, 1, 0, //5(Ⅹ△○)
};
int ShapeNum[Dr][2]={
	3, 4,
	2, 5,
	1, 5,
	0, 4,
	0, 3,
	1, 2,
};

#define INFILE "playboard10.in"
#define OUTFILE "playboard10.out"

#define MAKEN 100 //최대 100이하.
#define RANGE 500 //최대 500이하.

void makedata()
{
	ofstream out(INFILE);
	out << MAKEN << endl;

	srand(time(NULL));
	int i,j, v;
	for(i=0; i<MAKEN; i++) {
		for(j=0; j<3; j++) {
			v=rand()%RANGE+1;
			if(j!=0) out << " ";
			out << v;
		}
		out << endl;
	}
}



void print()
{
	int i,j;
	int path[MAXN+1], pos;
	char shape[MAXN+1][16]={
	  "○△Ⅹ",
	  "○Ⅹ△",
	  "△○Ⅹ",
	  "△Ⅹ○",
	  "Ⅹ○△",
	  "Ⅹ△○",
	};
	
	int max, maxidx;
	for(i=0; i<Dr; i++) {
		if(max < Dy[N][i] ) {
			max=Dy[N][i];
			maxidx=i;
		}
	}
	path[N]=maxidx;
	for(i=N-1; i>=1; i--) {
		pos=path[i+1];
		path[i]=Path[i+1][pos];
	}

	for(i=1; i<=N; i++) {
		for(j=0; j<Dr; j++) {
			cout << setw(3) << Dy[i][j];
		}
		cout << " ";
		for(j=0; j<Dr; j++) {
			cout << setw(3) << Path[i][j];
		}
		cout << " ";
		cout << shape[ path[i] ];
		cout << endl;
	}
	cout << endl;
}


void playboard()
{
	int i, j;
	ifstream in(INFILE);

	in >> N;
	for(i=0; i<N; i++) {
		in >> Value[i][0] >> Value[i][1] >> Value[i][2];
	}


	//Dr의 정의
	//0(○△Ⅹ) 1(○Ⅹ△) 2(△○Ⅹ) 3(△Ⅹ○) 4(Ⅹ○△) 5(Ⅹ△○)
	int v, up_idx1, up_idx2;
	int plus, minus, pathnum;
	for(i=1; i<=N; i++) {
		for(j=0; j<Dr; j++) {
			up_idx1=ShapeNum[j][0];
			up_idx2=ShapeNum[j][1];
			
			v=Dy[i-1][up_idx1];
			pathnum=up_idx1;
			if(v < Dy[i-1][up_idx2]) {
				v=Dy[i-1][up_idx2];
				pathnum=up_idx2;
			}
			
			plus=ShapeIdx[j][0];
			minus=ShapeIdx[j][2];
			v+=Value[i-1][plus];
			v-=Value[i-1][minus];

			Dy[i][j]=v;
			Path[i][j]=pathnum;
		}
	}

	int max=-999;
	ofstream out(OUTFILE);
	for(i=0; i<Dr; i++) {
		if(max < Dy[N][i] ) {
			max=Dy[N][i];
		}
	}
	out << max;
	//print();
}


void main()
{
	//makedata();
	playboard();
}
