#include<iostream.h>
#include<stdio.h>
int n;
float m,p[10],w[10],c[10];
void init()
{
	int i,j;
	float temp;
	cin >> n >> m;
	for(i=0;i<n;i++)
		cin>>p[i]>>w[i];
	for(i=0;i<n;i++)
		c[i] = p[i]/w[i];
	for(i=0;i<n-1;i++)
		for(j=i+1;i<n;j++)
			if(c[i]<c[j])
			{
				temp = c[i]; c[i] = c[j]; c[j] = temp;
				temp = w[i]; w[i] = w[j]; w[j] = temp;
				temp = p[i]; p[i] = p[j]; p[j] = temp;
			}
}
void process()
{
	float cur, scur =0, p1;
	int i;
	for(i=0;i<n;i++)
		if(m>0)
		{
			cur = c[i]