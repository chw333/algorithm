#include<string.h>
#include<Stdio.h>
#include<conio.h>
#include<stdlib.h>

FILE *fp;
char dt[1000];
char c[100][100];
int cur[100][100];
int f[100];
void input()
{
	fp = fopen("input.txt","r");
		fgets(dt,100,fp);
	fclose(fp);
}
void process()
{ 
	int i,j,cnt = 0,k = 0;
	for(i=0;i<strlen(dt);i++){
		if(dt[i] == ' '){k++;cnt = 0;}
		else c[k][cnt++] = dt[i];
	}		
	for(i=0;i<cnt;i++)f[i] = strlen(c[k]);

	for(i=0;i<strlen(dt);i++){
		t[i] = 9999;
		int w = 0;
		for(j=0;j<i-1;j++){
			t[i				
		}
	}
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

