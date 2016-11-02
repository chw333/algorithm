#include<stdlib.h>
#include<stdio.h>
#include<conio.h>
	static int a[10] = { 41,24,76,11,45,64,21,69,19,36};
	static int i,j;
int q(int a[10],int left,int right)
{
	int s;
	int imsi;
   if(left<right){
	s = a[i];
	i = left;
	j = right+1;
	}
	while(1){
		if(a[i]<s) i++;
		if(a[j]>s) j--;
		if(i>=j)break;
	imsi = a[i];
	a[i] = a[j];
	a[j] = imsi;
	}
	a[left] = a[j],a[j] = s;
}
main()
{
	clrscr();
	q(a,0,9);
	for(i = 0 ; i < 10; i++)
	printf("%d ",a[i]);
}