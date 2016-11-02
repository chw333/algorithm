/*
	ID:lge1435001
	PROB:barn1
*/

#include<stdio.h>
#include<stdlib.h>
main()
{

	int i,j,k, dt[200],m,s,c,imsi;
	static int dynamic[50][200];

	FILE *fp;
	fp = fopen("barn1.in","r");
		fscanf(fp,"%d %d %d",&m,&s,&c);
		for(i=0;i<c;i++){
			fscanf(fp, "%d",&dt[i]);
		}
	fclose(fp);
	if (c < m) m = c;

	for(i=0;i<c;i++)
		for(j=0;j<c;j++)
			if(dt[i] < dt[j])
			{
				imsi = dt[i];
				dt[i] = dt[j];
				dt[j] = imsi;
			}

// the best dynamic----------------------------------------------------
	for(i=0;i<c;i++){
		dynamic[0][i] = dt[i] - dt[0] +1;
	}

	for(i=1;i<m;i++){
		for(j=i;j<c;j++){
			int min = 10000;
			for(k = i-1 ; k < j ; k++){
				int buf = dynamic[i-1][k] + dt[j] - dt[k+1] + 1;
				if (min > buf) min = buf;
			}
			dynamic[i][j] = min;
		}

	}

	fp = fopen("barn1.out","w");
		fprintf(fp,"%d\n",dynamic[m-1][c-1]);
	fclose(fp);

/*	for (i = 0; i < m; i++)
	{
		for (j = 0; j < c; j++)
			printf("%d ", dynamic[i][j]);
		printf("\n");
	}
*/
}
