#include <fstream.h>

#define MaxN 1000

ifstream in ( "stickmove10.in" );
ofstream out ("stickmove10.out");

#define Min(a,b) ((a<b)?a:b)

double Stick[MaxN][4];
double Decline[MaxN][2];  // [0]->dx, [1]->dy
int Forw[MaxN][MaxN], Forwi[MaxN]; // Forw indegree  i  to self
int Back[MaxN][MaxN], Backi[MaxN]; // Back indegree  i  to self
int N, Path[MaxN], Visit[MaxN], R;
 
void input()
{
	int i;
	double dx, dy;
	double x1, y1, x2, y2, sx, sy, ex, ey;
	in >> N;
	for ( i = 0; i < N; i ++ ) {
		in >> x1 >> y1 >> x2 >> y2;
		if ( x1 < x2 ) {
		    	sx = x1; sy = y1; ex = x2; ey = y2;
		} else if ( x1 == x2 ) {
			if ( y1 < y2 ) {
				sx = x1; sy = y1; ex = x2; ey = y2;
			} else {
				sx = x2; sy = y2; ex = x1; ey = y1;
			}
		} else {
			    sx = x2; sy = y2; ex = x1; ey = y1;
		}
		Stick[i][0] = sx; Stick[i][1] = sy;
		Stick[i][2] = ex; Stick[i][3] = ey;
		dy = ex - sx; dx = -1*(ey - sy);
		Decline[i][0] = dx; Decline[i][1] = dy;
	}
}

int ccw ( double x, double y, double a, double b, double c, double d )
{
	if ( (a-x)*(d-y)-(b-y)*(c-x) > 0 ) return 1;
	else return -1;
}

int crosscheck ( double sx1, double sy1, double ex1, double ey1, double sx2, double sy2, double ex2, double ey2 )
{
	int r1, r2, r3, r4 ;
    r1 = ccw ( sx1, sy1, ex1, ey1, sx2, sy2 );
	r2 = ccw ( sx1, sy1, ex1, ey1, ex2, ey2 );
    r3 = ccw ( sx2, sy2, ex2, ey2, sx1, sy1 );
	r4 = ccw ( sx2, sy2, ex2, ey2, ex1, ey1 );
	if ( r1 * r2 <= 0 && r3 * r4 <= 0) return 1;
	else return 0;
}

int is_in ( double x1, double y1, double x2, double y2, 
			            double x3, double y3, double x4, double y4, double x, double y, int dir )
{
	if ( 
		ccw ( x1, y1, x2, y2, x, y ) == dir &&
		ccw ( x2, y2, x3, y3, x, y ) == dir &&
		ccw ( x3, y3, x4, y4, x, y ) == dir ) {
		return 1;
	}
	return 0;
}


void makedb ( int self, double x1, double y1, double x2, double y2, 
			            double x3, double y3, double x4, double y4, int f_b )
{
	int i, sw, dir;
	dir = ccw ( x1, y1, x2, y2, x3, y3 );
	for ( i = 0; i < N; i ++ ) {
		if ( i == self ) continue;
		sw = 0;
		if ( crosscheck ( x1, y1, x2, y2, Stick[i][0], Stick[i][1], Stick[i][2], Stick[i][3] ) ) {
			sw = 1;
		} else if ( is_in ( x1, y1, x2, y2, x3, y3, x4, y4, Stick[i][0], Stick[i][1], dir ) ) {
			sw = 1;
		} else if ( is_in ( x1, y1, x2, y2, x3, y3, x4, y4, Stick[i][2], Stick[i][3], dir ) ) {
			sw = 1;
		}
		if ( sw ) {
			if ( f_b ) { Forw[i][self] = 1; Forwi[self] ++; }
			else { Back[i][self] = 1; Backi[self] ++; }
		}
	}
}

void makedb_ ()
{
	int i;
	double x[4], y[4], sx, sy, ex, ey; 
	for ( i = 0; i < N; i ++ ) {
		sx = Stick[i][0]; sy = Stick[i][1];
		ex = Stick[i][2]; ey = Stick[i][3];
		if ( Decline[i][0] == 0 ) {
			x[0] = sx; y[0] = sy + 10000;
			x[1] = ex; y[1] = ey + 10000;
			x[2] = sx; y[2] = sy - 10000;
			x[3] = ex; y[3] = ey - 10000;
		} else {
			x[0] = sx+10000; y[0] = sy + 10000 * Decline[i][1]/Decline[i][0];
			x[1] = ex+10000; y[1] = ey + 10000 * Decline[i][1]/Decline[i][0];
			x[2] = sx-10000; y[2] = sy - 10000 * Decline[i][1]/Decline[i][0];
			x[3] = ex-10000; y[3] = ey - 10000 * Decline[i][1]/Decline[i][0];
		}
		makedb( i, x[0], y[0], sx, sy, ex, ey, x[1], y[1], 1 );
		makedb( i, x[3], y[3], ex, ey, sx, sy, x[2], y[2], 0 );
	}
}

void delete_degree ( int s )
{
	int i;
	for ( i = 0; i < N; i ++ ) {
        if ( Forw[s][i] ) { Forw[s][i] = 0; Forwi[i] --; }
		if ( Back[s][i] ) { Back[s][i] = 0; Backi[i] --; }
    }
}

int topol( int n )
{
	int i, ret;
	for ( i = 0; i < N; i ++ ) {
		if ( Visit[i] ) continue;
		if ( Forwi[i] == 0 || Backi[i] == 0 ) {
			Visit[i] = 1;
			Path[n] = i+1;
			if ( n+1 == N ) return 1;
            delete_degree ( i );
			ret = topol ( n+1 );
			if ( ret ) return ret;
			else return 0;
		}
	}
	return 0;
}

void output()
{
	int i;
	if ( R ) {
	    for ( i = 0; i < N; i ++ ) {
		    if ( i != 0 ) out << " ";
		    out << Path[i];
		}
	} else {
		out << "-1";
	}
}

void process()
{
	makedb_();
	if ( topol(0) ) R = 1;
}

void main()
{
	input();
	process();
	output();
}