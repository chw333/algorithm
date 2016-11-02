#include<string.h>
#include<stdio.h>
#include<Stdlib.h>
#include<conio.h> 

#define MAX 100
FILE *fp;
int c[MAX][MAX];
char in[MAX];
void input()
{
	fp = fopen("palin.in","r");
		fgets(in,100,fp);
	fclose(fp);
}
void process()
{
	int i,j;
	for(i=0;i<strlen(in);i++){
		for(j=i+1;j<strlen(in);j++){
			if(in[i] == in[j])c[i][j] = c[i+1][j-1];
			else{
				int cur[2],min = 9999;
				cur[0] = c[i+1][j]+1;
				cur[1] = c[i][j-1]+1;
				for(int k=0;k<2;k++)if(cur[k] < min)min = cur[k];
				c[i][j] = min;
			}
		}
	}

}
void output()
{
	printf("%d",c[0][strlen(in)-1]);	
}
void main()
{
	input();
	process();
	output();
}