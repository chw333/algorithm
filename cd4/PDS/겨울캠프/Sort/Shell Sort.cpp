#include<stdio.h>
#include<conio.h>
#include<stdlib.h>

void main(void)
{
	int i,j,k,h,v;
	for( h = n/2; h > 0; h /= 2) /* h <- h/2 */
	{
		for(i = 0;i < h; i++) /*����*/
		{
			for(j = i+h; j < n; j += h) /*j�� ���� ������ ��Ҹ� ����*/
			{
				v = a[j];
				k = j;
				while(k>h-1 && a[k-h] > v) /* �����Ұ��� ã�� */
				{
					a[k] = a[k-h]; /* �̵� */
					k-=h;
				}
				a[k] = v; /* ���� */
			}
		}
	}
}
for(i=0;i<n-1;i++){
	for(j=i+1;j<n;j++){
		