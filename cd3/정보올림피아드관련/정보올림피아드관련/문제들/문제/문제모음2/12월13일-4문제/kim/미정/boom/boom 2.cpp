#include <fstream.h>
#include <string.h>
#include <iomanip.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <conio.h>
#include <iomanip.h>


#define MAXM 200
#define MAXN 200
#define INFINIT 99

int M, N; //M�� y��, N�� x��
int Arr[MAXM+1][MAXN+1];
int Dy[MAXM+1][MAXN+1][2];
    //Dy[][][0] -> �ִ� ���簢���� ũ��
	//Dy[][][1] -> ������ġ������ �ּ� ��ź�� ����.

#define INFILE "boom01.in"
#define OUTFILE "boom.out"


void print()
{
	int i,j;
	for(i=1; i<=M; i++) {
		for(j=1; j<=N; j++) {
			cout << setw(3) << Dy[i][j][1];
		}
		cout << "    ";
		for(j=1; j<=N; j++) {
			cout << setw(3) << Dy[i][j][0];
		}
		cout << endl;
	}
	cout << endl;
}


void main()
{
	int i,j,k;
	int min, cnt;
	ifstream in(INFILE);

	in >> M >> N;
	for(i=1; i<=M; i++) {
		for(j=1; j<=N; j++) {
			in >> Arr[i][j];
			if(Arr[i][j]==1) {
				cnt= Dy[i-1][j-1][0]+1;
				for(k=1; k<cnt; k++) {
					if( Arr[i-k][j]==0 ) break;
					if( Arr[i][j-k]==0 ) break;
				}
				//k���簢��.
				Dy[i][j][0]=k;

			} else {
				Dy[i][j][0]= 0;
			}
			
		}
	}

	for(i=1; i<=M; i++) {
		for(j=1; j<=N; j++) {
			if(i==3 && j==7) {
				int a=7;
			}
			if(Dy[i][j][0]==0) {
				//��ź ���� �Ұ��� �����̸�?
				k=1;
				Dy[i][j][1] = Dy[i-k][j][1] + Dy[i][j-k][1] -
							  Dy[i-k][j-k][1];
			} else {
				min=INFINIT;
				for(k=1; k<=5; k+=2) {
					//kũ���� ��ź���ϰ� �����Ѱ�?
					if(Dy[i][j][0] >=k) {
						cnt = Dy[i-k][j][1] + Dy[i][j-k][1] -
							  Dy[i-k][j-k][1] + 1;
						if(cnt < min) {
							min=cnt;
						}
					}
				}
				Dy[i][j][1]=min;
			}
			print();
		}
	}

	ofstream out(OUTFILE);
	out << Dy[M][N][1];
}
