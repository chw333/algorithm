#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>
FILE *fp;
int dt[100][100];
int fun[100][5];
int n;
char wd[100][100],tx[100];
int com;

void input()
{
	int i;
	fp = fopen("words.inp","r");
	fscanf(fp,"%d\n",&n);
	for(i=0;i<n;i++){
		fscanf(fp,"%s\n",&wd[i]);
		fun[i][2] = strlen(wd[i]);
	}
	fclose(fp);
	fp = fopen("text.inp","r");
		fgets(tx,100,fp);
	fclose(fp);
	com = strlen(tx)-1;
}
void process()
{
	int i,j,max,wi,x=0,f=0,k;

	for(i=0;i<n;i++){
		int w = 0;
		for(j=0;j<strlen(tx);j++){
			if(wd[i][w]== tx[j]){
				if(w == strlen(wd[i])-1){
					fun[f][2] = j;
					for(k=j;k>=0;k--)
					{
						if(w == 0) fun[f++][1] = k;
						if(tx[k] == wd[i][w])w--;
					}
				}
				w++;
			}
		}
	}
f	for(i=0;i<=f;i++){
		printf("%d %d %d\n",fun[i][0],fun[i][1],fun[i][2]);
	}


	for(i=0;i<n-1;i++){
		for(j=i+1;j<n;j++){
			if(fun[i][0] > fun[j][0]){
				int imsi;
				imsi = fun[i][0]; fun[i][0] = fun[j][0];fun[j][0] = imsi;
				imsi = fun[i][1]; fun[i][1] = fun[j][1];fun[j][1] = imsi;
				imsi = fun[i][2]; fun[i][2] = fun[j][2];fun[j][2] = imsi;
			}
		}
	}
	for(i=0;i<n;i++){
		for(j=0;j<i;j++){
			if(fun[i][0] > fun[j][1] && max < fun[i][2]){
				max = fun[j][2];
				wi = i;
			}
		}
		fun[i][3] = max+ fun[i][2];
		fun[i][4] = wi;
	}
}
void main(void)
{
	input();
	process();
 //	output();
}