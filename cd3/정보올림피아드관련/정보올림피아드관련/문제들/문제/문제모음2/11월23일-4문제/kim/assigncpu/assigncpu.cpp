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
int Arr[MAXN][MAXN];
int Value;

int FlowN;
int Flow[MAXN+MAXN+2][MAXN+MAXN+2], 
    FlowVisit[MAXN+MAXN+2];
int Path[MAXN+MAXN+2], PathVisit[MAXN+MAXN+2];
int PathCnt, FlowCnt;

#define INFILE "assigncpu10.in"
#define OUTFILE "assigncpu10.out"


#define MAKEN 600
#define RANGE 800

void makedata()
{
	int i,j,v;
	srand(time(NULL));
	ofstream out(INFILE);
	out << MAKEN;
	for(i=0; i<MAKEN; i++) {
		out << endl;
		for(j=0; j<MAKEN; j++) {
			v=rand()%RANGE+1;
			if(j!=0) out << " ";
			out << v;
		}
	}
}





void print()
{
	int i,j;
	for(i=0; i<N; i++) {
		for(j=0; j<N; j++) {
			cout << setw(3) << Arr[i][j];
		}
		cout << endl;
	}
	cout << endl;
}


void flood(int node)
{
	FlowVisit[node]=1;
	int i;
	for(i=1; i<=FlowN; i++) {
		if(FlowVisit[i]==0 && Flow[node][i]!=0) {
			flood(i);
		}
	}
}

int path_finder(int node, int level)
{
	Path[level]=node;
	PathVisit[node]=1;
	if(node==FlowN) {
		PathCnt=level+1;
		return 1;
	}

	int i;
	for(i=1; i<=FlowN; i++) {
		if(PathVisit[i]==0 && Flow[node][i]==1) {
			if(path_finder(i, level+1)==1) return 1;
		}
	}
	return 0;
}


void assigncpu()
{
	int i,j;
	int min, num;
	ifstream in(INFILE);

	in >> N;
	for(i=0; i<N; i++) {
		in >> num;
		for(j=0; j<N; j++) {
			in >> Arr[i][j];
		}
	}

	//1. �ּ� �迭�� ����.
	//1-1. �໩��
	for(i=0; i<N; i++) {
		//�ּҰ����ϱ�
		min=Arr[i][0];
		for(j=1; j<N; j++) {
			if(min > Arr[i][j]) {
				min=Arr[i][j];
			}
		}
		//�໩��
		for(j=0; j<N; j++) {
			Arr[i][j]-=min;
		}
		Value+=min;
	}
	//1-2. ������
	for(i=0; i<N; i++) {
		//�ּҰ����ϱ�
		min=Arr[0][i];
		for(j=1; j<N; j++) {
			if(min > Arr[j][i]) {
				min=Arr[j][i];
			}
		}
		//������
		for(j=0; j<N; j++) {
			Arr[j][i]-=min;
		}
		Value+=min;
	}


	
	int start, end;
	int row[MAXN], col[MAXN];

	while(1) {

		//print();

		//2. 0�� ����� ������ N���� �Ǹ� ����.
		FlowN=N+N+1;

		//2-1. ��Ʈ��ũ �÷� �ʱ�ȭ.
		for(i=0; i<FlowN; i++) {
			for(j=0; j<FlowN; j++) {
				Flow[i][j]=0;
			}
		}
		for(i=1; i<=N; i++) {
			Flow[0][i]=1;
			for(j=0; j<N; j++) {
				if(Arr[i-1][j]==0) {
					Flow[i][N+1+j]=1;
				}
			}
		}
		for(i=N+1; i<FlowN; i++) {
			Flow[i][FlowN]=1;
		}

		FlowCnt=0;
		while(1) {

			//2-2. Ȯ���� ã��.
			for(i=0; i<=FlowN; i++) {
				PathVisit[i]=0;
			}
			if(path_finder(0, 0)==0) break;
			FlowCnt++;

			//2-3. ��� ����
			for(i=1; i<PathCnt; i++) {
				start=Path[i-1];
				end=Path[i];

				Flow[start][end]-=1;
				Flow[end][start]+=1;
			}
		}

		//3. 0�� ����� ����(FlowCnt)�� N�̸� ��.
		//   �ƴϸ�, �迭�� 0�� �ƴ� �ּҰ��� ã�� �ּҹ迭���� ����
		if(FlowCnt==N) break;

		//3-1. 0�� ����� ���� ã��
		//     ��迭, ���迭�� ����.
		for(i=0; i<N; i++) {
			row[i]=0;
			col[i]=0;
		}
		// flood fill
		for(i=0; i<=FlowN; i++) {
			FlowVisit[i]=0;
		}
		flood(0);
		// 0�� ����� �� ����
		for(i=1; i<=N; i++) {
			if(FlowVisit[i]==0) {
				row[i-1]=1;
			}
		}
		// 0�� ����� �� ����
		for(i=N+1; i<FlowN; i++) {
			if(FlowVisit[i]==1) {
				col[i-N-1]=1;
			}
		}

		min=INFINIT;
		for(i=0; i<N; i++) {
			if(row[i]==1) continue;
			for(j=0; j<N; j++) {
				if(col[j]==1) continue;
				if(Arr[i][j]<min) {
					min=Arr[i][j];
				}
			}
		}

		//3-2. �ּҰ��� �ּҹ迭���� ����.
		for(i=0; i<N; i++) {
			for(j=0; j<N; j++) {
				if(row[i]==1) {
					if(col[j]==1) Arr[i][j]+=min;
				} else if(col[j]==1) {
				} else {
					Arr[i][j]-=min;
				}
			}
		}

		Value+=min;
	}
	

	//�н����


	ofstream out(OUTFILE);
	out << Value;
}


void main()
{
	//makedata();
	assigncpu();
}