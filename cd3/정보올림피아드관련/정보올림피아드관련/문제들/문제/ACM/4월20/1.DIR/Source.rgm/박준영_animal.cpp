#include<fstream.h>
int n,m,arr[1000][1000],i,j,x,ji[1000],jj[1000],cnt,c,d[1000][1000],k,flag;
char s;
void bfs_scan(int y,int x)
{
	int cnt,i;
	cnt=c;
	for(i=y;i>=0;i--){
		if(arr[i][x]==1){break;}
		if(d[i][x]==-1){d[i][x]=cnt;}
		cnt++;
	}
	cnt=c;
	for(i=y;i<n;i++){
		if(arr[i][x]==1){break;}
		if(d[i][x]==-1){d[i][x]=cnt;}
		cnt++;
	}
	cnt=c;
	for(i=x;i>=0;i--){
		if(arr[y][i]==1){break;}
		if(d[y][i]==-1){d[y][i]=cnt;}
		cnt++;
	}
	cnt=c;
	for(i=x;i<m;i++){
		if(arr[y][i]==1){break;}
		if(d[y][i]==-1){d[y][i]=cnt;}
		cnt++;
	}
}
void main()
{
	ifstream in("animal.in");
	in >> m>>n;
	for(i=0;i<n;i++){
		for(j=0;j<m;j++){
			in >> s;
			if(s=='#'){arr[i][j]=1;}
			if(s=='.'){arr[i][j]=0;}
		}
	}
	for(i=0;i<n;i++){
		for(j=0;j<m;j++){
			if(arr[i][j]==0){
				if(arr[i-1][j]==1&&i>0&&arr[i][j-1]==1&&j>0){
					ji[cnt]=i;
					jj[cnt]=j;
					cnt++;
					continue;
				}
				if(arr[i-1][j]==1&&i>0&&arr[i][j+1]==1&&j<m-1){
					ji[cnt]=i;
					jj[cnt]=j;
					cnt++;
					continue;
				}
				if(arr[i+1][j]==1&&i<n-1&&arr[i][j-1]==1&&j>0){
					ji[cnt]=i;
					jj[cnt]=j;
					cnt++;
					continue;
				}
				if(arr[i+1][j]==1&&i<n-1&&arr[i][j+1]==1&&j<m-1){
					ji[cnt]=i;
					jj[cnt]=j;
					cnt++;
					continue;
				}
			}
		}
	}
	for(k=0;k<cnt;k++){
		for(i=0;i<n;i++){
			for(j=0;j<m;j++){
				d[i][j]=-1;
			}
		}
		c=0;
		bfs_scan(ji[k],jj[k]);
		c++;
		for(;;){
			flag=0;
			for(i=0;i<n;i++){
				for(j=0;j<m;j++){
					if(d[i][j]==c){bfs_scan(i,j);flag=1;}
					if(x<d[i][j]){x=d[i][j];}
				}
			}
			if(flag==0){break;}
			c++;
		}
	}
	ofstream out("animal.out");
	out << x;
}