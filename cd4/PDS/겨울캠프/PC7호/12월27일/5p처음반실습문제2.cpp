#include<stdio.h>
#include<conio.h>
  
int save[100];
void comb(int soo,int n, int i){
	int j;
	if( soo == 0 )
	 {
		for(  j = 0 ; j<n; j++){
			printf("%d ",save[j]);
		}
		printf("\n");
	 }
	 else
	 {
		for( j = i; j >= 1 ; j--)
			if ( soo -j >= 0)
			{
				save[n] = j;
				comb(soo-j, n+1, j);

			}
	 }
}
void main()
{
	comb(5,0,6 - 1);
} 