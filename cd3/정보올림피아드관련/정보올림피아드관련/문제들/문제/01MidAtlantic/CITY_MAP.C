#include <stdio.h>
#define UP 1
#define DOWN 2
#define RIGHT 3
#define LEFT 4

#define MAX_PATHS 50000

int rows;
int columns;

char map[25][25];
double loads[25][25];
char inputline[100];
int doorx[30];
int doory[30];


int start; 
int finish;
int load;
int paths[MAX_PATHS][100];
int current_path[500];
int travelled[25][25];
int num_paths;
int min_path;

void copy_path(int steps, int number)
{
	int x;

	if (number > MAX_PATHS)
	{
	    num_paths++;
		return;

printf("Resetting the minimum to %d\n", min_path);
		num_paths = 0;
		min_path = min_path - 1;
		return;
	}

	for (x = 0; x < steps; x++)
	{
		paths[number][x] = current_path[x];
//printf("Copying path %d step %d value %d\n", number, x, current_path[x]);
	}
	num_paths = number + 1;
}


void check_path(int sx, int sy, int fx, int fy, int step)
{
	if ((sx == fx) && (sy == fy))
	{
//printf("Found path %d %d %d %d %d %d\n", sx, sy, fx, fy, step, num_paths);
		if (step < min_path)
		{
			min_path = step;
			copy_path(step, 0);
		}
		else if (step == min_path) copy_path(step, num_paths);
		return;
	}

	// If I have been here, it is not a sidewalk, I have reached the minimum path, or it is not a valid space return
	if (travelled[sx][sy] != 0) return;
	if ((map[sx][sy] != '.') && (step != 0)) return;
	if (step >= min_path) return;
	if ((sx < 0) || (sy < 0) || (sx == rows) || (sy == columns)) return;

		travelled[sx][sy] = step;
	if (sx < fx)
	{ /* check down then up */
		current_path[step] = DOWN;
		check_path(sx+1, sy, fx, fy, step + 1);
		current_path[step] = UP;
		check_path(sx-1, sy, fx, fy, step + 1);
	}
	else 
	{ /* check down then up */
		current_path[step] = UP;
		check_path(sx-1, sy, fx, fy, step + 1);
		current_path[step] = DOWN;
		check_path(sx+1, sy, fx, fy, step + 1);
	}
	if (sy < fy)
	{
		current_path[step] = RIGHT;
		check_path(sx, sy+1, fx, fy, step + 1);
		current_path[step] = LEFT;
		check_path(sx, sy-1, fx, fy, step + 1);
	}
	else 
	{
		current_path[step] = LEFT;
		check_path(sx, sy-1, fx, fy, step + 1);
		current_path[step] = RIGHT;
		check_path(sx, sy+1, fx, fy, step + 1);
	}
	travelled[sx][sy] = 0;
	return;
}

void add_paths(int x, int y, int fx, int fy, double per)
{
	int cx, cy;
	int i, j;
if (num_paths > MAX_PATHS)
{ 
printf("Ran out of space %d %d %d %d %d\n", x, y, fx, fy, num_paths);
return;
}
//printf("Adding paths %d %d %d %d %lf\n", x, y, num_paths, min_path, per);
	for (j = 0; j < num_paths; j++)
	{
		cx = x; cy = y;

		for (i = 0; i < (min_path-1); i++)
		{
//printf("Adding to %d %d value %lf\n", cx, cy, per);
			switch (paths[j][i])
			{
				case UP: cx = cx-1; break;
				case DOWN: cx = cx+1; break;
				case RIGHT: cy = cy+1; break;
				case LEFT: cy = cy-1; break;
			}
			loads[cx][cy] += per;
		}
	}
}

void add_load(int s, int f, int l)
{
	int x, y;
	int myx, myy;
	int fx, fy;
	double per;
//printf("Adding load %d %d %d\n", s,f,l); 

	num_paths = 0;
	min_path = 60;

	for (x = 0; x < rows; x++)
		for (y = 0; y < columns; y++)
			travelled[x][y] = 0;

	myx = doorx[s];
	myy = doory[s];

	fx = doorx[f];
	fy = doory[f];

//printf("Path search for %d %d to %d %d\n", myx, myy, fx, fy);

	check_path(myx, myy, fx, fy, 0);

	per = (double)load / num_paths;

	add_paths(myx, myy, fx, fy, per);

 // printf("Adding load from %d %d to %d %d of size %d %lf %d\n", myx, myy, fx, fy, l, per, num_paths);
}

void print_loads(void)
{
	int x, y;

	for (x = 0; x < rows; x++)
	{
		for (y = 0; y < columns; y++)
		{
			printf("%7.2lf", loads[x][y]);
		}
		printf("\n");
	}
}


void main(void)
{
	int x,y;

	gets(inputline);
	sscanf(inputline, "%d %d", &columns, &rows);

	for (x = 0; x < rows; x++)
	{
		gets(inputline);
		for (y = 0; y < columns; y++)
		{
			loads[x][y] = 0;
			map[x][y] = inputline[y];
			if ((inputline[y] != '.') && (inputline[y] != 'X'))
			{
				doorx[inputline[y] - 'A'] = x;
				doory[inputline[y] - 'A'] = y;
			}
		}
	}
#if 0
	for (x = 0; x < rows; x++)
	{
		for (y = 0; y < columns; y++)
		{
			printf("%7.2lf", loads[x][y]);
		}
		printf("\n");
	}

	for (x = 0; x < rows; x++)
	{
		for (y = 0; y < columns; y++)
		{
			printf("%c", map[x][y]);
		}
		printf("\n");
	}
#endif 
	gets(inputline);
	while (inputline[0] != 'X')	
	{
		sscanf(&(inputline[2]), "%d",&load);
		start = inputline[0]-'A';
		finish = inputline[1]-'A';
		add_load(start, finish, load);
		gets(inputline);
	}

	print_loads();
}
