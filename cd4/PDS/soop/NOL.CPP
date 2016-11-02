#include<stdio.h>
#include<conio.h>
main()
{
	static int i[4],l1,l2;
	static int ipt1,ipt2;
	static int buf[100][100];
	static int rey,rex,rsx,rsy,hap,hap1,x[2][2];
	FILE *fp;
		clrscr();
		fp = fopen("ipt.in","r");
			fscanf(fp,"%d %d",&ipt1,&ipt2);
			for(i[0]=0;i[0]<ipt1;i[0]++){
				for(i[1]=0;i[1]<ipt2;i[1]++){
					fscanf(fp,"%d ",&buf[i[0]][i[1]]);
				}
			}
		fclose(fp);
		for(i[0]=0;i[0]<ipt1;i[0]++){
			for(i[1]=0;i[1]<ipt2;i[1]++){
				rsx = i[0];
				rsy = i[1];
			for(i[2]=0;i[2]<ipt1;i[2]++){
				for(i[3]=0;i[3]<ipt2;i[3]++){
					rex = i[2];
					rey = i[3];


			for(l1= i[0];l1<=i[2];l1++){
				for(l2 = i[1];l2<=i[3];l2++){
				hap += buf[l1][l2];
				}
			}
				if(hap>hap1){
				hap1 = hap;
				x[0][0] = i[0];
				x[0][1] = i[1];
				x[1][0] = i[2];
				x[1][1] = i[3];
				}
				hap = 0;
				}
			}
			}
		}
	printf("%d ++++++ %d - %d  /////// %d - %d",hap1,x[0][0]+1,x[0][1]+1,x[1][0]+1,x[1][1]+1);


}