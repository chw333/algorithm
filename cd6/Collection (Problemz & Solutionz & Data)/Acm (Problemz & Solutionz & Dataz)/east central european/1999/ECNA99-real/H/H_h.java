/* Copyright Howard Cheng (ACM ICPC ECNA 1999) */

import java.io.*;
import java.util.*;

public class H_h {
  static DataInputStream in = new DataInputStream(System.in);
  static final int ROWS = 10;
  static final int COLS = 15;
  static final int BONUS = 1000;
  static final char BLANK = '.';

  static int r, c;

  static char board[][] = new char[ROWS][COLS];
  static String colors = new String("RGB");

  static int read_int() throws IOException {
    String inputline = "";
    inputline = in.readLine();
    StringTokenizer str = new StringTokenizer(inputline);
    return Integer.parseInt(str.nextToken());
  }

  static void read_board() throws IOException {
    String inputline = "";
    int i, j;

    inputline = in.readLine();     // eat blank line
    for (i = ROWS-1; i >= 0; i--) {
      inputline = in.readLine();
      for (j = 0; j < COLS; j++) {
	board[i][j] = inputline.charAt(j);
      }
    }
  }

  static int region(boolean mark[][], int r, int c) {
    int sum;

    if (board[r][c] == BLANK || mark[r][c]) {
      return 0;
    }
  
    mark[r][c] = true;
    sum = 1;
    
    if (r > 0 && board[r-1][c] == board[r][c]) {
      sum += region(mark, r-1, c);
    }
    if (r < ROWS-1 && board[r+1][c] == board[r][c]) {
      sum += region(mark, r+1, c);
    }
    if (c > 0 && board[r][c-1] == board[r][c]) {
      sum += region(mark, r, c-1);
    }
    if (c < COLS-1 && board[r][c+1] == board[r][c]) {
      sum += region(mark, r, c+1);
    }
    
    return sum;
  }

  static int next_move() {
    boolean mark[][] = new boolean[ROWS][COLS];
    int i, j, t, best_val = 0;

    /* clear marks */
    for (i = 0; i < ROWS; i++) {
      for (j = 0; j < COLS; j++) {
	mark[i][j] = false;
      }
    }

    /* find the best spot */
    for (j = 0; j < COLS; j++) {
      for (i = 0; i < ROWS; i++) {
	if ((t = region(mark, i, j)) > best_val) {
	  best_val = t;
	  r = i;
	  c = j;
	}
      }
    }
    
    return best_val;
  }

  static void remove_ball(int r, int c) {
      char t = board[r][c];

      board[r][c] = BLANK;
      if (r > 0 && board[r-1][c] == t) {
	remove_ball(r-1, c);
      }
      if (r < ROWS-1 && board[r+1][c] == t) {
	remove_ball(r+1, c);
      }
      if (c > 0 && board[r][c-1] == t) {
	remove_ball(r, c-1);
      }
      if (c < COLS-1 && board[r][c+1] == t) {
	remove_ball(r, c+1);
      }
  }

  static void compress_board() {
    int i, j, k1, k2;
    
    /* compress each column first */
    for (j = 0; j < COLS; j++) {
      k1 = k2 = 0;
      while (k2 < ROWS) {
	if (board[k2][j] != BLANK) {
	  board[k1++][j] = board[k2][j];
	}
	k2++;
      }
      while (k1 < ROWS) {
	board[k1++][j] = BLANK;
      }
    }
    
    /* shift the columns to the left */
    k1 = k2 = 0;
    while (k2 < COLS) {
      if (board[0][k2] != BLANK) {
	/* copy columns */
	if (k1 != k2) {
	  for (i = 0; i < ROWS; i++) {
	    board[i][k1] = board[i][k2];
	  }
	}
	k1++;
      }
      k2++;
    }
    while (k1 < COLS) {
      for (i = 0; i < ROWS; i++) {
	board[i][k1] = BLANK;
      }
      k1++;
    }
  }

  static void solve_game() {
    int score = 0, remain = ROWS*COLS, t, m, moves = 0;
    
    while (remain > 1 && (m = next_move()) > 1) {
      t = (m-2) * (m-2);
      score += t;
      remain -= m;
      System.out.print("Move " + (++moves));
      System.out.print(" at (" + (r+1) + "," + (c+1) + "): ");
      System.out.print("removed " + m + " balls of color " + board[r][c]);
      System.out.println(", got " + t + " points.");
      remove_ball(r,c);
      compress_board();
    }

    if (remain == 0) {
      score += BONUS;
    }
    System.out.println("Final score: " + score +
		       ", with " + remain + " balls remaining.");
  }

  public static void main(String[] args) {
    int n, i;
    try {
      n = read_int();
      for (i = 0; i < n; i++) {
	if (i > 0) {
	  System.out.println("");
	}
	System.out.println("Game " + (i+1) + ":");
	System.out.println("");
	read_board();
	solve_game();
      }
    } catch (IOException e) {
    }
  }
}
