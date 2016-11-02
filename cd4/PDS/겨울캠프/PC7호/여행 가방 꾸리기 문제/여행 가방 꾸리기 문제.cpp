#include<stdio.h>
#include<conio.h>
#include<stdlib.h>

FILE *fp;
int cnt;
double buf[100],sum;
int check[100];

void input()
{
	int i,j;
	fp = fopen("input.txt","r");
		fscanf(fp,"%d\n",&cnt);
		for(i=0;i<cnt;i++)fscanf(fp,"%ld ",&buf[i]);
}
void process()
{
	int i,j;
	double sum = 1;
		for(i=0;i<cnt;i++){
				sum += buf[i];
		}
		sum /= 2;

		for(i=0;i<cnt-1;i++){
			for(j=1;j<cnt;j++){
				if(buf[i] > buf[j])
				{
					int imsi;
					imsi = buf[i];buf[i] = buf[j];buf[j] = imsi;
				}
			}
		}


		for(i=0;i<cnt;i++){
			int check;
start:
			for(j=0;j<cnt;j++){
				if(sum > buf[j]){
					sum -= buf[j];
					check = 1;
					printf("%d",buf[i]);
				}
				if(check == 1 && buf[i] != 0)goto start;
				else sum = 1;
			}
		}
void main(void)
{
	input();
	process();
}