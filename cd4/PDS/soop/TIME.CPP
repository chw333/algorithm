#include<stdio.h>

char dt1[10][20] = {"one","two","three","four","five","six","seven","eight","nine","ten"};
char dt2[9][20] = {"eleven","twelve","thirteen","fourteen","fifteen","sixteen","seventeen","eighteen", "nineteen"};
char dt3[4][20] = {"twenty","thirty","fourty","fifty"};

void soo(int s, int code)
{
	if ( s >= 1 && s <= 10 )
	{
		if ( code == 1 )
			fprintf(fp,"%c%s", dt1[s-1][0] - 32, &dt1[s-1][1]);
		else
			fprintf(fp,"%s",dt1[s-1]);
	}
	else
	{
		if (s >= 11 && s <= 19)
		{
			if ( code == 1 )
			       fprintf(fp,"%c%s", dt2[s-11][0] - 32, &dt2[s-11][1]);
			else
			printf("%s",dt2[s-11]);
		}
		else
		{
			if ( code == 1 )
				printf("%c%s", dt3[s / 10 - 2][0] - 32, &dt3[s / 10 - 2][1]);
			else
				printf("%s", dt3[s / 10 - 2]);
			if (s % 10 != 0)
			{
				printf("-");
				printf("%s", dt1[s % 10 - 1]);
			}
		}
	}
}

main()
{
	int h,m;
	FILE *fp;
	fp = fopen("clock.in","r");
		fscanf(fp,"%d:%d",&h,&m);
	fclose(fp);
	//h = 3; m = 0;
	if (m == 0)
	{
		soo(h,1);
		printf(" o'clock\n");
	}
	else if (m == 15){
		printf("Quarter past ");
		soo(h,0);
		printf("\n");
	}
	else if (m == 45){
		int bb;
		printf("Quarter to ");
		bb = h + 1;
		if (bb == 13) bb = 1;
		soo(bb,0);
		printf("\n");
	}
	else if (m > 45)
	{
		int bb = h + 1;
		if (bb == 13) bb = 1;
		soo(60 - m, 1);
		printf(" to ");
		soo(bb, 0);
		printf("\n");
	}
	else
	{
		soo(h, 1);
		printf(" ");
		soo(m, 1);
		printf("\n");
	}
}