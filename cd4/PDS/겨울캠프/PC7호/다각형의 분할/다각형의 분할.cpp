#include<stdio.h>
#include<conio.h>
#include<math.h>
#include<stdlib.h>

#define Input "input.txt","r"
FILE *fp;
int cnt;
int tri[100];
int sq[100];

void input()
{
	fp = fopen(Input);
		fscanf(fp,"%d ",&cnt);
	fclose(fp);
}
void process()
{
	int i,j,k;
  	tri[2] = tri[3] = 1;
	for(i=4;i<cnt;i++){
		for(k=2;k<i-1;k++){
			tri[i] += (tri[k] * tri[i-k+1]);
		}
	}
/*	for(i=5;i<cnt;i++){
		for(j=2;j<i-1;j++){
			sq[i] += sq[k-j+1] * a[n-k+1];
		}
	}
*/
}
void output()
{
	int i;
	for(i=0;i<cnt;i++){
		printf("%3d ",tri[i]);
	}

}
void main(void)
{
	input();
	process();
	output();
}