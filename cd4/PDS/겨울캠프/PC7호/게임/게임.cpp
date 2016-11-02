#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
int cnt,buf[100],odd,even;
FILE *fp;
void input()
{
	int i;
	fp = fopen("game.in","r");
		fscanf(fp,"%d\n",&cnt);
		for(i=0;i<cnt;i++)fscanf(fp,"%d ",&buf[i]);
}
void process()
{
	static int i,j;
	for(i=0;i<cnt;i++){
		if((i+1)%2 == 0)
			even+=buf[i];
		else
			odd+=buf[i];
	}
}
void output()
{
	int i;
	if(even>odd)
	{
		printf("A : ");
		for(i=0;i<cnt;i++){
			if((i+1)%2 == 0){
				printf("%d",buf[i]);
				if(i == cnt-1)printf(" = %d\n",even);
				else printf(" + ");
			}
		}
		printf("B : ");
		for(i=0;i<cnt;i++){
			if((i+1)%2 == 1){
				printf("%d",buf[i]);
				if(i == cnt-2)printf(" = %d\n",odd);
				else printf(" + ");
			}
		}
	}
	else
	{
		printf("A : ");
		for(i=0;i<cnt;i++){
			if((i+1)%2 == 1){
				printf("%d",buf[i]);
				if(i == cnt-2)printf(" = %d\n",odd);
				else printf(" + ");
			}
		}
		printf("B : ");
		for(i=0;i<cnt;i++){
			if((i+1)%2 == 0){
				printf("%d",buf[i]);
				if(i == cnt-1)printf(" = %d\n",even);
				else printf(" + ");
		
			}
		}
	}
}
void main(void)
{
	input();
	process();
	output();
}
