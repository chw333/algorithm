#include<stdlib.h>
#include<stdio.h>
#include<conio.h>
main()
{
	int i,input,k,fn,cnt;
	static int dt[100];
	char a;
	start:
	for(i=0;i<100;i++){
		dt[i] = 0;
	}
	i = 0 ;	input = 0;	k = 0;	fn = 0;	cnt = 0;

	clrscr();
	printf("?");
	scanf("%d",&input);
	if( input > 30){
		printf("INPUT ERRER");
		goto f;
	}
	cnt = 2;
	fn = 1;
	dt[0] = input -1;
	dt[1] = 1;
	printf("%2d =",input);
	while(dt[0]!=0)
	{
		for(i=0;i<=cnt;i++){
		if(dt[i] != 0 && i != cnt-1)
			printf("%2d + ",dt[i]);

		if(dt[i] !=0 && i == cnt-1)
			printf("%2d",dt[i]);
		}
		if (dt[0] == 1)
		goto d;
		printf("\n   =");

			if ( fn == 1){
				dt[0]--;
				if (dt[0] == 1)
				{
				  dt[cnt] = 1;
				  cnt++;
					fn = 2;
				}
				else
				{
					dt[1]++;
					fn = 2;
				}
			goto end;
			}
			if ( fn == 2){
				dt[1]--;
				if ( dt[1] == 1)
				{
					dt[cnt] = 1;
					cnt++;
				}
				fn = 1;
			}
			end:
	}
	d:
	f:
	printf("\nAGAIN 'Y' END 'N' \n");
	a = getch();
	if( a== 'Y')
		goto start;
	if( a== 'N')
		exit(0);
	if(a!=13&&a!=27)
	goto f;

}
