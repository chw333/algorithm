#include<fstream.h>

int sw;
int N;
float X[100],Y[100];
float Rx,Ry;

void init()
{
	int i;
	ifstream in("inside.in");
	in >> N;
	for(i=0; i<N; i++){
		in >> X[i] >> Y[i];
	}
	in >> Rx >> Ry;
}

float ccw(float Ax, float Ay, float Bx, float By, float Cx, float Cy)
{
	float sw;
	
	sw=(Bx-Ax)*(Cy-Ay)-(By-Ay)*(Cx-Ax);

	return sw;
}

void process()
{
	float temp1,temp2,temp3;
	int i,j,k;

	for(i=0; i<N; i++){
		for(j=i+1; j<N; j++){
			for(k=j+1; k<N; k++){
				temp1=ccw(X[i],Y[i],X[j],Y[j],Rx,Ry);
				temp2=ccw(X[j],Y[j],X[k],Y[k],Rx,Ry);
				temp3=ccw(X[k],Y[k],X[i],Y[i],Rx,Ry);
				if( (temp1<0 && temp2<0 && temp3<0) || (temp1>0 && temp2>0 && temp3>0) ) sw++;
			}
		}
	}
}

void output()
{
	ofstream out("inside.out");
	out << sw;
}

void main()
{
	init();
	process();
	output();
}