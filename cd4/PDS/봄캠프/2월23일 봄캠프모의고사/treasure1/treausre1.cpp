#include<stdio.h>
#include<conio.h>
#include<stdlib.h>

int max,n,m;
int dt[100];
int v[100];
int min[100];
void back(int i)
{
	int j;
	if(i == m){
		int y=0,count=0;
		for(i=0;i<n;i++){
			count+=dt[i];
			if(min[y] == i){
				printf("%d ",count);
				count = 0;
				y++;
			}
	
		}		
		printf("%d %d %d\n",min[0],min[1],min[2]);
		return;
	}
	for(j=i;j<n;j++){
		v[i] = j;
		if(i != 3)
//		min[i+1]-=min[j];
//		min[i]+=min[j];
		back(i+1);
		v[i] = 0;
	}
}
void input()
{
	FILE *fp;
	int i;
	fp = fopen("treasure1.inp","r");
	fscanf(fp,"%d %d\n",&n,&m);
	for(i=0;i<n;i++)fscanf(fp,"%d ",&dt[i]);
	fclose(fp);
}
void process()
{
	int i;	
	back(0);
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
