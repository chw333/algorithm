#include<fstream.h>
#include<string.h>

short src[1000];
short srcN=1;
short t[100]={0,};

void main()
{
	short i,j,j2;
	short w;
	char buf[256];
	ifstream fp("LINE.IN");
	fp>>buf;
	while(!fp.eof())
	{
		src[srcN++]=strlen(buf)+1;
		fp>>buf;
	}
	for(i=1;i<=srcN;i++)
	{
		t[i]=32767;
		w=0;
		for(j=0;j<=i;j++)
			w+=src[j];
		w--;
		for(j=0;j<i;j++)
		{
			w-=src[j];
			if(w<=20)
			{
				w=20-w;
				if(t[j]+w*w<t[i])
					t[i]=t[j]+w*w;
				w=20-w;
			}
		}
	}
	for(i=0;i<=srcN;i++)
		cout<<t[i]<<' ';
	cout<<endl;
	for(i=srcN-1;i>0;i--)
		if(t[i]<t[i+1])
			break;
	cout<<t[i]<<endl;
}
