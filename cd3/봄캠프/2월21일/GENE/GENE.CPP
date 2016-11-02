#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
int c1,c2;
int f,n;
int buf[100];
char mon[2001];
char str1[2][1001];
FILE *fp;

void back(int i)
{
	int j;
	if(c1 == n && c2 == n)
	{
		fp = fopen("gene.out","w");
		for(i=0;i<f;i++)fprintf(fp,"%d ",buf[i]);
		fclose(fp);
	}
	if(mon[i] == str1[0][c1] && c1 != n){
		c1++;
		buf[f++] = i+1;
		back(i+1);
		buf[f--] = 0;
		c1--;
	}
	else if(mon[i] == str1[1][c2] && c2 != n){
		c2++;back(i+1);
		c2--;
	}
	else if(c1 != n && c2 != n)
	{
		c1--;
		return;
	}
}
void main(void)
{
	int i,j;
	FILE *fp;
	fp = fopen("gene.inp","r");
		fscanf(fp,"%d",&n);
		fscanf(fp,"\n");
		fgets(str1[0],1001,fp);
			fscanf(fp,"\n");
		fgets(str1[1],1001,fp);
		fgets(mon,2001,fp);
	fclose(fp);
	back(0);
}
