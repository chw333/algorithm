/*
ID: lge1435001
PROG: beads
*/
#include<stdio.h>
#include<string.h>

main()
{
	static char dt[1000];
	static int n,i,si,wi;
	static int curup,curdn,hap,hapgj;
	int rr = 0, bb = 0;

	FILE *fp;
	fp = fopen ("beads.in","r");
		fscanf(fp,"%d",&n);
		fscanf(fp,"%s",dt);
	fclose(fp);
/////////////////////////////////////////////////////////

	for (i = 0; i < n; i++)
	{
		if (dt[i] == 'r') rr = 1;
		if (dt[i] == 'b') bb = 1;
	}
	if ((rr + bb) <= 1)
	{
		hapgj = n;
	}
	else
	for ( i = 0 ; i < n ; i ++){
		if (dt[i]!=dt[(i+1) % n])
		{
			char left, right;

			si = i;

			left = dt[i];
			right = dt[i + 1];

			while(left == dt[si] || left == 'w' || dt[si] =='w')
			{
				if (dt[si] != 'w')
					left = dt[si];
				curdn++;
				si = (si + (n - 1)) % n;
			}
			wi = i+1;

			while(right == dt[wi] || right == 'w' || dt[wi] =='w')
			{

				if (dt[wi] != 'w')
				{
					//if (i == 27) printf("%d \n", wi);

					right = dt[wi];
				}
				curup++;
				wi = (wi + 1) % n;
			}
			hap = curup+curdn;
			if(hapgj<hap)
			{
				hapgj = hap;
			}
			curup = 0 ; curdn = 0;
			wi = 0;si = 0;
	   }

	}
	fp = fopen("beads.out","w");
		fprintf(fp,"%d\n",hapgj);
	fclose(fp);
	return 0;
}
