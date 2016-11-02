/* ACM International Collegiate Programming Contest
   Central European Regional Contest 2000
   
   Problem C - Complete the sequence!
   Jan Kybic
*/

#include <stdio.h>

#define MAXQ 100

static int d[MAXQ][MAXQ] ;

void solve_one()
{
  int m,o,i,j ; 
  
  scanf("%d %d",&m,&o) ;
  /* now there's m values to be read */
  /* skip m-MAXQ values if needed */
  if (m>MAXQ) { 
    for(i=0;i<m-MAXQ;i++) scanf("%d",&d[0][0]) ;
    m=MAXQ ; 
  }
  /* we read m values into d */
  for(i=0;i<m;i++) scanf("%d",&d[0][i]) ;

  /* calculate differences */
  for(i=0;i<m-1;i++) {
    for(j=1;j<m;j++) d[i+1][j]=d[i][j]-d[i][j-1] ;
  }

  #if 0
   printf("The last column: ") ;
   for (j=0;j<m;j++) printf("%d ",d[j][m-1]) ;
   putchar('\n') ;
  #endif

  for (j=0;j<o;j++) /* generate j numbers */
    { for (i=m-2;i>=0;i--) d[i][m-1]+=d[i+1][m-1] ;
      printf("%d%c",d[0][m-1], (j==o-1)?'\n':' ') ;
    }
}

int main()
{
  int N ;
  scanf("%d",&N) ;
  while(N--) solve_one() ;  

  return 0 ;
}

