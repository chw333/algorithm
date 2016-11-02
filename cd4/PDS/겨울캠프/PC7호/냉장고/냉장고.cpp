#include<stdio.h>
#include<conio.h>

FILE *fp;
int buf[100][2];
int cur[100],cur1[100];
int cnt;

void input()
{
	int n,i;
	fp = fopen("input.txt","r");
		fscanf(fp,"%d\n",&cnt);
		for(i=0;i<cnt;i++)fscanf(fp,"%d %d\n",&buf[i][0],&buf[i][1]);
		}
void process()
{
	int i,j,cnt1;
	cnt1 = cnt;
	for( i = 0 ; i < cnt-1 ; i++ ){
		for(j=i+1;j<cnt;j++){
			if(buf[i][1] > buf[j][1]){
				int imsi;
				imsi = buf[i][0]; buf[i][0] = buf[j][0];buf[j][0] = imsi;
				imsi = buf[i][1]; buf[i][1] = buf[j][1];buf[j][1] = imsi;

			}
		}
	}
	while(cnt1>1){
		for(i=1;i<cnt;i++){
			if(buf[i][0] <= buf[0][1] && buf[0][1] <=buf[i][1]&&buf[i][0] !=0)
			{
				buf[i][0]  = buf[i][1] = 0;
				printf("%d",buf[0][1]);
				cnt1--;
			}
		}
		for(i=1;i<cnt;i++){
			if(buf[i][1] != 0){
				buf[0][0] = buf[i][0];
				buf[0][1] = buf[i][1];
			}
		}
	}


}
void output()
{


}

void main(void)
{
	input();
	process();
	output();
}