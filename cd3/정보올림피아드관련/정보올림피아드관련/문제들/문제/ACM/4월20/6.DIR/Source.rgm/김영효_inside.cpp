#include "fstream.h"

int n, count=0;
float data[20][2];
float rx,ry;
int que[1000][3];

void input()
{
	int i;
	ifstream in("inside.in");
	in >> n;
	for( i=0; i<n; i++ )
		in >> data[i][0] >> data[i][1];
	in >> rx >> ry;
}

double CCW(float x1, float y1, float x2, float y2, float x3, float y3)
{
	return (double)(x1*y2+x2*y3+x3*y1-x2*y1-x3*y2-x1*y3);
}

void proc()
{
	int i,j,k;
	double tmp1,tmp2;

	for( i=0; i<n; i++ )
	{
		for( j=0; j<n; j++ )
		{
			for( k=0; k<n; k++ )
			{
				if( i != j && j != k && k != i )
				{
					tmp1 = CCW(data[i][0],data[i][1],data[j][0],data[j][1],rx,ry);
					tmp2 = CCW(data[i][0],data[i][1],data[j][0],data[j][1],data[k][0],data[k][1]);

					if( tmp1 < 0 && tmp2 < 0 )
					{
						tmp1 = CCW(data[i][0],data[i][1],data[k][0],data[k][1],rx,ry);
						tmp2 = CCW(data[i][0],data[i][1],data[k][0],data[k][1],data[j][0],data[j][1]);
						
						if( tmp1 > 0 && tmp2 > 0 )
						{
							tmp1 = CCW(data[j][0],data[j][1],rx,ry,data[k][0],data[k][1]);
							tmp2 = CCW(data[k][0],data[k][1],rx,ry,data[j][0],data[j][1]);
							if( tmp1 > 0 && tmp2 < 0 )
							{
								cout << i << " " << j << " " << k << endl;
								que[count][0] = i;
								que[count][1] = j;
								que[count][2] = k;
								count++;
							}
						}
					}
					else if( tmp1 > 0 && tmp2 > 0 )
					{
						tmp1 = CCW(data[i][0],data[i][1],data[k][0],data[k][1],rx,ry);
						tmp2 = CCW(data[i][0],data[i][1],data[k][0],data[k][1],data[j][0],data[j][1]);

						if( tmp1 < 0 && tmp2 < 0 )
						{
							tmp1 = CCW(data[j][0],data[j][1],rx,ry,data[k][0],data[k][1]);
							tmp2 = CCW(data[k][0],data[k][1],rx,ry,data[j][0],data[j][1]);
							if( tmp1 < 0 && tmp2 > 0 )
							{
								cout << i << " " << j << " " << k << endl;
								que[count][0] = i;
								que[count][1] = j;
								que[count][2] = k;
								count++;
							}
						}
					}
				}
			}
		}
	}
}

void output()
{
	ofstream out("inside.out");
	int i,j,k,q;
	int check[20]={0,};
	int tail = count;

	for( i=0; i<tail; i++ )
	{
		if( !check[i] )
			for( j=0; j<tail; j++ )
			{
				if( check[j] == 0 && i != j )
				{
					int sw=0;
					for( k=0; k<3; k++ )
						for( q=0; q<3; q++ )
							if( que[j][k] == que[i][q] )
								sw++;

					if( sw == 3 )
					{
						check[j] = 1;
						count--;
					}
				}
			}
		check[i] = 1;
	}

	out << count;
}

void main()
{
	input();
	proc();
	output();
}