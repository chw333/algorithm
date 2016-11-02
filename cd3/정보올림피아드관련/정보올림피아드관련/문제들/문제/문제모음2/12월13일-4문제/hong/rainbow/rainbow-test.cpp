#include<assert.h>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define OUTPUT    "test05.in"

/* Because player locations are aligned to 100 units, sizes < 84
   and angles are constraints to 45 degrees, there should be no
   such thing as "grazed by the corner" (i.e. roundoff issues)   */
int main(void)
{
   FILE *outfile;
   int c, i;

   outfile = fopen(OUTPUT, "wt+");
   assert(outfile != NULL);

   srand((unsigned)time(NULL));

   fprintf(outfile, "%d\n", 20 + (rand() % 64));
   fprintf(outfile, "%d\n", c = ((rand() % 2000) + 1));
   for(i = 0; i < c; i++)
   {
      fprintf(outfile, "%d %d\n",
         100 * (rand() % 40000) - 2000000,
         100 * (rand() % 40000) - 2000000);
   }
   fprintf(outfile, "%d\n", c = ((rand() % 2000) + 1));
   for(i = 0; i < c; i++)
   {
      fprintf(outfile, "%d %d %d\n",
         100 * (rand() % 40000) - 2000000,
         100 * (rand() % 40000) - 2000000,
         (rand() % 8) * 45);
   }

   fclose(outfile);
   return 0;
}
