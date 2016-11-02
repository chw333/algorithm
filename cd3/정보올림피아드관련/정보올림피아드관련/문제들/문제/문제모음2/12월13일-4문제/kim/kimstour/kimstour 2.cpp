#include <stdio.h>
#include <fstream.h>

#define INFILE "kimstour07.in"
#define OUTFILE "kimstour.out"

#define MAX_N 10
#define GOOD_SQUARE 10 

/*
  GOOD_SQUARE is subtracted from the neighbors touched in cases when we
  don't care what the value is
*/

int n;
int count; /* number of good paths */
int touched[MAX_N][MAX_N];
int col_touched[MAX_N];
int row_touched[MAX_N];
int total_touched;

int target;
int neighbors_touched[MAX_N][MAX_N];

void go(int x, int y)
{
	if(x == 1 && y == n) {
		if(total_touched == target)
			count++;
		return;
	}
  
	if(touched[x][y])
		return;
  
	/* prune horizontal/vertical walls we've created */
	if(col_touched[x-1] == n)
		return;
  
	if(row_touched[y+1] == n)
		return;
  
	/* prune block-offs */
	if(x == n && !touched[n][y-1])
		return;
  
	if(y == n && !touched[x+1][n])
		return;

	if(x == 1 && !touched[1][y-1])
		return;

	if(y == 1 && !touched[x-1][1])
		return;

	neighbors_touched[x+1][y]++;
	neighbors_touched[x][y+1]++;
	neighbors_touched[x-1][y]++;
	neighbors_touched[x][y-1]++;
  
  
	  int dead_ends=0;
  
	if(neighbors_touched[x+1][y] > 2)
		dead_ends++;
	if(neighbors_touched[x][y+1] > 2)
		dead_ends++;
	if(neighbors_touched[x-1][y] > 2)
		dead_ends++;
	if(neighbors_touched[x][y-1] > 2)
		dead_ends++;
  
	/* prune cases of more than one dead end */
  
	if(dead_ends <= 1) {
    
		touched[x][y] = 1;
		neighbors_touched[x][y] -= GOOD_SQUARE;
    
		col_touched[x]++;
		row_touched[y]++;
    
		total_touched++;
    
		/* if there is one "dead end", make sure we go to it next */
    
		if(dead_ends == 1) {
			if(neighbors_touched[x+1][y] > 2)
				go(x+1, y);
			if(neighbors_touched[x][y+1] > 2)
				go(x, y+1);
			if(neighbors_touched[x-1][y] > 2)
				go(x-1, y);
			if(neighbors_touched[x][y-1] > 2)
				go(x, y-1);
		}
		else if(dead_ends == 0) {
			go(x+1, y);
			go(x, y+1);
			go(x-1, y);
			go(x, y-1);
	    }
    
		total_touched--;

		row_touched[y]--;
		col_touched[x]--;
		neighbors_touched[x][y] += GOOD_SQUARE;
		touched[x][y] = 0;
	}
  
	neighbors_touched[x+1][y]--;
	neighbors_touched[x][y+1]--;
	neighbors_touched[x-1][y]--;
	neighbors_touched[x][y-1]--;
}


void main()
{
	FILE *in = fopen(INFILE, "r");
	int i;
	fscanf(in, "%d", &n);
	target = n*n-1;

	for(i=1; i<=n; i++) {
		touched[i][n+1] = 1;
		touched[i][0] = 1;
		touched[n+1][i] = 1;
		touched[0][i] = 1;

		neighbors_touched[1][i]++;
		neighbors_touched[n][i]++;
		neighbors_touched[i][1]++;
		neighbors_touched[i][n]++;
	}

	for(i=0; i<=n+1; i++) {
		neighbors_touched[0][i] = -GOOD_SQUARE;
		neighbors_touched[i][0] = -GOOD_SQUARE;
		neighbors_touched[n+1][i] = -GOOD_SQUARE;
		neighbors_touched[i][n+1] = -GOOD_SQUARE;
	}

	neighbors_touched[1][n] = -GOOD_SQUARE;

	go(1, 1);

	FILE *out = fopen(OUTFILE, "w");
	fprintf(out, "%d\n", count);
	fclose(out);
}

