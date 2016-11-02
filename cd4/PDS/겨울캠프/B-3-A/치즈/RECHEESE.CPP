#include<stdio.h>
#include <conio.h>

main()
{
	int a[100][100];
	int  i, j;
	int que[4000][4];
	int s,e;
	int dir[4][2] = { {0, 1}, {0, -1}, {1, 0}, {-1, 0} };
	int MAX;
	int n[2];
	int cur[100][100];
	int buf[100][100];
	int fun[4],avr,k,w;

	clrscr();
	FILE *fp;
	fp = fopen("cheese.inp","r");
		fscanf(fp,"%d %d\n",&n[0],&n[1]);
		for(i=0;i<n[0];i++)
			for(j=0;j<n[1];j++){
				fscanf(fp,"%d ",&a[i][j]);
			}
		fscanf(fp,"\n");
	fclose(fp);
	if(n[0] > n[1])MAX = n[0];
	if(n[1] > n[0])MAX = n[1];
	if(n[0] == n[1]) MAX = n[0];
	e = 0;
	s = 0;
	que[s][0] = 1;que[s][1] = 1;que[s][2] = 2;que[s][3] = 0;a[1][1] = -1;
	for (i = 0; i < MAX; i++)
	{
		for (j =0; j < MAX; j++)
			if (a[i][j] == 1) printf("XX ");
			else printf("   ");
		printf("\n");
	}

	do
	{
		for (i = 0; i < 4; i++)
		{
			int bx = que[s][0] + dir[i][0];
			int by = que[s][1] + dir[i][1];
			if (a[by][bx] == 0)
			{
				e++;
				que[e][0] = bx;
				que[e][1] = by;
				que[e][3] = s;
				a[by][bx] = -1;
			}
		}

		s++;
		} while (s <= e);

	start:
	for(i=0;i<n[0];i++){
		for(j=0;j<n[1];j++){
			if(buf[i][j] == 1){
				fun[0] = buf[i-1][j];
				fun[1] = buf[i+1][j];
				fun[2] = buf[i][j+1];
				fun[3] = buf[i][j-1];
				if(i == 0)fun[0] =1;
				if(j == 0)fun[3] =1;
				if(i == n[0])fun[1] = 1;
				if(j == n[1])fun[2] = 1;
				for(k=0;k<4;k++){
					if(fun[k] == 0)
					{
						cur[i][j]++;
					}
				}
			}
		}
	}
	avr++;
	for(i=0;i<n[0];i++){
		for(j=0;j<n[1];j++){
			if(cur[i][j] > 1)buf[i][j] = 0;
			if(cur[i][j] == 1) w= 1;

		}
	}
	for(i=0;i<n[0];i++){
		for(j=0;j<n[1];j++){
			cur[i][j] = 0;
		}
	}

	if(w == 1){w = 0;goto start;}
	printf("%d",avr);
}



