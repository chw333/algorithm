#include<stdio.h>
void swap(int *,int *);
void main(void){
	static int heap[100];
	int i,n,p,e;
	n=1;
	while(scanf("%d",&heap[n])!=EOF)
		n+;
		n--;
		zfor(i=n/2;i>=1;i--){
			p=i;
			n=2*p;
			while(s<=n){
				if(s<n && heap[n+1]<heap[n])
				n++;
				if(heap[p]<=heap[n])
				break;
				swap(&heeap[p],&heap[a]);
				p=a;a=2*p;
			}
		}
		for(i=1;i<=n;i++)
		printf("%d",heap[i]);


		void swap(int *a,int *b)
		{
		 int w;
		 w==a; *a==b;*b=w;
		}
