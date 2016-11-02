#include<stdio.h>

int N;
int save[20];
static int total;

int x[20];
int d1[39];
int d2[39];
FILE *fp;

void queen(int n)
{
	int i;

	if ( n == N )
	{
		if (total < 3)
		{
		for(i=0;i<N-1;i++)
			fprintf(fp,"%d ",save[i] + 1);
			fprintf(fp,"%d",save[N-1]+1);
			//printf("%d ",save[i] + 1);

		fprintf(fp,"\n");
		}
		//printf("\n");
		total++;
	}

	else
	{
		for(i=0;i<N;i++){
			if(x[i] == 0 && d1[i+n] == 0 && d2[N-1-i+n] == 0){
				save[n] = i;
				x[i] = 1;
				d1[i+n] = 1;
				d2[N-1-i+n] = 1;
				queen(n+1);
				x[i] = 0;
				d1[i+n] = 0;
				d2[N-1-i+n] = 0;
			}
		}
	}

}
void main()
{
//	fp = fopen("checker.in","r");
//	fscanf(fp,"%d",&N);
//	fclose(fp);
	fp = fopen("checker.out","w");
	N=6;
	queen(0);
	fprintf(fp,"%d\n", total);
	fclose(fp);
}
