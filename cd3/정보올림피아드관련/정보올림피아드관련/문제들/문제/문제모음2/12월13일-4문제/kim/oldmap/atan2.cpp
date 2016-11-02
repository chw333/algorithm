#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

double v[10];

int main(void)
{
	//            0
	//  -pi*1/4   |    pi*1/4
	//      o     |     o
	//            |
	//-pi*2/4     |        pi*2/4
	//  -o--------+---------o-
	//            |
	//            |
	//      o     |     o pi*3/4
	//  -pi*3/4   o
	//            pi*4/4

	v[0]=atan2( 2, 0);
	v[1]=atan2( 2, 1);
	v[2]=atan2( 2, 2);
	v[3]=atan2( 0, 2);
	v[4]=atan2( -2, 2);
	v[5]=atan2( -2, 0);
	v[6]=atan2( -2, -2);
	v[7]=atan2( 0, -2);
	v[8]=atan2( 2, -2);

	int i;
	for(i=0; i<9; i++) {
		printf("%d, %lf\n", i, v[i]);
	}

	return 0;
}
