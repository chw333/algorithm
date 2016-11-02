#include<stdio.h>
#include<conio.h>
#include<stdlib.h>

void main(void)
{
	int i,j,k,h,v;
	for( h = n/2; h > 0; h /= 2) /* h <- h/2 */
	{
		for(i = 0;i < h; i++) /*변이*/
		{
			for(j = i+h; j < n; j += h) /*j는 삽입 졍렬할 요소를 지정*/
			{
				v = a[j];
				k = j;
				while(k>h-1 && a[k-h] > v) /* 삽입할곳을 찾음 */
				{
					a[k] = a[k-h]; /* 이동 */
					k-=h;
				}
				a[k] = v; /* 삽입 */
			}
		}
	}
}
for(i=0;i<n-1;i++){
	for(j=i+1;j<n;j++){
		