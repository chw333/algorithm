/* Program solving the Candy problem, IPSC 99 */
/* reads input from file b.txt */

#include <stdio.h>
#include <fstream.h>

int a[10000];  //sizes of packets
int n;
FILE *f;

ofstream out ("dama.out");
void main (void)
{
  long int sum, onePacket, result;
  int i;

  f = fopen ("dama02.in", "r");

  for (;;) {
    fscanf (f, "%d", &n);    //read number of packets
    if (n < 0) break;        //end of file

    sum = 0;                   //read sizes of packets and compute the sum
    for (i = 0; i < n; i++) {
      fscanf (f, "%d", a+i);
      sum += a[i];
    }

    if (sum % n != 0)  out << "-1\n"; // printf ("-1\n");  //it is not possible to distribute
                                        //candies evenly
    else {
      onePacket = sum / n;     //number of candies in one packet
      result = 0;              //number of moves

      for (i = 0; i < n; i++) {
        if (a[i] > onePacket)           //there are more candies than needed
          result += (a[i] - onePacket); //we add moves
      }
	  out << result << endl;
//      printf ("%ld\n", result);

    } //else
  } //for (;;)

  fclose (f);
}
