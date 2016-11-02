#include<stdio.h>
#include<conio.h>

int buf[100][2];
int cnt1,cnt2;
int cur[100];
void input()
{
	FILE *fp;
	int i,j;
	fp = fopen("jiha.in","r");
		fscanf(fp,"%d\n",&cnt1);
		fscanf(fp,"%d\n",&cnt2);
		for(i=0;i<cnt2;i++)	fscanf(fp,"%d %d\n",&buf[i][0],&buf[i][1]);
}
void process()
{
	int i,j;
	for(i=1;i<=cnt1;i++)cur[i] = i;
	for(i=0;i<cnt2;i++){
		if(buf[i][0] > buf[i][1]){
			int imsi;
			imsi = cur[buf[i][0]]; cur[buf[i][0]] = cur[buf[i][1]]; cur[buf[i][1]] = imsi;
		}
	}
}
void output()
{
	int i;
	for(i=1;i<=cnt1;i++)printf("%d",cur[i]);
}

void main()
{
	input();
	process();
	output();
}

