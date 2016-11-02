#include<stdio.h>
#include<conio.h>
#include<stdlib.h>

double dt[100];
double room[100];
int cur[100];
int cnt[100];
double buf[100][100];
int n;
FILE *fp;
void input()
{
	int i;
	fp = fopen("bag.in","r");
	fscanf(fp,"%d\n",&n);
	for(i=0;i<n;i++)fscanf(fp,"%lf ",&dt[i]);
	fclose(fp);
	for(i=0;i<100;i++)room[i] = 1;
}
void process()
{
	int i,j;
	for(i=0;i<n-1;i++){
		for(j=i+1;j<n;j++){
			if(dt[i] < dt[j]){
				double imsi;
				imsi = dt[i];dt[i] = dt[j];dt[j] = imsi;
			}
		}
	}
	for(i=0;i<n;i++){
		for(j=0;j<100;j++){
			if(room[j] >= dt[i]){
				room[j] -=dt[i];
				buf[j][cnt[j]++] = dt[i];
				break;
			}
		}
	}
}

void output()
{
	int i,j;
	fp = fopen("bag.out","w");
	for(i=0;i<100;i++)if(cnt[i] == 0){fprintf(fp,"%d\n",i);break;}
	for(i=0;i<100;i++){
		if(cnt[i] == 0)exit(0);
		else{
			for(j=0;j<cnt[i];j++)fprintf(fp,"%0.2lf ",buf[i][j]);
		fprintf(fp,"\n");
		}
	}
}

void main(void)
{
	input();
	process();
	output();
}