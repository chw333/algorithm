#include<stdio.h>
#include<stdio.h>
#include<conio.h>

int gil[101][101],v[101];
int sell[101][101];
int max = 9999,mn,city,n;
int back[100],fun[100],h;
void visit(int,int,int,int);

void main(void)
{
	FILE *fp;
	int i,j;
	fp = fopen("road.inp","r");
	fscanf(fp,"%d\n%d\n%d\n",&mn,&city,&n);
	for(i=1;i<=n;i++){
		int x,y,imgil,imsell;
		fscanf(fp,"%d %d %d %d\n",&x,&y,&imgil,&imsell);
		gil[x][y] = imgil;sell[x][y] = imsell;
	}
	fclose(fp);
	back[0] = 1;
	visit(1,0,0,1);
	
	fp = fopen("road.out","w");
		fprintf(fp,"%d\n",max);
		for(i=0;i<h;i++)fprintf(fp,"%d\n",fun[i]);
	fclose(fp);
}
void visit(int i,int l,int t,int m)
{
	int j,k;
	v[i] = 1;
	if(i == city && l<=mn && t < max){
		max = t;h = m;
		for(k=0;k<=h;k++)fun[k] = back[k];	
	}	
	for(j=1;j<=n;j++){
		if(gil[i][j] != 0 && v[j] == 0){		
			back[m] = j;
			visit(j,l+sell[i][j],t+gil[i][j],m+1);
			v[j] = 0;
		}
	}
}
