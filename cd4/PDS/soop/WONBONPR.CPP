/*
ID: lge1435001
PROB: pprime
*/
#include <stdio.h>
#include <string.h>
#include <math.h>

int ten[6] = {1, 10, 100, 1000, 10000, 100000};
int sv[4];

int isprime(long bb)
{
	long j;
	for(j=2;j<= ((long) sqrt(bb));j++)
		if(bb%j == 0)
			return 0;
	return 1;
}
void main()
{
	char test[80];
	long i,j,b,bb,a,buff,ia,ib;
	FILE *fp;
	fp = fopen("pprime.in","r");
		fscanf(fp, "%ld",&ia);
		fscanf(fp, "%ld",&ib);
	fclose(fp);


	fp = fopen("pprime.out","w");

	if (ia <= 5) fprintf(fp, "5\n");
	if (ia <= 7) fprintf(fp, "7\n");
	if (ia <= 11) fprintf(fp, "11\n");
	for(i=10;i<9999;i++){
		buff = i;
		for (j = 0; j < 5; j++)
		{
			if ( ten[j] <= i )
				b= j+1;
		}
		bb = (i / 10)*ten[b];
		for (j = 0; j < b; j++)
		{
			bb = bb + (buff % 10) * ten[b - 1 - j];
			buff /= 10; // 1256 -> 125 -> 12 ->  1
					//    6      5     2     1
		}
		if (bb > ib) break;
		if (isprime(bb) && ia<=bb) fprintf(fp,"%ld\n", bb);
	}
	fclose(fp);
}