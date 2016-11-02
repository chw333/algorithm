#include<stdio.h>
#include<stdlib.h>
#include<conio.h>

#define n 5
double p[100];
int l[100];
double c[100][100];
double m[100][100];
FILE *fp;

void input()
{
	int i;		
	fp = fopen("input.txt","r");
	for(i=0;i<5;i++)fscanf(fp,"%lf ",&l[i]);
	fscanf(fp,"\n");
	for(i=0;i<5;i++)fscanf(fp,"%lf ",&p[i]);
	fclose(fp);			
}
void process()
{
	int i,j,k;
	m[0][0] = p[0];
	for(i=1;i<5;i++) m[0][i] = (m[0][i-1]  + p[i]);
	for(i=1;i<5;i++){
		for(j=i;j<5;j++){
			m[i][j] = m[i-1][j] - m[i-1][i-1];
		}
	}

	for(i=0;i<5;i++){
		for(j=i;j<5;j++){
			double min = 9999;
			for(k=i;k<=j;k++){
				if(min > (c[i][k-1] + c[k+1][j]))min = (c[i][k-1] + c[k+1][j]);
			}
			c[i][j] = min + m[i][j];
		}
	}

	printf("5");
}	
void output()
{
}
void main(void)
{
	input();
	process();
	output();
}

