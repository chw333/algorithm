#include <fstream.h>
ifstream in("animal.in");
ofstream out("animal.out");
char b[5000][5000];
int g,s,check[5000][5000],wi,yop,flag,count,max,all,aall,aaa=1000000;
void input()
{
	int i;
	in>>g>>s;
	for(i=0;i<s;i++)in>>b[i];
}
void find(int i,int j)
{
	if((i-1<0||b[i-1][j]=='#')||(i+1==s||b[i+1][j]=='#')) wi=1;
	if((j-1<0||b[i][j-1]=='#')||(j+1==g||b[i][j+1]=='#')) yop=1;
}
void bfs_scan(int i,int j)
{
	if(i-1>=0&&b[i-1][j]=='.'&&check[i-1][j]>count){ check[i-1][j]=count; all++; flag=1;}
	if(i+1< s&&b[i+1][j]=='.'&&check[i+1][j]>count){ check[i+1][j]=count; all++; flag=1;}
	if(j-1>=0&&b[i][j-1]=='.'&&check[i][j-1]>count){ check[i][j-1]=count; all++; flag=1;}
	if(j+1< g&&b[i][j+1]=='.'&&check[i][j+1]>count){ check[i][j+1]=count; all++; flag=1;}
}
void process()
{
	int i,j,k,l;
	for(i=0;i<s;i++)
		for(j=0;j<g;j++)
			if(b[i][j]=='.'){
				wi=0; yop=0;
				find(i,j);
				if(wi&&yop){
					for(k=0;k<s;k++)
						for(l=0;l<g;l++){
							if(check[k][l]!=32000&&b[k][l]=='.'){ check[k][l]=32000; aaa--;}
							if(aaa==0) break;
						}
					aaa=0;
					count=1; check[i][j]=count; count++; all=1;
					for(;;){
						aaa+=all; aall=all; all=0; flag=0;
						for(k=0;k<s;k++){
							for(l=0;l<g;l++){
								if(check[k][l]==count-1){ bfs_scan(k,l); aall--;}
								if(aall==0) break;
							}
							if(aall==0) break;
						}
						if(flag==0) break;
						count++;
					}
					if(max<count-2) max=count-2;
				}
			}
}
void main()
{
	input();
	process();
	out<<max;
}
