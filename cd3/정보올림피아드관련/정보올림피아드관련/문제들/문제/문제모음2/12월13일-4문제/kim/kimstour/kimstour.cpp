#include <fstream.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <iomanip.h>

#define MAXN 10

int N;
int Visit[MAXN][MAXN];
int PathCnt, TotalDepth;
int ColCnt[MAXN];
int RowCnt[MAXN];


#define INFILE "kimstour07.in"
#define OUTFILE "kimstour.out"

void print(int lasty, int lastx, int depth)
{
	int i, j;
	Visit[lasty][lastx]=depth;

	for(i=0; i<=N; i++) {
		for(j=0; j<=N; j++) {
			if(lasty==i && lastx==j) {
				cout << setw(3) << "*";
			} else {
				cout << setw(3) << Visit[i][j];
			}
		}
		cout << endl;
	}
	cout << endl;
}


void dfs(int y, int x, int depth)
{
	if(x==0 && y==N) {
		if(depth==TotalDepth) {
			PathCnt++;
			//print(y, x, depth+1);
			//Visit[y][x]=0;
		}
		
		return;
	}
	depth++;
	Visit[y][x]=depth;
	ColCnt[x]++;
	RowCnt[y]++;

	int i, flag=0;
	int linecnt=N+1;
	if(ColCnt[x]==linecnt) {
		if(x!=N && ColCnt[x+1]!=linecnt) {
			flag=1;
		}
	}
	if(RowCnt[y]==linecnt) {
		if(y!=0 && RowCnt[y-1]!=linecnt) {
			flag=1;
		}
	}

	//print(y, x, depth);
	
	if(flag==0) {
		if(x>0) {
			if(Visit[y][x-1]==0) {
				dfs(y, x-1, depth);
			}
		}
		if(x<N) {
			if(Visit[y][x+1]==0) {
				dfs(y, x+1, depth);
			}
		}
		if(y>0) {
			if(Visit[y-1][x]==0) {
				dfs(y-1, x, depth);
			}
		}
		if(y<N) {
			if(Visit[y+1][x]==0) {
				dfs(y+1, x, depth);
			}
		}
	}

	ColCnt[x]--;
	RowCnt[y]--;
	Visit[y][x]=0;
	depth--;
}

void main()
{
	ifstream in(INFILE);
	in >> N;
	TotalDepth=N*N-1;
	N--;

	dfs(0,0, 0);

	ofstream out(OUTFILE);
	out << PathCnt;
}
