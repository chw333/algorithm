/* Copyright Howard Cheng (ACM ICPC ECNA 1999) */

import java.io.*;
import java.util.*;

public class G_h {
  static final int MAX_LAKE = 25;
  static final int MAX_HOUR = 16;
  static final int MAX_MIN5 = MAX_HOUR * 12;
  static int n, min5;
  static int F[] = new int[MAX_LAKE];
  static int d[] = new int[MAX_LAKE];
  static int t[] = new int[MAX_LAKE];
  static DataInputStream in = new DataInputStream(System.in);

  static void read_int(int n, int out[]) {
    String inputline = "";
    try {
      inputline = in.readLine();
    } catch (IOException e) {
    }
    StringTokenizer str = new StringTokenizer(inputline);
    for (int i = 0; i < n; i++) {
      out[i] = Integer.parseInt(str.nextToken());
    }
  }

  static boolean read_case() {
    int i;
    int out[] = new int[1];

    read_int(1, out);
    n = out[0];
    if (n == 0) {
      return false;
    }
    
    read_int(1, out);
    min5 = out[0] * 12;

    read_int(n, F);
    read_int(n, d);
    read_int(n-1, t);
    return true;
  }

  static void solve_case() {
    int fishes[][] = new int[MAX_LAKE][MAX_MIN5];
    int len[][] = new int[MAX_LAKE][MAX_MIN5];
    int i, j, k, sum, dec, f, temp;

    sum = dec = 0;
    for (j = min5-1; j >= 0; j--) {
      if ((f = F[n-1] - dec) < 0) {
	f = 0;
      }
      sum += f;
      fishes[n-1][j] = sum;
      len[n-1][j] = min5-j;
      dec += d[n-1];
    }

    for (i = n-2; i >= 0; i--) {
      for (j = min5-1; j >= 0; j--) {
	sum = dec = 0;
	fishes[i][j] = -1;
	for (k = 0; k <= min5-j; k++) {
	  if (j+k+t[i] < min5) {
	    /* fish 5*k minutes, then move on */
	    temp = fishes[i+1][j+k+t[i]] + sum; 
	  } else {
	    /* just stay here for the rest of time */
	    temp = sum;
	  }
	  
	  if (temp >= fishes[i][j]) {
	    fishes[i][j] = temp;
	    len[i][j] = k;
	  }
	  if ((f = F[i] - dec) < 0) {
	    f = 0;
	  }
	  sum += f;
	  dec += d[i];
	}
      }
    }

    /* now print the solution */
    for (i = j = 0; i < n; i++) {
      if (i > 0) {
	System.out.print(", ");
      }
      if (j < min5) {
	System.out.print(len[i][j]*5);
	if (i < n) {
	  j += len[i][j] + t[i];
	}
      } else {
	System.out.print("0");
      }
    }
    System.out.println("");
    System.out.println("Number of fish expected: " + fishes[0][0]);
  }

  public static void main(String[] args) {
    boolean first = true;
    
    while (read_case()) {
      if (!first) {
	System.out.println("");
      }
      solve_case();
      first = false;
    }
  }
}
