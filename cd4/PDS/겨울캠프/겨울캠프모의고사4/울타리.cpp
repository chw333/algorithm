#include<math.h>
#include<stdio.h>
#include<conio.h>

FILE *fp;
int dt[100];
int crs[100],cur[100];
int check[100];
int n,s,e,max = 9999;
int sss(int x,int y)
{
	if((x+y)<0) return (x+y)*-1;
	else return x+y;
}

void input()
{
	int i;
	fp = fopen("fence.in","r");
		fscanf(fp,"%d\n",&n);
		for(i=0;i<n;i++)fscanf(fp,"%d\n",&dt[i]);
	fclose(fp);
}
void process()
{
	int i,j,k,sum,linex,linen;

	for(i=0;i<n;i++){
		int cnt = 0;
		for(j=i;j<n;j++){
			cnt+=dt[j];
			if(abs(cnt) == max){
				if(i-j == linex){
					if(dt[i]<dt[s]){
						max = abs(cnt);s = i;e = j;	linex = i-j;
						goto end;
					}	
				}
				if(i-j > linex){
					max = abs(cnt);s = i;e = j;linex = i-j;
				}
			}
			if(abs(cnt) < max){
				max = abs(cnt);	s = i;e = j;linex = i-j;
			}
end:;
		}
	}
}
void output()
{
	fp = fopen("fence.out","w");
	fprintf(fp,"%d %d\n",s+1,e+1);
}
void main(void)
{
	input();
	process();
	output();
}