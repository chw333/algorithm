#include <fstream.h>
#include <string.h>
#include <iomanip.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <conio.h>
#include <iomanip.h>


#define MAXN 600
#define INFINIT 1000000

int N; 
int Cost[MAXN][MAXN];
int Assign[MAXN][MAXN];
int Opportunity[MAXN][MAXN];
int Supply[MAXN], Demand[MAXN];


#define INFILE "transport.in"
#define OUTFILE "transport.out"


#define MAKEN 600
#define RANGE 800

void makedata()
{
	srand(time(NULL));
	ofstream out(INFILE);
	out << MAKEN;
	
}





void print()
{
	int i,j;
	for(i=0; i<N; i++) {
		for(j=0; j<N; j++) {
			cout << setw(4) << Assign[i][j];
		}
		cout << "| " << Supply[i];
		cout << endl;
	}
	cout << "-------------" << endl;
	for(i=0; i<N; i++) {
		cout << setw(4) << Demand[i];
	}
	cout << endl;
}


void degen()
{
	int i,j;
	int assigncnt=0;
	for(i=0; i<N; i++) {
		for(j=0; j<N; j++) {
			if(Assign[i][j]>0) {
				assigncnt++;
			}
		}
	}
	int x, y, min=INFINIT;
	while(1) {
		if(assigncnt==N+N-1) break;
		assigncnt++;
		for(i=0; i<N; i++) {
			for(j=0; j<N; j++) {
				if(Cost[i][j]<min && Assign[i][j]==-1) {
					y=i;
					x=j;
					min=Cost[i][j];
				}
			}
		}
		Assign[y][x]=0;
	}
}



void transport()
{
	int i,j;
	ifstream in(INFILE);

	//0. ���� �б�.
	in >> N;
	for(i=0; i<N; i++) {
		for(j=0; j<N; j++) {
			in >> Cost[i][j];
		}
	}
	for(i=0; i<N; i++) {
		in >> Supply[i];
	}
	for(i=0; i<N; i++) {
		in >> Demand[i];
	}

	//1. �ϼ��ڳ� ��븸���.
	int num;
	int dem[MAXN];
	for(i=0; i<N; i++) {
		dem[i]=Demand[i];
	}

	for(i=0; i<N; i++) {
		num=Supply[i];
		for(j=0; j<N; j++) {
			if(num <= dem[j]) {
				Assign[i][j]=num;
				dem[j]-=num;
				num=0;
			} else {
				Assign[i][j]=dem[j];
				num-=dem[j];
				dem[j]=0;
			}
			
		}
	}
	
	print();

	//2. �������.
	int ri[MAXN], ki[MAXN];
	int assigncnt, sw;
	while(1) {
		//2-1. ��ȸ�����
		for(i=0; i<N; i++) {
			for(j=0; j<N; j++) {
				if(Assign[i][j]==0) Assign[i][j]=-1;
			}
		}
	
		//2-2. ��ȭ�ظ� �����ط� �ٲ�.
		degen();

		//2-3. ri�� ki���� ����.
		//     �ּ� �����ظ� ����.
		
		for(i=0; i<N; i++) {
			ri[i]=-1;
			ki[i]=-1;
		}
		ri[0]=0;
		sw=0;
		while(1) {
			if(sw

		}

	}
	
	

	ofstream out(OUTFILE);
}


void main()
{
	//makedata();
	transport();
}