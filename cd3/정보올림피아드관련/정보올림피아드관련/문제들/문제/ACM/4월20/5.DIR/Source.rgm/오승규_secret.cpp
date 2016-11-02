#include<fstream.h>
//coded by S.K.Oh kkkkkkkkkk
int m,n,p[20000][3],uni[20],cnt,inj[2000][2000],visit[2000],suddenly[20000][2],scnt;
void init()
{
	int i,j,temp;
	ifstream in ("secret.in");
	in >> m >> n;
	for(i=0;i<n;i++){
		in >> p[i][0] >> p[i][1] >> p[i][2];
		if(p[i][0]>p[i][1]){
			temp=p[i][0];
			p[i][0]=p[i][1];
			p[i][1]=temp;
		}
	}
	for(i=0;i<m;i++)
		uni[i]=i;
	in.close();
	for(i=0;i<n-1;i++)
		for(j=i+1;j<n;j++)
			if(p[i][2]>p[j][2]){
				temp=p[i][0];
				p[i][0]=p[j][0];
				p[j][0]=temp;
				temp=p[i][1];
				p[i][1]=p[j][1];
				p[j][1]=temp;
				temp=p[i][2];
				p[i][2]=p[j][2];
				p[j][2]=temp;
			}
}
void rc(int now,int st)
{
	int i;
	if(now!=st)
		visit[now]=1;
	for(i=0;i<n;i++)
		if(inj[now][i]!=0 && visit[i]==0){
			if(i==st && now!=st)
				return;
			if(now<i){
				suddenly[scnt][0]=now;
				suddenly[scnt++][1]=i;
			}else{
				suddenly[scnt][0]=i;
				suddenly[scnt++][1]=now;
			}
			rc(i,st);
			return;
		}
}
void secret()
{
	int i,j,f=0,l,max=0;
	for(i=0;i<n;i++){
		if(uni[p[i][0]]!=uni[p[i][1]]){
			for(j=0;j<=m;j++)
				if(uni[j]==uni[p[i][1]] && j!=p[i][1])
					uni[j]=uni[p[i][0]];
			uni[p[i][1]]=uni[p[i][0]];
			cnt+=p[i][2];
			inj[p[i][0]][p[i][1]]=inj[p[i][1]][p[i][0]]=p[i][2];
		}else if(f==0){
			l=i;
			f=1;
			cnt+=p[i][2];
		}
	}
	rc(l,l);
	for(i=0;i<scnt;i++)
		if(max<inj[suddenly[i][0]][suddenly[i][1]])
			max=inj[suddenly[i][0]][suddenly[i][1]];
	cnt-=max;
}
void output()
{
	ofstream out ("secret.out");
	out << cnt;
	out.close();
}
void main()
{
	init();
	secret();
	output();
}