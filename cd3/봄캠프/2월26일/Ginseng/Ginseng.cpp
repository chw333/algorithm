#include <Stdio.h>
#include <Conio.h>
#define swap(A,B){ int T=A; A=B; B=T; }

int n,N[1000]={0,},data[1000][1000]={0,};
int table[1000][1000]={0,},check[10000000]={0,};
int np[1000]={0,},num[1000][1000]={0,},outmax=0,mp;
unsigned long int outdata[1000][10000];

void input()
{
	int i,j;
	FILE *fp=fopen("Ginseng.inp","r");
	fscanf(fp,"%d\n",&n);
	for(i=0;i<n;i++){
		fscanf(fp,"%d ",&N[i]);
		for(j=0;j<N[i];j++)
			fscanf(fp,"%d ",&data[i][j]);
	}
	fclose(fp);
}

void output()
{
	int i;
	FILE *fp=fopen("Ginseng.out","w");
	fprintf(fp,"%d\n",outmax);
	for(i=0;i<mp;i++)
		fprintf(fp,"%d ",outdata[n-1][i]);
	fprintf(fp,"\n"); fclose(fp);
}

void process()
{
	int i,j,k,tt,sp=0,max;

	for(i=0;i<n;i++){
		max=-32767;
		for(j=0;j<N[i];j++){
			if(j==0){
				table[i][j]=100-data[i][j]; 
				if(max<table[i][j]){
					np[i]=0; max=table[i][j]; num[i][np[i]++]=j+1;
				}
				continue;
			}
			table[i][j]+=table[i][j-1]+(100-data[i][j]);
			if(max<table[i][j]){
				np[i]=0; max=table[i][j]; num[i][np[i]++]=j+1;
			}
			else if(max==table[i][j])
				num[i][np[i]++]=j+1;
		}
		outmax+=max;
	}

	for(i=0;i<np[0];i++){outdata[0][i]=num[0][i]; sp++;}
	for(i=1;i<n;i++){
		tt=sp; sp=0;
		for(j=0;j<tt;j++)
//np[i]
			for(k=0;k<10;k++){
				if(check[num[i][k]+outdata[i-1][j]]==0){
					outdata[i][sp++]=num[i][k]+outdata[i-1][j];
					check[num[i][k]+outdata[i-1][j]]=1;
				}
			}
		for(j=0;j<sp;j++){
			check[outdata[i][j]]=0;
			for(k=j+1;k<sp;k++)
				if(outdata[i][j]>outdata[i][k])
					swap(outdata[i][j],outdata[i][k]);
		}
		if(sp>10)sp=10;
	}

	mp=sp;
}

void main()
{
	input();
	process();
	output();
}