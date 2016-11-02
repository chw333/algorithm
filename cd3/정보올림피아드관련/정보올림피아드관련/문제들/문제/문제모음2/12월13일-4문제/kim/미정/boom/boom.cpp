#include <fstream.h>
#include <string.h>
#include <iomanip.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <conio.h>


#define MAXM 200
#define MAXN 200

int M, N; //M은 y축, N은 x축
int Arr[MAXM+1][MAXN+1];
int Dy[MAXM+1][MAXN+1][3]; //자신을 포함한 최대 정사각형 -> Dy[][0=x축, 1=y축, 2=정사각형]
int Set[MAXM+1][MAXN+1]; //체크한 놈인지를 말함.
int Cnt; //사용한 폭탄의 개수

#define INFILE "boom.in" 
#define OUTFILE "boom.out"

#define MAKEM 200 //y축 크기
#define MAKEN 200 //x축 크기
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

//다이나믹 값 출력
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


//배열 출력
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


//폭탄 맞은 자리에 1 설정
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


//자신의 위치를 포함하는 최대로 큰 사각형을 찾아
//폭탄을 떨어뜨리고, 폭탄 맞은 자리는 Set[]좌표에 1을 설정.
void setting(int y, int x)
{
	int size, pos, startx, starty;
	int posx, posy, line, linesize;
	int i,j, sx, sy;
	int cnt, max, boomx, boomy;
	
	//if(y==6 && x==10) {
	//	int a=7;
	//}
	
	//3개짜리와 5개짜리 폭탄만 계산.
	for(size=5; size>1; size-=2) {
		//size개의 줄만큼 이동.
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
					
					//성공 = 포탄 투하.
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
		//폭파시킨 적이 있으면, 즉 max가 0이 아니면,
		//다음 단계 탐색을 중단.
		//왜냐하면, 폭파시킬 수 있다면, 큰 놈으로 폭파시키는 것이 유리하니까.
		if(max!=0) {
			putting(boomy, boomx, size);
		}

	}
	
	//아직 처리 되지 않은 것은 1개짜리 폭탄임.
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

	//자신을 포함하면서 가장 큰 정사각형을 계산
	for(i=1; i<=M; i++) {
		for(j=1; j<=N; j++) {
			if(Arr[i][j]==0) {
				Dy[i][j][0]=0;
				Dy[i][j][1]=0;
				Dy[i][j][2]=0;
			} else {
				//x좌표 보기
				Dy[i][j][0]=Dy[i][j-1][0]+1;
				//y좌표 보기
				Dy[i][j][1]=Dy[i-1][j][1]+1;
				//정사각형 계산
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