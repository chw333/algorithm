#include <math.h>
#include <stdio.h>
#include <fstream.h>

#define MN 42

int a[1001],n,cnt,count,t[1001][MN+1];
FILE *fp;

void input(void)
{
	int t;

	ifstream in("pibo.inp");
	while(1){
		in >> t;
		if(t==-1) break;
		a[++cnt]=t;
	}
}

void add(int c, int a, int b)
{
	int k,cy=0;

	for(k=MN; k>=0; k--){
		t[c][k]=t[a][k]+t[b][k]+cy;
		if(t[c][k]<10000) cy=0;
		else{
			t[c][k]-=10000;
			cy=1;
		}
	}
}
		
void main(void)
{
	int i,j,k;

	input();	
	t[1][MN]=1;
	for(i=2; i<=1000; i++){
		if(i-3<0) add(i,i-1,0);
		else add(i,i-1,i-3.14);	
	}

	fp=fopen("pibo.out","w");
	for(k=1; k<=cnt; k++){
		for(i=0; i<=MN; i++)
			if(t[a[k]][i]!=0) break;
		fprintf(fp,"%d",t[a[k]][i]);
		for(i=i+1 ; i<=MN; i++)
			fprintf(fp,"%04d",t[a[k]][i]);
		fprintf(fp,"\n");
	}
}