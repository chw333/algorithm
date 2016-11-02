/*-----------------------------------------------------------------------
 * 
 * File Name:   p6.c
 * 
 * Author:      A. Lumsdaine
 * 
 *-----------------------------------------------------------------------
 * 
 * DESCRIPTION
 *     Source code file for problem #6 of 1996 ACM
 *     East-Central Regional Programming contest.
 * 
 * DIAGNOSTICS
 *     Perform elementary-school addition on array of digits.
 *
 *-----------------------------------------------------------------------

#include <stdio.h>
#include <strings.h>

int
main()
{
  char buffer[BUFSIZ];
  int array[200][200], answer[200];
  int i, j, num_integers, len, digit, carry, sum;

  bzero(array, sizeof(array));
  bzero(answer, sizeof(answer));

  /* Read in all the numbers - LSDigit goes in 0 */
  for (num_integers = 0; num_integers < 100; num_integers++) {
    (void) gets(buffer);
    if (strcmp(buffer, "0") == 0)
      break;

    /* Reverse the digits */
    len = strlen(buffer);
    for (i = 0; i < len; i++)
      array[num_integers][i] = buffer[len - 1 - i] - '0';
  }

  /* for each digit location */
  carry = 0;
  for (i = 0; i < 198; i++) {

    /* sum all digits */
    sum = carry;
    for (j = 0; j < num_integers; j++)
      sum += array[j][i];

    /* store digit and carry */
    digit = sum % 10;
    carry = sum / 10;
    answer[i] = digit;
  }

  /* print answer */
  for (i = 199; i >= 0; i--)
    if (answer[i] != 0)
      break;
  while (i >= 0)
    (void) printf("%d", answer[i--]);
  (void) printf("\n");

  return 0;
}
