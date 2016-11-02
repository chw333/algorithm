#include<stdio.h>
#include<conio.h>

#define MAX 15
main()
{
	int a[100][100];
	int dt[100][100];
	int i, j;
	int que[4000][4];
	int s,e,d[2],k,f,p;
	int dir[3][2] = { { 0 , 1 } , { - 1 , 1 } , { 1 , 1 }};
	int n[2];
	FILE *fp;
		fp = fopen("path.inp","r");
			fscanf(fp,"%d\n",&k);
			fscanf(fp,"%d %d\n",&d[0],&d[1]);
		for(i=0;i<d[0];i++){
			for(j=0;j<d[1];j++){
				fscanf(fp,"%d ",&dt[i][j]);
			}
		fscanf(fp,"\n");
		}
	fclose(fp);
	e = 0;
	s = 0;

	for(f=0;f<d[0];f++){
		for(p=0;p<d[1];p++){
			que[s][0] = f;
			que[s][1] = p;
			que[s][2] = 2;
			que[s][3] = 0;
			a[1][1] = 2;
			do
			{
				for (i = 0; i < 3; i++)
				{
					int bx = que[s][0] + dir[i][0];
					int by = que[s][1] + dir[i][1];
					if (a[by][bx] == 0)
					{
						e++;
						que[e][0] = bx;
						que[e][1] = by;
						que[e][2] = que[s][2] + dt[bx][by];
						que[e][3] = s;
						a[by][bx] = que[e][2];
					}
				}
				s++;
			} while (s <= e);
		}
	}
}