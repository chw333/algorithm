#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
FILE *fp;
int sp1[2];
int sp2[2];
int x[2],y[2];
int dt[100][2];

int dt[100][2];
int c[1000][1000];

void main(void)
{
	fp = fopen("height.inp","r");
	fscanf(fp,"%d\n",&n);
	for(i=0;i<n;i++)fscanf(fp,"%d %d\n",&dt[i][0],&dt[i][1]);
	fclose(fp);
	for(i=0;i<n;i++){
		if(dt[i][0] == dt[i+1][0])
		for(j=dt[i][1];j<=dt[i+1][1];j++)c[i][j] = 1;
	}
	sp1[0] = dt[0][0];
	sp1[1] = dt[0][1];
	sp2[0] = dt[n-1][0];
	sp2[1] = dt[n-1][0];
	
	
	
	
}









