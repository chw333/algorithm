/*
ID: lge1435001
PROB: checker
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define MAXN 13
#define NPRINT 3

int n;
int nsol;
FILE *fout;

void
solution(int *a)
{
    int i;
	if(nsol == NPRINT)
		return;
		    nsol++;
			for(i=0; i<n; i++) {
				if(i != 0)
					    fprintf(fout, " ");
						fprintf(fout, "%d", a[i]+1);
						    }
							fprintf(fout, "\n");
							}

							/* Keep track of whether there is a checker on each column, and diagonal. */
							int col[MAXN];		/* (i, j) -> j */
							int updiag[2*MAXN];	/* (i, j) -> i+j */
							int downdiag[2*MAXN];	/* (i, j) -> i-j + N */

							/*
							 * Calculate number of ways to place checkers
							  * on each row of the board starting at row i and going to row n.
							   */
							   int
							   nway(int i, int *row)
							   {
							       int j, s;

								   if(i == n) {
									solution(row);
										return 1;
										    }

											s = 0;
											    for(j=0; j<n; j++){
												if(!col[j] && !updiag[i+j] && !downdiag[i-j+MAXN]){
													    row[i] = j;

														    col[j]++;
															    updiag[i+j]++;
																    downdiag[i-j+MAXN]++;

																	    s += nway(i+1, row);

																		    col[j]--;
																			    updiag[i+j]--;
																				    downdiag[i-j+MAXN]--;
																					}
																					    }
																						return s;
																						}

																						void
																						main(void)
																						{
																						    FILE *fin;
																							int i, s, row[MAXN];

																							    fin = fopen("checker.in", "r");
																								assert(fin != NULL);
																								    fout = fopen("checker.out", "w");
																									assert(fout != NULL);

																									    fscanf(fin, "%d", &n);
																										s = nway(0, row);
																										    fprintf(fout, "%d\n", s);
																										    }

