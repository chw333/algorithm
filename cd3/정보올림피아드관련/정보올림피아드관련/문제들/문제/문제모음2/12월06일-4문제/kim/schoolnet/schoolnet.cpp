#include <stdio.h>

#define MAX_N 100
#define INFILE "schoolnet20.in"
#define OUTFILE "schoolnet20.out"

int n;
int conn[MAX_N][MAX_N]; //[from][to]

int is_top[MAX_N];
int has_top[MAX_N];
int touched[MAX_N];
int reachable[MAX_N];

int max(int a, int b)
{
    return a>b?a:b;
}

void fill_from(int x)
{
    if(touched[x])
        return;
  
    is_top[x] = 0;
    has_top[x] = 1;
    touched[x] = 1;
  
    for(int i=0; i<n; i++)
        if(conn[x][i])
            fill_from(i);
}

int count_tops()
{
	int i;
    for(i=0; i<n; i++) {
        has_top[i] = 0;
        is_top[i] = 0;
    }
  
    while(1) {
    
    // find one that has no top
    
      for(i=0; i<n; i++)
          if(!has_top[i])
              break;
    
      if(i == n)
          break;
    
      for(int j=0; j<n; j++)
          touched[j] = 0;
    
      // flood-fill all descendents of it to have a top, and not be a top
      fill_from(i);
    
      is_top[i] = 1;
    }
  
    int count = 0;
  
    for(i=0; i<n; i++)
        if(is_top[i])
            count++;
  
    return count;
}

void fill_reachable(int x)
{
    if(reachable[x])
        return;
  
    reachable[x] = 1;
  
    for(int i=0; i<n; i++)
        if(conn[x][i])
            fill_reachable(i);
}

// check to see if the graph is already fully connected
int none_needed()
{
	int i,j;
    for(i=0; i<n; i++) {
      for(j=0; j<n; j++)
          reachable[j] = 0;
      fill_reachable(i);
    
      for(j=0; j<n; j++)
          if(!reachable[j])
              return 0;
    }
    return 1;
}
      

int main()
{
    FILE *in;
  
    in = fopen(INFILE, "r");
  
    fscanf(in, "%d", &n);
  
	int i, j;
    for(i=0; i<n; i++) {
        while(1) {
            int to;
            fscanf(in, "%d", &to);
            if(to == 0)
                break;
            conn[i][to-1] = 1;
        }
    }
    fclose(in);
  
    int tops = count_tops();
  
    // reverse the graph
    for(i=0; i<n; i++)
        for(j=i+1; j<n; j++) {
            int temp = conn[i][j];
            conn[i][j] = conn[j][i];
            conn[j][i] = temp;
        }
  
    int bottoms = count_tops();
    int b;
  
    if(none_needed())
        b = 0;
    else
        b = max(tops, bottoms);
  
    FILE *out;
    out = fopen(OUTFILE, "w");
    fprintf(out, "%d\n%d\n", tops, b);
    fclose(out);
    return 0;
}

