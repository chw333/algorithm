#include <fstream.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAXN 30
#define MAXG 50
#define MAXGEN 64
#define MAXCELL 6

int N, G;
int Gen[MAXGEN][MAXCELL];
int Start[MAXN][MAXN];
int End[MAXN][MAXN];


#define INFILE "cellular07.in"
#define OUTFILE "cellular07.out"

#define MAKEN 30
#define MAKEG 50
#define MAKEGEN 33

int MakeStart[MAXN][MAXN];
int MakeEnd[MAXN][MAXN];


void nextgen(int prev[MAXN][MAXN], int next[MAXN][MAXN], int gen[MAXGEN]);
void makedata()
{
	int i,j;

	//진화 정보 만들기 =64가지
	char str[MAXCELL+2], bistr[MAXCELL+2];
	for(i=0; i<MAXGEN; i++) {
		itoa(i, str, 2);
		sprintf(bistr, "%06s", str);
		for(j=0; j<MAXCELL; j++) {
			Gen[i][j]=bistr[MAXCELL-j-1]-'0';
		}
	}

	srand(time(NULL));
	ofstream out(INFILE);
	int v;
	//초기상태 만들기.
	for(i=0; i<MAKEN; i++) {
		for(j=0; j<MAKEN; j++) {
			v=rand()%2;
			MakeStart[i][j]=v;
		}
	}
	
	int list1[MAXN][MAXN];
	int list2[MAXN][MAXN];
	int n1, n2;
	//Start로 초기화.
	N=MAKEN;
	for(n1=0; n1<MAKEN; n1++) {
		for(n2=0; n2<MAKEN; n2++) {
			list1[n1][n2]=MakeStart[n1][n2];
		}
	}
	//진화시키기.
	for(i=1; i<=MAKEG; i++) {
		nextgen(list1, list2, Gen[MAKEGEN]);
		for(n1=0; n1<MAKEN; n1++) {
			for(n2=0; n2<MAKEN; n2++) {
				list1[n1][n2]=list2[n1][n2];
			}
		}
	}


	//출력
	out << MAKEN << " " << MAKEG << endl;
	for(n1=0; n1<MAKEN; n1++) {
		for(n2=0; n2<MAKEN; n2++) {
			out << MakeStart[n1][n2];
		}
		out << endl;
	}
	for(n1=0; n1<MAKEN; n1++) {
		for(n2=0; n2<MAKEN; n2++) {
			out << list2[n1][n2];
		}
		out << endl;
	}

}


void nextgen(int prev[MAXN][MAXN], int next[MAXN][MAXN], int gen[MAXGEN])
{
	int i,j, cnt;
	for(i=0; i<N; i++) {
		for(j=0; j<N; j++) {
			cnt=0;
			if(j-1>=0 && prev[i][j-1]==1) cnt++;
			if(j+1< N && prev[i][j+1]==1) cnt++;
			if(i-1>=0 && prev[i-1][j]==1) cnt++;
			if(i+1< N && prev[i+1][j]==1) cnt++;
			cnt+=prev[i][j];
			next[i][j]=gen[cnt];
		}
	}
}


void cellular()
{
	int i, j;
	char str[MAXN+1];
	ifstream in(INFILE);
	in >> N >> G;
	for(i=0; i<N; i++) {
		in >> str;
		for(j=0; j<N; j++) {
			Start[i][j]=str[j]-'0';
		}
	}
	for(i=0; i<N; i++) {
		in >> str;
		for(j=0; j<N; j++) {
			End[i][j]=str[j]-'0';
		}
	}

	//진화 정보 만들기 =64가지
	char bistr[MAXCELL+2];
	for(i=0; i<MAXGEN; i++) {
		itoa(i, str, 2);
		sprintf(bistr, "%06s", str);
		for(j=0; j<MAXCELL; j++) {
			Gen[i][j]=bistr[MAXCELL-j-1]-'0';
		}
	}

	//진화 구하기
	int list1[MAXN][MAXN];
	int list2[MAXN][MAXN];
	int n1, n2, flag;
	int value=-1, v;

	for(i=0; i<MAXGEN; i++) {
		//Start로 초기화.
		for(n1=0; n1<N; n1++) {
			for(n2=0; n2<N; n2++) {
				list1[n1][n2]=Start[n1][n2];
			}
		}

		if(i==9) {
			int a=9;
		}

		//i번 진화 정보로 G세대 후의 값 구하기.
		for(j=1; j<=G; j++) {
			nextgen(list1, list2, Gen[i]);
			for(n1=0; n1<N; n1++) {
				for(n2=0; n2<N; n2++) {
					list1[n1][n2]=list2[n1][n2];
				}
			}
		}

		//g번 진화후, 목표와 같은 가를 비교.
		flag=0;
		for(n1=0; n1<N; n1++) {
			for(n2=0; n2<N; n2++) {
				if(list2[n1][n2]!=End[n1][n2]) {
					flag=1;
					n1=N;
					break;
				}
			}
		}
		//같음.=진화 정보임.
		if(flag==0) {
			value=0;
			for(j=0; j<MAXCELL; j++) {
				v=1;
				for(n1=0; n1<j; n1++) {
					v*=2;
				}
				v*=Gen[i][j];
				value+=v;
			}
			break;
		}
	}

	ofstream out(OUTFILE);
	out << value;
}


void main()
{
	//makedata();
	cellular();
}
