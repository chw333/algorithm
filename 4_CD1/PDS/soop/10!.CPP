// factorier
#include<stdio.h>
#include<conio.h>


long input;

long a(long input)
{
	if ( input == 0 )
	return 1;
	else
	{
		return input*a(input-1);
	}
}
void main()
{
	clrscr();
	scanf("%ld",&input);
	printf("%ld",a(input));

}