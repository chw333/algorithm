#include<string.h>
#include<stdio.h>
#include<conio.h>
main()
{
	char buf[100];
	int i;
	clrscr();
	printf("¹®ÀÚ¿­ : ");
	gets(buf);
	for(i=strlen(buf)-1;i>=0;i--){
		if(buf[i] == ' '){printf(" "); goto end;}
		if((buf[i] >='a' && buf[i]<='z') || (buf[i] >='A' && buf[i]<='Z'))
			printf("%c",buf[i]);
		else
		{
			printf("%c",buf[i-1]);
			printf("%c",buf[i]);
			i--;
		}
		end:
	}
}
