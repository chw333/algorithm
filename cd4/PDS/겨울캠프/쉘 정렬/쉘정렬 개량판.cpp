#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<math.h>

#define N 100

void main(void)
{
		int a[N],i,j,k,gap,t;
		for(i=0;i<N;i++)
				a[i]=rand();
		for(gap=1;gap<N/3;gap=3*gap+1)
			while(gap>0){
				for(i=gap;i<N;i++){
					for(j=i-gap;j>=0;j=j-gap){
						if(a[j]>a[j+gap]){
							t=a[j];a[j] = a[j+gap];a[j+gap] = t;
						}
						else
							break;
					}
				}
				gap/=3;
			}
			for(i=0;i<N;i++)printf("%8d",a[j]);
}