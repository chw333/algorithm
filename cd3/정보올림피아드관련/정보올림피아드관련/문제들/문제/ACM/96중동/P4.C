/*-----------------------------------------------------------------------
 * 
 * File Name:   p4.c
 * 
 * Author:      A. Lumsdaine
 * 
 *-----------------------------------------------------------------------
 * 
 * DESCRIPTION
 *     Source code file for problem #4 of 1996 ACM
 *     East-Central Regional Programming contest.
 * 
 * DIAGNOSTICS
 *     Look for matches in each row, column, and diagonal, using
 *     north, south, east, west, northeast, northwest, southeast, and
 *     southwest directions.  The matches are made by copying 
 *     stripes out of the puzzle and checking for matches of the
 *     words within the copied stripe.
 *
 *----------------------------------------------------------------------*/

#include <stdio.h>
#include <strings.h>


typedef struct {
  char *word;
  int xb, yb, xe, ye;
} Word;


static void
match(const char *string, Word word_array[], int x[], int y[])
{
  int i, j, n = strlen(string);

  /* for each letter */
  for (i = 0; i < n; i++)
    for (j = 0; word_array[j].word != NULL; j++)
      if (strncmp(string+i, word_array[j].word, strlen(word_array[j].word)) == 0) {
	word_array[j].xb = x[i] + 1;
	word_array[j].xe = x[i+strlen(word_array[j].word)-1] + 1;
	word_array[j].yb = y[i] + 1;
	word_array[j].ye = y[i+strlen(word_array[j].word)-1] + 1;
      }
}


int
main()
{
  int i, j, k, size, num_words = 0;
  Word word_array[101];
  char puzzle[101][101], buffer[BUFSIZ];
  int row, col, x[101], y[101];
  
  bzero((void *) puzzle, sizeof(puzzle));
  bzero((void *) word_array, sizeof(word_array));

  for (k = 0; k < 100; k++)
    word_array[k].xb = word_array[k].yb = 
      word_array[k].xe = word_array[k].ye = -1;
  
  (void) scanf("%d\n", &size);

  for (k = 0; k < size; k++)
    (void) gets(puzzle[k]);

  do {
    (void) gets(buffer);
    if (buffer[0] == '0')
      break;
    word_array[num_words++].word = strdup(buffer);
  } while (1);


  /* Get stripes: n, s, e, w, ne, nw, se, sw */
  /* look for substrings */
  
  /* n */
  for (i = 0; i < size; i++) {
    for (j = 0; j < size; j++) {
      row = size - 1 - j;
      col = i;
      if (row < 0 || row >= size || col < 0 || col >= size)
	break;
      buffer[j] = puzzle[row][col];
      x[j] = row;
      y[j] = col;
    }
    buffer[size] = 0;
    match(buffer, word_array, x, y);
  }

  /* e */
  for (i = 0; i < size; i++) {
    for (j = 0; j < size; j++) {
      buffer[j] = puzzle[i][j];
      x[j] = i;
      y[j] = j;
    }
    buffer[size] = 0;
    match(buffer, word_array, x, y);
  }

  /* w */
  for (i = 0; i < size; i++) {
    for (j = 0; j < size; j++) {
      row = i;
      col = size - 1 - j;
      if (row < 0 || row >= size || col < 0 || col >= size)
	break;
      buffer[j] = puzzle[row][col];
      x[j] = row;
      y[j] = col;
    }
    buffer[size] = 0;
    match(buffer, word_array, x, y);
  }

  /* s */
  for (i = 0; i < size; i++) {
    for (j = 0; j < size; j++) {
      buffer[j] = puzzle[j][i];
      x[j] = j;
      y[j] = i;
    }
    buffer[size] = 0;
    match(buffer, word_array, x, y);
  }

  /* ne */
  for (i = 0; i < size; i++) {
    for (j = 0; j < size; j++) {
      row = i - j;
      col = j;
      if (row < 0 || row >= size || col < 0 || col >= size)
	break;
      buffer[j] = puzzle[row][col];
      x[j] = row;
      y[j] = col;
    }
    buffer[j] = 0;
    match(buffer, word_array, x, y);
  }
  for (i = 0; i < size; i++) {
    for (j = 0; j < size; j++) {
      row = size - 1 - j;
      col = i + j;
      if (row < 0 || row >= size || col < 0 || col >= size)
	break;
      buffer[j] = puzzle[row][col];
      x[j] = row;
      y[j] = col;
    }
    buffer[j] = 0;
    match(buffer, word_array, x, y);
  }

  /* se */
  for (i = 0; i < size; i++) {
    for (j = 0; j < size; j++) {
      row = i + j;
      col = j;
      if (row < 0 || row >= size || col < 0 || col >= size)
	break;
      buffer[j] = puzzle[row][col];
      x[j] = row;
      y[j] = col;
    }
    buffer[j] = 0;
    match(buffer, word_array, x, y);
  }
  for (i = 0; i < size; i++) {
    for (j = 0; j < size; j++) {
      row = j;
      col = i + j;
      if (row < 0 || row >= size || col < 0 || col >= size)
	break;
      buffer[j] = puzzle[row][col];
      x[j] = row;
      y[j] = col;
    }
    buffer[j] = 0;
    match(buffer, word_array, x, y);
  }

  /* nw */
  for (i = 0; i < size; i++) {
    for (j = 0; j < size; j++) {
      row = i - j;
      col = size - 1 - j;
      if (row < 0 || row >= size || col < 0 || col >= size)
	break;
      buffer[j] = puzzle[row][col];
      x[j] = row;
      y[j] = col;
    }
    buffer[j] = 0;
    match(buffer, word_array, x, y);
  }
  for (i = 0; i < size; i++) {
    for (j = 0; j < size; j++) {
      row = size - 1 - j;
      col = i - j;
      if (row < 0 || row >= size || col < 0 || col >= size)
	break;
      buffer[j] = puzzle[row][col];
      x[j] = row;
      y[j] = col;
    }
    buffer[j] = 0;
    match(buffer, word_array, x, y);
  }

  /* sw */
  for (i = 0; i < size; i++) {
    for (j = 0; j < size; j++) {
      row = j;
      col = i - j;
      if (row < 0 || row >= size || col < 0 || col >= size)
	break;
      buffer[j] = puzzle[row][col];
      x[j] = row;
      y[j] = col;
    }
    buffer[j] = 0;
    match(buffer, word_array, x, y);
  }
  for (i = 0; i < size; i++) {
    for (j = 0; j < size; j++) {
      row = i + j;
      col = size - 1 - j;
      if (row < 0 || row >= size || col < 0 || col >= size)
	break;
      buffer[j] = puzzle[row][col];
      x[j] = row;
      y[j] = col;
    }
    buffer[j] = 0;
    match(buffer, word_array, x, y);
  }

  for (k = 0; k < num_words; k++) {
    if (word_array[k].xe != -1) {
      (void) printf("%d,%d %d,%d\n", word_array[k].xb, word_array[k].yb, 
	word_array[k].xe, word_array[k].ye);
    } else
      (void) printf("Not found\n");
  }

  return 0;
}
