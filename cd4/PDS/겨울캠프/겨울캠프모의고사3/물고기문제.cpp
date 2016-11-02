#include<math.h>
#include<stdio.h>
#include<conio.h>
#include<stdlib.h>

#define MAX 100

FILE *fp;

int dt[100];
int cur[MAX];
int crs[MAX],cnt[MAX];
int n,k;

void input()
{
	int i;
	fp = fopen("fish.inp","r");
	fscanf(fp,"%d %d\n",&n,&k);
	for(i=0;i<n;i++)fscanf(fp,"%d\n",&dt[i]);
}

void process()
{
	int i,j,f;
	for(i=1;i<=k;i++)crs[i] = -1;
	for(i=0;i<n-1;i++)
		for(j=i+1;j<n;j++)
			if(dt[i] > dt[j]){
				int imsi;
				imsi = dt[i];dt[i] = dt[j];dt[j] = imsi;
			}
	for(i=0;i<n;i++){
		for(j=k-dt[i];j>=0;j--){
			if(crs[j] != -1){
				cur[j+dt[i]] = 1;
				crs[j+dt[i]] = j;
			}
		}
	}

}
void output()
{
	int i,j,go;
	go = k;	
	for(i=k;i>=0;i--){
		printf("%2d ",k-cur[i]);
	}
}

void main(void)
{
	input();
	process();
	output();
}