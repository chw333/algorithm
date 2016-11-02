#include<stdlib.h>
#include<stdio.h>
#include<conio.h>
main()
{
	char dt[3][100],a,b,c;
	static int wa,wb,wc,i;
	printf("A$");
	gets(dt[0]);
	printf("B$");
	gets(dt[1]);
	printf("C$");
	gets(dt[2]);
	for(i=0;i<100;i++){
		dt[0][i] = ' ';
		dt[1][i] = ' ';
		dt[2][i] = ' ';
	}

	a=dt[0][wa];b=dt[1][wb];c=dt[2][wc];
	start:
	clrscr();
	printf("A$           B$       C$\n");
	printf("------------------------\n");
	printf("%c          %c        %c\n",a,b,c);
	if(a<b && b<c && a<c){
	wa++;
	a= dt[0][wa];
	goto end;
	}
	if(a<c && c<b && a<b){
	wa++;
	a= dt[0][wa];
	goto end;
	}
	if(b<a && a<c && b<c){
	wb++;
	b= dt[1][wb];
	goto end;
	}
	if(b<c && c<a && b<a){
	wb++;
	b= dt[1][wb];
	goto end;
	}
	if(c<a && a<b && c<b){
	wc++;
	c= dt[2][wc];
	goto end;
	}
	if(c<b && b<a && c<a){
	wc++;
	c= dt[2][wc];
	goto end;
	}
	if(a==' '&&b==' '&&c== ' ')
	exit(0);
	end:
	getch();
	goto start;

}