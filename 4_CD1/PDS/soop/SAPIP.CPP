#include<Stdio.h>
#include<conio.h>
main()
{
	static int i,j,imsi,read,address;
	int dt[5] = { 5 , 3 , 1 , 2 , 4 };

	clrscr();

	for( j = 0 ; j < 6 ; j++ )
	{

		for( i = 0 ; i < j ; i++ )
		{
			if ( dt[j-1] < dt[i])
			{
				imsi = dt[j-1] ; dt[j-1] = dt[i] ; dt[i] = imsi;
				goto sd;
			}
		}
		sd:
		for( i = 0 ; i < j ; i++ )
		{
			printf("%d ", dt[i]);
		}
		printf("\n");

	}
}