include<stdio.h>
#include<conio.h>
int max[2][2];	
int buf[100][100],cur[100];
int cnt[2],cp=0,tt=0;
FILE *fp;
void input()
{
	int i,j;
		fp = fopen("sea.in","r");
		fscanf(fp,"%d %d\n",&cnt[0],&cnt[1]);
		for(i=0;i<cnt[0];i++){
			for(j=0;j<cnt[1];j++)fscanf(fp,"%d ",&buf[i][j]);
			fscanf(fp,"\n");
		}
		fclose(fp);
}
void process()
{
	int i,j,l,k,f;
	int x1,y1,x2,y2;
	fp = fopen("sea.out","w");
	x1 = x2 = y1 = y2 = 0;
	max[0][0] = 0;max[0][1] = 0;max[1][0] = 0;max[1][1] = 0;
	for(i=0;i<cnt[0];i++){
		for(j=i;j<cnt[0];j++){
				if(j == i)for(f=0;f<100;f++)cur[f] = 0;
				for(l=0;l<cnt[1];l++)cur[l] += buf[j][l];
				x1  = y1 = x2 = y2 = 0;				
				for(l=0;l<cnt[1];l++)fprintf(fp,"%3d ",cur[l]);
					fprintf(fp,"\n");
				cp = 0;
				for(l=0;l<cnt[1];l++)
				{
					if(cp+cur[l] >=0)
					{
						x2 = l;	y2 = j;
						cp+= cur[l];
						if(tt < cp){
							tt = cp;max[1][0] = x2;max[1][1] = y2;
							max[0][0] = x1;max[0][1] = y1;
						}
					}
					else{cp = 0;x1 = l;	y1 = i;}
				}
		} 
	}
}
void output()
{
	printf("%d",tt);
	printf("(%d,%d)-(%d,%d)",max[0][0],max[0][1],max[1][0],max[1][1]);

}
void main(void)
{
	input();
	process();
	output();
}