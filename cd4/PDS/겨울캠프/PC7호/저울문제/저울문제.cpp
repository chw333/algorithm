#include<stdio.h>
#include<conio.h>
#include<stdlib.h>

FILE *fp;
int buf[100][2];
int cur[100][100],cnt[100],n;
int sum,k;
void main(void)
{
	int i,j;
	fp = fopen("scale.in","r");
		fscanf(fp,"%d\n",&n);
		for(i=0;i<n;i++)fscanf(fp,"%d ",&buf[i][0]);
		fscanf(fp,"\n");
		for(i=0;i<n;i++){
			fscanf(fp,"%d ",&buf[i][1]);
			cur[buf[i][1]][0] = 1;
		}
		fscanf(fp,"\n");
		fclose(fp);
		for(i=0;i<n;i++)sum += buf[i][1];

		if(sum%2 != 0 ) printf("IMPOSSIBLE");
		sum /=2;
		for(i=0;i<n;i++)cnt[i] = 1;

		for(i=0;i<sum;i++){
			if(cur[i][0] == 1)
			{
				for(j=0;j<n;j++){
						if(cur[i+buf[j][1]][0] != 1)
						{
							int k;
							for(k=0;k<n;k++)if(cur[buf[j][1]][k] == 1)cur[i+buf[j][1]][k] = 1;
							
   							if(cur[i+buf[j][1]][buf[j][1]+1] != 0){
								cur[i+buf[j][1]][0] = 1;
								cur[i+buf[j][1]][buf[j][1]+1] = 1;
								cnt[i+buf[j][1]]++;	
							}
						}
				}
			}
		}
		for(i=0;i<50;i++){
			printf("%d",cur[sum][i]);
		}
}
