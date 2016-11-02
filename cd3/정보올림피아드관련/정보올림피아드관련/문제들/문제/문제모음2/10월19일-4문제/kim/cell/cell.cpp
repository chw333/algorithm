#include <fstream.h>
#include <string.h>
#include <iomanip.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>


#define MAX 50

int X, Y, Z;
int List[MAX][MAX][MAX];
int Visit[MAX][MAX][MAX];
int Cnt;

#define INFILE "cell10.in" 
#define OUTFILE "cell10.out"

#define MAKEX 50 //X크기
#define MAKEY 50 //Y크기
#define MAKEZ 50 //Z크기
#define RANGE 3 //키의 범위
#define MAKENUM 100000 //키의 범위

int MakeList[MAX][MAX][MAX];

void makedata()
{
	int i,j,k;
	int x,y,z, v;
	srand(time(NULL));

	ofstream out(INFILE);
	out << MAKEX << " " << MAKEY << " " << MAKEZ;
	i=0;
	while(i<MAKENUM) {
		x=rand()%MAKEX;
		y=rand()%MAKEY;
		z=rand()%MAKEZ;

		v=rand()%RANGE+1;
		
		if(MakeList[z][y][x]!=0) continue;

		MakeList[z][y][x]=v;

		i++;
	}

	for(i=0; i<MAKEZ; i++) {
		out << endl;
		for(j=0; j<MAKEY; j++) {
			for(k=0; k<MAKEX; k++) {
				if(k!=0) out << " ";
				out << MakeList[i][j][k];
			}
			out << endl;
		}
	}
	
}



void print()
{
	int i,j,k;
	for(i=0; i<Z; i++) {
		for(j=0; j<Y; j++) {
			for(k=0; k<X; k++) {
				cout << List[i][j][k];
			}
		}
		cout << endl;
	}
	cout << endl;
}

void dfs(int z, int y, int x, int color)
{
	static int dr[6][3]= {
		0, 0, -1,
		0, 0, 1,
		0, -1, 0,
		0, 1, 0,
		-1, 0, 0,
		1, 0, 0
	};

	Visit[z][y][x]=1;

	int i, nx, ny, nz;
	for(i=0; i<6; i++) {
		nx=x+dr[i][2];
		ny=y+dr[i][1];
		nz=z+dr[i][0];
		
		if(nx <0 || nx >=X) continue;
		if(ny <0 || ny >=Y) continue;
		if(nz <0 || nz >=Z) continue;

		if(List[nz][ny][nx]==color && Visit[nz][ny][nx]==0) {
			dfs(nz, ny, nx, color);
		}
	}

}

void cell()
{
	int i, j, k;
	ifstream in(INFILE);
	in >> X >> Y >> Z;
	for(i=0; i<Z; i++) {
		for(j=0; j<Y; j++) {
			for(k=0; k<X; k++) {
				in >> List[i][j][k];
			}
		}
	}

	int c;
	for(i=0; i<Z; i++) {
		for(j=0; j<Y; j++) {
			for(k=0; k<X; k++) {
				if(List[i][j][k]!=0 && Visit[i][j][k]==0) {
					c=List[i][j][k];
					dfs(i,j,k, c);
					Cnt++;
				}
			}
		}
	}
	//print();

	ofstream out(OUTFILE);
	out << Cnt;
}

void main()
{
	makedata();
	cell();
}