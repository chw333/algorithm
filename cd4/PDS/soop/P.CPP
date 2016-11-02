#include<stdio.h>
#include<conio.h>
int ccw(int x1,int y1,int x2,int y2,int x3,int y3)
{
	return (x1 * y2 + x2 * y3 + x3 * y1) - (x2 * y1 + x3 * y2 + x1 * y3);
}

main()
{
	int i,j,k;
	int cnt;
	int buf[100][2];

	FILE *fp;
	fp = fopen("input.txt","r");
		fscanf(fp,"%d",&cnt);
		for(i=0;i<cnt;i++){
			fscanf(fp,"%d %d",&buf[i][0],&buf[i][1]);
		}
	fclose(fp);

	for(i=0;i<cnt;i++) // Start point
		for(j=0;j<(cnt - 3);j++) // Distance to End point
		{
			int aa = 0;
			int d = (i + j + 2) % cnt;

			for(k=0;k<=j;k++){
			       int p = (i + k + 1) % cnt;
			       if (ccw(buf[i][0],buf[i][1],buf[d][0],buf[d][1],buf[p][0],buf[p][1]) > 0)
					aa ++;
			}
			//printf("%d-%d %d\n", i, d, aa);
			if (aa == (j + 1))
			{
				// START POINT = i;
				// END POINT = (i + j + 2) % cnt
				// K <- j + 2 bun dolagam..
				int d = (i + j + 2) % cnt;
				int gap = 0;
				for(k=0; k <= j + 1; k++){
				       int p = (i + k) % cnt;
				       gap += buf[p][0] * buf[(p + 1) % cnt][1];
				       gap -= buf[(p + 1) % cnt][0] * buf[p][1];
				}
				gap = gap + buf[d][0] * buf[i][1] - buf[d][1] * buf[i][0];
				gap /= 2;
				printf("--%d-%d %d\n", i, d, -gap);
			}
		}
}