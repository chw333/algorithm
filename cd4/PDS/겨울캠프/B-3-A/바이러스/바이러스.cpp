#include<stdio.h>
#include<conio.h>
#include<stdlib.h>

FILE *fp;

void input()
{
	fp = fopen("input.txt","r");
		fscanf(fp,"%d",&n);
	fclose(fp);
}		
void process()
{
	int i,j;


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