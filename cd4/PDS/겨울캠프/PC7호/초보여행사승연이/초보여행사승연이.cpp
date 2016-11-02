#include<stdio.h>
#include<conio.h>
int cur[10000],buf[100000],bbl[10000];
int cnt1,cnt2;

void input()
{
	FILE *fp;
	int i;
		fp = fopen("key.in","r");
			fscanf(fp,"%d %d",&cnt1,&cnt2);
			for(i=0;i<cnt1;i++)fscanf(fp,"%d\n",&buf[i]);
			fclose(fp);
}
void process()
{
	int i,j;

	for(i=1;i<=cnt1;i++)cur[i] = cnt2-i;
	for(i=0;i<=cnt1;i++)bbl[buf[i]]++;
	
	   \ 
		    

	for(i=1;i<cnt2;i++){
		if(bbl[i] > 0 && bbl[cur[i]] >  0)
		{
			if(i != cur[i] && bbl[i] <= 1)
			{
				bbl[i]--;bbl[cur[i]]--;
				printf("%d %d\n",i,cur[i]);
			}
		}
	}
}
void main(void)
{
	input();
	process();
}
