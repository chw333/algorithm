#include <iostream.h>

// author: Owen Astrachan
// for internet programming contest 1993 (problem 4)
//
// how many pipes fit in a rectangular box? (see problem description)

const double sqrtThree = 1.7320508075;

int
Grid(double x, double y)
// postcondition: return # pipes fit in a box with dimensions x,y
//                if pipes stacked 'rectangularly' or 'grid' style
//  O O O
//  O O O   <- pipes grid style
//  O O O     
{
    return int(x)*int(y);
}

int
Skew(double x, double y)
// postcondition: return # of pipes fit in a box with dimensions x,y
//                if pipes fit 'skewed'
//  O O O
//   O O    <- pipes skew style
//  O O O          
{
    int rows = 1 + 2*(y - 1)/sqrtThree;

    if (y < 1.0){     // be safe
	return 0;
    }
    else{

	    // do some geometry
	
	return int(x)*((1+rows)/2) + int(x - 0.5)*(rows/2);
    }
}

inline int Max(int x, int y)
{
    return x > y ? x : y;
}

main()
{
    double x,y;

    while (cin >> x >> y){
	int grid = Grid(x,y);
	int skew1 = Skew(x,y);
	int skew2 = Skew(y,x);
//	cout << "\t\t" << grid << " s1 " << skew1 << " s2 " << skew2
//	    << endl;
	if (grid >= Max(skew1,skew2)){
	    cout << grid << " grid" << endl;
	}
	else{
	    cout << Max(skew1,skew2) << " skew" << endl;
	}
    }
}
