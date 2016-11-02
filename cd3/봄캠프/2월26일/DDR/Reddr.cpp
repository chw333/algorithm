#include<fstream.h>
#include<math.h>
#include<time.h>
#define infilename  "ddr.inp"
#define outfilename "ddr.out"
#define MAXN 1000000
#define MAX 99999999

int data[MAXN],matrix[5][5];
int cnt,min;
double stime=clock();

void input()
{
	int temp;
	ifstream fin(infilename);

	cnt++;
	while(1)
	{
		fin >> temp;
		if(temp==0) break;
		data[cnt++] = temp;
	}
	fin.close();
}

void core()
{
	int i,j,k,l,r,t1,t2;

	int table[10000][5][5]={0};
	for(i=1; i<=cnt; i++) matrix[0][i] = 2;
	for(i=1; i<=4; i++) {
		for(j=1; j<=4; j++) {
			if(i-j==0) matrix[i][j]=1;
			else if(abs(i-j)==1 || abs(i-j)==3) matrix[i][j]=3;
			else if(abs(i-j)==2) matrix[i][j]=4;
		}
	}

	table[0][0][0]=1;
	for(i=1; i<=cnt; i++) {
		for(l=0; l<5; l++) {
			for(r=0; r<5; r++) {
				if(l!=r || (l==0 && r==0)) {
					if(table[i-1][l][r]!=0) {
						k=data[i];
					
						if(table[i][k][r]==0 || table[i][k][r]>table[i-1][l][r]+matrix[l][k]) {
							if(k!=r) {
								t1 = table[i-1][l][r] + matrix[l][k];
								table[i][k][r] = t1;
							}
						}
								
						if(table[i][l][k]==0 || table[i][l][k]>table[i-1][l][r]+matrix[r][k]) {
							if(k!=l) {
								t2 = table[i-1][l][r] + matrix[r][k];
								table[i][l][k] = t2;
							}
						}					
						
					}
				}
			}
		}
	}

	min=MAX;
	for(i=0; i<5; i++) {
		for(j=0; j<5; j++) {
			if(i!=j && table[cnt][i][j]!=0) {
				if(min > table[cnt][i][j]) min = table[cnt][i][j];
			}
		}
	}

}

void output()
{
	ofstream fout(outfilename);
	fout << min-1;
	fout.close();
}

void main()
{
	input();
	core();
	output();
//	cout << (clock()-stime)/1000.0;
}