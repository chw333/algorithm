/*
 *-------------------
 *    기본삽입법 
 *-------------------
 */
#include<stdio.h>
#include<math.h>
#include<conio.h>
#include<stdlib.h>

#define N 100 /*데이터 수*/

void main(void)
{
		int a[N],i,j,t;

		for(i=0;i<N;i++)	/*N개의 난수*/
			a[i] = rand();
		
		for(i=1;i<N;i++){                        
			for(j=i-1;j>=0;j--){				 /*                                                */
				if(a[j]>a[j+1]){				 /* -------------┐ t= a[i];                       */ 
					t=a[j];a[j]=a[j+1];a[j+1]=t; /*              │ for(j=i-1; j>=0&& a[j]>t; j--) */
				}								 /*              │		a[j+1] = a[j];             */
				else							 /*              │ a[j+1] = t;                    */
					break;						 /*              │  옆의 것은 이렇게 줄일수 있다. */
			}									 /* -------------┘                                */
		}
	for(i=0;i<N;i++)
		printf("%8d",a[i]);
}
