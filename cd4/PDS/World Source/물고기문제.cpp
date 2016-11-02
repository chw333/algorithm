#include<stdio.h>
#include<conio.h>
#include<stdlib.h>

#define MAX 7000
int n1,n2;
int dt[500000];
int buf[MAX],street[MAX];
int max = 0;

FILE *fp;

void input()
{
	int i,j,f = 0;
	fp = fopen("fish.inp","r");
	fscanf(fp,"%d %d\n",&n1,&n2);
		for(i=0;i<n1;i++){
			int imsi;
			fscanf(fp,"%d\n",&imsi);
			if(imsi < 7000){
				street[imsi]++;
				if(imsi > max) max = imsi;
			}
		}
		for(i=max;i>=0;i--){
			if(street[i] != 0){
				for(j=0;j<street[i];j++){
					dt[f++] = i;
				}
			}
		}
	fclose(fp);
}
void process()
{
	int i,j;
	for(i=0;i<n1;i++){
		for(j=max+1;j>=0;j--){
			if(buf[j] != 0){
				if(buf[j+dt[i]] != 0 && buf[j+dt[i]] > buf[j]+1){
					buf[j+dt[i]] = buf[j] + 1;
					if(j+dt[i] > max) max = j+dt[i];
					street[j+dt[i]] = j;
				}
				if(buf[j+dt[i]] == 0){
					buf[j+dt[i]] = buf[j] +1;
					if(j+dt[i] > max) max = j+dt[i];
					street[j+dt[i]] = j;
				}
			}
			if(j == 0){
				buf[dt[i]] = 1;
				if(dt[i] > max)max = dt[i];
				street[j+dt[i]] = j;
			}
		}
	}
}
void output()
{
	int visit,visit1,i;
	fp = fopen("fish.out","w");
	fprintf(fp,"%d\n",buf[n2]);
	visit = n2;
	visit1 = n2;
	for(i=0;i<buf[n2];i++){
		visit = street[visit];
		fprintf(fp,"%d\n",visit1 - visit);	
		visit1 = street[visit1];
	}
	fclose(fp);
}
void main(void)
{
	input();
	process();
	output();
}