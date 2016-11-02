#include<stdio.h>
#include<conio.h>
#include<math.h>

int ccw(int x1, int y1, int x2, int y2, int x3 , int y3)
{
	return x1 * y2 + x2 * y3 + x3 * y1 - x1 * y3 - x2 * y1 - x3 * y2;
}

/*
double geri(double x1, double y1, double x2, double y2)
{
	return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}
*/

int buf[100][2],cnt;
int what[100], nwhat;

void process(int start)
{
	int imsi[100][3];
	int i, j, k, c;
	int a;
	int bue;

	nwhat = 0;

	a = start;
	what[nwhat] = a;
	nwhat++;
	do
	{
		c = 0;
		for (i = 0; i < cnt; i++)
			if (a != i)
			{
				imsi[c][0] = buf[i][0];
				imsi[c][1] = buf[i][1];
				imsi[c][2] = i;
				c++;
			}
		for (i = 0; i < c; i++)
			for (j = 0; j < c; j++)
				if (ccw(buf[a][0], buf[a][1], imsi[i][0], imsi[i][1], imsi[j][0], imsi[j][1]) < 0)
				{
					int temp;
					temp = imsi[i][0]; imsi[i][0] = imsi[j][0]; imsi[j][0] = temp;
					temp = imsi[i][1]; imsi[i][1] = imsi[j][1]; imsi[j][1] = temp;
					temp = imsi[i][2]; imsi[i][2] = imsi[j][2]; imsi[j][2] = temp;
				}
		printf("%d,%d,%d : ", buf[a][0], buf[a][1], a);
		for (i = 0;i < c; i++)
			printf("%d,%d,%d   ", imsi[i][0], imsi[i][1], imsi[i][2]);
		printf("\n");
		scanf("%d", &bue);
		if (bue == 0) return;

		a = imsi[0][2];
		what[nwhat] = a;
		nwhat++;
	} while(a != start);
	for (i = 0; i < nwhat; i++)
	{
		printf("%d ", what[i]);
	}
	printf("\n");
}

main()
{
	int max[3] = {9999,9999, 0};
	int i,j;
	FILE *fp;

	fp = fopen("input.txt","r");
		fscanf(fp,"%d",&cnt);
		for(i=0;i<cnt;i++){
				fscanf(fp,"%d %d",&buf[i][0],&buf[i][1]);
			if(buf[i][1] <= max[1])
			{
				if(buf[i][1] == max[1]){
					if(buf[i][0] < max[0]){
						max[0] = buf[i][0];
						max[1] = buf[i][1];
						max[2] = i;
					}
				}
				else
				{
					max[0] = buf[i][0];
					max[1] = buf[i][1];
					max[2] = i;
				}
			}
		}
	printf("-----------------\n");
	process(max[2]);
}