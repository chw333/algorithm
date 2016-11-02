/*-----------------------------------------------------------------------
 * 
 * File Name:   p5.c
 * 
 * Author:      A. Lumsdaine
 * 
 *-----------------------------------------------------------------------
 * 
 * DESCRIPTION
 *     Source code file for problem #5 of 1996 ACM
 *     East-Central Regional Programming contest.
 * 
 * DIAGNOSTICS
 *     Use Dijkstra's algorithm to find shortest paths to each vertex.
 *     Print the value of the longest shortest path.  Infinity is 
 *     designated with -1.
 *
 *-----------------------------------------------------------------------

#include <stdio.h>
#include <strings.h>
#include <math.h>
#include <limits.h>


#define MAX_SIZE 100

static int
MIN(int x, int y) 
{
  if (x == -1 && y == -1)
    return -1;
  if (x == -1)
    return y;
  if (y == -1)
    return x;

  return (x < y ? x : y);
}


static int 
isamin(int n, int c[], int d[])
{
  int i, j, min = INT_MAX, imin = -1;
  
  for (i = 0; i < n; i++) {
    j = c[i];
    if (d[j] >= 0 && d[j] < min) {
      min = d[j];
      imin = j;
    }
  }
  
  return imin;
}


static int 
amax(int n, int a[])
{
  int i, max = 0;
  
  for (i = 0; i < n; i++)
    if (a[i] > max)
      max = a[i];
  
  return max;
}


static void
erase_v(int n, int a[], int v)
{
  int i;

  for (i = 0; a[i] != v; i++)
    ;

  for (; i < n-1; i++)
    a[i] = a[i+1];
  a[n-1] = -1;
}


int
main()
{
  char buffer[BUFSIZ], *cptr;
  int i, j, v, w, size, csize;
  int L[MAX_SIZE][MAX_SIZE];
  int C[MAX_SIZE];
  int D[MAX_SIZE];

  (void) scanf("%d\n", &size);

  bzero((void *) L, sizeof(L));

  /* For each row */
  for (i = 1; i < size; i++) {
    (void) gets(buffer);
    cptr = strtok(buffer, " ");
    for (j = 0; j < i; j++) {
      if (cptr[0] == 'x')
	L[i][j] =  -1;		/* -1 means infinity */
      else
	(void) sscanf(cptr, "%d", &L[i][j]);
      L[j][i] = L[i][j];
      cptr = strtok(NULL, " ");
    }
  }

  /* Now do Dijkstra's algorithm */
  for (i = 0; i < size - 1; i++)
    C[i] = i+1;
  
  D[0] = -1;
  for (i = 1; i < size; i++)
    D[i] = L[0][i];
  
  for (csize = size - 1; csize > 1; csize--) {
    v = isamin(csize, C, D);
    erase_v(csize, C, v);
    for (j = 0; j < csize; j++) {
      w = C[j];
      if (L[v][w] != -1)
	D[w] = MIN(D[w], D[v] + L[v][w]);
    }      
  }
    
  (void) printf("%d\n", amax(size, D));

  return 0;
}
 

