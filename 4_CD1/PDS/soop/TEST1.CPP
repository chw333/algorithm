/*
ID: lge1435001
PROG: pprime
*/
#include<stdio.h>
main()
{
	long ipt1,ipt2,i,j,n;
	FILE *fp;
	fp = fopen("pprime.in","r");
		fscanf(fp,"%ld",&ipt1);
		fscanf(fp,"%ld",&ipt2);
	fclose(fp);

 fp = fopen("pprime.out","w");
	for(i=ipt1;i<=ipt2;i++){
		for(j=2;j<i;j++){
			if(i%j==0)
			{
				goto end;
			}
		}
		fprintf(fp,"%d\n", i);
	end:
	}
  fclose(fp);
}
