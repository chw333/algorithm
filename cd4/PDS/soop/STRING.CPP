#include<stdio.h>
#include<conio.h>
main()
{
	int i,j,l;
	static char data[100];
	int input;
	char input1;
	static int cnt;
	int wi1,wi2;

	clrscr();
	printf("INPUT DATA ( char , int )");
	scanf("%c,%d",&input1,&input);
		wi1=40;
		wi2=1;

		for(i= input/2 ; i>0 ; i--)
		{
			for(l=0;l<4;l++)
			{
					for(j=i;j>0;j--)
					{

						data[cnt] = input1;

						if(input1 == 'z')
						{
							input1 = 'a'-1;
						}
						if(input1 == 'Z')
						{
							input1 = 'A'-1;
						}
						if(input1 == '9')
						{
							input1 = '0'-1;
						}
					input1++; cnt ++;
						}
			}
		}
		data[cnt]  = input1;
		cnt = 0;
		clrscr();
		for(i=input/2;i>0; i--)
		{
			for(j=1;j<=i;j++)
			{
				gotoxy(wi1,wi2);
				printf("%c",data[cnt]);
				cnt++;wi1--;wi2++;
			}
			for(j=1;j<=i;j++)
			{
				gotoxy(wi1,wi2);
				printf("%c",data[cnt]);
				cnt++;wi1++;wi2++;
			}
			for(j=1;j<=i;j++)
			{
				gotoxy(wi1,wi2);
				printf("%c",data[cnt]);
				cnt++;wi1++;wi2--;
			}
			for(j=1;j<=i;j++)
			{
				gotoxy(wi1,wi2);
				printf("%c",data[cnt]);
				cnt++;wi1--;wi2--;
			}
		wi2++;
		}
		gotoxy(wi1,wi2);
		printf("%c",data[cnt]);

}
