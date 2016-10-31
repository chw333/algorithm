#include<ctype.h>
#include<stdio.h>
#include<conio.h>
main()
{
	static 	int buf[100],buf1[100];
	static  int wr[100][2];
	int i,j,cnt;
	FILE *fp;
	clrscr();
	fp = fopen("01101302.in","r");
		fscanf(fp,"%d\n",&cnt);
		for(i=0;i<cnt*cnt;i++){	char a;	fscanf(fp,"%c ",&a);a=toupper(a);buf[i] = a-'A';}
		fscanf(fp,"\n");
		for(i=0;i<cnt*cnt;i++){	char a;	fscanf(fp,"%c ",&a);a=toupper(a);buf1[i] = a-'A';}
		fclose(fp);

	int k = 0,ff = 0;
	i = 0;
	while(i<cnt*cnt && k<cnt*cnt){
		if ( buf1[i] == buf[k] ){i++;k++;}
		else{
			for(j=0;j<cnt*cnt;j++){
				if(buf1[j] == buf[i]){
					wr[ff][0] = buf[i];	wr[ff][1] = buf[j];	ff++;
					int imsi;
					imsi = buf[j];buf[j] = buf[i];buf[i] = imsi;
//graphic//////////////////////////////////////////////////////////
/*						clrscr();
							int j1,i1,t;
						t = 0;
								for(i1=0;i1<8;i1+=2){
									for(j1=5;j1>i1;j1--)printf(" ");
									for(j1=1;j1<i1;j1++){printf("%c ",buf[t]+'A');t++;}
									printf("\n");
								}
						t = 0;
								for(i1=0;i1<8;i1+=2){
									for(j1=5;j1>i1;j1--)printf(" ");
									for(j1=1;j1<i1;j1++){printf("%c ",buf1[t]+'A');t++;}
									printf("\n");
								}
					getch();
*/
					goto end;
				}
			}
			end:
			i++;k++;
		}
	}
	fp = fopen("01101302.out","w");
		fprintf(fp,"%d\n",ff);
		for(i=0;i<ff;i++)fprintf(fp,"%c %c\n",wr[i][0]+'A',wr[i][1]+'A');
	fclose(fp);
}