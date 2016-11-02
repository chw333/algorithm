#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <conio.h>
#define	MAX	1000
#define	filename1	"position.in"
#define	filename2	"position.out"
#define	sqr(x)		(((double)x)*((double)x))

class	center {
public:
	double x,y ; 
	double longest ; 
	bool	find;
}sol ; 

class	point {
public:
	int	x,y;

	center tri_center2(point a,point b){
		center temp ;
		if ( ( (_int64)(x-a.x)*(_int64)(b.y-a.y)-(_int64)(b.x-a.x)*(_int64)(y-a.y)  )==0) 
		{
			temp.x =0 ; temp.y=0 ; return temp;
		}

		temp.x = -(double)( (sqr(a.x)-sqr(x)+sqr(a.y)-sqr(y))*(b.y-a.y) -
					(sqr(a.x)-sqr(b.x)+sqr(a.y)-sqr(b.y))*(y-a.y)  ) /
					(2*( (double)(x-a.x)*(double)(b.y-a.y)-(double)(b.x-a.x)*(double)(y-a.y)  ) ) ;
		if ( ( (_int64)(y-a.y)*(_int64)(b.x-a.x)-(_int64)(b.y-a.y)*(_int64)(x-a.x)  )==0)
		{
			temp.x =0 ; temp.y=0 ; return temp;
		}

		temp.y = -(double)( (sqr(a.y)-sqr(y)+sqr(a.x)-sqr(x))*(b.x-a.x) -
					(sqr(a.y)-sqr(b.y)+sqr(a.x)-sqr(b.x))*(x-a.x)  ) /
					(2*( (double)(y-a.y)*(double)(b.x-a.x)-(double)(b.y-a.y)*(double)(x-a.x)  ) ) ;
		return temp ; 
	}

	center bi_center(point a){
		center temp ; 
		temp.x = (double) (x+a.x) / 2 ; 
		temp.y = (double) (y+a.y) / 2 ; 
		return temp ; 
	}
	double distance2(center a){
		return (sqr(x-a.x)+sqr(y-a.y));
	
	}
	int turn(point a,point b){
		return ( x*a.y+a.x*b.y+b.x*y-a.x*y-b.x*a.y-x*b.y );
	}
} island[MAX] , convex[MAX];

int n,m ; 

void read_data()
{
	FILE *infile = fopen(filename1,"r");
	fscanf(infile,"%d",&n);
	int i,j;
	for(i=0 ; i<n; i++) {
		fscanf(infile,"%d %d",&island[i].x,&island[i].y);
		for(j=0;j<i;j++)
			if ( island[i].x== island[j].x && island[i].y==island[j].y)
				printf("exist coupled data \n");
	}
	fclose(infile);
}

void test_output(center temp)
{
	if ((sol.longest==-1) || (sol.longest>temp.longest)) {
		sol = temp ; 
	}
}

void find_convex_hull()			//  + + +  + +  + ++ +++   + ?
{
	m = 1 ; 
	convex[0] = island[0] ; 
	int i,start=0,before,next=-1,visit[MAX] ;
	for (i=1 ;i<n; i++)
		if ( (convex[0].x > island[i].x) ||
			(convex[0].x==island[i].x && convex[0].y>island[i].y) ){
				start = i ; 
				convex[0] = island[i] ; 
		}

	for(i=0; i<n; i++)
		visit[i] = false ; 

	before = start ; next = -1 ; 
	while( start!=next)
	{
		for(i=0 ; i<n ; i++)
			if (before!=i && !visit[i] ) {next = i ; break;}
		for(i=0 ; i<n ; i++)
			if (before!=i && next!=i && !visit[i]) {

				if (convex[m-1].turn(island[next],island[i])>0) {
					next = i ;
				} else if ( (convex[m-1].turn(island[next],island[i])==0) && 
							! ( (island[i].x-convex[m-1].x)*(island[i].x-island[next].x) >=0 &&
						        (island[i].y-convex[m-1].y)*(island[i].y-island[next].y) >=0 ) ) {
					next = i ;
				}
			}
		before = next ;
		if (next!=start) {
			convex[m++] = island[next] ;
			visit[next] = true ; 
		}
	}
}

void process2()
{
	sol.longest = -1 ;
	int i,j,k,l	;
	for(i=0;i<m;i++){
		for(j=i+1;j<m;j++)
			for(k=j+1;k<m;k++){
				center temp = convex[i].tri_center2(convex[j],convex[k]); //,island[k]);
					temp.longest=convex[i].distance2(temp);

					bool isItokay = true; 
					for(l=0;l<n;l++)
						if (island[l].distance2(temp)>temp.longest+0.00001) {
							isItokay = false ; 
							break;
						}

					if(isItokay){
						test_output(temp);
					}
			}
	}
	for(i=0;i<m;i++)
		for(j=i+1;j<m;j++){
			center temp = convex[i].bi_center(convex[j]); //,island[k]);
			temp.longest=convex[i].distance2(temp);
					if( fabs(convex[i].distance2(temp)-convex[j].distance2(temp))>0.0001  ) {
					printf("%f %f %f \n",temp.longest,sqrt(convex[i].distance2(temp)),sqrt(convex[j].distance2(temp)));
						printf ("%f %f \n",fabs(convex[i].distance2(temp)-convex[j].distance2(temp)));
						printf(" center error \n");
					}
			bool isItokay = true; 
			for(l=0;l<n;l++)
				if (island[l].distance2(temp)>temp.longest+0.00001) {
					isItokay = false ; 
					break;
				}
			if(isItokay){
				test_output(temp);
			}
		}
}

void output()
{
	FILE *outfile = fopen(filename2,"w");
	fprintf(outfile,"%.3f %.3f\n%.3f\n",sol.x,sol.y,sqrt(sol.longest));
	fclose(outfile);
}

int main()
{
	read_data();
	find_convex_hull();
	process2();
	output();
	return 0 ;
}
