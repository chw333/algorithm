#include<stdio.h>
#include<conio.h>
main()
{
	int cnt;
	int x,y;
	int i,j;
	FILE *fp;
	fp = fopen("01101305.in","r");
		fscanf(fp,"%d %d %d",&cnt,&x,&y);
		fclose(fp);
