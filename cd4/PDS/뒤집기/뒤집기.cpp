#include<stdio.h>
#include<conio.h>
#include<stdlib.h>

#define MAX 512

int buf[10];
char dt[10][10];
int cur[10];
int k,so[1000][10],n,push[1000][10];

void process1()
{
	int i[10],k,f=0;
	for(i[0]=0;i[0]<=1;i[0]++){
	 if(i[0] == 1){buf[1]++;buf[2]++;buf[4]++;buf[5]++;}
	
	 for(i[1]=0;i[1]<=1;i[1]++){
		 if(i[1] == 1){buf[1]++;buf[2]++;buf[3]++;buf[4]++;buf[5]++;buf[6]++;}
	
		 for(i[2]=0;i[2]<=1;i[2]++){
			 if(i[2] == 1){buf[2]++;buf[3]++;buf[5]++;buf[6]++;}
		
			 for(i[3]=0;i[3]<=1;i[3]++){
				 if(i[3] == 1){buf[1]++;buf[2]++;buf[4]++;buf[5]++;buf[7]++;buf[8]++;}
			
				 for(i[4]=0;i[4]<=1;i[4]++){
					 if(i[4] == 1){buf[1]++;buf[2]++;buf[3]++;buf[4]++;buf[5]++;buf[6]++;buf[7]++;buf[8]++;buf[9]++;}
				
					 for(i[5]=0;i[5]<=1;i[5]++){
						 if(i[5] == 1){buf[2]++;buf[3]++;buf[5]++;buf[6]++;buf[8]++;buf[9]++;}
					
						 for(i[6]=0;i[6]<=1;i[6]++){
							  if(i[6] == 1){buf[4]++;buf[5]++;buf[7]++;buf[8]++;}
						  
							 for(i[7]=0;i[7]<=1;i[7]++){
								if(i[7] == 1){buf[4]++;buf[5]++;buf[6]++;buf[7]++;buf[8]++;buf[9]++;}
									
								for(i[8]=0;i[8]<=1;i[8]++){
									if(i[8] == 1){buf[5]++;buf[6]++;buf[8]++;buf[9]++;}	
									for(k=1;k<=9;k++){so[f][k] = buf[k]%2;push[f][k] = i[k-1];}
									f++;
								}
							 }
						 }
					 }
				 }
			}
		 }
	 }
}
}
void input()
{
	FILE *fp;
	int i;	
	fp = fopen("input.txt","r");
	fscanf(fp,"%d\n",&n);
		for(i=0;i<n;i++){
			fgets(dt[i],9,fp);
		}
	fclose(fp);
}
void process2()
{
	int i,j;
	for(k=0;k<n;k++){
		for(i=0;i<9;i++)if(dt[k][i] == 'b')cur[i] = 1;
		
		for(i=0;i<MAX;i++){
			int visit[10];
			for(j=0;j<8;j++){
				int imsi = cur[i];
				if(so[i][j] != imsi && imsi == 0)imsi++;
				if(so[i][j] != imsi && imsi == 1)imsi = 0;
				if(imsi != 0)break;
				else{
					visit[j] = 1;
					if(j == 7){for(int f = 0; f<9;f++)if(visit[j] == 1)printf("%d",f+1);printf("\n");}
				}
			}
		}
	}
}
void main(void)
{
	process1();
	input();
	process2();
}
