#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<math.h>

#define Input "input.txt","r"

int cnt;
int buf[100][2];
double cur[100];
int stack[100];
FILE *fp;
int ccw(int x1, int y1, int x2, int y2, int x3 , int y3)
{
	int x;
	x = x1 * y2 + x2 * y3 + x3 * y1 - x1 * y3 - x2 * y1 - x3 * y2;
	if(x == 0)return 0;
	if(x > 0) return 1;
	if(x < 0) return -1;
}

void input()
{
	int i;
	fp = fopen("input.txt","r");
		fscanf(fp,"%d\n",&cnt);
		for(i=0;i<cnt;i++)fscanf(fp,"%d %d\n",&buf[i][0],&buf[i][1]);
	fclose(fp);
}
void process()
{
	int i,j,x = 0, y = 0,p[3] = {0,0,0},q = 4,n,f[3] = {1,2,3};
	
	for(i=0;i<cnt;i++){
		if(buf[i][1] >= y){
			if(x > buf[i][0] && buf[i][1] == y){
				x = buf[i][0];
				y = buf[i][1];
				n = i;
			}
			if(buf[i][1] > y){
				x = buf[i][0];
				y = buf[i][1];
				n = i;
			}
		}
	}
	for(i=0;i<cnt;i++){
		if(buf[i][1]  == y && buf[i][0] == x){
			cur[i] = 100;
		}
		else cur[i] = atan2(buf[i][1] - y,buf[i][0] - x);
	}
	for(i=0;i<cnt-1;i++){
		for(j=i+1;j<cnt;j++){
			if(cur[i]<cur[j]){
				double imsi;
				int im;
				imsi = cur[i];cur[i] = cur[j];cur[j] = imsi;
				im = buf[i][0];buf[i][0] = buf[j][0];buf[j][0] = im;
				im = buf[i][1];buf[i][1] = buf[j][1];buf[j][1] = im;
			}
		}
	}
	p[0] = stack[0] = 1;
	p[1] = stack[1] = 2;
	p[2] = stack[2] = 3;
	
	for(i=0;;i++){
		if(ccw(buf[p[0]-1][0],buf[p[0]-1][1],buf[p[1]-1][0],buf[p[1]-1][1],buf[p[2]-1][0],buf[p[2]-1][1]) == 1){	
				for(j=i;j<cnt;j++){
				stack[j] = stack[j+1];
				if(stack[j] == 0)stack[j-1] = 0;
				}
				for(j=0;j<3;j++){
					p[j]--;f[j]--;
					if(p[j] == 0)p[j] = cnt;
		
				}
		}
		else
		{
			for(j=0;j<3;j++){
				p[j]++;f[j]++;
				if(p[j] == cnt+1) p[j] = 1;
			}
			stack[f[2]-1] = q++;
			if(q == cnt+1)q = 1;
		}	
		if(f[2] == 2)break;
	}
}	
void main(void)
{
	input();
	process();
}

 