#include <fstream.h>

/*int n,cnt,chk[20];
struct S{
	double x,y;
}b[20],r;*/

int n,cnt;
bool chk[20];
struct S{
	double x,y;
}b[20],r;

void input()
{
	int i;
	ifstream in("inside.in");
	in >> n;
	for(i=0;i<n;i++)
		in >> b[i].x >> b[i].y;
	in >> r.x >> r.y;
}
int where(int f,int s){
	if( (b[s].x-b[f].x)*(r.y-b[f].y) - (b[s].y-b[f].y)*(r.x-b[f].x) >0)
		return 1;
	else if((b[s].x-b[f].x)*(r.y-b[f].y) - (b[s].y-b[f].y)*(r.x-b[f].x) ==0){
		if( (0<r.x-b[f].x &&  r.x-b[f].x< b[s].x-b[f].x) &&
			(0<r.y-b[f].y &&  r.y-b[f].y< b[s].y-b[f].y))return 1;
	}
	return 5;
}
void play()
{
	int i,j,k,hap,hap2;
	for(i=0;i<n-2;i++){
		chk[i]=1;
		for(j=i+1;j<n-1;j++){
			hap=where(i,j);
			chk[j]=1;
			if(hap<3)
				hap2=hap;
				for(k=j+1;k<n;k++){
					if(chk[k]!=1){
						hap=hap2;
						hap+=where(k,i); hap+=where(j,k);
							if(hap<5)cnt++;
					}
				}	
			chk[j]=0;
		}
	}
}
void output()
{
	ofstream out("inside.out");
	out << cnt;
	out.close();
}
void main()
{	
	input();
	play();
	output();
}