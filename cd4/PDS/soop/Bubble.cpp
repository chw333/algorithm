#include<stdio.h>
#include<conio.h>
main()
{
	int i,j,imsi;
	int dt[5] = { 5, 3, 1, 2, 4 };

	for(j=3;j>0;j--){
		for(i=0;i<5;i++){
			printf("%d ", dt[i]);
		}
		printf("\n");

		for(i=0;i<=j;i++)
		{
			if(dt[i] > dt[i+1])
			{
				imsi = dt[i]; dt[i] = dt[i+1] ; dt[i+1] = imsi;
			}
		}
	}


}
