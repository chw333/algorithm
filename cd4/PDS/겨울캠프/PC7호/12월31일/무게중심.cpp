#include<Stdio.h>
#include<conio.h>

int buf[100][2];
void input()
{
	FILE *fp;
	int cnt1,cnt2,cur;
	fp = fopen("inpout.txt","r");
	fscanf(fp,"%d\n",&cur);
	fscanf(fp,"%d %d\n",&cnt1,&cnt2);
	for(i=0;i<cur;i++){
			fscanf("%d %d\n",&buf[i][0],&buf[i][1]);
	}
}
void process()
{
	int i,j;
	int rx,lx,ux,dx;
	int l1, l2;

	for(i=0;i<cur;i++){
		if(rx < buf[i][0])rx = buf[i][0];
		if(lx > buf[i][0])lx = buf[i][0];
		if(ux < buf[i][1])ux = buf[i][1];			
		if(dx > buf[i][1])dx = buf[i][1];
	}
	l1 = lx-rx;
	l2 = ux-dx;



}
void main(void)
{
	input();
	process();
}

