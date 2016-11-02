#include<stdio.h>
#include<conio.h>
#include<stdlib.h>

FILE *fp;
int m,n;
int dt[100];
int cur[100][100];

void input()
{
	fp = fopen("input.txt","r");
		fscanf(fp,"% d %d\n",&m,&n);
		for(int i  = 0 ; i < n ; i++)fscanf(fp,"%d\n",&dt[i]);
}
void process()
{
	int i,j;
	for(i=0;i<n;i++){
		for(j=1;j<i;j++){
		

		
		
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