/*
 *-------------------
 *    �⺻���Թ� 
 *-------------------
 */
#include<stdio.h>
#include<math.h>
#include<conio.h>
#include<stdlib.h>

#define N 100 /*������ ��*/

void main(void)
{
		int a[N],i,j,t;

		for(i=0;i<N;i++)	/*N���� ����*/
			a[i] = rand();
		
		for(i=1;i<N;i++){                        
			for(j=i-1;j>=0;j--){				 /*                                                */
				if(a[j]>a[j+1]){				 /* -------------�� t= a[i];                       */ 
					t=a[j];a[j]=a[j+1];a[j+1]=t; /*              �� for(j=i-1; j>=0&& a[j]>t; j--) */
				}								 /*              ��		a[j+1] = a[j];             */
				else							 /*              �� a[j+1] = t;                    */
					break;						 /*              ��  ���� ���� �̷��� ���ϼ� �ִ�. */
			}									 /* -------------��                                */
		}
	for(i=0;i<N;i++)
		printf("%8d",a[i]);
}
