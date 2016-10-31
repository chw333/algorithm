#include<stdlib.h>
#include<stdio.h>
#include<conio.h>
main()
{
	int i,j;
	int k[10] = {11,22,12,23,13,24,14,25,15,26};
	static int k1[10];
	static int input,cnt,cnt1,cnt2,ct;
	char a;
	clrscr();

	start:
		ct = 0;
	printf("?");
	scanf("%d",&input);
	switch(input)
	{
		case 1:
			cnt = 0;
		break;
		case 2:
			cnt = 2;
		break;
		case 3:
			cnt = 4;
		break;
		case 4:
			cnt = 6;
		break;
		case 5:
			cnt = 8;
		break;
	}
	set:
	while(1)
	{
			if (cnt >= 7)
			cnt2=cnt-7;
		if (cnt<=6)
			cnt2=cnt+3;


		if ( k1[cnt] == 1|| k1[cnt2] == 1)
			goto end;
		if ( cnt1 == 3 && k1[cnt] != 1){
			k1[cnt] = 0;
			cnt1=0;
		goto f;
		}

		if ( cnt1 < 3){
			k1[cnt] = 1;
			cnt1++;
		}
		f:
		cnt++;

		if (cnt == 10)cnt = 0;
	}
		end:
		ct++;
		if(ct == 4) goto t;
			printf("%d ==>",ct);																											if ( ct == 2 ) printf("F5 P1 F1 F2 P3 F3");if (ct == 3) printf("F2 P5 F5");
		if(ct >=2 ) goto k;
		for(i=0;i<10;i++){
			if(k1[i] == 1)
			{
				if(k[i]-10 <= 9)
					printf("F%d ",k[i]-10);
				if(k[i]-20 <= 9 && 1<= k[i]-20)
					printf("P%d ",k[i]-20);
			}
		}
		k:printf("\n");
		k1[0] = 0;
		for(i=2;i<10;i+=2)	k1[i] = 0;
		for(i=1;i<10;i+=2){
			if(k1[i] != 1){
			cnt--;
			cnt1=0;
			}
		}
		goto end;
	t:
	printf("\nAGAIN 'Y' END 'N' \n");
	a = getch();
	if( a== 'Y')
		goto start;
	if( a== 'N')
		exit(0);
	if(a!=13&&a!=27)
	goto t;

}