#include<stdio.h>
#include<conio.h>
#include<stdlib.h>

int cur[100][100];
int buf[100][100];
int n[2];
int fun[4],avr;
FILE *fp;

void input()
{
	int i,j;
	fp = fopen("cheese.inp","r");
		fscanf(fp,"%d %d\n",&n[0],&n[1]);
		for(i=0;i<n[0];i++)
			for(j=0;j<n[1];j++){
				fscanf(fp,"%d ",&buf[i][j]);
			}
		fscanf(fp,"\n");
	fclose(fp);
}
void process()
{
	int i,j,k,w;
	start:
	for(i=0;i<n[0];i++){
		for(j=0;j<n[1];j++){
			if(buf[i][j] == 1){
				fun[0] = buf[i-1][j];
				fun[1] = buf[i+1][j];
				fun[2] = buf[i][j+1];
				fun[3] = buf[i][j-1];
				if(i == 0)fun[0] =1;
				if(j == 0)fun[3] =1;
				if(i == n[0])fun[1] = 1;
				if(j == n[1])fun[2] = 1;
				for(k=0;k<4;k++){
					if(fun[k] == 0)
					{
						cur[i][j]++;
					}
				}
			}
		}
	}
	avr++;
	for(i=0;i<n[0];i++){
		for(j=0;j<n[1];j++){
			if(cur[i][j] > 1)buf[i][j] = 0;
			if(cur[i][j] == 1) w= 1;

		}
	}
	for(i=0;i<n[0];i++){
		for(j=0;j<n[1];j++){
			cur[i][j] = 0;
		}
	}

	if(w == 1){w = 0;goto start;}
}

void output()
{
	fp = fopen("cheese.ans","w");
	fprintf(fp,"%d",avr);
	fclose(fp);
}
void main(void)
{
	input();
	process();
	output();
}