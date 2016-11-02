/* Copyright John Bonomo (ACM ICPC ECNA 1999) */

import java.io.*;
import java.util.StringTokenizer;

public class D_j {
  
  static final int MAXDIM = 100;
  static final int MAXLINES=50;
  static final int MAXNODES = MAXLINES*MAXLINES;
  
  static DataInputStream in = new DataInputStream(System.in);
  
  static point tpoint = new point();                      // treasure point
  
  static node [] graph = new node[MAXNODES];
  static int nNodes = 0;
  
  static line [] lines = new line[MAXLINES];
  static int nlines;
  
  static void printGraph()
    {
      for(int i=0; i<nNodes; i++) {
	System.out.print("[" + graph[i].p.x + ',' + graph[i].p.y + ']');
	System.out.print(" " + graph[i].out + ' ');
	for(listnode temp = graph[i].list; temp != null; temp = temp.next)
	  System.out.print("(" + graph[temp.nodenum].p.x + ','
			   + graph[temp.nodenum].p.y + ')');
	System.out.println();
      }
    }

  static void insertPoint(point p, line l)
    {
      int i = l.nsects++;
      boolean equal = (i > 0 && (Math.abs(l.isects[i-1].x - p.x) < 0.0001));
      while (i > 0 && ((!equal && l.isects[i-1].x >p.x) ||
		       (equal && l.isects[i-1].y > p.y))) {
	l.isects[i] = l.isects[i-1];
	i--;
      }
      l.isects[i] = p;
    }
  
  static void calcIsect(int l1, int l2)
    {
      float det = lines[l1].b*lines[l2].d - lines[l1].d*lines[l2].b;
      if (det == 0)
	return;
      float t = (lines[l2].a - lines[l1].a)*lines[l2].d -
	(lines[l2].c - lines[l1].c)*lines[l2].b;
      t = t/det;
      if (t>= 0 && t <= 1) {
	point p = new point();
	p.x = lines[l1].a + t*lines[l1].b;
	p.y = lines[l1].c + t*lines[l1].d;
	insertPoint(p, lines[l1]);
	insertPoint(p, lines[l2]);
      }
      return;
    }

  static void calcMidPoints(line l)
    {
      for(int i=0; i<l.nsects-1; i++) {
	l.isects[i].x = (l.isects[i].x+l.isects[i+1].x)/2;
	l.isects[i].y = (l.isects[i].y+l.isects[i+1].y)/2;
	graph[nNodes].p = l.isects[i];
	graph[nNodes].visited = false;
	graph[nNodes].list = null;
	if((graph[nNodes].p.x == 0 || graph[nNodes].p.x == MAXDIM ||
	    graph[nNodes].p.y == 0 || graph[nNodes].p.y == MAXDIM))
	  graph[nNodes].out = 1;
	else
	  graph[nNodes].out = -1;
	l.nodenum[i] = nNodes;
	nNodes++;
      }
      l.nsects--;
    }
  
  static boolean adjacent(point p1, point p2, int lnum1, int lnum2)
    {
      float a = p1.x;
      float b = p2.x-a;
      float c = p1.y;
      float d = p2.y-c;
      for(int i=0; i<nlines; i++) {
	if (i == lnum1 || i == lnum2)
	  continue;
	float det = b*lines[i].d - d*lines[i].b;
	if (det == 0)
	  continue;
	float t = (lines[i].a - a)*lines[i].d -
	  (lines[i].c - c)*lines[i].b;
	t = t/det;
	if (t >=0 && t <= 1)
	  return false;
      }
      return true;
    }

  static void createGraph()
    {
      for(int i=0; i<nlines; i++) {
	line l1 = lines[i];
	for(int j=0; j<l1.nsects; j++) {
	  point p1 = l1.isects[j];
	  for(int k=i+1; k<nlines; k++) {
	    line l2 = lines[k];
	    for(int l=0; l<l2.nsects; l++) {
	      point p2 = l2.isects[l];
	      if (adjacent(p1, p2, i, k)) {
		graph[l1.nodenum[j]].list = new listnode(l2.nodenum[l], graph[l1.nodenum[j]].list);
		graph[l2.nodenum[l]].list = new listnode(l1.nodenum[j], graph[l2.nodenum[l]].list);
	      }
	    }
	  }
	  if (adjacent(p1, tpoint, i, -1)) {
	    graph[l1.nodenum[j]].list = new listnode(nNodes-1, graph[l1.nodenum[j]].list);
	    graph[nNodes-1].list = new listnode(l1.nodenum[j], graph[nNodes-1].list);
	  }
	}
      }
    }
  
  static int getDoors()
    {
      int ndoors = 1;
      while (true) {
	for(int i=0; i<nNodes; i++) {
	  if (graph[i].out == ndoors)
	    for(listnode t=graph[i].list; t!= null; t=t.next) {
	      if (graph[t.nodenum].out == -1)
		graph[t.nodenum].out = ndoors+1;  
	    }
	}
	if (graph[nNodes-1].out != -1)
	  return graph[nNodes-1].out-1;
	ndoors++;
      }
    }

  public static void main(String [] args)
    {
      for(int i=0; i<MAXLINES; i++)
	lines[i] = new line();
      lines[0].a = lines[0].p1.x = 0;
      lines[0].c = lines[0].p1.y = 0;
      lines[0].p2.x = 0;
      lines[0].b = 0-lines[0].a;
      lines[0].p2.y = 100;
      lines[0].d = 100-lines[0].c;
      lines[0].nsects = 0;
      lines[1].a = lines[1].p1.x = 0;
      lines[1].c = lines[1].p1.y = 100;
      lines[1].p2.x = 100;
      lines[1].b = 100-lines[1].a;
      lines[1].p2.y = 100;
      lines[1].d = 100-lines[1].c;
      lines[1].nsects = 0;
      lines[2].a = lines[2].p1.x = 100;
      lines[2].c = lines[2].p1.y = 0;
      lines[2].p2.x = 100;
      lines[2].b = 100-lines[2].a;
      lines[2].p2.y = 100;
      lines[2].d = 100-lines[2].c;
      lines[2].nsects = 0;
      lines[3].a = lines[3].p1.x = 0;
      lines[3].c = lines[3].p1.y = 0;
      lines[3].p2.x = 100;
      lines[3].b = 100-lines[3].a;
      lines[3].p2.y = 0;
      lines[3].d = 0-lines[3].c;
      lines[3].nsects = 0;
      String line="";
      try {line = in.readLine();} catch (IOException e) {}
      nlines = Integer.parseInt(line);
      nlines += 4;
      
      int x1, x2, y1, y2;
      for(int i=4; i<nlines; i++) {
	try {line = in.readLine();} catch (IOException e) {}
	StringTokenizer str = new StringTokenizer(line);
	x1 = Integer.parseInt(str.nextToken());
	y1 = Integer.parseInt(str.nextToken());
	x2 = Integer.parseInt(str.nextToken());
	y2 = Integer.parseInt(str.nextToken());
	if (x1 > x2 || (x1==x2 && y1 > y2)) {
	  int temp = x1;
	  x1 = x2;
	  x2 = temp;
	  temp = y1;
	  y1 = y2;
	  y2 = temp;
	}
	lines[i].a = lines[i].p1.x = x1;
	lines[i].c = lines[i].p1.y = y1;
	lines[i].p2.x = x2;
	lines[i].b = x2-lines[i].a;
	lines[i].p2.y = y2;
	lines[i].d = y2-lines[i].c;
	lines[i].nsects = 0;
      }
      for(int i=0; i<nlines-1; i++) {
	for(int j=i+1; j<nlines; j++) {
	  calcIsect(i,j);
	}
      }
      for(int i=0; i<MAXNODES; i++)
	graph[i] = new node();
      for(int i=0; i<nlines; i++) {
	calcMidPoints(lines[i]);
      }
      
      try {line = in.readLine();} catch (IOException e) {}
      StringTokenizer str = new StringTokenizer(line);
      tpoint.x = new Float(str.nextToken()).floatValue();
      tpoint.y = new Float(str.nextToken()).floatValue();
      graph[nNodes].p = tpoint;
      graph[nNodes].out = -1;
      graph[nNodes].visited = false;
      graph[nNodes].list = null;
      nNodes++;
      createGraph();
      //              printGraph();
      System.out.println("Number of doors = " + getDoors());
    }
}

class point {
  public float x, y;
};

class listnode {
  public int nodenum;
  public listnode next;
  public listnode(int n, listnode nxt) {nodenum=n; next = nxt;};
};

class node {
  public point p;
  public int out;
  public boolean visited;
  public listnode list;
  
  public node() {p = new point(); list = null;};
}; 

class line {
  public point p1,p2;
  public float a, b, c, d;
  public point [] isects;
  public int [] nodenum;
  public int nsects;
  
  public line() {
    p1 = new point();
    p2 = new point();
    isects = new point[D_j.MAXLINES];
    for(int i=0; i<D_j.MAXLINES; i++)
      isects[i] = new point();
    nodenum = new int[D_j.MAXLINES];
  };
}; 




  
  
