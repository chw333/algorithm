#include <iostream.h>
#include <iomanip.h>

// author: Owen Astrachan
// for internet programming contest 1993 (problem 8)
//
// given directed graph, determine # of paths between every
// pair of vertices


const int MAX_V = 40;           // maximum # of vertices in a graph

int graph[MAX_V][MAX_V];        // use adjacency matrix
int numVerts;                   // number of vertices in graph
int cycle[MAX_V];               // boolean, cycle[k] = 1 iff cycle to k
int visited[MAX_V];             // used in dfs

int ReadGraph();
void Paths();
void Dfs(int,int);

main()
{
    int num = 0;
    while (ReadGraph()){
	int k;
	for(k=0; k < numVerts; k++){
	    int j;
	    for(j=0; j < numVerts;j++){    // no nodes visited
		visited[j] = 0;
	    }
	    Dfs(k,k);                      // search for cycles 
	}
	cout << "matrix for city " << num << endl;
	Paths();
	num++;
    }
}

void
ZeroGraph()
// postcondition: no connections between any vertices (all zero)
{
    int j,k;
    for(j=0; j < MAX_V; j++){
	cycle[j] = visited[j] = 0;
	for(k=0; k < MAX_V; k++){
	    graph[j][k] = 0;
	}
    }
}

void
Dfs(int vertex,int start)
// precondition: start = first node of a depth-first search
// postcondition: all nodes reachable from start (using dfs)
//                explored, cycle[start] = 1 iff cycle exists      
{
    if (!visited[vertex]){
	visited[vertex] = 1;
	int k;
	for(k=0; k < numVerts; k++){
	    if (graph[vertex][k]){
		Dfs(k,start);
	    }
	}
    }
    else{
	if (vertex == start){
	    cycle[start] = 1;
	}
    }
}

void
Paths()
// standard transitive closure augmented to determine # of paths
// rather than whether a path exists     
{
    static int cost[MAX_V][MAX_V];         // # of paths between verts
    int j,k;
    for(j=0; j < numVerts; j++){
	for(k=0; k < numVerts; k++){
	    cost[j][k] = graph[j][k];   
	}
    }
    int i;
    for(k=0; k < numVerts; k++){
	for(i=0; i < numVerts; i++){
	    for(j=0; j < numVerts; j++){
		int preK = cost[i][j];
		int postK1 = cost[i][k];
		int postK2 = cost[k][j];
		int prod = postK1*postK2;
		if (preK < 0){               // infinity?
		    cost[i][j] = -1;
		}
		else if (prod < 0){
		    cost[i][j] = -1;
		}
		else if (prod > 0 && (postK1 < 0 || postK2 < 0)){
		    cost[i][j] = -1;
		}
		else if (prod != 0 && cycle[k]){
		    cost[i][j] = -1;
		}
		else{
		    cost[i][j] = preK + prod;
		}
	    }
	}
    }

    for(j=0; j < numVerts; j++){
	for(k=0; k < numVerts; k++){
	    cout << " " << cost[j][k];
	}
	cout << endl;
    }
    
}

int
ReadGraph()
{
    ZeroGraph();
    int one,two;
    int max = -1;
    int roads;
    if (cin >> roads){
	int k;
	for(k=0; k < roads; k++){
	    cin >> one >> two;
	    graph[one][two] = 1;
	    if (one > max) max = one;       // determine # of vertices
	    if (two > max) max = two;    
	}
	numVerts = max+1;
	return 1;
    }
    else{
	return 0;
    }
}
