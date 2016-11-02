#include<fstream.h>
int n,bu[1000][2],d[1000],cnt,b1,b2,b3,i,m,f,c,dap[2][1000],cn,j,k,c2,cc2[1000];
void main()
{
	ifstream in("c:/work/eq19.in");
	in >> n>>m;
	for(i=0;i<m;i++){
		in >> b1>>b2>>b3;
		bu[b1][0]=b2;
		bu[b1][1]=b3;
	}
	for(;;){
		f=0;
		for(i=1;i<=n;i++){
			if(d[i]==cnt){
				if(bu[i][0]!=0){
					d[bu[i][0]]=cnt+1;
				}
				if(bu[i][1]!=0){
					d[bu[i][1]]=cnt+1;
				}
				f=1;
			}
		}
		if(f==0){break;}
		cnt++;
	}	
	cnt--;
	for(k=cnt;k>0;k--){
		c2=0;
		f=0;
		for(i=1;i<=n;i++){
			cn=0;
			for(j=1;j<=n;j++){
				if(bu[i][cn]==j&&d[i]==k-1){
					cn++;
				}
				if(cn==2){
					dap[c2][c]=i;
					c2++;
					cc2[c]=c2;
					if(f==1){f=0;}
					if(c2==2){
						c2=0;c++;f=1;
					}
					cn=0;
				}
			}
		}
		if(f==0){c++;}
	}
	ofstream out("c:/work/eq19.out");
	out << (c+1)/2<<endl;
	for(i=0;i<c;i++){
		f=0;
		for(j=0;j<cc2[i];j++){
			if(dap[j][i]>0){out << dap[j][i]<<" ";f=1;}
		}
		if(f==1){out << endl;}
	}
}