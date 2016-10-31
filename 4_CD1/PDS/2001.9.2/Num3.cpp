#include<Fstream.H>

long int a[30][30],b[30][30],c[30][30],d[30][30],e[30][30],f[30][30],g[30][30],h[30][30],cnt;

ofstream fout ( "Output.Txt" );

void output2(int x,int y)
{
	if(x==y)
	{
		return;
	}
	if(c[x][y])
	{
		fout << " " << d[x][y];
		return;
	}
	else
	{
		output2(x,h[x][y]);
		if(h[x][y]!=x)
		{
			output2(h[x][y],y);
		}
	}
}

void output1(int x,int y)
{
	if(x==y)
	{
		return;
	}
	if(a[x][y])
	{
		fout << " " << b[x][y];
		return;
	}
	else
	{
		output1(x,f[x][y]);
		if(f[x][y]!=x)
		{
			output1(f[x][y],y);
		}
	}
}

void main(void)
{
	char t1,t2,t3,t4;
	int l1,l2,l3;
	ifstream fin ( "Input.Txt" );
	for(cnt=1;;)
	{
		fin >> t1 >> t2 >> t3 >> t4;
		if(fin.eof())
		{
			break;
		}
		if(t1=='!')
		{
			if(t3=='E')
			{
				if(e[t4-'A'][t2-'A'])
				{
					fout << "Error" << endl;
				}
				else
				{
					a[t2-'A'][t4-'A']=1;
					b[t2-'A'][t4-'A']=cnt;
					b[t4-'A'][t2-'A']=cnt;
				}
			}
			else if(t3=='W')
			{
				if(e[t2-'A'][t4-'A'])
				{
					fout << "Error" << endl;
				}
				else
				{
					a[t4-'A'][t2-'A']=1;
					b[t4-'A'][t2-'A']=cnt;
					b[t2-'A'][t4-'A']=cnt;
				}
			}
			else if(t3=='S')
			{
				if(g[t4-'A'][t2-'A'])
				{
					fout << "Error" << endl;
				}
				else
				{
					c[t2-'A'][t4-'A']=1;
					d[t2-'A'][t4-'A']=cnt;
					d[t4-'A'][t2-'A']=cnt;
				}
			}
			else if(t3=='N')
			{
				if(g[t2-'A'][t4-'A'])
				{
					fout << "Error" << endl;
				}
				else
				{
					c[t4-'A'][t2-'A']=1;
					d[t4-'A'][t2-'A']=cnt;
					d[t2-'A'][t4-'A']=cnt;
				}
			}
			for(l1=0;l1<26;l1++)
			{
				for(l2=0;l2<26;l2++)
				{
					e[l1][l2]=a[l1][l2];
					if(e[l1][l2]==0)
					{
						e[l1][l2]=10000;
					}
					f[l1][l2]=l1;
				}
			}
			for(l1=0;l1<26;l1++)
			{
				for(l2=0;l2<26;l2++)
				{
					if(l1==l2)
					{
						continue;
					}
					for(l3=0;l3<26;l3++)
					{
						if(l1==l3)
						{
							continue;
						}
						else if(l2==l3)
						{
							continue;
						}
						else if(e[l2][l1]+e[l1][l3]<e[l2][l3])
						{
							e[l2][l3]=e[l2][l1]+e[l1][l3];
							f[l2][l3]=l1;
						}
					}
				}
			}
			for(l1=0;l1<26;l1++)
			{
				for(l2=0;l2<26;l2++)
				{
					g[l1][l2]=c[l1][l2];
					if(!g[l1][l2])
					{
						g[l1][l2]=10000;
					}
					h[l1][l2]=l1;
				}
			}
			for(l1=0;l1<26;l1++)
			{
				for(l2=0;l2<26;l2++)
				{
					if(l1==l2)
					{
						continue;
					}
					for(l3=0;l3<26;l3++)
					{
						if(l1==l3)
						{
							continue;
						}
						else if(l2==l3)
						{
							continue;
						}
						else if(g[l2][l1]+g[l1][l3]<g[l2][l3])
						{
							g[l2][l3]=g[l2][l1]+g[l1][l3];
							h[l2][l3]=l1;
						}
					}
				}
			}
			for(l1=0;l1<26;l1++)
			{
				for(l2=0;l2<26;l2++)
				{
					if(e[l1][l2]==10000)
					{
						e[l1][l2]=0;
					}
					if(g[l1][l2]==10000)
					{
						g[l1][l2]=0;
					}
				}
			}
			cnt++;
		}
		else
		{
			if(t3=='E')
			{
				if(e[t4-'A'][t2-'A'])
				{
					fout << "F";
					output1(t4-'A',t2-'A');
					fout << endl;
				}
				else if(e[t2-'A'][t4-'A'])
				{
					fout << "T";
					output1(t2-'A',t4-'A');
					fout << endl;
				}
				else
				{
					fout << "U" << endl;
				}
			}
			else if(t3=='W')
			{
				if(e[t2-'A'][t4-'A'])
				{
					fout << "F";
					output1(t2-'A',t4-'A');
					fout << endl;
				}
				else if(e[t4-'A'][t2-'A'])
				{
					fout << "T";
					output1(t4-'A',t2-'A');
					fout << endl;
				}
				else
				{
					fout << "U" << endl;
				}
			}
			else if(t3=='S')
			{
				if(g[t4-'A'][t2-'A'])
				{
					fout << "F";
					output2(t4-'A',t2-'A');
					fout << endl;
				}
				else if(g[t2-'A'][t4-'A'])
				{
					fout << "T";
					output2(t2-'A',t4-'A');
					fout << endl;
				}
				else
				{
					fout << "U" << endl;
				}
			}
			else if(t3=='N')
			{
				if(g[t2-'A'][t4-'A'])
				{
					fout << "F";
					output2(t2-'A',t4-'A');
					fout << endl;
				}
				else if(g[t4-'A'][t2-'A'])
				{
					fout << "T";
					output2(t4-'A',t2-'A');
					fout << endl;
				}
				else
				{
					fout << "U" << endl;
				}
			}
		}
	}
	fin.close();
	fout.close();
}