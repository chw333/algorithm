#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#define MAX 100
#define swap(A,B){ int T=A;A=B;B=T;}

FILE *fp;
int dyn[MAX][MAX],high[MAX][MAX][MAX];
int check[MAX][MAX],dt[MAX][MAX];
int max[MAX],count[MAX],visit[MAX],goi[MAX];
int n,t[1000][1000],sp=0,tt=0,ch[10000000],mp;

void input()
{
	int i,j;
	fp = fopen("ginseng.inp","r");
	fscanf(fp,"%d\n",&n);
	for(i=1;i<=n;i++){
		int k;
		fscanf(fp,"%d ",&k);
		for(j=1;j<=k;j++){
			fscanf(fp,"%d ",&dt[i][j]);
			if(j != 1){
				dyn[i][j] = dyn[i][j-1]+100-dt[i][j];
			}
			else 
			{
				dyn[i][j] = 100-dt[i][j];
			}
			if(dyn[i][j] > max[i]) max[i] = dyn[i][j];
		}
		for(j=1;j<=k;j++)if(dyn[i][j] == max[i])check[i][count[i]++] = j;
	}
	fclose(fp);
}
void process()
{
	int i,j,k;
	
	for(i=1;i<=count[1];i++){t[0][i] = check[0][i];sp++;}
	for(i=2;i<=n;i++){
		tt = sp;sp = 0;
		for(j=1;j<=tt;j++){
			for(k=1;k<=count[i];k++){
				if(ch[check[i][k]+t[i-1][j]]==0){
					t[i][sp++]=check[i][k]+t[i-1][j];
					ch[check[i][k]+t[i-1][j]]=1;
				}
			}
		}
		for(j=1;j<=sp;j++){
			ch[t[i][j]]=0;
			for(k=j+1;k<=sp;k++)
				if(t[i][j]>t[i][k])
					swap(t[i][j],t[i][k]);
		}
	if(sp>10)sp=10;
	}
	mp=sp;

}
void output()
{
	int i,cnt=0;
	fp = fopen("ginseng.out","w");
		for(i=1;i<=mp;i++){
			fprintf(fp,"%d ",t[n][i]);
		}
	fclose(fp);
}	
void main(void)
{
	input();
	process();
	output();
}