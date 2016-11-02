#include <fstream.h>
#include <string.h>
#include <iomanip.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <conio.h>


#define MAXM 200
#define MAXN 200

int M, N; //M�� y��, N�� x��
int Arr[MAXM+1][MAXN+1];
int Dy[MAXM+1][MAXN+1][3]; //�ڽ��� ������ �ִ� ���簢�� -> Dy[][0=x��, 1=y��, 2=���簢��]
int Set[MAXM+1][MAXN+1]; //üũ�� �������� ����.
int Cnt; //����� ��ź�� ����

#define INFILE "boom.in" 
#define OUTFILE "boom.out"

#define MAKEM 200 //y�� ũ��
#define MAKEN 200 //x�� ũ��
#define MAKET 1
int MakeArr[MAXM][MAXN];

void makedata()
{
	ofstream out(INFILE);
	out << MAKEM << " " << MAKEN << endl;
	int i, j, x, y, v;
	i=0;
	srand(time(NULL));

	while(i<MAKET) {
		y=rand()%MAKEM+1;
		x=rand()%MAKEN+1;
		if(MakeArr[y][x]==1) continue;
		MakeArr[y][x]=1;
		i++;
	}

	for(i=1; i<=MAKEM; i++) {
		for(j=1; j<=MAKEN; j++) {
			v=(MakeArr[i][j]==0)? 1 : 0;
			if(j!=1) out << " ";
			out << v;
		}
		out << endl;
	}
}

//���̳��� �� ���
void printDy()
{
	int i,j;
	for(i=1; i<=M; i++) {
		for(j=1; j<=N; j++) {
			cout << setw(3) << Arr[i][j];
		}
		cout << endl;
	}
	cout << endl;

	for(i=1; i<=M; i++) {
		for(j=1; j<=N; j++) {
			cout << setw(3) << Dy[i][j][2];
		}
		cout << endl;
	}
	cout << endl;
	cout << "--------------------------" << endl;
}


//�迭 ���
int printcnt;
int printSet[MAXM+1][MAXN+1];
void print()
{
	int i,j;
	for(i=1; i<=M; i++) {
		for(j=1; j<=N; j++) {
			if(printSet[i][j]==1) {
				cout << setw(3) << "*";
			} else {
				cout << setw(3) << Set[i][j];
			}
			printSet[i][j]=0;
		}
		cout << endl;
	}
	cout << endl;
	//getch();
	printcnt=0;
}


//��ź ���� �ڸ��� 1 ����
void putting(int boomy, int boomx, int size)
{
	int i,j, sx, sy;
	sy=boomy;
	for(i=0; i<size; i++) {
		sx=boomx;
		for(j=0; j<size; j++) {
			Set[sy][sx]++;
			printSet[sy][sx]=printcnt+1;
			sx--;
		}
		sy--;
	}
}


//�ڽ��� ��ġ�� �����ϴ� �ִ�� ū �簢���� ã��
//��ź�� ����߸���, ��ź ���� �ڸ��� Set[]��ǥ�� 1�� ����.
void setting(int y, int x)
{
	int size, pos, startx, starty;
	int posx, posy, line, linesize;
	int i,j, sx, sy;
	int cnt, max, boomx, boomy;
	
	//if(y==6 && x==10) {
	//	int a=7;
	//}
	
	//3��¥���� 5��¥�� ��ź�� ���.
	for(size=5; size>1; size-=2) {
		//size���� �ٸ�ŭ �̵�.
		startx=x+(size-1);
		starty=y+(size-1);
		max=0;
		
		for(line=0; line<=size; line++) {
			if(line==size) {
				linesize=size-1;
				posx=startx-1;
				posy=y;
			} else {
				linesize=line+1;
				posx=startx;
				posy=starty-line;
			}
			

			for(pos=0; pos<linesize; pos++) {
				if(posy <= M && posx <= N) {
					
					//���� = ��ź ����.
					if(Dy[posy][posx][2] >= size) {
						sy=posy;
						cnt=0;
						for(i=0; i<size; i++) {
							sx=posx;
							for(j=0; j<size; j++) {
								if(Set[sy][sx]==0) {
									cnt++;
								}
								sx--;
							}
							sy--;
						}
						if(max < cnt) {
							max=cnt;
							boomx=posx;
							boomy=posy;
							if(max==size*size) {
								putting(boomy, boomx, size);
								return;
							}
						}
						//return;
					}
				}
				posx--;
				posy++;
			}
		}
		//���Ľ�Ų ���� ������, �� max�� 0�� �ƴϸ�,
		//���� �ܰ� Ž���� �ߴ�.
		//�ֳ��ϸ�, ���Ľ�ų �� �ִٸ�, ū ������ ���Ľ�Ű�� ���� �����ϴϱ�.
		if(max!=0) {
			putting(boomy, boomx, size);
		}

	}
	
	//���� ó�� ���� ���� ���� 1��¥�� ��ź��.
	Set[y][x]++;
	printSet[y][x]=printcnt+1;
}



int min(int a, int b, int c)
{
	if(a < b) {
		if(a < c) {
			return a;
		} else {
			return c;
		}
	} else {
		if(b < c) {
			return b;
		} else {
			return c;
		}
	}
}

void boom()
{
	int i,j;
	ifstream in(INFILE);
	in >> M >> N;
	for(i=1; i<=M; i++) {
		for(j=1; j<=N; j++) {
			in >> Arr[i][j];
		}
	}

	//�ڽ��� �����ϸ鼭 ���� ū ���簢���� ���
	for(i=1; i<=M; i++) {
		for(j=1; j<=N; j++) {
			if(Arr[i][j]==0) {
				Dy[i][j][0]=0;
				Dy[i][j][1]=0;
				Dy[i][j][2]=0;
			} else {
				//x��ǥ ����
				Dy[i][j][0]=Dy[i][j-1][0]+1;
				//y��ǥ ����
				Dy[i][j][1]=Dy[i-1][j][1]+1;
				//���簢�� ���
				Dy[i][j][2]=min(Dy[i][j][0], Dy[i][j][1], Dy[i-1][j-1][2]+1);
			}
		}
	}
	//printDy();

	for(i=1; i<=M; i++) {
		for(j=1; j<=N; j++) {
			if( Set[i][j]==0 && Arr[i][j]==1 ) {
				setting(i,j);
				Cnt++;
				print();
				cout << Cnt << endl;
				getch();
			}
		}
	}

	ofstream out(OUTFILE);
	out << Cnt;
}

void main()
{
	//makedata();
	boom();
}