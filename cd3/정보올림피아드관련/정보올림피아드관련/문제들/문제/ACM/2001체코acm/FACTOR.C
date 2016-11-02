/* ACM International Collegiate Programming Contest
   Central European Regional Contest 2000
   
   Problem F - Factorial
   Michal Sevcenko
*/

#include <stdio.h>

void DoIt()
{
	int n;
	int cc, c = 0;

	scanf("%i", &n);
	while (n)
	{
		cc = n / 5;
		c += cc;
		n = cc;
	}
	printf("%d\n", c);
}

int main()
{
	int i, n;

	scanf("%i", &n);
	for (i=0; i<n; i++)
		DoIt();

	return 0;
}