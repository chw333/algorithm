#include<stdlib.h>
#include<math.h>
#include<stdio.h>
#include<conio.h>
void main(void)
{
	FILE *fp;
	static int i,cnt,j,x=9999,y=9999;
	static int dt[100][2];
	static double cur[100];

	fp = fopen("input.txt","r");
	fscanf(fp,"%d\n",&cnt);
		for(i=0;i<cnt;i++){
		fscanf(fp,"%d %d\n",&dt[i][0],&dt[i][1]);
		if(y > dt[i][1]){
					if(x > dt[i][0] || y > dt[i][1]){
			   y = dt[i][1];
			   x = dt[i][0];
			}
		}

	}
	for(i=0;i<cnt;i++){
		if( x != dt[i][0] && y != dt[i][1])
		{
			cur[i] = atan2(dt[i][1] - y, dt[i][0] - x);
		}
	}
	for(i=0;i<cnt-1;i++){
		for(j=i+1;j<i;j++){
			if(cur[i] > cur[j]){
				int imsi;
				imsi = cur[i];cur[i] = cur[j];cur[j] = imsi;

			}
		}
	}

	for(i=0;i<cnt;i++){
		for(j=0;j<cnt;j++){
			for(l=0;l<cnt;l++){
				if( x == 1){
				}
				if( x == 0){
				}
				if( x == -1){
				}

}
int gho(int x1,int y2,int x2,int y3,int x3,int y1)
{

	int x;
	x = (x1*y2 + x2*y3 + x3*y1) - (x2*y1+x3*y2+x1*y3);
	if(x== 0)
		return 0;
	if(x>0)
		return 1;
	if(x<0)
		return -1;

}