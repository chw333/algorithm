#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
int visit[1001];
int a[2],b[2],l[2],n;
void back(int);
FILE *fp;

void main(void)
{
	fp = fopen("seq.in","r");
		fscanf(fp,"%d,%d,%d,%d,%d,%d,%d",&n,&a[0],&b[0],&l[0],&a[1],&b[1],&l[1]);
	fclose(fp);
	back(0);
	fp = fopen("seq.out","w");
		fprintf(fp,"-1");
	fclose(fp);
}
void output()
{
	int i;
	fp = fopen("seq.out","w");
	for(i=0;i<n;i++)fprintf(fp,"%d",visit[i]);
	fclose(fp);
}

void back(int i)
{
	int j,k;
	if(i==n){
		for(j=0;j<=n-l[0];j++){
			int bc = 0;
				for(k=j;k<j+l[0];k++)if(visit[k] == 1)bc++;				
				if(!(a[0] <= bc && bc <= b[0]))goto end;
		}
		for(j=0;j<=n-l[1];j++){
			int bc = 0;
				for(k=j;k<j+l[1];k++)if(visit[k] == 1)bc++;	
				if(!(a[1] <= bc &&  bc <= b[1]))goto end;
		}
		output();
		exit(0);
	}
end:
	if(i<n)
		for(j=0;j<2;j++){
			visit[i] = j;
			back(i+1);
			visit[i] = 0;
		}
}
