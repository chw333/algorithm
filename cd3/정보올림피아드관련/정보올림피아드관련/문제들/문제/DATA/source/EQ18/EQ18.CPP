#include<fstream.h>
int n,room[100][100],m,i,j,x,y,yx,ry,ly,dx,mx,my;
int ca[4][100][100],c[2],k,l,ax[4],ay[4],cnt,flag;
void jick(int k,int l,int h)
{
	int b,t1=0,t2=1;
	if(h==1){
		b=mx;mx=my;my=b;t1=1;t2=0;}
	ax[k]=my;
	ay[k]=mx;
	c[t1]=0;
	c[t2]=mx-1;
	for(i=0;i<mx;i++){
		for(j=0;j<my;j++){
			ca[k][i][j]=ca[l][c[t1]][c[t2]];
			c[t1]++;
		}
		c[t2]--;
		c[t1]=0;
	}
	if(h==1){b=mx;mx=my;my=b;}
}
void main()
{
	ifstream in("c:/work/eq18.in");
	in >> n>>m;
	for(i=0;i<m;i++){
		in >> y>>x;
		room[y-1][x-1]=1;
	}
	in >> yx>>ry>>dx>>ly;
	if(yx>dx){mx=yx;}else{mx=dx;}
	if(ry>ly){my=ry;}else{my=ly;}
	for(i=0;i<ly;i++){
		for(j=0;j<yx;j++){
			ca[0][i][j]=1;
		}
	}
	if(ry>ly){
		for(i=0;i<ry;i++){
			for(j=yx-1;j>=yx-dx;j--){
				ca[0][i][j]=1;
			}
		}
	}else{
		for(i=0;i<ly;i++){
			for(j=0;j<dx;j++){
				ca[0][i][j]=1;
			}
		}
	}
	ax[0]=mx;
	ay[0]=my;
	jick(1,0,0);
	jick(2,1,1);
	jick(3,2,0);
	for(m=0;m<4;m++){
		for(i=0;i<=n-ay[m];i++){
			for(j=0;j<=n-ax[m];j++){
				flag=0;
				for(k=0;k<ay[m];k++){
					for(l=0;l<ax[m];l++){
						if(room[i+k][j+l]+ca[m][k][l]<2){
							flag++;			
						}
					}
				}
				if(flag==ay[m]*ax[m]){
					cnt++;
				}
			}
		}
	}
	ofstream out("c:/work/eq18.out");
	out << cnt;
}