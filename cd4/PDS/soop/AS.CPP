#include<stdio.h>
#include<conio.h>
main()
{
	int i;
	for(i=1;i<256;i++){
		printf("%d %c",i,i);
		if(i%10==0){
		clrscr();
		getch();
		}
	}
}