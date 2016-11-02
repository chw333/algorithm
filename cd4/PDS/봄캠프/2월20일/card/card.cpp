#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
int gcd(int,int);
int c[5000][5000];
int n;

void main(void)
{
	int i,j,k,a,b,max;
	
FILE *fp;
	fp = fopen("card.inp","r");
	fscanf(fp,"%d",&n);
	fclose(fp);
	for(j=1;j<=n;j++){
		for(i=1;i<=n;i++){
			c[j][1] = j;
			if(i==j)c[i][j] = 1;
		}
	}
	
	
	for(i=1;i<=n;i++){
		if(i == 1)continue;
		for(j=2;j<n;j++){
		int max= -9999;
			for(k=1;k<i-1;k++){
				int imsi=0,imsi1=0;
				imsi = (c[k][j-1]*(i-k))/(gcd(c[k][j-1],i-k));
			if(imsi > max)max = imsi;
			}
		if(c[i][j] < max)c[i][j] =max;
		}
	}
	for(i=1;i<=n;i++)if(max < c[n][i])max = c[n][i];
	fp = fopen("card.out","w");
	fprintf(fp,"%d",max);
	fclose(fp);
}
int gcd(int m,int n)
{
		if(n==0)
			return(m);
		else
			gcd(n,m%n);
}