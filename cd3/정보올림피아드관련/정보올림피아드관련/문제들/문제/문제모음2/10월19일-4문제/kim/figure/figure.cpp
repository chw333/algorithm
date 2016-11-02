#include <fstream.h>
#include <string.h>
#include <iomanip.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <conio.h>


#define MAXN 60
#define INFINIT 5000.1

int N1, N2; //N1은 남자의 수, N2는 여자의 수
float List1[MAXN+1], List2[MAXN+1];
float Dy[MAXN+1][MAXN+1][MAXN+1];
float Min;

#define INFILE "figure01.in" 
#define OUTFILE "figure01.out"

#define MAKEN1 200 //남자의 수
#define MAKEN2 200 //여자의 수
#define RANGE 80 //키의 범위
#define MUL 10 //키의 범위

void makedata()
{
	int i;
	double v;
	char str[100];
	srand(time(NULL));

	ofstream out(INFILE);
	out << MAKEN1 << " " << MAKEN2 << endl;
	for(i=0; i<MAKEN1; i++) {
		v=110.0 + (double)(rand()%RANGE*MUL);
		sprintf(str, "%.1f", v);
		out << str << endl;
	}
	for(i=0; i<MAKEN2; i++) {
		v=110.0 + (double)(rand()%RANGE*MUL);
		sprintf(str, "%.1f", v);
		out << str << endl;
	}
	
}

float calc(int start, int end, int num)
{
	int i;
	float min, v;
	min=INFINIT;
	for(i=start; i<=end; i++) {
		v=List2[i]-List1[num];
		if(v<0) v=-v;
		if(min > v) {
			min=v;
		}
	}
	return min;
}

float mf(int start, int end, int group)
{
	if( Dy[start][end][group] ) return Dy[start][end][group];

	float min,v;
	int num=N1-group+1; //남자의 번호 1번그룹은 남자1번 할당.
	int k, newend=end-group+1;
	if(group==1) {
		min=calc(start, end, num);
		Dy[start][end][group]=min;
		return min;
	}

	min=INFINIT;
	for(k=start; k<=newend; k++) {
		v=calc(start, k, num);
		v+=mf(k+1, end, group-1);
		if(min > v) {
			min=v;
		}
	}
	Dy[start][end][group]=min;
	return min;
}


int sortf(const void *a, const void *b)
{
	float *p=(float *)a, *q=(float *)b;
	if(*p > *q) return 1;
	if(*p < *q) return -1;
	return 0;
}

void figure()
{
	int i;
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

	Min=mf(1, N2, N1);


	ofstream out(OUTFILE);
	out << Min;
}

void main()
{
	//makedata();
	figure();
}