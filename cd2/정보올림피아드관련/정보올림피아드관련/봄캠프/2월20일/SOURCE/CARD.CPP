#include<fstream.h>

#define i_fnm "card.inp"
#define o_fnm "card.out"

int b[101][101],c[101],Top;
long long a[101][101],Sol,Temp;
int n,Temp2,Temp3;

int main(void)
{
	int l1,l2,l3,End;
	long long t1,t2,t3;

	ifstream fin(i_fnm);
	ofstream fout(o_fnm);
	fin >> n;
	for(l1=1;l1<=n;l1++)
	{
		a[1][l1]=l1;
		b[1][l1]=l1;
	}
	for(l1=2;l1<=n;l1++)
	{
		for(l2=l1;l2<=n;l2++)
		{
			End=l2-l1;
			for(l3=1;l3<=End;l3++)
			{
				t1=a[l1-1][l2-l3];
				t2=l3;
				while(t2)
				{
					t3=t1%t2;
					t1=t2;
					t2=t3;
				}
				t2=a[l1-1][l2-l3]*l3/t1;
				if(a[l1][l2]<t2)
				{
					a[l1][l2]=t2;
					b[l1][l2]=l3;
				}
			}
		}
	}
	for(l1=1;l1<=n;l1++)
	{
		if(a[l1][n]>Sol)
		{
			Sol=a[l1][n];
			Temp2=l1;
		}
	}

/*
	for(Temp3=n;Temp2;)
	{
		c[Top++]=b[Temp2][Temp3];
		Temp3-=b[Temp2][Temp3];
		Temp2--;
	}

	for(l1=1,Temp2=0;l1<=n&&Temp2<Top;Temp2++)
	{
		fout << l1 + c[Temp2] - 1 << ' ';
		for(Temp3=1;Temp3<c[Temp2];Temp3++,l1++)
		{
			fout << l1 << ' ';
		}
		l1++;
	}
*/
	fout << Sol << endl;
	fin.close();
	fout.close();

	return 0;
}