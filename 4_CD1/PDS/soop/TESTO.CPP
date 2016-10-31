#include<stdio.h>
#include<conio.h>

main()
{
	int i,j,k;
	int cnt;
	int buf[100][2];
	int gap;
	FILE *fp;
	fp = fopen("yo.txt","r");
		fscanf(fp,"%d",&cnt);
		for(i=0;i<cnt;i++){
			fscanf(fp,"%d %d",&buf[i][0],&buf[i][1]);
		}
	fclose(fp);

	gap = 0;
	for(i=0;i<cnt;i++){
		gap += buf[i][0] * buf[i + 1 % cnt][1];
		gap -= buf[i][0] * buf[(i + cnt - 1) % cnt][1];
	}
	printf("%d \n", gap/2);
}