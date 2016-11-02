#include<conio.h>
#include<stdio.h>
#include<stdlib.h>
#define MAX 100

int dt[MAX][MAX];
int cnt[2];
int dyn[MAX];
int visit[MAX],buf[MAX],max,gojum;
FILE *fp;
	
void input()
{
	int i,j,k,gap,t,f,l;
	fp = fopen("boxes.inp","r");
		fscanf(fp,"%d %d",&cnt[0],&cnt[1]);
		for(i=0;i<cnt[0];i++){
			buf[i]=i+1;
			for(j=0;j<cnt[1];j++)fscanf(fp,"%d ",&dt[i][j]);
			fscanf(fp,"\n");
		}
	fclose(fp);
	for(k=0;k<cnt[0];k++){
		for(gap=1;gap<cnt[1]/3;gap=3*gap+1);
			while(gap>0){
				for(i=gap;i<cnt[1];i=i++){
					for(j=i-gap;j>=0;j=j-gap){
						if(dt[k][j]>dt[k][j+gap]){
							t=dt[k][j];dt[k][j] = dt[k][j+gap];dt[k][j+gap]=t;
						}
						else
							break;
					}
				}
			gap=gap/3;
			}
	}
	for(gap=1;gap<cnt[0]/3;gap=3*gap+1);
			while(gap>0){
				for(i=gap;i<cnt[0];i=i++){
					for(j=i-gap;j>=0;j=j-gap){
						for(l=0;l<cnt[1];l++){
							if(dt[j][l]==dt[j+gap][l])continue;
							if(dt[j][l]>dt[j+gap][l]){
								for(f=0;f<cnt[1];f++){t=dt[j][f];dt[j][f]=dt[j+gap][f];dt[j+gap][f]=t;}
								t=buf[j];buf[j]=buf[j+gap];buf[j+gap]=t;
								break;
							}
							else
								break;
						}
					}
				}
			gap=gap/3;
			}
}
void process()
{
	int i,j,k;

	for(i=1;i<cnt[0];i++){
		for(j=0;j<i;j++){
			if(dyn[j]+1 >= dyn[i]){
				int count = 0;
				for(k=0;k<cnt[1];k++){
					if(dt[j][k] < dt[i][k])count++;
					else break;
				}
				if(count ==cnt[1]){
					dyn[i] = dyn[j]+1;
					if(dyn[i] > max){
						max = dyn[i];
						gojum = i;
					}
				visit[i] = j+1;
				}
			}
		}
	}
}
void output()
{
	int i,j,imsi[MAX];
	for(i=0;i<=max;i++){
		imsi[i] = buf[gojum];
		gojum = visit[gojum]-1;
	}
	fp = fopen("boxes.out","w");
	fprintf(fp,"%d\n",max+1);
	for(i=max;i>=0;i--)fprintf(fp,"%d ",imsi[i]);
	fclose(fp);

	for(i=0;i<cnt[0];i++){
		for(j=0;j<cnt[1];j++){
			printf("%3d ",dt[i][j]);
		}
		printf("%2d",dyn[i]);
		printf("\n");
	}
}
void main(void)
{
	input();
	process();
	output();
}