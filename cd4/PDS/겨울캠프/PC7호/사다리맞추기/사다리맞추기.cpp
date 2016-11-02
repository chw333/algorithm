#include<stdio.h>
#include<conio.h>

int dt[100],dt1[100];
int cnt;
void input()
{
	FILE *fp;
	int i;
	fp = fopen("input.txt","r");
		fscanf(fp,"%d",&cnt);
		for(i=0;i<cnt;i++){fscanf(fp,"%d ",&dt[i]);dt1[i] = dt[i];}
	fclose(fp);
}
void process()
{
	int i,j,imsi,l,fun,k;
	static int che[100][100],co[100];
	for(j=cnt+1;j>0;j--){
		for(i=0;i<=j;i++)
		{
			if(dt[i] > dt[i+1])
			{
				imsi = dt[i]; dt[i] = dt[i+1] ; dt[i+1] = imsi;
				if(dt[i] != 0 && dt[i+1] != 0)
				{

					for(k=0;k<cnt;k++){
						if(dt[i+1] == dt1[k])
							printf("%d\n",k+1);
					}
				}	
			}
		}
	}
	}
	}
}
void main(void)
{
	input();
	process();
}

