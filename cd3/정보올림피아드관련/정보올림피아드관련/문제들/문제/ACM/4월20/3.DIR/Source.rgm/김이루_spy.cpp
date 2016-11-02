#include <fstream.h>
#include <math.h>

int n;
int data[4][500];
int cn;


void Input_Data()
{
	int i,j;
	ifstream in("spy.in");
	{
		in >> n;
		for(i=0;i<n;i++)
			for(j=0;j<4;j++)
				in >> data[j][i];
	}in.close();
}

void Process_Output()
{
	int i;
	for(i=0;i<n;i++)
	{
		if((data[0][i]>data[2][i] && data[1][i]>data[3][i]) || (data[0][i]>data[3][i] && data[1][i]>data[2][i])
		   || ((double)(data[2][i]+data[3][i]) < (double)sqrt(data[0][i]*data[0][i]+data[1][i]*data[1][i])))
		{

			cn++;
		}
	}
	ofstream out ("spy.out");
	{
		out << cn;
	}out.close();
}

void main()
{
	Input_Data();
	Process_Output();

}
