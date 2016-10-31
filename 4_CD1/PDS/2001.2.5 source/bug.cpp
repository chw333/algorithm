#include <stdio.h>
#include <fstream.h>
#include <math.h>

int n,garo,sero,max=-9999,bugchk[100],count;

int bugx[100],bugy[100],max_x1,max_y1,max_x2,max_y2;

int no_bug_in_limit(int x1, int y1, int x2, int y2)
{
	int i,chk=1;

	count=0;
	for(i=1; i<=n; i++)
		if(bugx[i]>x1 && bugx[i]<x2 && bugy[i]>y1 && bugy[i]<y2){
			bugchk[++count]=i;
		}
	
	if(count==0) return 1;
	else return 0;
}
		
void divide(int x1, int y1, int x2, int y2)
{
	int width,i;
		
	if(no_bug_in_limit(x1,y1,x2,y2)){
		width=abs((x1-x2)*(y1-y2));
		if(width>max){
			max=width;
			max_x1=x1;
			max_y1=y1;
			max_x2=x2;
			max_y2=y2;
		}
	}
	else
		for(i=1; i<=count; i++){
			divide(bugx[bugchk[i]],y1,x2,y2);
			divide(x1,bugy[bugchk[i]],x2,y2);
			divide(x1,y1,bugx[bugchk[i]],y2);
			divide(x1,y1,x2,bugy[bugchk[i]]);
		}
}

void main(void)
{
	int i;
	FILE *fp;
		fp = fopen("bug.inp","r");
		fscanf(fp,"%d\n",&n);
	for(i=1; i<=n; i++)fscanf(fp,"%d %d\n",&bugx[i],&bugy[i]);
	fclose(fp);
	divide(0,0,1000,1000);
	printf("(%d,%d) - (%d,%d) - (%d,%d) - (%d,%d)",max_x1,max_y1,max_x2,max_y1,max_x2,max_y2,max_x1,max_y2);
}