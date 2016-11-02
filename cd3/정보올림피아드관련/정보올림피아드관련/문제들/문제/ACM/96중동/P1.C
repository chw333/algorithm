/*-----------------------------------------------------------------------
 * 
 * File Name:   p1.c
 * 
 * Author:      A. Lumsdaine
 * 
 *-----------------------------------------------------------------------
 * 
 * DESCRIPTION
 *     Source code file for problem #1 of 1996 ACM
 *     East-Central Regional Programming contest.
 * 
 * DIAGNOSTICS
 *     The main concern here is keeping all of the days of the week 
 *     straight across the various months of the year.  Also,
 *     transitions across months and years need to be taken into
 *     account.
 *
 *-----------------------------------------------------------------------

#include <stdio.h>
#include <strings.h>


typedef char time_block[32];

typedef struct {
  char day_name;
  int day_date;
  time_block times;
} day_block;

typedef day_block month_block[31];
typedef month_block year_block[12];
typedef struct {
  char day_name; 
  int month, day;
} date;

typedef struct {
  int start, stop;
} time;


#define INDEX(t) (((t-900)/100)*4+(t-100*(t/100))/15)

static int days_per_month[12] = {
/*Ja  Fe  Ma  Ap  My  Jn  Jl  Au  Se  Oc  No  De*/
  31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31
};

static char weekdays[7] = {
  'M', 'T', 'W', 'R', 'F', 'S', 'S'
};

int
main()
{
  int mo, dy, start, xmo;
  int i, j, k, len;
  char buffer[BUFSIZ];
  int num_to_schedule, length_to_schedule;
  date current_date;
  year_block year;

  bzero(&year, sizeof(year));

  /* get current date */
  (void) scanf("%c %d %d\n", &current_date.day_name,  
	       &current_date.month, &current_date.day);
  current_date.month--, current_date.day--;

  /* get desired meetings */
  (void) scanf("%d %d\n", &num_to_schedule, &length_to_schedule);
  
  while (1) {
    date appt_date;
    time appt_time;

    /* read line */
    (void) gets(buffer);

    /* break if done */
    if (strcmp(buffer, "done") == 0)
      break;

    /* else must be name -- read appointments and store */
    else while (1) {
      (void) gets(buffer);
      if (strcmp(buffer, "done") == 0)
	break;
      (void) sscanf(buffer, "%c %d %d %d %d", 
		    &appt_date.day_name, &appt_date.month, &appt_date.day,
		    &appt_time.start, &appt_time.stop);

      for (i = appt_time.start; i != appt_time.stop; i += 15) {
	year[appt_date.month-1][appt_date.day-1].times[INDEX(i)] = 'x';
	if ((i - 100*(i/100)) % 60 == 45)
	  i += 40;
      }
    }
  }

  /* Initialize day names for year */
  for (start = 0; start < 7; start++)
    if (weekdays[start] == current_date.day_name)
      break;
  for (i = 0; i < 12; i++) {
    mo = (i + current_date.month) % 12;
    for (j = 0; j < 31; j++) {
      dy = (j + current_date.day) % 31;
      xmo = (dy < current_date.day ? mo+1 : mo) % 12;
      if (dy >= days_per_month[mo])
	continue;
      year[xmo][dy].day_name = weekdays[(start++)%7];
    }
  }
  

  /* Find appointments by brute force */
  len = 0;
  while (num_to_schedule > 0) {

    for (i = 0; i < 12; i++) {
      mo = (i + current_date.month)  % 12;

      for (j = 0; j < 31; j++) {
	dy = (j + current_date.day) % 31;
	xmo = (dy < current_date.day ? mo+1 : mo) % 12;
	
	if (year[xmo][dy].day_name == 'S' || dy >= days_per_month[mo])
	  continue;
	
	len = start = 0;
	for (k = 900; k < 1700; k += 15) {

	  if (year[xmo][dy].times[INDEX(k)] != 'x') {
	    if (start == 0) 
	      start = k;
	    len++;
	  } else
	    len = start = 0;

	  if (len == length_to_schedule/15) {
	    (void) printf("%c %d %d %d\n", 
			  year[xmo][dy].day_name, xmo+1, dy+1, start);
	    len = start = 0;
	    num_to_schedule--;
	    if (num_to_schedule == 0)
	      goto done;	/* AAAAAHHHH!!! */
	  }
	  if ((k - 100*(k/100)) % 60 == 45)
	    k += 40;
	}
      }
    }
  }
  while (num_to_schedule-- > 0)
    (void) printf("No more times available\n");

done:

  return 0;
}
