#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>

char buf[100];
FILE *fp;
int tab[100][100];
int cur[2][100];
int cnt,fun;
int dt[100][2];

void input()
{
	fp = fopen("input.txt","r");
		fgets(buf,100,fp);
}
void process()
{
	int i,j,tt = 0,cnt;
	
	cnt = strlen(buf)-1;

	for(i=0;i<cnt;i++){
		cur[0][i] = toupper(buf[i])-'A';
		cur[1][i] = cur[0][i];
	}
	
	for(i=0;i<cnt-1;i++){
		for(j=i+1;j<cnt;j++){
			if(cur[1][i] > cur[1][j]){
				int imsi;
				imsi = cur[1][i]; cur[i][1] = cur[j][1]; cur[j][1] = imsi;
			}
		}
	}

	for(i=0;i<cnt;i++)for(j=0;j<=cnt;j++)tab[cur[0][i]][cur[1][i]]++;
	
	for(i=0;i<cnt;i++){
		for(j=0;j<i;j++){
			if(tab[i][j] < tab[j][i]){
				tab[i][j] = 0;
				tab[j][i] -= tab[i][j];goto end;
			fun += tab[i][j];
			}
			if(tab[i][j] > tab[j][i]){
				tab[j][i] = 0;
				tab[i][j] -=tab[j][i];goto end;
			fun += tab[j][i];
			}

			if(tab[i][j] == tab[j][i]){tab[i][j] = tab[j][i] = 0;fun += tab[i][j];}
end:
		}
	}
	
	for(i=0;i<cnt;i++){
		for(j=0;j<cnt;j++){
			dt[tt][0] = i;
			dt[tt][1] = j;
			tt++;
		}
	}
	for(i=0;i<tt-1;i++){
		for(j=i+1;j<tt;j++){
			if(dt[i][0] > dt[j][0]){
				int imsi;
				imsi = dt[i][0]; dt[i][0] = dt[j][0]; dt[j][0] = imsi;
			}
			if(dt[i][1] > dt[j][1]){
				int imsi;
				imsi = dt[i][1]; dt[i][1] = dt[j][1]; dt[j][1] = imsi;
			}
		}
	}

	for(i=0;i<tt;i++){
		if(dt[i][0] != dt[i][1])
		exit(0);
	}
	fun+= tt-1;
	


}
void output()
{
	printf("%d",fun);
}
void main(void)
{
	input();
	process();
	output();
}