#include<fstream.h>
#include<stdlib.h>
//                                <<<Final Version>>>
#define i_fnm "reversal.inp"
#define o_fnm "reversal.out"
#define MAXN 600
#define TimeCut 34
#define _abs(xxx) (((xxx)<0)?(-(xxx)):(xxx))
#define Swap(aa,bb) {cc=aa;aa=bb;bb=cc;}
#define rever(from,to)                 \
{                                      \
	Path1[Sol]=(from);                  \
	Path2[Sol]=(to);                    \
	Sol++;                              \
	LLEnd=(((to)-(from)+1)>>1);         \
	for(l0=0;l0<LLEnd;l0++)             \
	{                                   \
		Swap(a[(from)+l0],a[(to)-l0]);   \
		Swap(b[(from)+l0],b[(to)-l0]);   \
	}                                   \
	for(l0=from;l0<=to;l0++)            \
	{	a[l0]*=-1;	}                    \
}

int a[MAXN],b[MAXN],n,Sol,cc,Opt=1500;
int a2[MAXN],b2[MAXN],LLEnd,l0;
int Path1[1500],Path2[1500];
long far *T2=(long far *)(0x0040006c),T1;

void In(void)
{
	int l1;

	ifstream fin(i_fnm);
	fin >> n;
	for(l1=1;l1<=n;l1++)
	{
		fin >> a[l1];
		b[l1]=_abs(a[l1]);
		a2[l1]=a[l1];
		b2[l1]=b[l1];
	}
	fin.close();
}

void Set(void)
{
	int l1;
	for(l1=1;l1<=n;l1++)
	{
		a[l1]=a2[l1];
		b[l1]=b2[l1];
	}
	Sol=0;
}

void G1(void)
{
	int l1,l2;

	for(l1=1;l1<=n;l1++)
	{
		if(b[l1]!=l1)
		{
			for(l2=l1+1;l2<=n;l2++)
			{
				if(b[l2]==l1)
				{
					break;
				}
			}
			rever(l1,l2);
			if(Sol==Opt)
				return;
		}
	}
	for(l1=1;l1<=n;l1++)
	{
		if(a[l1]<0)
		{
			Path1[Sol]=l1;
			Path2[Sol]=l1;
			Sol++;
			if(Sol==Opt)
				return;
		}
	}
	if(Sol<Opt)
	{
		Opt=Sol;
		ofstream fout(o_fnm);
		for(l1=0;l1<Sol;l1++)
		{
			fout << Path1[l1] << ' ' << Path2[l1] << endl;
		}
		fout << "-1 -1" << endl;
		fout.close();
	}
}

void G2(void)
{
	int l1,l2;

	for(l1=n;l1>=1;l1--)
	{
		if(b[l1]!=l1)
		{
			for(l2=l1-1;l2>=1;l2--)
			{
				if(b[l2]==l1)
				{
					break;
				}
			}
			rever(l2,l1);
			if(Sol==Opt)
				return;
		}
	}
	for(l1=1;l1<=n;l1++)
	{
		if(a[l1]<0)
		{
			Path1[Sol]=l1;
			Path2[Sol]=l1;
			Sol++;
			if(Sol==Opt)
				return;
		}
	}
	if(Sol<Opt)
	{
		Opt=Sol;
		ofstream fout(o_fnm);
		for(l1=0;l1<Sol;l1++)
		{
			fout << Path1[l1] << ' ' << Path2[l1] << endl;
		}
		fout << "-1 -1" << endl;
		fout.close();
	}
}

void G3(void)
{
	int l1,l2,l3;

	for(l1=1;l1<=n;l1++)
	{
		if(b[l1]!=l1)
		{
			for(l2=l1+1;l2<=n;l2++)
			{
				if(b[l2]==l1)
				{
					break;
				}
			}
			if(b[l2+1]==l1+1)
			{
				for(l3=1;;l3++)
				{
					if(b[l2+l3]!=l1+l3)
					{
						break;
					}
				}
				l3--;
				rever(l2,l2+l3);
				rever(l1,l2+l3);
				if(Sol>=Opt)
					return;
			}
			else
			{
				rever(l1,l2);
				if(Sol==Opt)
					return;
			}
		}
	}
	for(l1=1;l1<=n;l1++)
	{
		if(a[l1]<0)
		{
			Path1[Sol]=l1;
			Path2[Sol]=l1;
			Sol++;
			if(Sol==Opt)
				return;
		}
	}
	if(Sol<Opt)
	{
		Opt=Sol;
		ofstream fout(o_fnm);
		for(l1=0;l1<Sol;l1++)
		{
			fout << Path1[l1] << ' ' << Path2[l1] << endl;
		}
		fout << "-1 -1" << endl;
		fout.close();
	}
}

void G4(void)
{
	int l1,l2,l3;

	for(l1=n;l1>=1;l1--)
	{
		if(b[l1]!=l1)
		{
			for(l2=l1-1;l2>=1;l2--)
			{
				if(b[l2]==l1)
				{
					break;
				}
			}
			if(b[l2-1]==l1-1)
			{
				for(l3=1;;l3++)
				{
					if(b[l2-l3]!=l1-l3)
					{
						break;
					}
				}
				l3--;
				rever(l2-l3,l2);
				rever(l2-l3,l1);
				if(Sol>=Opt)
					return;
			}
			else
			{
				rever(l2,l1);
				if(Sol==Opt)
					return;
			}
		}
	}
	for(l1=1;l1<=n;l1++)
	{
		if(a[l1]<0)
		{
			Path1[Sol]=l1;
			Path2[Sol]=l1;
			Sol++;
		}
	}
	if(Sol<Opt)
	{
		Opt=Sol;
		if(Sol==Opt)
			return;
		ofstream fout(o_fnm);
		for(l1=0;l1<Sol;l1++)
		{
			fout << Path1[l1] << ' ' << Path2[l1] << endl;
		}
		fout << "-1 -1" << endl;
		fout.close();
	}
}

void G5(void)
{
	int l1,l2,Want;

	for(l1=1;l1<=n;l1++)
	{
		Want=n-l1+1;
		if(b[l1]!=Want)
		{
			for(l2=l1+1;l2<=n;l2++)
			{
				if(b[l2]==Want)
				{
					break;
				}
			}
			rever(l1,l2);
			if(Sol==Opt)
				return;
		}
	}
	rever(1,n);
	if(Sol==Opt)
		return;
	for(l1=1;l1<=n;l1++)
	{
		if(a[l1]<0)
		{
			Path1[Sol]=l1;
			Path2[Sol]=l1;
			Sol++;
			if(Sol==Opt)
				return;
		}
	}
	if(Sol<Opt)
	{
		Opt=Sol;
		ofstream fout(o_fnm);
		for(l1=0;l1<Sol;l1++)
		{
			fout << Path1[l1] << ' ' << Path2[l1] << endl;
		}
		fout << "-1 -1" << endl;
		fout.close();
	}
}

void G6(void)
{
	int l1,l2,l3,Want;

	for(l1=1;l1<=n;l1++)
	{
		Want=n-l1+1;
		if(b[l1]!=Want)
		{
			for(l2=l1+1;l2<=n;l2++)
			{
				if(b[l2]==Want)
				{
					break;
				}
			}
			if(b[l2+1]==Want-1)
			{
				for(l3=1;;l3++)
				{
					if(b[l2+l3]!=Want-l3)
					{
						break;
					}
				}
				l3--;
				rever(l2,l2+l3);
				rever(l1,l2+l3);
				if(Sol>=Opt)
					return;
			}
			else
			{
				rever(l1,l2);
				if(Sol==Opt)
					return;
			}
		}
	}
	rever(1,n);
	if(Sol==Opt)
		return;
	for(l1=1;l1<=n;l1++)
	{
		if(a[l1]<0)
		{
			Path1[Sol]=l1;
			Path2[Sol]=l1;
			Sol++;
			if(Sol==Opt)
				return;
		}
	}
	if(Sol<Opt)
	{
		Opt=Sol;
		ofstream fout(o_fnm);
		for(l1=0;l1<Sol;l1++)
		{
			fout << Path1[l1] << ' ' << Path2[l1] << endl;
		}
		fout << "-1 -1" << endl;
		fout.close();
	}
}

void G7(void)
{
	int l1,l2,Want;

	for(l1=n;l1>=1;l1--)
	{
		Want=n-l1+1;
		if(b[l1]!=Want)
		{
			for(l2=l1-1;l2>=1;l2--)
			{
				if(b[l2]==Want)
				{
					break;
				}
			}
			rever(l2,l1);
			if(Sol==Opt)
				return;
		}
	}
	rever(1,n);
	if(Sol==Opt)
		return;
	for(l1=1;l1<=n;l1++)
	{
		if(a[l1]<0)
		{
			Path1[Sol]=l1;
			Path2[Sol]=l1;
			Sol++;
			if(Sol==Opt)
				return;
		}
	}
	if(Sol<Opt)
	{
		Opt=Sol;
		ofstream fout(o_fnm);
		for(l1=0;l1<Sol;l1++)
		{
			fout << Path1[l1] << ' ' << Path2[l1] << endl;
		}
		fout << "-1 -1" << endl;
		fout.close();
	}
}

void G8(void)
{
	int l1,l2,l3,Want;

	for(l1=n;l1>=1;l1--)
	{
		Want=n-l1+1;
		if(b[l1]!=Want)
		{
			for(l2=l1-1;l2>=1;l2--)
			{
				if(b[l2]==Want)
				{
					break;
				}
			}
			if(b[l2-1]==Want+1)
			{
				for(l3=1;;l3++)
				{
					if(b[l2-l3]!=Want+l3)
					{
						break;
					}
				}
				l3--;
				rever(l2-l3,l2);
				rever(l2-l3,l1);
				if(Sol>=Opt)
					return;
			}
			else
			{
				rever(l2,l1);
				if(Sol==Opt)
					return;
			}
		}
	}
	rever(1,n);
	if(Sol==Opt)
		return;
	for(l1=1;l1<=n;l1++)
	{
		if(a[l1]<0)
		{
			Path1[Sol]=l1;
			Path2[Sol]=l1;
			Sol++;
			if(Sol==Opt)
				return;
		}
	}
	if(Sol<Opt)
	{
		Opt=Sol;
		ofstream fout(o_fnm);
		for(l1=0;l1<Sol;l1++)
		{
			fout << Path1[l1] << ' ' << Path2[l1] << endl;
		}
		fout << "-1 -1" << endl;
		fout.close();
	}
}

void Shuffle(void)
{
	int l1,l2;

	for(l1=0;l1<Opt;l1++)
	{
		if(*T2-T1>=TimeCut)
		{
			return;
		}
		for(l2=1;l2<=n;l2++)
		{
			if(b[l2]!=l2)
			{
				break;
			}
		}
		if(l2>n)
		{
			break;
		}
		Path1[l1]=random(n)+1;
		Path2[l1]=random(n)+1;
		if(Path1[l1]>Path2[l1])
		{
			Swap(Path1[l1],Path2[l1]);
		}
		rever(Path1[l1],Path2[l1]);
	}
	if(l1<Opt)
	{
		for(l2=1;l2<=n;l2++)
		{
			if(a[l2]<0)
			{
				Path1[l1]=l2;
				Path2[l1]=l2;
				l1++;
			}
		}
		if(l1<Opt)
		{
			Opt=l1;
			ofstream fout(o_fnm);
			for(l2=0;l2<l1;l2++)
			{
				fout << Path1[l2] << ' ' << Path2[l2] << endl;
			}
			fout << "-1 -1" << endl;
			fout.close();
		}
	}
}

void G9(void)
{
	int l1,l2,End;
	End=(n>>1);
	for(l1=1;l1<=End;l1++)
	{
		if(b[l1]!=l1)
		{
			for(l2=l1+1;l2<=n;l2++)
			{
				if(b[l2]==l1)
				{
					break;
				}
			}
			rever(l1,l2);
			if(Sol==Opt)
				return;
		}
		if(b[n-l1+1]!=n-l1+1)
		{
			for(l2=n-l1;l2>=1;l2--)
			{
				if(b[l2]==n-l1+1)
				{
					break;
				}
			}
			rever(l2,n-l1+1);
			if(Sol==Opt)
				return;
		}
	}
	for(l1=1;l1<=n;l1++)
	{
		if(a[l1]<0)
		{
			Path1[Sol]=l1;
			Path2[Sol]=l1;
			Sol++;
			if(Sol==Opt)
				return;
		}
	}
	if(Sol<Opt)
	{
		Opt=Sol;
		ofstream fout(o_fnm);
		for(l1=0;l1<Sol;l1++)
		{
			fout << Path1[l1] << ' ' << Path2[l1] << endl;
		}
		fout << "-1 -1" << endl;
		fout.close();
	}
}

void G10(void)
{
	int l1,l2,End;
	End=(n>>1);
	for(l1=1;l1<=End;l1++)
	{
		if(b[n-l1+1]!=n-l1+1)
		{
			for(l2=n-l1;l2>=1;l2--)
			{
				if(b[l2]==n-l1+1)
				{
					break;
				}
			}
			rever(l2,n-l1+1);
			if(Sol==Opt)
				return;
		}
		if(b[l1]!=l1)
		{
			for(l2=l1+1;l2<=n;l2++)
			{
				if(b[l2]==l1)
				{
					break;
				}
			}
			rever(l1,l2);
			if(Sol==Opt)
				return;
		}
	}
	for(l1=1;l1<=n;l1++)
	{
		if(a[l1]<0)
		{
			Path1[Sol]=l1;
			Path2[Sol]=l2;
			Sol++;
			if(Sol==Opt)
				return;
		}
	}
	if(Sol<Opt)
	{
		Opt=Sol;
		ofstream fout(o_fnm);
		for(l1=0;l1<Sol;l1++)
		{
			fout << Path1[l1] << ' ' << Path2[l1] << endl;
		}
		fout << "-1 -1" << endl;
		fout.close();
	}
}

void G11(void)
{
	int l1,l2,End;
	End=(n>>1);
	for(l1=1;l1<=End;l1++)
	{
		if(l1&1)
		{
			if(b[l1]!=l1)
			{
				for(l2=l1+1;l2<=n;l2++)
				{
					if(b[l2]==l1)
					{
						break;
					}
				}
				rever(l1,l2);
				if(Sol==Opt)
					return;
			}
			if(b[n-l1+1]!=n-l1+1)
			{
				for(l2=n-l1;l2>=1;l2--)
				{
					if(b[l2]==n-l1+1)
					{
						break;
					}
				}
				rever(l2,n-l1+1);
				if(Sol==Opt)
					return;
			}
		}
		else
		{
			if(b[n-l1+1]!=n-l1+1)
			{
				for(l2=n-l1;l2>=1;l2--)
				{
					if(b[l2]==n-l1+1)
					{
						break;
					}
				}
				rever(l2,n-l1+1);
				if(Sol==Opt)
					return;
			}
			if(b[l1]!=l1)
			{
				for(l2=l1+1;l2<=n;l2++)
				{
					if(b[l2]==l1)
					{
						break;
					}
				}
				rever(l1,l2);
				if(Sol==Opt)
					return;
			}
		}
	}
	for(l1=1;l1<=n;l1++)
	{
		if(a[l1]<0)
		{
			Path1[Sol]=l1;
			Path2[Sol]=l2;
			Sol++;
			if(Sol==Opt)
				return;
		}
	}
	if(Sol<Opt)
	{
		Opt=Sol;
		ofstream fout(o_fnm);
		for(l1=0;l1<Sol;l1++)
		{
			fout << Path1[l1] << ' ' << Path2[l1] << endl;
		}
		fout << "-1 -1" << endl;
		fout.close();
	}
}

void G12(void)
{
	int l1,l2,End;
	End=(n>>1);
	for(l1=1;l1<=End;l1++)
	{
		if(l1&1)
		{
			if(b[n-l1+1]!=n-l1+1)
			{
				for(l2=n-l1;l2>=1;l2--)
				{
					if(b[l2]==n-l1+1)
					{
						break;
					}
				}
				rever(l2,n-l1+1);
				if(Sol==Opt)
					return;
			}
			if(b[l1]!=l1)
			{
				for(l2=l1+1;l2<=n;l2++)
				{
					if(b[l2]==l1)
					{
						break;
					}
				}
				rever(l1,l2);
				if(Sol==Opt)
					return;
			}
		}
		else
		{
			if(b[l1]!=l1)
			{
				for(l2=l1+1;l2<=n;l2++)
				{
					if(b[l2]==l1)
					{
						break;
					}
				}
				rever(l1,l2);
				if(Sol==Opt)
					return;
			}
			if(b[n-l1+1]!=n-l1+1)
			{
				for(l2=n-l1;l2>=1;l2--)
				{
					if(b[l2]==n-l1+1)
					{
						break;
					}
				}
				rever(l2,n-l1+1);
				if(Sol==Opt)
					return;
			}
		}
	}
	for(l1=1;l1<=n;l1++)
	{
		if(a[l1]<0)
		{
			Path1[Sol]=l1;
			Path2[Sol]=l2;
			Sol++;
			if(Sol==Opt)
				return;
		}
	}
	if(Sol<Opt)
	{
		Opt=Sol;
		ofstream fout(o_fnm);
		for(l1=0;l1<Sol;l1++)
		{
			fout << Path1[l1] << ' ' << Path2[l1] << endl;
		}
		fout << "-1 -1" << endl;
		fout.close();
	}
}

void Do(void)
{
	randomize();
	Set(); G1();
	Set(); G2();
	Set(); G3();
	Set(); G4();
	Set(); G5();
	Set(); G6();
	Set(); G7();
	Set(); G8();
	Set(); G9();
	Set(); G10();
	Set(); G11();
	Set(); G12();
	while(*T2-T1<TimeCut)
	{
		Set();
		Shuffle();
	}
}

void main(void)
{
	T1=*T2;
	In();
	Do();
}