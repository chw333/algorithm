#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<ctype.h>

	FILE *fp;
	int buf[100][100];
	int hap[100];
	int cur[100][2];
	int comb[3][100];
	int ton[100];
	int n,host,tm,max;

void input()
{
	fp = fopen("input.txt","r");
	int i;
		fscanf(fp,"%d\n",&n);
		for(i=0;i<n;i++)fscanf(fp,"%d ",&ton[i]);
		fscanf(fp,"\n%d %d",&host,&tm);
}

void process() 
{
	int i,j,max = 0,k;
	for(i=0;i<n;i++){
		hap[i] = ton[i] / host;
	}
	for(i=0;i<n;i++){
		for(j=0;j<=hap[i];j++){ 
			buf[i][j] = (hap[i] - (host * i))/ tm
		}
	}
	for(i=0;i<n;i++){
		for(j=0;j<hap[i];j++){
			for(k=0;k<hap[t];k++){
				if(cur[i][k] != 0 && ((hap[i] - (host * k))/tm) > cur[i][k]){
					cur[i][k] = (hap[i] - (host * k))/tm;
				}
			}
		}
	for(j=0;j<hap[i];j++){
		cur[0][j] = cur[2][j];
		cur[2][j] = 0;
	}
	for(i=0;;i++){
		if(cur[i][i] == 
	
}

void output()
{
	printf("%d",max);
}

void main(void)
{
	input();
	process();
	output();
}
