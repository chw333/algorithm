/* Copyright Howard Cheng (ACM ICPC ECNA 1999) */

import java.io.*;
import java.util.*;

public class A_h {
  static int filled[] = new int[9];
  static Triangle triangle[] = new Triangle[10];
  static boolean line[][] = new boolean[11][11];
  static int edge[][] = new int[18][2];
  static DataInputStream in = new DataInputStream(System.in);

  static void fill_triangle() {
    int i, j, k;
    for (i = 0; i < 10; i++) {
      triangle[i] = new Triangle();
      for (j = 0; j < 3; j++) {
	triangle[i].to[j] = -1;
	for (k = 0; k < 2; k++) {
	  triangle[i].triangle[j][k] = -1;
	}
      }
    }

    triangle[1].to[0] = 2;
    triangle[1].to[1] = 3;
    triangle[2].to[0] = 3;
    triangle[2].to[1] = 4;
    triangle[2].to[2] = 5;
    triangle[3].to[0] = 5;
    triangle[3].to[1] = 6;
    triangle[4].to[0] = 5;
    triangle[4].to[1] = 7;
    triangle[4].to[2] = 8;
    triangle[5].to[0] = 6;
    triangle[5].to[1] = 8;
    triangle[5].to[2] = 9;
    triangle[6].to[0] = 9;
    triangle[6].to[1] = 10;
    triangle[7].to[0] = 8;
    triangle[8].to[0] = 9;
    triangle[9].to[0] = 10;

    triangle[1].triangle[0][0] = 0;
    triangle[1].triangle[1][0] = 0;
    triangle[2].triangle[0][0] = 0;
    triangle[2].triangle[0][1] = 2;
    triangle[2].triangle[1][0] = 1;
    triangle[2].triangle[2][0] = 1;
    triangle[2].triangle[2][1] = 2;
    triangle[3].triangle[0][0] = 2;
    triangle[3].triangle[0][1] = 3;
    triangle[3].triangle[1][0] = 3;
    triangle[4].triangle[0][0] = 1;
    triangle[4].triangle[0][1] = 5;
    triangle[4].triangle[1][0] = 4;
    triangle[4].triangle[2][0] = 4;
    triangle[4].triangle[2][1] = 5;
    triangle[5].triangle[0][0] = 3;
    triangle[5].triangle[0][1] = 7;
    triangle[5].triangle[1][0] = 5;
    triangle[5].triangle[1][1] = 6;
    triangle[5].triangle[2][0] = 6;
    triangle[5].triangle[2][1] = 7;
    triangle[6].triangle[0][0] = 7;
    triangle[6].triangle[0][1] = 8;
    triangle[6].triangle[1][0] = 8;
    triangle[7].triangle[0][0] = 4;
    triangle[8].triangle[0][0] = 6;
    triangle[9].triangle[0][0] = 8;
  }

  static void init_edge() {
    int i, j, k, t;
    
    k = 0;
    for (i = 1; i < 10; i++) {
      for (j = 0; j < 3; j++) {
	t = triangle[i].to[j];
	if (t != -1) {
	  edge[k][0] = i;
	  edge[k][1] = t;
	  k++;
	}
      }
    }
  }

  static int fill_line(int n1, int n2, boolean fill) {
    int d, i, t, r;

    r = 0;
    if (n1 > n2) {
      return fill_line(n2, n1, fill);
    }
    
    d = (fill) ? 1 : -1;
    
    if (fill) {
      line[n1][n2] = true;
    } else {
      line[n1][n2] = false;
    }

    for (i = 0; i < 3 && triangle[n1].to[i] != n2; i++)
      ;

    t = triangle[n1].triangle[i][0];
    if (t != -1) {
      filled[t] += d;
      if ((filled[t] == 3 && fill) || (filled[t] == 2 && !fill)) {
	r++;
      }
    }
    
    t = triangle[n1].triangle[i][1];
    if (t != -1) {
      filled[t] += d;
      if ((filled[t] == 3 && fill) || (filled[t] == 2 && !fill)) {
	r++;
      }
    }

    return r;
  }

  static int result(int turn, int move, int input_left, int Ascore, 
			int Bscore) {
    int res;
    int r, n1, n2, i, next;

    if (Ascore >= 5 && input_left <= 0) {
      return 1;
    } else if (Bscore >= 5 && input_left <= 0) {
      return 2;
    } else if (move == 18) {
      return (Ascore >= 5) ? 1 : 2;
    }
    
    if (input_left > 0) {
      String inputline = "";
      try {
	inputline = in.readLine();
      } catch (IOException e) {
      }
      StringTokenizer str = new StringTokenizer(inputline);
      n1 = Integer.parseInt(str.nextToken());
      n2 = Integer.parseInt(str.nextToken());

      r = fill_line(n1, n2, true);
      next = (r != 0) ? turn : 3 - turn;
      return result(next, move+1, input_left-1, 
		    (turn == 1) ? Ascore + r : Ascore,
		    (turn == 2) ? Bscore + r : Bscore);
    }
    for (i = 0; i < 18; i++) {
      n1 = edge[i][0];
      n2 = edge[i][1];
      if (!line[n1][n2]) {
	r = fill_line(n1, n2, true);
	next = (r != 0) ? turn : 3 - turn;
	res = result(next, move+1, input_left, 
		     (turn == 1) ? Ascore + r : Ascore,
		     (turn == 2) ? Bscore + r : Bscore);
	fill_line(n1, n2, false);
	
	if (res == turn) {
	  /* current player wins by playing here, so just prune */
	  return turn;
	}
      }
    }
    return 3 - turn;
  }

  public static void main(String[] args) {
    int games, m, i, j, k;

    fill_triangle();
    init_edge();

    String inputline = "";
    try {
      inputline = in.readLine();
    } catch (IOException e) {
    }
    StringTokenizer str = new StringTokenizer(inputline);
    games = Integer.parseInt(str.nextToken());

    for (i = 1; i <= games; i++) {
      for (k = 0; k < 9; k++) {
	filled[k] = 0;
      }
      
      for (j = 0; j < 11; j++) {
	for (k = 0; k < 11; k++) {
	  line[j][k] = false;
	}
      }

      try {
	inputline = in.readLine();
      } catch (IOException e) {
      }
      str = new StringTokenizer(inputline);
      m = Integer.parseInt(str.nextToken());
      
      if (result(1, 0, m, 0, 0) == 1) {
	System.out.println("Game " + i + ": A wins.");
      } else {
	System.out.println("Game " + i + ": B wins.");
      }
    }
  }
}

class Triangle {
  public int to[];
  public int triangle[][];

  Triangle() {
    to = new int[3];
    triangle = new int[3][2];
  }
}
