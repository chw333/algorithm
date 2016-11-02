#include<string.h>
#include<stdio.h>
#include<conio.h>

FILE *fp;
int buf[100][100];
int n;
int sum=9999;
char in1[100],in2[100];
void input()
{
	fp = fopen("input.txt","r");
		fgets(in1,100,fp);
		fscanf(fp,"\n");
		fgets(in2,100,fp);
	fclose(fp);
}
void process()
{
	int i,j,k;
	int imsi;
	for(i=1;i<strlen(in2);i++){
		buf[i][0] = i;
		for(j=1;j<strlen(in1);j++){
			if(in1[j-1] == in2[i-1])
				buf[i][j] = buf[i-1][j-1];
			else
			{
				int che[3] = {0,0,0},min = 9999;
				che[0] = buf[i-1][j] +1;
				che[1] = buf[i][j-1] +1;
				che[2] = buf[i-1][j-1] +1;
				for(k=0;k<3;k++){
					if(che[k] < min)min = che[k];
				}
				buf[i][j] = min;
			}
		}
	}
	for(i=0;i<=strlen(in1);i++)if(sum>buf[strlen(in2)][i])sum = buf[strlen(in2)][i];
}
void output()
{
	printf("%d - ±Ù»ç¸ÅÄª",sum);
}


void main(void)
{
	input();
	process();
	output();
}