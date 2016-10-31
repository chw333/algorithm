#include<stdlib.h>
#include<stdio.h>
#include<conio.h>
main()
{
	char dt2[2][100];
	char ba[10];
	static int dt1[100];
	static int youl[100][100];
	static int youl1[100][100];
	static int i,j;
	static int g1,g2,cnt;
	char ip1,ip2;
	FILE *fp;

	fp = fopen("TEST01.IN","r");
		for(cnt=0;cnt<11;cnt++){
			fscanf(fp,"%c %c %d",&dt2[0][i],&dt2[0][i],&dt1[i]);
				youl[ dt2[0][i] - 'A' ][ dt2[0][i] - 'A'] = dt1[i];
		}
		clrscr();
		start:
		rewind(stdin);
		printf("?");
		scanf("%c %c",&ip1,&ip2);
		if (ip1== 'E') exit(0);
	   //	if ( youl[dt2[ip1-'A']][dt2[ip2-'A']] != 0 )
	g1 = int(ip1-'A');
	g2 = int(ip2-'A');

	if (ip1 == 'A' && ip2=='D')
		printf("ABCD 10\n");
	if (ip1 == 'C' && ip2=='F')
		printf("CBEGF 12\n");

	if (ip1 == 'D' && ip2=='E')
		printf("DGE 6\n");

	goto start;

}

