#include<fstream.h>
int weight,n,p[500][2],d[10000],visit[10000];
void init()
{
	int tmp,temp,i;
	ifstream in ("juice.in");
	in >> tmp >> temp;
	weight=temp-tmp;
	in >> n;
	for(i=0;i<n;i++)
		in >> p[i][0] >> p[i][1];
	in.close();
}
void juice()
{
	int i,j;
	for(i=0;i<n;i++)
		for(j=p[i][1];j<=weight;j++)
			if((d[j]>d[j-p[i][1]]+p[i][0] || visit[j]==0) && (visit[j-p[i][1]]==1 || j-p[i][1]==0)){
				d[j]=d[j-p[i][1]]+p[i][0];
				visit[j]=1;
			}
}
void output()
{
	ofstream out ("juice.out");
	if(visit[weight]==0)
		out << "impossible";
	else
		out << d[weight];
	out.close();
}
void main()
{
	init();
	juice();
	output();
}