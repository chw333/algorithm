#include <fstream.h>

int f,n;
int data[2][502];
int ja[10002];
int dab;

void Input_Data()
{
	int i=0;
	ifstream in("juice.in");
	{
		in >> i >> f;

		f-=i;
		in >> n;

		for(i=0;i<n;i++)
		{
			in >> data[0][i] >> data[1][i];
		}
	}in.close();
}

void Process()
{
	int i,j;


	for(i=0;i<=f;i++)
	{
		ja[i]=999999;
		for(j=0;j<n;j++)
		{
			if(i-data[1][j]>=0)
				if(ja[i]>ja[i-data[1][j]]+data[0][j])
					ja[i]=ja[i-data[1][j]]+data[0][j];
			if(ja[i]>data[0][j] && data[1][j]==i)
				ja[i]=data[0][j];
		}
		
	}


	/*

	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			if(ja[i]<ja[j])
			{
				k=data[0][i];
				data[0][i]=data[0][j];
				data[0][j]=k;

				k=data[1][i];
				data[1][i]=data[1][j];
				data[1][j]=k;
				
				kk=ja[i];
				ja[i]=ja[j];
				ja[j]=kk;
			}
		}
	}

	
	for(i=0;i<n;i++)
	{
		while(1)
		{
			if(f-data[1][i]<0) break;
			cout << i << endl;
			f-=data[1][i];
			dab+=data[0][i];
		}
	}
	*/

	
}

void Output_Data()
{
	ofstream out ("juice.out");
	{
		if(ja[f]!=999999) 
			out << ja[f];
		else
			out << "impossible";

	}out.close();
}

void main()
{
	Input_Data();
	Process();
	Output_Data();
}