/* ACM International Collegiate Programming Contest
   Central European Regional Contest 2000
   
   Problem G - The Game of Master-Mind
   Pavel Kos
*/
         
#include <stdio.h>
#include <string.h>

#define MAX_PINS   11
#define MAX_COLORS 101
#define MAX_MOVES  101

int move_pos[MAX_MOVES][MAX_PINS];
int move_col[MAX_MOVES][MAX_COLORS];
int black[MAX_MOVES];
int white[MAX_MOVES];
int test[MAX_PINS];
int hlp_col[MAX_COLORS];

int p, c, m, perform;

int debug;

void Yes(void)
{
   int i;

/*
   printf("Possible combination:");
   for (i = 0; i < p; ++i)
      printf(" %d", test[i]);
*/
   printf("%d", test[0]);
   for (i = 1; i < p; ++i)
      printf(" %d", test[i]);
   printf("\n");
   perform = 0;
}

void No(void)
{
   printf("You are cheating!\n");
   perform = 0;
}

int Change(int chng)
{
   int i = chng + 1;

   while (i < p)
      test[i++] = 1;
   while (chng >= 0)
   {
      if (++test[chng] > c)
         test[chng--] = 1;
      else
         break;
   }
   if (chng < 0)
      No();
   return 0;
}

int Copy(int copy, int index)
{
   if (test[copy] > move_pos[index][copy]) /* daval bych tam kombinaci, ktera uz byla zamitnuta */
      if (copy > 0)
         return Change(copy - 1);
      else
      {
         No();
         return 0;
      }
   test[copy] = move_pos[index][copy];
   ++copy;
   while (copy < p)
      test[copy++] = 1;
   return 0;
}

int Try(int index)
{
   int i, b, nb, w, nw, chng, copy;

   /* Prvni faze: test na cerne koliky */
 /*++debug;
 printf("Testing:");
 for (i = 0; i < p; ++i)
    printf(" %d", test[i]);
 printf(" with:");
 for (i = 0; i < p; ++i)
    printf(" %d", move_pos[index][i]);
 printf(" (");
 for (i = 0; i < c; ++i)
    printf(" %d", move_col[index][i]);
 printf(") {%d %d} %d\n", black[index], white[index], index);*/
   chng = copy = p;
   b = black[index];
   nb = p - b;
   for (i = 0; i < p; ++i)
      if (move_pos[index][i] == test[i]) /* pozice odpovida */
      {
         if (--b < 0) /* uz jich je moc na spravnem miste */
         {
            chng = i;
 //printf("Too many on the right place (%d)\n", i);
            break;
         }
      }
      else /* pozice neodpovida */
         if (--nb < 0) /* uz jich je moc na spatnem miste */
         {
            copy = i;
 //printf("Too few on the right place (%d)\n", i);
            break;
         }
   /* Druha faze: test na bile koliky */
   memcpy(hlp_col, move_col[index], sizeof(hlp_col));
   w = white[index] + black[index];
   nw = p - w; /* pocet koliku, kde neodpovida ani barva */
   for (i = 0; i < p; ++i)
      if (hlp_col[test[i] - 1]-- > 0) /* barva odpovida */
      {
   //printf("Right color detected on pos. %d\n", i + 1);
         if (--w < 0) /* uz jich je moc stejne barvy */
         {
            if (chng > i)
               chng = i;
 //printf("Too many of the right color (%d)\n", i);
            break;
         }
      }
      else /* barva neodpovida */
         if (--nw < 0) /* uz jich je moc, kde neodpovida ani barva */
         {
            if (chng > i)
               chng = i;
 //printf("Too few of the right color (%d)\n", i);
            break;
         }
   /* vyhodnoceni */
   if (chng < copy)
      return Change(chng);
   else if (copy < p)
      return Copy(copy, index);
   else /* kombinace je v poradku */
      return 1;
}

int main(void)
{
   int n, i, j, k;

   scanf("%d", &n);
   while (n--)
   {
      debug = 0;
      memset (move_col, 0, sizeof(move_col));
      scanf("%d%d%d", &p, &c, &m);
      for (i = 0; i < m; ++i)
      {
         for (j = 0; j < p; ++j)
         {
            scanf("%d ", &k);
            move_pos[i][j] = k;
            ++move_col[i][k - 1];
         }
         scanf("%d%d", black + i, white + i);
      }
      for (i = 0; i < p; ++i)
         test[i] = 1;
      perform = 1;
      while (perform)
      {
         i = 0;
         while ((i < m) && (Try(i)))
            ++i;
         if (i == m) /* vyzkousel jsem vsechny tahy a vyhovuje to */
            Yes();
      }
      /* printf("Debug: %d\n", debug); */
   }
   return 0;
}
