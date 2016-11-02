#include <fstream.h>
ifstream in("tetris.in");
ofstream out("tetris.out");
int s1,s2,g1,g2,max=0;
int a[1000][1000],b[1000][1000],dab[1000][1000],check[1000][1000];
void input()
{
	char t;
	int i,j;
	in>>s1>>g1;
	for(i=0;i<s1;i++)
		for(j=0;j<g1;j++){
			in>>t;
			if(t=='#') a[i][j]=1;
			else a[i][j]=0;
		}
	in>>s2>>g2;
	for(i=0;i<s2;i++)
		for(j=0;j<g2;j++){
			in>>t;
			if(t=='#') b[i][j]=1;
			else b[i][j]=0;
		}
}
void set()
{
	int c,d,k=0,l=0;
	for(c=s1;c<s1+s2;c++){
		for(d=0;d<g2;d++){
			dab[c][d]=b[k][l]; l++;
		}
		k++; l=0;
	}
}
void process(int i,int j,int depth)
{
	int c,d,k=0,l=0,sw=0;
	if(depth>max) max=depth;
	if(i==s1+s2){ max=32000; return;}
	if(j+g1>g2||j<0) return;
	check[i][j]=1;
	for(c=i+1;c<i+1+s1;c++){
		for(d=j;d<j+g1;d++){
			if(dab[c][d]+a[k][l]==2){ sw=1; break;}
			l++;
		}
		if(sw==1) break;
		k++; l=0;
	}
	if(sw==0) process(i+1,j,depth+1);
	k=0; l=0; sw=0;
	if(!check[i][j+1]&&j+1<g2){
		for(c=i;c<i+s1;c++){
			for(d=j+1;d<j+g1+1;d++){
				if(dab[c][d]+a[k][l]==2){ sw=1; break;}
				l++;
			}
			if(sw==1) break;
			k++; l=0;
		}
		if(sw==0) process(i,j+1,depth);
	}
	k=0; l=0; sw=0;
	if(!check[i][j-1]&&j-1>=0){
		for(c=i;c<i+s1;c++){
			for(d=j-1;d<j+g1-1;d++){
				if(dab[c][d]+a[k][l]==2){ sw=1; break;}
				l++;
			}
			if(sw==1) break;
			k++; l=0;
		}
		if(sw==0) process(i,j-1,depth);
	}
}
void main()
{
	int i;
	input();
	set();
	for(i=0;i<g2-g1;i++){
		process(0,i,0);
	}
	if(max==32000) out<<"pass";
	else out<<max;
}