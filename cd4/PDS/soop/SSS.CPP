#include<Stdio.h>
#include<conio.h>
	char stack[50],polish[50];
	int pri[255];
	int sp1,sp2;
void main(void)
{
	int i;
	char *p="1+3-1*4/5";
	clrscr();
	for(i=0;i<=255;i++)
		pri[i] = 3;
	pri['+'] = pri['-'] = 1;
	pri['*'] = pri['/'] = 2;

	stack[0] = 0; pri[0] = -1;
	sp1 = sp2 = 0;

	while (*p!='\0'){
		while(pri[*p]<=pri[stack[sp1]])
			polish[++sp2] = stack[sp1--];
		stack[++sp1] = *p++;
	}
	for(i=sp1;i>0;i--)
		polish[++sp2] = stack[i];

	for(i=1;i<=sp2;i++)
		putchar(polish[i]);



}