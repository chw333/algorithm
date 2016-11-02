#include <fstream.h>
#include <string.h>
#include <iomanip.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <conio.h>


#define MAXN 600
#define INFINIT 10000.1

int N1, N2; //N1은 남자의 수, N2는 여자의 수
double List1[MAXN+1], List2[MAXN+1];
double Dy[MAXN+1][MAXN+1];
double Min;

#define INFILE "figure10.in" 
#define OUTFILE "figure10.out"

#define MAKEN1 590 //남자의 수
#define MAKEN2 600 //여자의 수
#define RANGE 800 //키의 범위
#define MUL 1 //키의 범위

void makedata()
{
	int i;
	double v;
	char str[100];
	srand(time(NULL));

	ofstream out(INFILE);
	out << MAKEN1 << " " << MAKEN2 << endl;
	for(i=0; i<MAKEN1; i++) {
		v=110.0 + (double)((rand()%RANGE)*MUL)/10;
		sprintf(str, "%.1f", v);
		out << str << endl;
	}
	for(i=0; i<MAKEN2; i++) {
		v=110.0 + (double)((rand()%RANGE)*MUL)/10;
		sprintf(str, "%.1f", v);
		out << str << endl;
	}
	
}



void print()
{
	int i,j;
	for(i=1; i<=N1; i++) {
		for(j=1; j<=N2; j++) {
			cout << setw(5) << Dy[i][j];
		}
		cout << endl;
	}
	cout << endl;
}


int sortf(const void *a, const void *b)
{
	double *p=(double *)a, *q=(double *)b;
	if(*p > *q) return 1;
	if(*p < *q) return -1;
	return 0;
}

void figure()
{
	int i, j, k;
	ifstream in(INFILE);
	in >> N1 >> N2;
	for(i=1; i<=N1; i++) {
		in >> List1[i];
	}
	for(i=1; i<=N2; i++) {
		in >> List2[i];
	}

	qsort(&List1[1], N1, sizeof(List1[0]), sortf);
	qsort(&List2[1], N2, sizeof(List2[0]), sortf);

	//i세로는 그룹 / j가로는 여자 선수
	int m;
	double min, v;
	for(i=1; i<=N1; i++) {
		for(j=i; j<=N2; j++) {
			//Dy[i][j]는 i번째남자로 j번째 여자까지 고려했을 때의 최소값.
			//i번째 남자가 j번째 여자를 선택하면,
			//i-1번째 남자는 j-1번째 여자까지 선택할 수 있다.
			min=INFINIT;
			for(k=i-1; k<j; k++) {
				if(min > Dy[i-1][k]) {
					min=Dy[i-1][k];
				}
			}

			v=List2[j]-List1[i];
			if(v<0) v=-v;

			Dy[i][j]=min+v;
			//print();
		}
	}

	//print();

	ofstream out(OUTFILE);
	Min=INFINIT;
	for(i=N1; i<=N2; i++) {
		if(Min > Dy[N1][i]) {
			Min=Dy[N1][i];
		}
	}
	out << Min;
}

void main()
{
	//makedata();
	figure();
}