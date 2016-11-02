#include<fstream.h>
int n,i,j,k,w,cnt;
double bx[50],by[50],rx,ry;
int ccw(double ax,double ay,double bx,double by,double cx,double cy)
{
	double s,a=by-ay;
	s=(bx-ax)*(ry-ay)-(by-ay)*(rx-ax);
	if(s>0){w++;}
	if(s<0){w--;}
	s=(cx-bx)*(ry-by)-(cy-by)*(rx-bx);
	if(s>0){w++;}
	if(s<0){w--;}
	s=(ax-cx)*(ry-cy)-(ay-cy)*(rx-cx);
	if(s>0){w++;}
	if(s<0){w--;}
	return w;
}
void main()
{
	ifstream in("inside.in");
	in >> n;
	for(i=0;i<n;i++){
		in >> bx[i]>>by[i];
	}
	in >> rx>>ry;
	for(i=0;i<n-2;i++){
		for(j=i+1;j<n-1;j++){
			for(k=j+1;k<n;k++){
				w=0;
				ccw(bx[i],by[i],bx[j],by[j],bx[k],by[k]);	
				if(w==3||w==-3){cnt++;}
			}
		}
	}
	ofstream out("inside.out");
	out << cnt;
}