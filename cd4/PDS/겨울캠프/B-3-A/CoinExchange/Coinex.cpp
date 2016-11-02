#include<stdio.h>
#include<conio.h>
#include<stdlib.h>

FILE *fp;
int buf[100][100];
int cnt[100];
int n,mok;
int dt[100];

void input()
{
	int i,j;
	fp = fopen("coinex.inp","r");
		fscanf(fp,"%d\n",&n);
		for(i=0;i<n;i++){
			fscanf(fp,"%d ",&dt[i]);
			buf[dt[i]][cnt[dt[i]]] = dt[i];
			cnt[dt[i]]++;
		}
		fscanf(fp,"\n%d",&mok);
}
void process()
{
	int i,j,k;
	for(i=0;i<mok;i++){
		for(j=0;j<n;j++){
			if(buf[i+dt[j]][cnt[i+dt[j]]] !=0 && cnt[i+dt[j]] > cnt[i]+1){
				for(k=0;k<=cnt[i+dt[j]];k++)buf[i+dt[j]][cnt[i+dt[j]]] = 0;
				cnt[i+dt[j]] = 0;
				for(k=0;k<=cnt[i];k++)buf[i+dt[j]][cnt[i]++] = buf[i][k];
				buf[i+dt[j]][cnt[i+dt[j]]++] = dt[j];
			}
			else if(buf[i+dt[j]][cnt[i+dt[j]]] ==0){
				for(k=0;k<=cnt[i];k++)buf[i+dt[k]][cnt[i+dt[k]]++] = buf[i][k];
				buf[i+dt[k]][cnt[i+dt[k]]++] = dt[k];
			}
		}
	}
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