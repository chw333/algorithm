#include<stdio.h>
#include<conio.h>
#include<stdlib.h>

FILE *fp;
int dt[100][100];
int buf[100],v[100];
int n,m,g;                                                                                                                                                                                                                                                                                                                      

void input()
{
	int i,j;
	fp = fopen("comm.inp","r");
	fscanf(fp,"%d %d %d\n",&n,&m,&g);
	for(i=1;i<=n;i++){
		for(j=1;j<=n;j++)fscanf(fp,"%d ",&dt[i][j]);
		fscanf(fp,"\n");
	}
	fclose(fp);
}	
void process()
{
	int i,j,tail=1,head=0;
	buf[head] = 1;
	v[1] = 1;
	for(i=1;i<=n;i++){
		for(j=1;j<=n;j++){
			if(dt[buf[head]][j] != 0 && v[j] != 1 && j != m && j != g){
				buf[tail++] = j;
				v[j] = 1;
			}
		}
		head++;
	}
	g=tail;
}
void output()
{
	int imsi=0,i,j;
	fp = fopen("comm.out","w");
	for(i=0;i<g;i++){
		if(buf[i] > buf[i+1])
		{
			for(j=1;j<3;j++){
				fprintf(fp,"%d ",buf[i+j]);
			}
			exit(0);	
		}
	}
	fclose(fp);
}
void main(void)
{
	input();
	process();
	output();
}