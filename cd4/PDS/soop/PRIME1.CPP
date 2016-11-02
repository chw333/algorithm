/*
 PROG: pprime
 ID: joongee001
*/
#include <stdio.h>

int ten[6] = {1, 10, 100, 1000 ,10000, 100000};
//int prime[100];
char realprime[10000000]; 
int a, b;
FILE *fp;

int isprime(int aa)
{
	if ((aa < a) || (aa > b)) return 0;
	if (realprime[aa] == 1) return 0;	
	return 1;
}

void comb(int n, int soo, int testn, int testwhat)
{
	int i, test, buff;
	if (n <= 0)
	{		
		if (testwhat)		
			test = soo / 10 * ten[testn] ;
		else
			test = soo / 100 * ten[testn] ; 		
		buff = soo / 10;
		for (i = 0; i < testn; i++)		
		{
			test += (buff % 10) * ten[testn - 1 - i];
			buff /= 10;
		}
		if (isprime(test)) fprintf(fp, "%ld\n", test);		
	}
	else
	{
		if (soo == 1)
		{
			for (i = 1; i < 10; i+=2)
				comb(n - 1, i * 10, testn, testwhat);
			
		}
		else
		{
			for (i = 0; i < 10; i++)
				comb(n - 1, (soo + i) * 10, testn, testwhat);
		}
	}
}

void main()
{
	int i, j, total = 0;		
	fp = fopen("pprime.in", "r");
	fscanf(fp, "%d", &a);
	fscanf(fp, "%d", &b);		
	fclose(fp);

	for (i = 2; i <= b; i++)
		if (realprime[i] == 0)
		{
			for (j = i * 2; j <= b; j += i)
				realprime[j] = 1;
		}
	fp = fopen("pprime.out", "w");
	comb(1, 1, 1, 0);
	comb(1, 1, 1, 1);	
	comb(2, 1, 2 , 0);
	comb(2, 1, 2 , 1);	
	comb(3, 1, 3 , 0);
	comb(3, 1, 3 , 1);	
	comb(4, 1, 4, 0);
	fclose(fp);
}, 1);
	comb(2, 1, 2 , 0);
	comb(2, 1, 2 , 1);
	comb(3, 1, 3 , 0);
	comb(3, 1, 3 , 1);
	comb(4, 1, 4, 0);
	fclose(fp);
}