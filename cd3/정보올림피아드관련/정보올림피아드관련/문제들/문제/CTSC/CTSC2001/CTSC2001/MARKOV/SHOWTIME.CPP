#include <dos.h>
#include <stdio.h>
void main()
{
struct  time t;

gettime(&t);
printf("The current time is: %2d:%02d:%02d.%02d\n",
       t.ti_hour, t.ti_min, t.ti_sec, t.ti_hund);
}