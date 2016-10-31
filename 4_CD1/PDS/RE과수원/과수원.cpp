#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
int max;
void input()
{
	FILE *fp;
	fp = fopen("input.txt","r");
		fscanf(fp,"%d\n",&n);
		for(i=0;i<n;i++)fscanf(fp,"%d %\n",&dt[i][0],&dt[i][1]);
	fclose(fp);
}

void devide(int x1,int y1,int x2,int y2)
{
	int i,j;
	for(i=0;i<n;i++){
		if(x1 < x[i] && x[i] < x2 && y1 < y[i] && y[i] < y2)
			a[++cnt] = i;
	}
	if(cnt == 0){
		if(max < (x2-x1)*(y2-y1))
			max = (x2-x1)*(y2-y1);
	}
	else{
		for(i = 1;i<=cnt;i++){
			divide(X[a[i]],y1,x2,y2);
			divide(x1,y1,X[a[i]],y2);
			divide(x1,Y[a[i]],x2,y2);
			divide(x1,y1,x2,Y[a[i]]);
		}
	}

	

}
void main(void)
{
	input();
	devide(0,0,1000,1000);
	printf("%d",max);
}
