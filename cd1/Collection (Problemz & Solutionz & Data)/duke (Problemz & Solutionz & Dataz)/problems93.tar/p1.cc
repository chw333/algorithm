#include <iostream.h>
#include <string.h>

// author: Owen Astrachan
// for internet programming contest 1993 (problem 1)

const int MAX = 55;            // maximum grid size (be safe)
const int MAXSTRING = 120;     // maximum robot instruction string length

int grid[MAX][MAX];            // the grid
int length, width;             // x max, y max

void Process(int, int, char, char *);

main()
{
    int j,k;
    char instruction[MAXSTRING];
    
	// initialize grid to be safe

    for(j=0; j < MAX; j++){
	for(k=0; k < MAX; k++){
	    grid[j][k] = 0;
	}
    }
    
    cin >> length >> width;    // read max x, max y coordinates

    int x,y;
    char orient;

    while (cin >> x >> y >> orient){
	cin >> instruction;
	Process(x,y,orient,instruction);
    }
}

char Left(char dir)               // return orientation when left-turn
{
    if (dir == 'N') return 'W';
    if (dir == 'S') return 'E';
    if (dir == 'E') return 'N';
    if (dir == 'W') return 'S';
}

char Right(char dir)              // return orientation when right-turn
{
    if (dir == 'N') return 'E';
    if (dir == 'S') return 'W';
    if (dir == 'E') return 'S';
    if (dir == 'W') return 'N';
}

void
Move(int x, int y, char orient, int & nx, int & ny)
// convert x,y, orient to a newx and newy coordinate     
{
    nx = x;    // default is don't change coordinates
    ny = y;
    if (orient == 'E'){
	nx = x + 1;
    }
    else if (orient == 'W'){
	nx = x - 1;
    }
    else if (orient == 'N'){
	ny = y + 1;
    }
    else if (orient == 'S'){
	ny = y - 1;
    }
}


void
Process(int x, int y, char orient, char * s)
// pre: x, y = init grid point, orient = init orientation
//      s = robot instruction set
// post: robot motion simulating, if robot lost, final grid point = 1     
{
    int len = strlen(s);
    int k;
    int newX, newY;
    
    for(k=0; k < len; k++){
	switch (s[k]){
	  case 'L':
	    orient = Left(orient);
	    break;
	  case 'R':
	    orient = Right(orient);
	    break;
	  case 'F':
	    Move(x,y,orient,newX,newY);
	    if (newX < 0 || newX > length || newY < 0 || newY > width){
		if (grid[x][y] == 0){
		    grid[x][y] = 1;     // remember getting lost
		    cout << x << " " << y << " " << orient << " LOST"
			<< endl;
		    return;
		}
	    }
	    else{
		x = newX;
		y = newY;
	    }
	    break;
	}
    }
    cout << x << " " << y << " " << orient << endl;
}
