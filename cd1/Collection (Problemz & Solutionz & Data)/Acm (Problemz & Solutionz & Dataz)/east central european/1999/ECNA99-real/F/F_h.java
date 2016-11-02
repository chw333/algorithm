/* Copyright Howard Cheng (ACM ICPC ECNA 1999) */

import java.io.*;
import java.util.*;

public class F_h {

  public static void main(String [] args) {
    DataInputStream in = new DataInputStream(System.in);
    String line = "";
    int case_num = 1, k;

    try {
      line = in.readLine();
    } catch (IOException ioe) {}
    StringTokenizer str = new StringTokenizer(line);
    int p = Integer.parseInt(str.nextToken());
    int e = Integer.parseInt(str.nextToken());
    int i = Integer.parseInt(str.nextToken());
    int d = Integer.parseInt(str.nextToken());
      
    while (p != -1 && e != -1 && i != -1 && d != -1) {
      for (k = d+1; (k - p) % 23 != 0 ||
	            (k - e) % 28 != 0 ||
                    (k - i) % 33 != 0; k++)
	;
      System.out.println("Case " + (case_num++) + 
			 ": the next triple peak occurs in " +
			 (k - d) + " days.");
      try {
	line = in.readLine();
      } catch (IOException ioe) {}
      str = new StringTokenizer(line);
      p = Integer.parseInt(str.nextToken());
      e = Integer.parseInt(str.nextToken());
      i = Integer.parseInt(str.nextToken());
      d = Integer.parseInt(str.nextToken());
    }
  }
}

