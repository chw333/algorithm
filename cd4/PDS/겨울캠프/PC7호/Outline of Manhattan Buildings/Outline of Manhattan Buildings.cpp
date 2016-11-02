#include<stdio.h>
#include<conio.h>
#include<stdlib.h>

int dt[100][2];
int cur[1000],n;
int max;

FILE *fp;

void input()
{
	int i,j;
	fp = fopen("input.txt","r");
		fscanf(fp,"%d\n",&n);
		for(i=0;i<n;i++){
			fscanf(fp,"%d %d %d\n",&dt[i][0],&dt[i][1],&dt[i][2]);
			if(dt[i][0] > max) max = dt[i][0];
			if(dt[i][1] > max) max = dt[i][1];
		}
}
void process()
{
	int i,j;
	for(i=0;i<n;i++){
	for(j=dt[i][0];j<dt[i][1];j++){
			if(cur[j] < dt[i][2])cur[j] = dt[i][2];
		}
	}
}
void output()
{
	int i,l;
	for(i=0;i<max+2;i++)if(cur[i] != 0){ l = cur[i];break;}
	for(i=0;i<max+2;i++){
		if(cur[i] != 0 && cur[i] != l){	printf("%d ",l);l = cur[i];}
	}
}

void main(void)
{
	input();
	process();
	output();
}