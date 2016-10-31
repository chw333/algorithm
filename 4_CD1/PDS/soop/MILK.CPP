/*
ID : lge1435001
PROB : milk
*/

#include<stdio.h>
//#include<stdlib.h>
main()
{
	static int mk[2][10000];
	static int i,j,mon,cnt,it1,it2,imsi;

	FILE *fp;
	fp = fopen("milk.in","r");
		fscanf(fp,"%d %d",&it1,&it2);

		for(i=0;i<it2;i++){
			fscanf(fp,"%d %d",&mk[0][i],&mk[1][i]);
		}
	fclose(fp);
	for(i = 0 ; i < it2-1; i++){
		for(j=i+1;j<it2;j++){
			if( mk[0][i] > mk[0][j] ){
				imsi = mk[0][i]; mk[0][i] = mk[0][j]; mk[0][j] = imsi;
				imsi = mk[1][i]; mk[1][i] = mk[1][j]; mk[1][j] = imsi;
			 }
		}
	}
	i=0;
	cnt = it1;
	while(cnt != 0)
	{
		if ( mk[1][i] !=0 ){
			mk[1][i]--;
			cnt--;
			mon = mon + mk[0][i];
		}
		else
		i++;
	}

	fp = fopen("milk.out","w");
		fprintf(fp,"%d\n",mon);
	fclose(fp);

}
