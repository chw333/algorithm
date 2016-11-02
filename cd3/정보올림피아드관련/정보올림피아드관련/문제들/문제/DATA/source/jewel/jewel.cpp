#include <fstream.h>

int table_cnt;
char table[210][210];
int checking[210];

void Input();
void Process();

void Input()
{
	ifstream fin ("jewel.in");
	
	fin >> table_cnt;
	for(int i=0;i<table_cnt;i++)
		fin >> table[i];

	fin.close();
}

void Process()
{
	int i,j,k,l;
	int check,max;
	
	for(i=0;i<table_cnt;i++)
	{
		for(j=0;j<table_cnt;j++)
		{
			if(table[i][j]=='1' && table[i+1][j]=='1' && table[i][j+1]=='1' && table[i+1][j+1]=='1')
				checking[2]++;
			else
				continue;
			check=1;
			if(i>j)
				max=i;
			else
				max=j;
			max=table_cnt-max;
			for(k=2;k<max;k++)
			{
				for(l=0;l<k;l++)
					if(table[i+l][j+k]=='0')
						check=0;
				for(l=0;l<k;l++)
					if(table[i+k][j+l]=='0')
						check=0;
				if(table[i+k][j+k]=='0')
					check=0;
				if(check==1)
					checking[k+1]++;
				else
					break;
			}
		}
	}

	ofstream fout ("jewel.out");
	for(i=0;i<210;i++)
		if(checking[i]>0)
			fout << i << " " << checking[i] << endl;
	fout.close();
}

void main()
{
	Input();
	Process();
}