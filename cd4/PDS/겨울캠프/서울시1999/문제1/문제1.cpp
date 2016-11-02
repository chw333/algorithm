#include<stdio.h>
#include<conio.h>
#include<stdlib.h>

char in1[100],in2[100];
int dt[1000][1000];
FILE *fp;

void input()
{
	int i,j;
	fp = fopen("input.txt","r");
		fgets(in1,100,fp);
		fscanf(fp,"\n");
		fgets(in2,100,fp);
}
void process()
{
	int i,j,mal;
	for(i=1;i<strlen(in2);i++){
		dt[0][i] = i;
		for(j=1;j<strlen(in1);j++){
			if(in1[i-1] == in2[j-1])
				dt[i][j] = dt[i-1][j-1];
			else{
				int cur[3] = {0,0,0},min = 9999;				
				cur[0] = dt[i][j-1] +1;
				cur[1] = dt[i-1][j] +1;
				cur[2] = dt[i-1][j-1] +1;
				for(k=0;k<3;k++)if(cur[k] < min) min = cur[k];
			}
		}
	}
	for(i=0;i<strlen(in1);i++){
		if(m
}
void output()
{
}



{
 	input();
	process();
	output();
}

