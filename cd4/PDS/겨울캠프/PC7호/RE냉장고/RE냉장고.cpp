#include<stdio.h>
#include<conio.h>
#include<stdlib.h>

FILE *fp;
int fun[100];
int cur[100],f;
int dt[100][2];
int n;

void main(void)
{
	int i,j,gu,tt = 0,k=0;                    
	fp= fopen("input.txt","r");
		fscanf(fp,"%d\n",&n);
		for(i=0;i<n;i++)fscanf(fp,"%d %d\n",&dt[i][0],&dt[i][1]);
	fclose(fp);
		

	for(i=0;i<n-1;i++){                  
		for(j=i+1;j<n;j++){
			if(dt[i][1] > dt[j][1]){           
				int imsi;
				imsi = dt[i][0];dt[i][0] = dt[j][0];dt[j][0]=imsi;
				imsi = dt[i][1];dt[i][1] = dt[j][1];dt[j][1]=imsi;
			}
		}
	}
	fun[0] = 1;
	gu = dt[0][1];
	fp = fopen("output.txt","w");
	
	for(i=0;;i++){
		for(j=0;j<n;j++){
			if(fun[j] != 1 && dt[j][0] <= gu && gu <=dt[j][1]){
				fun[j] = 1;
			}
		}
		for(j=0;j<n;j++){if(fun[j] == 1)tt++;}
		cur[f] = gu;
		f++;
		for(j=0;j<n;j++)if(fun[j] != 1){fun[j] = 1;gu = dt[j][1];break;}
		if(tt == n){
			fprintf(fp,"%d\n",f);
			for(j=0;j<f;j++){
					fprintf(fp,"%d\n",cur[j]);
			}
			exit(0);				
		}
		tt=0;
	}
	fclose(fp);
}